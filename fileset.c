/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 *
 * Portions Copyright 2008 Denis Cheng
 */

#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>
#include <libgen.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <fts.h>
#include <sys/stat.h>

#include "filebench.h"
#include "fileset.h"
#include "gamma_dist.h"
#include "utils.h"
#include "fsplug.h"

/*
 * File sets (fileset_t) are entities containing information about collections
 * of files and subdirectories used by the Filebench workloads. Once populated,
 * the fileset consists of a tree of fileset entries (filesetentry_t) that
 * represent files, inner, and leaf directories. The fileset is rooted in a
 * directory specified by fileset_path (or fileset_path and fileset_path_str
 * if path=$variable/string).
 *
 * Filesets are allocated by fileset_alloc() via parser_fileset_define(), the
 * function invoked by the parser. Once "create filesets" or "run" is invoked,
 * fileset_createsets() creates all filesets. Fileset creation is a two-phase
 * process. First, the filesetentry tree described above is built (populated)
 * in memory by fileset_populate(). Then, fileset_create() instantiates the
 * fileset on the storage medium by pre-allocating designated files and dirs.
 *
 * Note that files are implemented as filesets that comprise a single file.
 */

/* Prefix for files created by filebench. Helps telling apart what's imported
 * from what's generated
 * TODO: Make a parameter of define/import commands */
#define	FB_PREFIX "fb"

/* maximum parallel allocation control */
#define	MAX_PARALLOC_THREADS 32

/* Used by during import to keep track of parent/child relations between
 * files/dirs, as well as their depth */
struct fse_stack {
	filesetentry_t *fse;
	int level;
	struct fse_stack *fse_next;
};

/*
 * returns pointer to file or fileset string, as appropriate
 */
static char *
fileset_entity_name(fileset_t *fileset)
{
	if (fileset->fs_attrs & FILESET_IS_FILE)
		return ("file");
	else
		return ("fileset");
}

/*
 * Removes the last file or directory name from a pathname. Basically removes
 * characters from the end of the path by setting them to \0 until a forward
 * slash '/' is encountered. It also removes the forward slash.
 */
static char *
trunc_dirname(char *dir)
{
	char *s = dir + strlen(dir);

	while (s != dir) {
		int c = *s;

		*s = 0;
		if (c == '/')
			break;
		s--;
	}
	return (dir);
}

/*
 * Prints a list of allowed options and how to specify them.
 */
void
fileset_usage(void)
{
	(void) fprintf(stderr,
	    "define [file | fileset]  name=<str>, path=[<var>/]<str>,"
	    ",entries=<number>\n");
	(void) fprintf(stderr,
	    "		        [,filesize=[size]]\n");
	(void) fprintf(stderr,
	    "		        [,dirwidth=[width]]\n");
	(void) fprintf(stderr,
	    "		        [,dirdepthrv=$random_variable_name]\n");
	(void) fprintf(stderr,
	    "		        [,dirgamma=[100-10000]] "
	    "(Gamma * 1000)\n");
	(void) fprintf(stderr,
	    "		        [,prealloc=[percent]]\n");
	(void) fprintf(stderr, "		        [,paralloc]\n");
	(void) fprintf(stderr, "		        [,reuse]\n");
	(void) fprintf(stderr, "\n");
	(void) fprintf(stderr,
	    "import [file | fileset] name=<str>, path=[<var>/]<str>\n");
	(void) fprintf(stderr,
	    "                  ,<entries=<number> | prealloc=<percent>>\n");
	(void) fprintf(stderr,
	    "		        [,filesize=[size]]\n");
	(void) fprintf(stderr, "		        [,paralloc]\n");
	(void) fprintf(stderr, "		        [,reuse]\n");
	(void) fprintf(stderr, "\n");
}

/*
 * Creates a path string from the filesetentry_t "*entry" and all of its
 * parent's path names. The resulting path is a concatination of all the
 * individual parent paths. Allocates memory for the path string and
 * returns a pointer to it.
 */
char *
fileset_resolvepath(filesetentry_t *entry)
{
	filesetentry_t *fsep = entry;
	char path[MAXPATHLEN];
	char pathtmp[MAXPATHLEN];
	char *s;

	path[0] = '\0';
	while (fsep->fse_parent) {
		(void) strcpy(pathtmp, "/");
		(void) fb_strlcat(pathtmp, fsep->fse_path, MAXPATHLEN);
		(void) fb_strlcat(pathtmp, path, MAXPATHLEN);
		(void) fb_strlcpy(path, pathtmp, MAXPATHLEN);
		fsep = fsep->fse_parent;
	}

	s = malloc(strlen(path) + 1);
	(void) fb_strlcpy(s, path, MAXPATHLEN);
	return (s);
}

/*
 * Creates multiple nested directories as required by the supplied path.
 * Starts at the end of the path, creating a list of directories to mkdir, up
 * to the root of the path, then mkdirs them one at a time from the root down.
 */
static int
fileset_mkdir(char *path, int mode)
{
	char *p;
	char *dirs[65536];
	int i = 0;

	if ((p = strdup(path)) == NULL)
		goto null_str;

	/*
	 * Fill an array of subdirectory path names until either we
	 * reach the root or encounter an already existing subdirectory
	 */
	/* CONSTCOND */
	while (1) {
		struct stat64 sb;

		if (stat64(p, &sb) == 0)
			break;
		if (strlen(p) < 3)
			break;
		if ((dirs[i] = strdup(p)) == NULL) {
			free(p);
			goto null_str;
		}

		(void) trunc_dirname(p);
		i++;
	}

	/* Make the directories, from closest to root downwards. */
	for (--i; i >= 0; i--) {
		(void) FB_MKDIR(dirs[i], mode);
		free(dirs[i]);
	}

	free(p);
	return (FILEBENCH_OK);

null_str:
	/* clean up */
	for (--i; i >= 0; i--)
		free(dirs[i]);

	filebench_log(LOG_ERROR,
	    "Failed to create directory path %s: Out of memory", path);
	return (FILEBENCH_ERROR);
}

/*
 * creates the subdirectory tree for a fileset.
 */
static int
fileset_create_subdirs(fileset_t *fileset, char *filesetpath)
{
	filesetentry_t *direntry;
	char full_path[MAXPATHLEN];
	char *part_path;

	/* walk the subdirectory list, instanciating subdirs */
	direntry = fileset->fs_dirlist;
	while (direntry) {
		(void) fb_strlcpy(full_path, filesetpath, MAXPATHLEN);
		part_path = fileset_resolvepath(direntry);
		(void) fb_strlcat(full_path, part_path, MAXPATHLEN);
		free(part_path);

		/* now create this portion of the subdirectory tree */
		if (fileset_mkdir(full_path, 0755) == FILEBENCH_ERROR)
			return (FILEBENCH_ERROR);

		direntry = direntry->fse_nextoftype;
	}
	return (FILEBENCH_OK);
}

/*
 * move filesetentry between exist tree and non-exist tree, source_tree
 * to destination tree.
 */
static void
fileset_move_entry(avl_tree_t *src_tree, avl_tree_t *dst_tree,
    filesetentry_t *entry)
{
	avl_remove(src_tree, entry);
	avl_add(dst_tree, entry);
}

/*
 * Gets the fileset path. If the path is defined as the concatenation of a
 * variable and a string, this function does the extra work. The destination
 * string must be preallocated with length len.
 */
void
fileset_getpath(fileset_t *fileset, char *dest, int len)
{
	(void) fb_strlcpy(dest, avd_get_str(fileset->fs_path), len);
	if (avd_get_str(fileset->fs_pathstr) != NULL)
		(void) fb_strlcat(dest, avd_get_str(fileset->fs_pathstr), len);
}

/*
 * given a fileset entry, determines if the associated leaf directory
 * needs to be made or not, and if so does the mkdir.
 */
static int
fileset_alloc_leafdir(filesetentry_t *entry)
{
	fileset_t *fileset;
	char path[MAXPATHLEN];
	struct stat64 sb;
	char *pathtmp;

	fileset = entry->fse_fileset;
	fileset_getpath(fileset, path, MAXPATHLEN);
	pathtmp = fileset_resolvepath(entry);
	(void) fb_strlcat(path, pathtmp, MAXPATHLEN);
	free(pathtmp);

	filebench_log(LOG_DEBUG_IMPL, "Populated %s", entry->fse_path);

	/* see if not reusing and this directory does not exist */
	if (!((entry->fse_flags & FSE_REUSING) && (stat64(path, &sb) == 0))) {

		/* No file or not reusing, so create */
		if (FB_MKDIR(path, 0755) < 0) {
			filebench_log(LOG_ERROR,
			    "Failed to pre-allocate leaf directory %s: %s",
			    path, strerror(errno));
			fileset_unbusy(entry, TRUE, FALSE, 0);
			return (FILEBENCH_ERROR);
		}
	}

	/* unbusy the allocated entry */
	fileset_unbusy(entry, TRUE, TRUE, 0);
	return (FILEBENCH_OK);
}

/*
 * given a fileset entry, determines if the associated file
 * needs to be allocated or not, and if so does the allocation.
 */
static int
fileset_alloc_file(filesetentry_t *entry)
{
	fileset_t *fileset;
	char path[MAXPATHLEN];
	char *buf;
	struct stat64 sb;
	char *pathtmp;
	off64_t seek;
	fb_fdesc_t fdesc;
	int trust_tree;

	fileset = entry->fse_fileset;
	fileset_getpath(fileset, path, MAXPATHLEN);
	pathtmp = fileset_resolvepath(entry);
	(void) fb_strlcat(path, pathtmp, MAXPATHLEN);
	free(pathtmp);

	filebench_log(LOG_DEBUG_IMPL, "Populated %s", entry->fse_path);

	/* see if reusing and this file exists */
	trust_tree = avd_get_bool(fileset->fs_trust_tree);
	if ((entry->fse_flags & FSE_REUSING) && (trust_tree ||
	    (FB_STAT(path, &sb) == 0))) {
		if (FB_OPEN(&fdesc, path, O_RDWR, 0) == FILEBENCH_ERROR) {
			filebench_log(LOG_INFO,
			    "Attempted but failed to Re-use file %s",
			    path);
			fileset_unbusy(entry, TRUE, FALSE, 0);
			return (FILEBENCH_ERROR);
		}

		if (trust_tree || (sb.st_size == (off64_t)entry->fse_size)) {
			filebench_log(LOG_DEBUG_IMPL,
			    "Reusing file %s", path);

			if (!avd_get_bool(fileset->fs_cached))
				(void) FB_FREEMEM(&fdesc, entry->fse_size);

			(void) FB_CLOSE(&fdesc);

			/* unbusy the allocated entry */
			fileset_unbusy(entry, TRUE, TRUE, 0);
			return (FILEBENCH_OK);

		} else if (sb.st_size > (off64_t)entry->fse_size) {
			/* reuse, but too large */
			filebench_log(LOG_DEBUG_IMPL,
			    "Truncating & re-using file %s", path);

			(void) FB_FTRUNC(&fdesc, (off64_t)entry->fse_size);

			if (!avd_get_bool(fileset->fs_cached))
				(void) FB_FREEMEM(&fdesc, entry->fse_size);

			(void) FB_CLOSE(&fdesc);

			/* unbusy the allocated entry */
			fileset_unbusy(entry, TRUE, TRUE, 0);
			return (FILEBENCH_OK);
		}
	} else {

		/* No file or not reusing, so create */
		if (FB_OPEN(&fdesc, path, O_RDWR | O_CREAT, 0644) ==
		    FILEBENCH_ERROR) {
			filebench_log(LOG_ERROR,
			    "Failed to pre-allocate file %s: %s",
			    path, strerror(errno));

			/* unbusy the unallocated entry */
			fileset_unbusy(entry, TRUE, FALSE, 0);
			return (FILEBENCH_ERROR);
		}
	}

	if ((buf = (char *)malloc(FILE_ALLOC_BLOCK)) == NULL) {
		/* unbusy the unallocated entry */
		fileset_unbusy(entry, TRUE, FALSE, 0);
		return (FILEBENCH_ERROR);
	}

	for (seek = 0; seek < entry->fse_size; ) {
		off64_t wsize;
		int ret = 0;

		/* Write FILE_ALLOC_BLOCK's worth, except on last write */
		wsize = MIN(entry->fse_size - seek, FILE_ALLOC_BLOCK);

		ret = FB_WRITE(&fdesc, buf, wsize);
		if (ret != wsize) {
			filebench_log(LOG_ERROR,
			    "Failed to pre-allocate file %s: %s",
			    path, strerror(errno));
			(void) FB_CLOSE(&fdesc);
			free(buf);
			fileset_unbusy(entry, TRUE, FALSE, 0);
			return (FILEBENCH_ERROR);
		}
		seek += wsize;
	}

	if (!avd_get_bool(fileset->fs_cached))
		(void) FB_FREEMEM(&fdesc, entry->fse_size);

	(void) FB_CLOSE(&fdesc);

	free(buf);

	/* unbusy the allocated entry */
	fileset_unbusy(entry, TRUE, TRUE, 0);

	filebench_log(LOG_DEBUG_IMPL,
	    "Pre-allocated file %s size %llu",
	    path, (u_longlong_t)entry->fse_size);

	return (FILEBENCH_OK);
}

/*
 * Given a fileset entry, determines if the associated file needs to be
 * allocated or not, and if so does the allocation.
 * Sets shm_fsparalloc_count to -1 on error.
 */
static void *
fileset_alloc_thread(filesetentry_t *entry)
{
	if (fileset_alloc_file(entry) == FILEBENCH_ERROR) {
		(void) pthread_mutex_lock(&filebench_shm->shm_fsparalloc_lock);
		filebench_shm->shm_fsparalloc_count = -1;
	} else {
		(void) pthread_mutex_lock(&filebench_shm->shm_fsparalloc_lock);
		filebench_shm->shm_fsparalloc_count--;
	}

	(void) pthread_cond_signal(&filebench_shm->shm_fsparalloc_cv);
	(void) pthread_mutex_unlock(&filebench_shm->shm_fsparalloc_lock);

	pthread_exit(NULL);
	return (NULL);
}


/*
 * First creates the parent directories of the file using fileset_mkdir().
 * Then optionally sets the O_DSYNC flag and opens the file with open64().
 * It unlocks the fileset entry lock, sets the DIRECTIO_ON or DIRECTIO_OFF
 * flags as requested, and returns the file descriptor integer for the opened
 * file in the supplied filebench file descriptor.
 * Returns FILEBENCH_ERROR on error, and FILEBENCH_OK on success.
 */
int
fileset_openfile(fb_fdesc_t *fdesc, fileset_t *fileset,
    filesetentry_t *entry, int flag, int filemode, int attrs)
{
	char path[MAXPATHLEN];
	char dir[MAXPATHLEN];
	char *pathtmp;
	struct stat64 sb;
	int open_attrs = 0;

	fileset_getpath(fileset, path, MAXPATHLEN);
	pathtmp = fileset_resolvepath(entry);
	(void) fb_strlcat(path, pathtmp, MAXPATHLEN);
	(void) fb_strlcpy(dir, path, MAXPATHLEN);
	free(pathtmp);
	(void) trunc_dirname(dir);

	/* If we are going to create a file, create the parent dirs */
	if ((flag & O_CREAT) && (stat64(dir, &sb) != 0)) {
		if (fileset_mkdir(dir, 0755) == FILEBENCH_ERROR)
			return (FILEBENCH_ERROR);
	}

	if (attrs & FLOW_ATTR_DSYNC)
		open_attrs |= O_SYNC;

#ifdef HAVE_O_DIRECT
	if (attrs & FLOW_ATTR_DIRECTIO)
		open_attrs |= O_DIRECT;
#endif /* HAVE_O_DIRECT */

	if (FB_OPEN(fdesc, path, flag | open_attrs, filemode)
	    == FILEBENCH_ERROR) {
		filebench_log(LOG_ERROR,
		    "Failed to open file %d, %s, with status %x: %s",
		    entry->fse_index, path, entry->fse_flags, strerror(errno));

		fileset_unbusy(entry, FALSE, FALSE, 0);
		return (FILEBENCH_ERROR);
	}

#ifdef HAVE_DIRECTIO
	if (attrs & FLOW_ATTR_DIRECTIO)
		(void)directio(fdesc->fd_num, DIRECTIO_ON);
#endif /* HAVE_DIRECTIO */

#ifdef HAVE_NOCACHE_FCNTL
	if (attrs & FLOW_ATTR_DIRECTIO)
		(void)fcntl(fdesc->fd_num, F_NOCACHE, 1);
#endif /* HAVE_NOCACHE_FCNTL */

	/* Disable read ahead with the help of fadvise, if asked for */
	if (attrs & FLOW_ATTR_FADV_RANDOM) {
#ifdef HAVE_FADVISE
		if (posix_fadvise(fdesc->fd_num, 0, 0, POSIX_FADV_RANDOM) 
			!= FILEBENCH_OK) {
			filebench_log(LOG_ERROR,
				"Failed to disable read ahead for file %s, with status %s", 
			    	path, strerror(errno));
			fileset_unbusy(entry, FALSE, FALSE, 0);
			return (FILEBENCH_ERROR);
		}
		filebench_log(LOG_INFO, "** Read ahead disabled **");
#else
		filebench_log(LOG_INFO, "** Read ahead was NOT disabled: not supported on this platform! **");
#endif
	}


	if (flag & O_CREAT)
		fileset_unbusy(entry, TRUE, TRUE, 1);
	else
		fileset_unbusy(entry, FALSE, FALSE, 1);

	return (FILEBENCH_OK);
}

/*
 * removes all filesetentries from their respective btrees, and puts them
 * on the free list. The supplied argument indicates which free list to use.
 */
static void
fileset_pickreset(fileset_t *fileset, int entry_type)
{
	filesetentry_t	*entry;

	switch (entry_type & FILESET_PICKMASK) {
	case FILESET_PICKFILE:
		entry = (filesetentry_t *)avl_first(&fileset->fs_noex_files);

		/* make sure non-existing files are marked free */
		while (entry) {
			entry->fse_flags |= FSE_FREE;
			entry->fse_open_cnt = 0;
			fileset_move_entry(&fileset->fs_noex_files,
			    &fileset->fs_free_files, entry);
			entry = AVL_NEXT(&fileset->fs_noex_files, entry);
		}

		/* free up any existing files */
		entry = (filesetentry_t *)avl_first(&fileset->fs_exist_files);

		while (entry) {
			entry->fse_flags |= FSE_FREE;
			entry->fse_open_cnt = 0;
			fileset_move_entry(&fileset->fs_exist_files,
			    &fileset->fs_free_files, entry);

			entry =  AVL_NEXT(&fileset->fs_exist_files, entry);
		}

		break;

	case FILESET_PICKDIR:
		/* nothing to reset, as all (sub)dirs always exist */
		break;

	case FILESET_PICKLEAFDIR:
		entry = (filesetentry_t *)
		    avl_first(&fileset->fs_noex_leaf_dirs);

		/* make sure non-existing leaf dirs are marked free */
		while (entry) {
			entry->fse_flags |= FSE_FREE;
			entry->fse_open_cnt = 0;
			fileset_move_entry(&fileset->fs_noex_leaf_dirs,
			    &fileset->fs_free_leaf_dirs, entry);
			entry =  AVL_NEXT(&fileset->fs_noex_leaf_dirs, entry);
		}

		/* free up any existing leaf dirs */
		entry = (filesetentry_t *)
		    avl_first(&fileset->fs_exist_leaf_dirs);

		while (entry) {
			entry->fse_flags |= FSE_FREE;
			entry->fse_open_cnt = 0;
			fileset_move_entry(&fileset->fs_exist_leaf_dirs,
			    &fileset->fs_free_leaf_dirs, entry);

			entry =  AVL_NEXT(&fileset->fs_exist_leaf_dirs, entry);
		}

		break;
	}
}

/*
 * find a filesetentry from the fileset using the supplied index
 */
static filesetentry_t *
fileset_find_entry(avl_tree_t *atp, uint_t index)
{
	avl_index_t	found_loc;
	filesetentry_t	desired_fse, *found_fse;

	/* find the file with the desired index, if it is in the tree */
	desired_fse.fse_index = index;
	found_fse = avl_find(atp, (void *)(&desired_fse), &found_loc);
	if (found_fse != NULL)
		return (found_fse);

	/* if requested node not found, find next higher node */
	found_fse = avl_nearest(atp, found_loc, AVL_AFTER);
	if (found_fse != NULL)
		return (found_fse);

	/* might have hit the end, return lowest available index node */
	found_fse = avl_first(atp);
	return (found_fse);
}

/*
 * Selects a fileset entry from a fileset. If the FILESET_PICKLEAFDIR flag is
 * set it will pick a leaf directory entry, if the FILESET_PICKDIR flag is set
 * it will pick a non leaf directory entry, otherwise a file entry. The
 * FILESET_PICKUNIQUE flag will take an entry off of one of the free (unused)
 * lists (file or directory), otherwise the entry will be picked off of one of
 * the rotor lists (file or directory). The FILESET_PICKEXISTS will insure that
 * only extant (FSE_EXISTS) state files are selected, while FILESET_PICKNOEXIST
 * ensures that only non extant (not FSE_EXISTS) state files are selected. Note
 * that the selected fileset entry (file) is returned with its FSE_BUSY flag
 * (in fse_flags) set.
 */
filesetentry_t *
fileset_pick(fileset_t *fileset, int flags, int tid, int index)
{
	filesetentry_t *entry = NULL;
	filesetentry_t *start_point;
	avl_tree_t *atp = NULL;
	fbint_t max_entries = 0;

	(void) ipc_mutex_lock(&fileset->fs_pick_lock);

	/* see if we have to wait for available files or directories */
	switch (flags & FILESET_PICKMASK) {
	case FILESET_PICKFILE:
		if (fileset->fs_filelist == NULL)
			goto empty;

		while (fileset->fs_idle_files == 0) {
			(void) pthread_cond_wait(&fileset->fs_idle_files_cv,
			    &fileset->fs_pick_lock);
		}

		max_entries = fileset->fs_constentries;
		if (flags & FILESET_PICKUNIQUE) {
			atp = &fileset->fs_free_files;
		} else if (flags & FILESET_PICKNOEXIST) {
			atp = &fileset->fs_noex_files;
		} else {
			atp = &fileset->fs_exist_files;
		}
		break;

	case FILESET_PICKDIR:
		if (fileset->fs_dirlist == NULL)
			goto empty;

		while (fileset->fs_idle_dirs == 0) {
			(void) pthread_cond_wait(&fileset->fs_idle_dirs_cv,
			    &fileset->fs_pick_lock);
		}

		max_entries = 1;
		atp = &fileset->fs_dirs;
		break;

	case FILESET_PICKLEAFDIR:
		if (fileset->fs_leafdirlist == NULL)
			goto empty;

		while (fileset->fs_idle_leafdirs == 0) {
			(void) pthread_cond_wait(&fileset->fs_idle_leafdirs_cv,
			    &fileset->fs_pick_lock);
		}

		max_entries = fileset->fs_constleafdirs;
		if (flags & FILESET_PICKUNIQUE) {
			atp = &fileset->fs_free_leaf_dirs;
		} else if (flags & FILESET_PICKNOEXIST) {
			atp = &fileset->fs_noex_leaf_dirs;
		} else {
			atp = &fileset->fs_exist_leaf_dirs;
		}
		break;
	}

	/* see if asking for impossible */
	if (avl_is_empty(atp))
		goto empty;

	if (flags & FILESET_PICKUNIQUE) {
		uint64_t  index64;

		/*
		 * pick at random from free list in order to distribute
		 * initially allocated files more randomly on storage media.
		 * Use uniform random number generator to select index
		 * if it is not supplied with pick call.
		 */
		if (index) {
			index64 = index;
		} else {
			fb_urandom64(&index64, max_entries, 0, NULL);
		}

		entry = fileset_find_entry(atp, (int)index64);

		if (entry == NULL)
			goto empty;

	} else if (flags & FILESET_PICKBYINDEX) {
		/* pick by supplied index */
		entry = fileset_find_entry(atp, index);

	} else {
		/* pick in rotation */
		switch (flags & FILESET_PICKMASK) {
		case FILESET_PICKFILE:
			if (flags & FILESET_PICKNOEXIST) {
				entry = fileset_find_entry(atp,
				    fileset->fs_file_nerotor);
				fileset->fs_file_nerotor =
				    entry->fse_index + 1;
			} else {
				entry = fileset_find_entry(atp,
				    fileset->fs_file_exrotor[tid]);
				fileset->fs_file_exrotor[tid] =
				    entry->fse_index + 1;
			}
			break;

		case FILESET_PICKDIR:
			entry = fileset_find_entry(atp, fileset->fs_dirrotor);
			fileset->fs_dirrotor = entry->fse_index + 1;
			break;

		case FILESET_PICKLEAFDIR:
			if (flags & FILESET_PICKNOEXIST) {
				entry = fileset_find_entry(atp,
				    fileset->fs_leafdir_nerotor);
				fileset->fs_leafdir_nerotor =
				    entry->fse_index + 1;
			} else {
				entry = fileset_find_entry(atp,
				    fileset->fs_leafdir_exrotor);
				fileset->fs_leafdir_exrotor =
				    entry->fse_index + 1;
			}
			break;
		}
	}

	if (entry == NULL)
		goto empty;

	/* see if entry in use */
	start_point = entry;
	while (entry->fse_flags & FSE_BUSY) {

		/* it is, so try next */
		entry = AVL_NEXT(atp, entry);
		if (entry == NULL)
			entry = avl_first(atp);

		/* see if we have wrapped around */
		if ((entry == NULL) || (entry == start_point)) {
			filebench_log(LOG_DEBUG_SCRIPT,
			    "All %d files are busy", avl_numnodes(atp));
			goto empty;
		}

	}

	/* update file or directory idle counts */
	switch (flags & FILESET_PICKMASK) {
	case FILESET_PICKFILE:
		fileset->fs_idle_files--;
		break;
	case FILESET_PICKDIR:
		fileset->fs_idle_dirs--;
		break;
	case FILESET_PICKLEAFDIR:
		fileset->fs_idle_leafdirs--;
		break;
	}

	/* Indicate that file or directory is now busy */
	entry->fse_flags |= FSE_BUSY;

	(void) ipc_mutex_unlock(&fileset->fs_pick_lock);
	filebench_log(LOG_DEBUG_SCRIPT, "Picked file %s", entry->fse_path);
	return (entry);

empty:
	filebench_log(LOG_DEBUG_SCRIPT, "No file found");
	(void) ipc_mutex_unlock(&fileset->fs_pick_lock);
	return (NULL);
}

/*
 * Removes a filesetentry from the "FSE_BUSY" state, signaling any threads
 * that are waiting for a NOT BUSY filesetentry. Also sets whether it is
 * existant or not, or leaves that designation alone.
 */
void
fileset_unbusy(filesetentry_t *entry, int update_exist,
    int new_exist_val, int open_cnt_incr)
{
	fileset_t *fileset = NULL;

	if (entry)
		fileset = entry->fse_fileset;

	if (fileset == NULL) {
		filebench_log(LOG_ERROR, "fileset_unbusy: NO FILESET!");
		return;
	}

	(void) ipc_mutex_lock(&fileset->fs_pick_lock);

	/* modify FSE_EXIST flag and actual dirs/files count, if requested */
	if (update_exist) {
		if (new_exist_val == TRUE) {
			if (entry->fse_flags & FSE_FREE) {

				/* asked to set and it was free */
				entry->fse_flags |= FSE_EXISTS;
				entry->fse_flags &= (~FSE_FREE);
				switch (entry->fse_flags & FSE_TYPE_MASK) {
				case FSE_TYPE_FILE:
					fileset_move_entry(
					    &fileset->fs_free_files,
					    &fileset->fs_exist_files, entry);
					break;

				case FSE_TYPE_DIR:
					break;

				case FSE_TYPE_LEAFDIR:
					fileset_move_entry(
					    &fileset->fs_free_leaf_dirs,
					    &fileset->fs_exist_leaf_dirs,
					    entry);
					break;
				}

			} else if (!(entry->fse_flags & FSE_EXISTS)) {

				/* asked to set, and it was clear */
				entry->fse_flags |= FSE_EXISTS;
				switch (entry->fse_flags & FSE_TYPE_MASK) {
				case FSE_TYPE_FILE:
					fileset_move_entry(
					    &fileset->fs_noex_files,
					    &fileset->fs_exist_files, entry);
					break;
				case FSE_TYPE_DIR:
					break;
				case FSE_TYPE_LEAFDIR:
					fileset_move_entry(
					    &fileset->fs_noex_leaf_dirs,
					    &fileset->fs_exist_leaf_dirs,
					    entry);
					break;
				}
			}
		} else {
			if (entry->fse_flags & FSE_FREE) {
				/* asked to clear, and it was free */
				entry->fse_flags &= (~(FSE_FREE | FSE_EXISTS));
				switch (entry->fse_flags & FSE_TYPE_MASK) {
				case FSE_TYPE_FILE:
					fileset_move_entry(
					    &fileset->fs_free_files,
					    &fileset->fs_noex_files, entry);
					break;

				case FSE_TYPE_DIR:
					break;

				case FSE_TYPE_LEAFDIR:
					fileset_move_entry(
					    &fileset->fs_free_leaf_dirs,
					    &fileset->fs_noex_leaf_dirs,
					    entry);
					break;
				}
			} else if (entry->fse_flags & FSE_EXISTS) {

				/* asked to clear, and it was set */
				entry->fse_flags &= (~FSE_EXISTS);
				switch (entry->fse_flags & FSE_TYPE_MASK) {
				case FSE_TYPE_FILE:
					fileset_move_entry(
					    &fileset->fs_exist_files,
					    &fileset->fs_noex_files, entry);
					break;
				case FSE_TYPE_DIR:
					break;
				case FSE_TYPE_LEAFDIR:
					fileset_move_entry(
					    &fileset->fs_exist_leaf_dirs,
					    &fileset->fs_noex_leaf_dirs,
					    entry);
					break;
				}
			}
		}
	}

	/* update open count */
	entry->fse_open_cnt += open_cnt_incr;

	/* increment idle count, clear FSE_BUSY and signal IF it was busy */
	if (entry->fse_flags & FSE_BUSY) {

		/* unbusy it */
		entry->fse_flags &= (~FSE_BUSY);

		/* release any threads waiting for unbusy */
		if (entry->fse_flags & FSE_THRD_WAITNG) {
			entry->fse_flags &= (~FSE_THRD_WAITNG);
			(void) pthread_cond_broadcast(
			    &fileset->fs_thrd_wait_cv);
		}

		/* increment idle count and signal waiting threads */
		switch (entry->fse_flags & FSE_TYPE_MASK) {
		case FSE_TYPE_FILE:
			fileset->fs_idle_files++;
			if (fileset->fs_idle_files == 1) {
				(void) pthread_cond_signal(
				    &fileset->fs_idle_files_cv);
			}
			break;

		case FSE_TYPE_DIR:
			fileset->fs_idle_dirs++;
			if (fileset->fs_idle_dirs == 1) {
				(void) pthread_cond_signal(
				    &fileset->fs_idle_dirs_cv);
			}
			break;

		case FSE_TYPE_LEAFDIR:
			fileset->fs_idle_leafdirs++;
			if (fileset->fs_idle_leafdirs == 1) {
				(void) pthread_cond_signal(
				    &fileset->fs_idle_leafdirs_cv);
			}
			break;
		}
	}

	(void) ipc_mutex_unlock(&fileset->fs_pick_lock);
}

/*
 * Given a fileset "fileset", create the associated files as specified in the
 * attributes of the fileset. The fileset is rooted in a directory whose
 * pathname is in fileset_path. If the directory exists, meaning that there is
 * already a fileset, and the fileset_reuse attribute is false, then remove it
 * and all its contained files and subdirectories. Next, the routine creates a
 * root directory for the fileset. All the file type filesetentries are cycled
 * through creating as needed their containing subdirectory trees in the file
 * system and creating actual files for fileset_preallocpercent of them. The
 * created files are filled with fse_size bytes of unitialized data.
 * The routine returns FILEBENCH_ERROR on errors, FILEBENCH_OK on success.
 */
static int
fileset_create(fileset_t *fileset)
{
	filesetentry_t *entry;
	char path[MAXPATHLEN];
	struct stat64 sb;
	hrtime_t start = gethrtime();
	char *fileset_path;
	char *fileset_name;
	int randno;
	int preallocated = 0;
	int reusing;

	if ((fileset_path = avd_get_str(fileset->fs_path)) == NULL) {
		filebench_log(LOG_ERROR, "%s path not set",
		    fileset_entity_name(fileset));
		return (FILEBENCH_ERROR);
	}

	if ((fileset_name = avd_get_str(fileset->fs_name)) == NULL) {
		filebench_log(LOG_ERROR, "%s name not set",
		    fileset_entity_name(fileset));
		return (FILEBENCH_ERROR);
	}

	/* treat raw device as special case */
	if (fileset->fs_attrs & FILESET_IS_RAW_DEV)
		return (FILEBENCH_OK);

	/* XXX Add check to see if there is enough space */

	/* set up path to fileset */
	fileset_getpath(fileset, path, MAXPATHLEN);

	/* if reusing and trusting to exist, just blindly reuse */
	if (avd_get_bool(fileset->fs_trust_tree)) {
		reusing = 1;

	/* if exists and resusing, then don't create new */
	} else if (((stat64(path, &sb) == 0) && (strlen(path) > 3) &&
	    (strlen(avd_get_str(fileset->fs_path)) > 2)) &&
	    avd_get_bool(fileset->fs_reuse)) {
		reusing = 1;
	} else {
		reusing = 0;
	}

	if (!fileset->fs_import && !reusing) {
		/* Remove existing */
		filebench_log(LOG_INFO,
		    "Removing %s tree (if exists)", fileset_name);

		FB_RECUR_RM(path);
	} else if (reusing) {
		/* we are re-using */
		filebench_log(LOG_INFO, "Reusing existing %s tree",
							fileset_name);
	} else if (fileset->fs_import) {
		/* we are importing */
		filebench_log(LOG_INFO, "Importing existing %s tree",
							fileset_name);
	}

	/* make the filesets directory tree unless in reuse mode */
	if (!reusing && (avd_get_bool(fileset->fs_prealloc)) &&
		!fileset->fs_import) {
		filebench_log(LOG_INFO,
			"Pre-allocating directories in %s tree", fileset_name);

		(void) FB_MKDIR(path, 0755);

		if (fileset_create_subdirs(fileset, path) == FILEBENCH_ERROR)
			return (FILEBENCH_ERROR);
	}

	start = gethrtime();

	filebench_log(LOG_INFO,
		"Pre-allocating files in %s tree", fileset_name);

	randno = ((RAND_MAX * (100
	    - avd_get_int(fileset->fs_preallocpercent))) / 100);

	/* alloc any files, as required */
	fileset_pickreset(fileset, FILESET_PICKFILE);
	while ((entry = fileset_pick(fileset,
	    FILESET_PICKFREE | FILESET_PICKFILE, 0, 0))) {
		pthread_t tid;

		if (fileset->fs_import) {
			/* XXX is this needed? */
			if (reusing)
				entry->fse_flags |= FSE_REUSING;
			else
				entry->fse_flags &= (~FSE_REUSING);

			if (entry->fse_flags & FSE_IMPORTED) {
				preallocated++;

				/* unbusy the unallocated entry,
				 * and mark as existing */
				fileset_unbusy(entry, TRUE, TRUE, 0);
			} else {
				fileset_unbusy(entry, TRUE, FALSE, 0);
			}

			continue;
		}

		/* Decide whether to instantiate this file */
		if (randno && rand() <= randno) {
			/* unbusy the unallocated entry */
			fileset_unbusy(entry, TRUE, FALSE, 0);
			continue;
		}

		preallocated++;

		if (reusing)
			entry->fse_flags |= FSE_REUSING;
		else
			entry->fse_flags &= (~FSE_REUSING);

		/* fire off allocation threads for each file if paralloc set */
		if (avd_get_bool(fileset->fs_paralloc)) {

			/* limit total number of simultaneous allocations */
			(void) pthread_mutex_lock(
			    &filebench_shm->shm_fsparalloc_lock);
			while (filebench_shm->shm_fsparalloc_count
			    >= MAX_PARALLOC_THREADS) {
				(void) pthread_cond_wait(
				    &filebench_shm->shm_fsparalloc_cv,
				    &filebench_shm->shm_fsparalloc_lock);
			}

			/* quit if any allocation thread reports an error */
			if (filebench_shm->shm_fsparalloc_count < 0) {
				(void) pthread_mutex_unlock(
				    &filebench_shm->shm_fsparalloc_lock);
				return (FILEBENCH_ERROR);
			}

			filebench_shm->shm_fsparalloc_count++;
			(void) pthread_mutex_unlock(
			    &filebench_shm->shm_fsparalloc_lock);

			/*
			 * Fire off a detached allocation thread per file.
			 * The thread will self destruct when it finishes
			 * writing pre-allocation data to the file.
			 */
			if (pthread_create(&tid, NULL,
			    (void *(*)(void*))fileset_alloc_thread,
			    entry) == 0) {
				/*
				 * A thread was created; detach it so it can
				 * fully quit when finished.
				 */
				(void) pthread_detach(tid);
			} else {
				filebench_log(LOG_ERROR,
				    "File prealloc thread create failed");
				filebench_shutdown(1);
			}

		} else {
			if (fileset_alloc_file(entry) == FILEBENCH_ERROR)
				return (FILEBENCH_ERROR);
		}
	}

	/* alloc any leaf directories, as required */
	fileset_pickreset(fileset, FILESET_PICKLEAFDIR);
	while ((entry = fileset_pick(fileset,
	    FILESET_PICKFREE | FILESET_PICKLEAFDIR, 0, 0))) {

		if (fileset->fs_import) {
			/* XXX is this needed? */
			if (reusing)
				entry->fse_flags |= FSE_REUSING;
			else
				entry->fse_flags &= (~FSE_REUSING);

			/* unbusy the unallocated entry, mark as existing */
			if (entry->fse_flags & FSE_IMPORTED)
				fileset_unbusy(entry, TRUE, TRUE, 0);
			else
				fileset_unbusy(entry, TRUE, FALSE, 0);

			continue;
		}

		/* Decide whether to instantiate this leaf dir */
		if (rand() < randno) {
			/* unbusy the unallocated entry */
			fileset_unbusy(entry, TRUE, FALSE, 0);
			continue;
		}

		if (reusing)
			entry->fse_flags |= FSE_REUSING;
		else
			entry->fse_flags &= (~FSE_REUSING);

		if (fileset_alloc_leafdir(entry) == FILEBENCH_ERROR)
			return (FILEBENCH_ERROR);
	}

	filebench_log(LOG_VERBOSE,
	    "Pre-allocated %d of %llu files in %s in %llu seconds",
	    preallocated,
	    (u_longlong_t)fileset->fs_constentries,
	    fileset_name,
	    (u_longlong_t)(((gethrtime() - start) / 1000000000) + 1));

	return (FILEBENCH_OK);
}

/*
 * Removes all files and directories associated with a fileset
 * from the storage subsystem.
 */
static void
fileset_delete_storage(fileset_t *fileset)
{
	char path[MAXPATHLEN];

	if (avd_get_str(fileset->fs_path) == NULL)
		return;

	fileset_getpath(fileset, path, MAXPATHLEN);

	/* treat raw device as special case */
	if (fileset->fs_attrs & FILESET_IS_RAW_DEV)
		return;

	/* now delete any files and directories on the disk */
	FB_RECUR_RM(path);
}

/*
 * Removes the fileset entity and all of its filesetentry entities.
 */
static void
fileset_delete_fileset(fileset_t *fileset)
{
	filesetentry_t *entry, *next_entry;

	/* run down the file list, removing and freeing each filesetentry */
	for (entry = fileset->fs_filelist; entry; entry = next_entry) {

		/* free the entry */
		next_entry = entry->fse_next;

		/* return it to the pool */
		switch (entry->fse_flags & FSE_TYPE_MASK) {
		case FSE_TYPE_FILE:
		case FSE_TYPE_LEAFDIR:
		case FSE_TYPE_DIR:
			ipc_free(FILEBENCH_FILESETENTRY, (void *)entry);
			break;
		default:
			filebench_log(LOG_ERROR,
			    "Unallocated filesetentry found on list");
			break;
		}
	}

	ipc_free(FILEBENCH_FILESET, (void *)fileset);
}

void
fileset_delete_all_filesets(void)
{
	fileset_t *fileset, *next_fileset;

	for (fileset = filebench_shm->shm_filesetlist;
	    fileset; fileset = next_fileset) {
		next_fileset = fileset->fs_next;
		fileset_delete_storage(fileset);
		fileset_delete_fileset(fileset);
	}

	filebench_shm->shm_filesetlist = NULL;
}

/*
 * Adds an entry to the fileset's file list. Single threaded,
 * so no locking needed.
 */
static void
fileset_insfilelist(fileset_t *fileset, filesetentry_t *entry)
{
	entry->fse_flags = FSE_TYPE_FILE | FSE_FREE;
	avl_add(&fileset->fs_free_files, entry);

	if (fileset->fs_filelist == NULL) {
		fileset->fs_filelist = entry;
		entry->fse_nextoftype = NULL;
	} else {
		entry->fse_nextoftype = fileset->fs_filelist;
		fileset->fs_filelist = entry;
	}
}

/*
 * Adds an entry to the fileset's directory list. Single threaded,
 * so no locking needed.
 */
static void
fileset_insdirlist(fileset_t *fileset, filesetentry_t *entry)
{
	entry->fse_flags = FSE_TYPE_DIR | FSE_EXISTS;
	avl_add(&fileset->fs_dirs, entry);

	if (fileset->fs_dirlist == NULL) {
		fileset->fs_dirlist = entry;
		entry->fse_nextoftype = NULL;
	} else {
		entry->fse_nextoftype = fileset->fs_dirlist;
		fileset->fs_dirlist = entry;
	}
}

/*
 * Adds an entry to the fileset's leaf directory list. Single threaded,
 * so no locking needed.
 */
static void
fileset_insleafdirlist(fileset_t *fileset, filesetentry_t *entry)
{
	entry->fse_flags = FSE_TYPE_LEAFDIR | FSE_FREE;
	avl_add(&fileset->fs_free_leaf_dirs, entry);

	if (fileset->fs_leafdirlist == NULL) {
		fileset->fs_leafdirlist = entry;
		entry->fse_nextoftype = NULL;
	} else {
		entry->fse_nextoftype = fileset->fs_leafdirlist;
		fileset->fs_leafdirlist = entry;
	}
}

/*
 * Compares two fileset entries to determine their relative order
 */
static int
fileset_entry_compare(const void *node_1, const void *node_2)
{
	if (((filesetentry_t *)node_1)->fse_index <
	    ((filesetentry_t *)node_2)->fse_index)
		return (-1);

	if (((filesetentry_t *)node_1)->fse_index ==
	    ((filesetentry_t *)node_2)->fse_index)
		return (0);

	return (1);
}

/*
 * Obtains a filesetentry entity for a file to be placed in a (sub)directory of
 * a fileset. The size of the file may be specified by fileset_meansize, or
 * calculated from a gamma distribution of parameter fileset_sizegamma and of
 * mean size fileset_meansize. The filesetentry entity is placed on the file
 * list in the specified parent filesetentry entity, which may be a directory
 * filesetentry, or the root filesetentry in the fileset. It is also placed on
 * the fileset's list of all contained files.
 * Returns FILEBENCH_OK if successful or FILEBENCH_ERROR if ipc memory for the
 * path string cannot be allocated.
 */
static int
fileset_populate_file(fileset_t *fileset, filesetentry_t *parent, off64_t size,
	void *name, int isimported, int depth)
{
	char tmp[MAXPATHLEN];
	filesetentry_t *entry;
	uint_t index;

	if ((entry = (filesetentry_t *)ipc_malloc(FILEBENCH_FILESETENTRY))
	    == NULL) {
		filebench_log(LOG_ERROR,
		    "fileset_populate_file: Can't malloc filesetentry");
		return FILEBENCH_ERROR;
	}

	/* Another currently idle file */
	(void) ipc_mutex_lock(&fileset->fs_pick_lock);
	index = fileset->fs_idle_files++;
	(void) ipc_mutex_unlock(&fileset->fs_pick_lock);

	entry->fse_depth = depth;
	entry->fse_index = index;
	entry->fse_parent = parent;
	entry->fse_fileset = fileset;
	fileset_insfilelist(fileset, entry);

	if (!isimported) {
		int *serial = (int *)name;

		(void) snprintf(tmp, sizeof(tmp), FB_PREFIX "%08d", *serial);
	} else {
		char *path = (char *)name;

		entry->fse_flags |= FSE_IMPORTED;

		filebench_log(LOG_VERBOSE, "import %s %s: importing file %s",
			fileset_entity_name(fileset),
			avd_get_str(fileset->fs_name), path);

		if (path[strlen(path)-1] == '/')
			path[strlen(path)-1] = '\0';
		(void) strncpy(tmp, strrchr(path, '/')+1, sizeof(tmp));
	}

	entry->fse_path = (char *)ipc_pathalloc(tmp);
	if (!(entry->fse_path)) {
		filebench_log(LOG_ERROR,
		    "fileset_populate_file: Can't alloc path string");
		return FILEBENCH_ERROR;
	}

	entry->fse_size = size;
	fileset->fs_bytes += entry->fse_size;

	fileset->fs_realfiles++;
	return FILEBENCH_OK;
}

/*
 * Obtains a filesetentry entity for a directory to be placed in a directory of
 * a fileset. If this is a leaf directory, it will always be empty so it can be
 * created and deleted (mkdir, rmdir) at will. The filesetentry is placed on
 * the leaf or inner directory list in the specified parent filesetentry, which
 * may be a (sub) directory filesetentry, or the root filesetentry in the
 * fileset. It is also placed on the fileset's list of all contained leaf or
 * inner directories. Returns FILEBENCH_OK if successful or FILEBENCH_ERROR if
 * ipc memory cannot be allocated.
 */
static int
fileset_populate_dir(fileset_t *fileset, filesetentry_t *parent, void *name,
	int isimported, int isleaf, int depth, filesetentry_t **retentry)
{
	char tmp[MAXPATHLEN];
	filesetentry_t *entry;
	uint_t index;

	/* Create dir node */
	if ((entry = (filesetentry_t *)ipc_malloc(FILEBENCH_FILESETENTRY))
	    == NULL) {
		filebench_log(LOG_ERROR,
		    "fileset_populate_dir: Can't malloc filesetentry");
		return FILEBENCH_ERROR;
	}

	/* Another currently idle directory */
	(void) ipc_mutex_lock(&fileset->fs_pick_lock);
	if (isleaf)
		index = fileset->fs_idle_leafdirs++;
	else
		index = fileset->fs_idle_dirs++;
	(void) ipc_mutex_unlock(&fileset->fs_pick_lock);

	entry->fse_depth = depth;
	entry->fse_index = index;
	entry->fse_parent = parent;
	entry->fse_fileset = fileset;
	if (isleaf)
		fileset_insleafdirlist(fileset, entry);
	else
		fileset_insdirlist(fileset, entry);

	if (!isimported) {
		int *serial = (int *)name;

		(void) snprintf(tmp, sizeof(tmp), FB_PREFIX "%08d", *serial);
	} else {
		char *path = (char *)name;

		entry->fse_flags |= FSE_IMPORTED;

		filebench_log(LOG_VERBOSE, "import %s %s: importing dir %s",
			fileset_entity_name(fileset),
			avd_get_str(fileset->fs_name), path);

		if (path[strlen(path)-1] == '/')
			path[strlen(path)-1] = '\0';
		(void) strncpy(tmp, strrchr(path, '/')+1, sizeof(tmp));
	}

	entry->fse_path = (char *)ipc_pathalloc(tmp);
	if (!(entry->fse_path)) {
		filebench_log(LOG_ERROR,
		    "fileset_populate_dir: Can't alloc path string");
		return FILEBENCH_ERROR;
	}

	if (isleaf)
		fileset->fs_realleafdirs++;
	else
		*retentry = entry;

	return FILEBENCH_OK;
}

/*
 * Creates a directory node in a fileset, by obtaining a filesetentry entity
 * for the node and initializing it according to parameters of the fileset. It
 * determines a directory tree depth and directory width, optionally using a
 * gamma distribution. If its calculated depth is less then its actual depth
 * in the directory tree, it becomes a leaf node and files itself with "width"
 * number of file type filesetentries, otherwise it files itself with "width"
 * number of directory type filesetentries, using recursive calls to
 * fileset_populate_define. The end result of the initial call to this routine
 * is a tree of directories of random width and varying depth with sufficient
 * leaf directories to contain all required files.
 * Returns FILEBENCH_OK on success. Returns FILEBENCH_ERROR if ipc path
 * string memory cannot be allocated and returns the error code (currently
 * also FILEBENCH_ERROR) from calls to fileset_populate_file or recursive
 * calls to fileset_populate_define.
 */
static int
fileset_populate_define(fileset_t *fileset, filesetentry_t *parent, int serial,
	int depth)
{
	double randepth, drand, ranwidth;
	int isleaf = 0;
	filesetentry_t *entry = NULL;
	int i;

	if (fileset_populate_dir(fileset, parent, (void *)&serial,
		0 /* not imported */, isleaf, depth, &entry))
		return FILEBENCH_ERROR;

	depth += 1;

	if (fileset->fs_dirdepthrv) {
		randepth = (int)avd_get_int(fileset->fs_dirdepthrv);
	} else {
		double gamma;

		gamma = avd_get_int(fileset->fs_dirgamma) / 1000.0;
		if (gamma > 0) {
			drand = gamma_dist_knuth(gamma,
			    fileset->fs_meandepth / gamma);
			randepth = (int)drand;
		} else {
			randepth = (int)fileset->fs_meandepth;
		}
	}

	if (fileset->fs_meanwidth == -1) {
		ranwidth = avd_get_dbl(fileset->fs_dirwidth);
	} else {
		double gamma;

		gamma = avd_get_int(fileset->fs_dirgamma) / 1000.0;
		if (gamma > 0) {
			drand = gamma_dist_knuth(gamma,
			    fileset->fs_meanwidth / gamma);
			ranwidth = drand;
		} else {
			ranwidth = fileset->fs_meanwidth;
		}
	}

	if (randepth == 0)
		randepth = 1;
	if (ranwidth == 0)
		ranwidth = 1;
	if (depth >= randepth)
		isleaf = 1;

	/*
	 * Create directory of random width filled with files according
	 * to distribution, or if root directory, continue until #files required
	 */
	for (i = 1; ((parent == NULL) || (i < ranwidth + 1)) &&
	    (fileset->fs_realfiles < fileset->fs_constentries);
	    i++) {
		int ret = 0;

		if (parent && isleaf)
			ret = fileset_populate_file(fileset, entry,
				(off64_t)avd_get_int(fileset->fs_size),
				(void *)&i, 0 /* not imported */, depth);
		else
			ret = fileset_populate_define(fileset, entry, i, depth);

		if (ret != 0)
			return ret;
	}

	/*
	 * Create directory of random width filled with leaf directories
	 * according to distribution, or if root directory, continue until
	 * the number of leaf directories required has been generated.
	 */
	for (i = 1; ((parent == NULL) || (i < ranwidth + 1)) &&
	    (fileset->fs_realleafdirs < fileset->fs_constleafdirs);
	    i++) {
		int ret = 0;

		if (parent && isleaf)
			ret = fileset_populate_dir(fileset, entry, (void *)&i,
				0 /* not imported */, isleaf, depth, NULL);
		else
			ret = fileset_populate_define(fileset, entry, i, depth);

		if (ret != 0)
			return ret;
	}

	return FILEBENCH_OK;
}

/*
 * If we are importing a file, all we do is populate one filesetentry. If the
 * file doesn't exist, we return an error and give up.
 *
 * If we are importing a fileset, the function traverses the given namespace,
 * and populates fileset data structures with file/dir information along the
 * way. Combines the functionality of the fileset_populate_* functions. To
 * track down parent-child relationships and tree level (0 for root), we keep
 * a stack of path components seen so far. During the traversal, we do not
 * follow symbolic links.
 *
 * TODO: Simplify import process. Instead of using the FSE_IMPORTED flag, just
 * put files/dirs in the right lists right away.
 */
static int
fileset_import_files(fileset_t *fileset)
{
	struct fse_stack *stack, *tmp;
	FTS *ftsp;
	FTSENT *ftsep;
	int fts_options = FTS_NOCHDIR | FTS_PHYSICAL;
	filesetentry_t *entry = NULL;
	char path[MAXPATHLEN];
	char *args[] = { path, NULL };
	struct stat64 sb;
	int isleafdir;

	fileset_getpath(fileset, path, MAXPATHLEN);

	/* If it's a file, just populate it and return */
	if (fileset->fs_attrs & FILESET_IS_FILE) {
		if (stat64(path, &sb) != 0) {
			filebench_log(LOG_ERROR,
				"import file %s: stat failed", path);
			return FILEBENCH_ERROR;
		}

		return fileset_populate_file(fileset, NULL, sb.st_size,
			(void *)path, 1 /* imported */, 0);
	}

	/* Allocate dummy node containing fileset root dir */
	stack = (struct fse_stack *)malloc(sizeof(struct fse_stack));
	if (!stack) {
		filebench_log(LOG_ERROR,
			"import fileset %s: stack alloc failed", path);
		goto error;
	}

	/* Populate the parent directory */
	if (fileset_populate_dir(fileset, NULL, (void *)path, 1 /* imported */,
		0 /* inner dir */, 0, &entry))
		goto error;

	/* Now that we're all set, push parent dir in the stack */
	stack->fse = entry;
	stack->fse_next = NULL;
	stack->level = 0;

	/* Open hierarchy for traversal */
	filebench_log(LOG_DEBUG_IMPL, "import fileset %s: traversing namespace",
		avd_get_str(fileset->fs_name));
	ftsp = fts_open(args, fts_options, NULL);
	if (!ftsp) {
		filebench_log(LOG_ERROR,
			"import fileset %s: fts_open failed on %s",
			avd_get_str(fileset->fs_name), path);
		goto error;
	}

	/* Traverse hierarchy */
	while ((ftsep = fts_read(ftsp)) != NULL) {
		switch (ftsep->fts_info) {
		case FTS_D: /* It's a directory */
			/* We should skip the root directory */
			if (!strcmp(ftsep->fts_path, path))
				break;

			/* Pop any visited, deeper branches */
			while (stack->level >= ftsep->fts_level) {
				tmp = stack;
				stack = stack->fse_next;
				free(tmp);
			}

			/* Check if it's empty */
			isleafdir = (fts_children(ftsp, 0) == NULL) ? 1 : 0;

			if (fileset_populate_dir(fileset, stack->fse,
				(void *)ftsep->fts_path, 1 /* imported */,
				isleafdir, ftsep->fts_level-1, &entry))
				goto error;

			if (!isleafdir) {
				/* Push it in the stack */
				tmp = stack;
				stack = (struct fse_stack *) malloc
					(sizeof(struct fse_stack));
				stack->fse = entry;
				stack->fse_next = tmp;
				stack->level = ftsep->fts_level;
			}

			break;
		case FTS_F: /* It's a file */
			if (fileset_populate_file(fileset, stack->fse,
				(off64_t) ftsep->fts_statp->st_size,
				(void *)ftsep->fts_path, 1 /* imported */,
				ftsep->fts_level-1))
				goto error;

			/* Pop any visited, deeper branches */
			while (stack->level >= ftsep->fts_level) {
				tmp = stack;
				stack = stack->fse_next;
				free(tmp);
			}
		default: /* Fall through */
			break;
		}
	}

	fts_close(ftsp);
	return 0;

error:
	while (stack != NULL) {
		tmp = stack;
		stack = stack->fse_next;
		free(tmp);
	}

	return FILEBENCH_ERROR;
}

/*
 * Traverses the fileset tree, and creates files in existing directories. The
 * location of the files is decided in a manner that allows a uniform
 * distribution across directories. We generate F/D files per directory, where
 * F is the total number of files we need to create, and D is the number of
 * existent directories. The file size is determined based on the fs_size
 * variable.
 * Returns FILEBENCH_OK on success. Returns FILEBENCH_ERROR on error.
 */
static int
fileset_populate_import(fileset_t *fileset)
{
	filesetentry_t *cur;
	fbint_t fperd;
	char path[MAXPATHLEN], tmp[MAXPATHLEN];
	char *eos, *fpath;

	/* Find number of files that we need to add per directory.
	 * If there are no directories (only root), then put all files there */
	if (fileset->fs_idle_dirs) {
		fperd = (fileset->fs_constentries - fileset->fs_idle_files) /
			fileset->fs_idle_dirs;
		if (fperd * fileset->fs_idle_dirs < fileset->fs_constentries)
			fperd++;
	} else {
		fperd = fileset->fs_constentries;
	}

	fileset_getpath(fileset, path, MAXPATHLEN);

	/* Iterate over list of inner dirs */
	eos = &path[strlen(path)];
	cur = fileset->fs_dirlist;
	while (cur != NULL) {
		int i, idx = 0;
		struct stat64 sb;

		/* Add fperd files, but stop if we reach max files */
		for (i = 0; i < fperd; i++) {
			do {
				idx++;
				*eos = '\0';
				fpath = fileset_resolvepath(cur);
				(void) snprintf(tmp, sizeof(tmp), "%s%s/"
					FB_PREFIX "%08d", path, fpath, idx);
				free(fpath);
			} while (stat64(tmp, &sb) == 0);

			filebench_log(LOG_DEBUG_IMPL,
				"fileset_populate_import: populating %s", tmp);

			if (fileset_populate_file(fileset, cur,
				(off64_t)avd_get_int(fileset->fs_size),
				(void *)&idx, 0 /* not imported */,
				cur->fse_depth + 1))
				return FILEBENCH_ERROR;

			if (fileset->fs_idle_files == fileset->fs_constentries)
				return FILEBENCH_OK;
		}

		cur = cur->fse_nextoftype;
	}

	return FILEBENCH_OK;
}

/*
 * Populates a fileset with files and subdirectory entries.
 *
 * If the fileset is not imported, it uses the supplied fileset_dirwidth and
 * fileset_entries (number of files) to calculate the required fileset_meandepth
 * (of subdirectories) and initialize the fileset_meanwidth and fileset_meansize
 * variables. Then calls fileset_populate_subdir() to do the recursive
 * subdirectory entry creation and leaf file entry creation.
 *
 * If the fileset is imported, it traverses the given path's subdirectories and
 * generates the proper in-memory representation. The total number of files in
 * the fileset is determined by either assuming that the imported files corres-
 * pond to the percentage of preallocated files requested, or alternatively,
 * we use the number of entries. The supplied fileset size variable is used for
 * new files. Then calls fileset_populate_subdir() to do the recursive subdir
 * entry creation and leaf file entry creation for any additional files
 * required.
 *
 * All of the above is skipped if the fileset has already been populated.
 * Returns 0 on success, or an error code from the call to
 * fileset_populate_subdir if that call fails.
 */
static int
fileset_populate(fileset_t *fileset)
{
	fbint_t entries = avd_get_int(fileset->fs_entries);
	fbint_t leafdirs = avd_get_int(fileset->fs_leafdirs);
	char path[MAXPATHLEN];
	int meandirwidth = 0;

	/* Skip if already populated */
	if (fileset->fs_bytes > 0)
		goto exists;

	/* check for raw device */
	if (fileset->fs_attrs & FILESET_IS_RAW_DEV)
		return (FILEBENCH_OK);

	/*
	 * save value of entries and leaf dirs obtained for later
	 * in case it was random
	 */
	fileset->fs_constentries = entries;
	fileset->fs_constleafdirs = leafdirs;

	/* initialize idle files and directories condition variables */
	(void) pthread_cond_init(&fileset->fs_idle_files_cv, ipc_condattr());
	(void) pthread_cond_init(&fileset->fs_idle_dirs_cv, ipc_condattr());
	(void) pthread_cond_init(&fileset->fs_idle_leafdirs_cv, ipc_condattr());

	/* no files or dirs idle (or busy) yet */
	fileset->fs_idle_files = 0;
	fileset->fs_idle_dirs = 0;
	fileset->fs_idle_leafdirs = 0;

	/* initialize locks and other condition variables */
	(void) pthread_mutex_init(&fileset->fs_pick_lock,
	    ipc_mutexattr(IPC_MUTEX_NORMAL));
	(void) pthread_mutex_init(&fileset->fs_histo_lock,
	    ipc_mutexattr(IPC_MUTEX_NORMAL));
	(void) pthread_cond_init(&fileset->fs_thrd_wait_cv, ipc_condattr());

	/* Initialize avl btrees */
	avl_create(&(fileset->fs_free_files), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_noex_files), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_exist_files), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_free_leaf_dirs), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_noex_leaf_dirs), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_exist_leaf_dirs), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));
	avl_create(&(fileset->fs_dirs), fileset_entry_compare,
	    sizeof (filesetentry_t), FSE_OFFSETOF(fse_link));

	fileset_getpath(fileset, path, MAXPATHLEN);

	if (fileset->fs_import) {
		filebench_log(LOG_INFO, "import %s %s: importing %s",
			fileset_entity_name(fileset),
			avd_get_str(fileset->fs_name), path);

		if (fileset_import_files(fileset))
			return FILEBENCH_ERROR;

		/* If prealloc is set, it takes precedence over # of entries */
		if (avd_get_int(fileset->fs_preallocpercent)) {
			fileset->fs_constentries =
				(fileset->fs_idle_files * 100) /
				avd_get_int(fileset->fs_preallocpercent);
			entries = fileset->fs_constentries;
		}

		filebench_log(LOG_VERBOSE,
			"import %s %s: prealloc = %d, entries = %d",
			fileset_entity_name(fileset),
			avd_get_str(fileset->fs_name),
			avd_get_int(fileset->fs_preallocpercent),
			fileset->fs_constentries);

		if (fileset->fs_idle_files > fileset->fs_constentries) {
			filebench_log(LOG_ERROR,
				"import %s %s: imported too many files",
				fileset_entity_name(fileset), path);
			return FILEBENCH_ERROR;
		}

		/* Populate any additional artificial entries as required */
		if (fileset_populate_import(fileset))
			return FILEBENCH_ERROR;
	} else {
		/* is dirwidth a random variable? */
		if (AVD_IS_RANDOM(fileset->fs_dirwidth)) {
			meandirwidth =
				(int)fileset->fs_dirwidth->avd_val.randptr->rnd_dbl_mean;
			fileset->fs_meanwidth = -1;
		} else {
			meandirwidth = (int)avd_get_int(fileset->fs_dirwidth);
			fileset->fs_meanwidth = (double)meandirwidth;
		}

		/*
		 * Input params are:
		 *	# of files
		 *	ave # of files per dir
		 *	max size of dir
		 *	# ave size of file
		 *	max size of file
		 */
		fileset->fs_meandepth =
			log(entries+leafdirs) / log(meandirwidth);

		/* Has a random variable been supplied for dirdepth? */
		if (fileset->fs_dirdepthrv) {
			/* yes, so set its mean value to meandepth */
			fileset->fs_dirdepthrv->avd_val.randptr->rnd_dbl_mean =
			    fileset->fs_meandepth;
		}

		if (fileset_populate_define(fileset, NULL, 1, 0)) {
			filebench_log(LOG_ERROR,
				"define %s %s: failed to populate namespace",
				fileset_entity_name(fileset), path);
			return FILEBENCH_ERROR;
		}
	}

	if (fileset_populate_define(fileset, NULL, 1, 0))
		return FILEBENCH_ERROR;

exists:
	if (fileset->fs_attrs & FILESET_IS_FILE) {
		filebench_log(LOG_VERBOSE, "File %s(%s): %.3lfMB",
		    avd_get_str(fileset->fs_name), path,
		    (double)fileset->fs_bytes / 1024UL / 1024UL);
	} else {
		if (!fileset->fs_import)
			filebench_log(LOG_INFO, "%s populated at %s: "
				"%llu files, avg. dirwidth = %d, "
				"avg. dirdepth = %.1lf, %llu leafdirs, "
				"%.3lfMB total size",
				avd_get_str(fileset->fs_name), path, entries,
				meandirwidth, fileset->fs_meandepth, leafdirs,
				(double)fileset->fs_bytes / 1024UL / 1024UL);
		else
			filebench_log(LOG_INFO, "%s populated at %s: "
				"%llu files, %llu leafdirs, "
				"%.3lfMB total size",
				avd_get_str(fileset->fs_name), path, entries,
				leafdirs,
				(double)fileset->fs_bytes / 1024UL / 1024UL);
	}

	return FILEBENCH_OK;
}

/*
 * Allocates a fileset instance, initializes fileset_dirgamma and
 * fileset_sizegamma default values, and sets the fileset name to the supplied
 * name string. Puts the allocated fileset on the master fileset list and
 * returns a pointer to it.
 *
 * This routine implements the 'define fileset' and 'import fileset' calls
 * found in a .fb workload, such as in the following examples:
 *   define fileset name=drew4ever, path=$var/str, entries=$nfiles
 *   import fileset name=drew5ever, path=$var/str, entries=$nfiles
 */
fileset_t *
fileset_alloc(avd_t name)
{
	fileset_t *fileset;

	if (name == NULL)
		return (NULL);

	if ((fileset = (fileset_t *)ipc_malloc(FILEBENCH_FILESET)) == NULL) {
		filebench_log(LOG_ERROR,
		    "fileset_alloc: Can't malloc fileset");
		return (NULL);
	}

	filebench_log(LOG_DEBUG_IMPL,
	    "Allocating file %s", avd_get_str(name));

	(void) ipc_mutex_lock(&filebench_shm->shm_fileset_lock);

	fileset->fs_dirgamma = avd_int_alloc(1500);
	fileset->fs_histo_id = -1;

	/* Add fileset to global list */
	if (filebench_shm->shm_filesetlist == NULL) {
		filebench_shm->shm_filesetlist = fileset;
		fileset->fs_next = NULL;
	} else {
		fileset->fs_next = filebench_shm->shm_filesetlist;
		filebench_shm->shm_filesetlist = fileset;
	}

	(void) ipc_mutex_unlock(&filebench_shm->shm_fileset_lock);

	fileset->fs_name = name;

	return (fileset);
}

/*
 * checks to see if the path/name pair points to a raw device. If
 * so it sets the raw device flag (FILESET_IS_RAW_DEV) and returns 1.
 * If RAW is not defined, or it is not a raw device, it clears the
 * raw device flag and returns 0.
 */
int
fileset_checkraw(fileset_t *fileset)
{
	char path[MAXPATHLEN];
	struct stat64 sb;

	fileset->fs_attrs &= (~FILESET_IS_RAW_DEV);

	if (avd_get_str(fileset->fs_path) == NULL) {
		filebench_log(LOG_ERROR, "%s path not set",
		    fileset_entity_name(fileset));
		filebench_shutdown(1);
	}

	fileset_getpath(fileset, path, MAXPATHLEN);
	if ((stat64(path, &sb) == 0) &&
	    ((sb.st_mode & S_IFMT) == S_IFBLK)) {
		fileset->fs_attrs |= FILESET_IS_RAW_DEV;
		if (!(fileset->fs_attrs & FILESET_IS_FILE)) {
			filebench_log(LOG_ERROR,
			    "WARNING Fileset %s(%s) Cannot be RAW device",
			    avd_get_str(fileset->fs_name), path);
			filebench_shutdown(1);
		}
		return 1;
	}

	return 0;
}

/*
 * Calls fileset_populate() and fileset_create() for all filesets on the
 * fileset list. Returns an error when a call to fileset_populate() or
 * fileset_create() fails.
 */
int
fileset_createsets()
{
	char path[MAXPATHLEN];
	fileset_t *list;
	int ret = 0;

	/* Set up for possible parallel pre-allocation */
	filebench_shm->shm_fsparalloc_count = 0;
	(void) pthread_cond_init(&filebench_shm->shm_fsparalloc_cv,
							ipc_condattr());

	filebench_log(LOG_INFO, "Populating and pre-allocating filesets");

	list = filebench_shm->shm_filesetlist;
	while (list) {
		/* Verify fileset parameters are valid */
		if ((avd_get_int(list->fs_entries) == 0) &&
			    (avd_get_int(list->fs_leafdirs) == 0)) {
				filebench_log(LOG_ERROR, "Fileset has no files or leafdirs");
		}

		if (list->fs_dirdepthrv && !AVD_IS_RANDOM(list->fs_dirdepthrv)) {
			filebench_log(LOG_ERROR,
			    "Define fileset: dirdepthrv must be random var");
			filebench_shutdown(1);
		}

		if (AVD_IS_RANDOM(list->fs_dirgamma)) {
			filebench_log(LOG_ERROR,
			    "Define fileset: dirgamma attr cannot be random");
			filebench_shutdown(1);
		}

		/* check for raw files */
		if (fileset_checkraw(list)) {
			fileset_getpath(list, path, MAXPATHLEN);
			filebench_log(LOG_INFO,
			    "File %s(%s) is a RAW device",
			    avd_get_str(list->fs_name), path);
			list = list->fs_next;
			continue;
		}

		ret = fileset_populate(list);
		if (ret) {
			fileset_getpath(list, path, MAXPATHLEN);
			filebench_log(LOG_ERROR, "Error populating fileset "
				"%s(%s)", avd_get_str(list->fs_name), path);
			return ret;
		}

		if (filebench_shm->shm_debug_level >= LOG_DEBUG_IMPL)
			fileset_print(list, 1);

		ret = fileset_create(list);
		if (ret) {
			fileset_getpath(list, path, MAXPATHLEN);
			filebench_log(LOG_ERROR, "Error creating fileset "
				"%s(%s)", avd_get_str(list->fs_name), path);
			return ret;
		}

		list = list->fs_next;
	}

	/* wait for allocation threads to finish */
	filebench_log(LOG_INFO, "Waiting for pre-allocation to finish "
			"(in case of a parallel pre-allocation)");

	(void) pthread_mutex_lock(&filebench_shm->shm_fsparalloc_lock);
	while (filebench_shm->shm_fsparalloc_count > 0)
		(void) pthread_cond_wait(
		    &filebench_shm->shm_fsparalloc_cv,
		    &filebench_shm->shm_fsparalloc_lock);
	(void) pthread_mutex_unlock(&filebench_shm->shm_fsparalloc_lock);

	filebench_log(LOG_INFO,
	    "Population and pre-allocation of filesets completed");

	if (filebench_shm->shm_fsparalloc_count < 0)
		return (FILEBENCH_ERROR);

	return 0;
}

/*
 * Searches through the master fileset list for the named fileset.
 * If found, returns pointer to same, otherwise returns NULL.
 */
fileset_t *
fileset_find(char *name)
{
	fileset_t *fileset = filebench_shm->shm_filesetlist;

	(void) ipc_mutex_lock(&filebench_shm->shm_fileset_lock);

	while (fileset) {
		if (strcmp(name, avd_get_str(fileset->fs_name)) == 0) {
			(void) ipc_mutex_unlock(
			    &filebench_shm->shm_fileset_lock);
			return (fileset);
		}
		fileset = fileset->fs_next;
	}
	(void) ipc_mutex_unlock(&filebench_shm->shm_fileset_lock);

	return (NULL);
}

/*
 * Iterates over all the file sets in the filesetlist, executing the supplied
 * command "*cmd()" on them. Also indicates to the executed command if it is
 * the first time the command has been executed since the current call to
 * fileset_iter.
 */
int
fileset_iter(int (*cmd)(fileset_t *fileset, int first))
{
	fileset_t *fileset = filebench_shm->shm_filesetlist;
	int count = 0;

	(void) ipc_mutex_lock(&filebench_shm->shm_fileset_lock);

	while (fileset) {
		if (cmd(fileset, count == 0) == FILEBENCH_ERROR) {
			(void) ipc_mutex_unlock(
			    &filebench_shm->shm_fileset_lock);
			return (FILEBENCH_ERROR);
		}
		fileset = fileset->fs_next;
		count++;
	}

	(void) ipc_mutex_unlock(&filebench_shm->shm_fileset_lock);
	return (FILEBENCH_OK);
}

/*
 * Prints information to the filebench log about the file
 * object. Also prints a header on the first call.
 */
int
fileset_print(fileset_t *fileset, int first)
{
	int pathlength;
	char path[MAXPATHLEN];
	char *fileset_name;
	static char pad[] = "                              "; /* 30 spaces */

	if (avd_get_str(fileset->fs_path) == NULL) {
		filebench_log(LOG_ERROR, "%s path not set",
		    fileset_entity_name(fileset));
		return (FILEBENCH_ERROR);
	}

	if ((fileset_name = avd_get_str(fileset->fs_name)) == NULL) {
		filebench_log(LOG_ERROR, "%s name not set",
		    fileset_entity_name(fileset));
		return (FILEBENCH_ERROR);
	}

	fileset_getpath(fileset, path, MAXPATHLEN);
	pathlength = strlen(path);

	if (pathlength > 29)
		pathlength = 29;

	if (first) {
		filebench_log(LOG_INFO, "File or Fileset name%20s%12s%10s",
		    "file size",
		    "dir width",
		    "entries");
	}

	if (fileset->fs_attrs & FILESET_IS_FILE) {
		if (fileset->fs_attrs & FILESET_IS_RAW_DEV) {
			filebench_log(LOG_INFO,
			    "%s(%s)%s         (Raw Device)",
			    fileset_name, path, &pad[pathlength]);
		} else {
			filebench_log(LOG_INFO,
			    "%s(%s)%s%9llu     (Single File)",
			    fileset_name, path, &pad[pathlength],
			    (u_longlong_t)avd_get_int(fileset->fs_size));
		}
	} else {
		filebench_log(LOG_INFO, "%s(%s)%s%9llu%12llu%10llu",
		    fileset_name, path, &pad[pathlength],
		    (u_longlong_t)avd_get_int(fileset->fs_size),
		    (u_longlong_t)avd_get_int(fileset->fs_dirwidth),
		    (u_longlong_t)fileset->fs_constentries);
	}

	if (filebench_shm->shm_debug_level >= LOG_DEBUG_IMPL) {
		filesetentry_t *cur;
		char *fpath;

		/* Print fileset path */
		filebench_log(LOG_INFO, "Printing contents of fileset %s.",
			avd_get_str(fileset->fs_name));

		/* Print dir list */
		filebench_log(LOG_INFO, "  Inner directories:");
		cur = fileset->fs_dirlist;
		while (cur != NULL) {
			fpath = fileset_resolvepath(cur);
			filebench_log(LOG_INFO, "  %s (d=%d)",
				fpath, cur->fse_depth);
			free(fpath);
			cur = cur->fse_nextoftype;
		}

		/* Print leaf dir list */
		filebench_log(LOG_INFO, "  Leaf directories:");
		cur = fileset->fs_leafdirlist;
		while (cur != NULL) {
			fpath = fileset_resolvepath(cur);
			filebench_log(LOG_INFO, "  %s (d=%d)",
				fpath, cur->fse_depth);
			free(fpath);
			cur = cur->fse_nextoftype;
		}

		/* Print file list */
		filebench_log(LOG_INFO, "  Files:");
		cur = fileset->fs_filelist;
		while (cur != NULL) {
			fpath = fileset_resolvepath(cur);
			filebench_log(LOG_INFO, "  %s (d=%d), %zdb",
				fpath, cur->fse_depth, cur->fse_size);
			free(fpath);
			cur = cur->fse_nextoftype;
		}
	}

	return (FILEBENCH_OK);
}

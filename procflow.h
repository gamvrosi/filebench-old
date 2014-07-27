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
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _FB_PROCFLOW_H
#define	_FB_PROCFLOW_H

#define	IDLE_DEBUG
//#define DO_WAITCHAN

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#include "filebench.h"

typedef struct procflow {
	char		pf_name[128];
	int		pf_instance;
	avd_t		pf_instances;
	int		pf_running;
	int		pf_sleep_threads; /* Indicates if threads should sleep or not */
    double pf_delay; /* store the delay time for barrier operations to start */
#ifdef DO_WAITCHAN
	pthread_cond_t	pf_cv;		/* Block/wakeup CV */
	pthread_mutex_t	pf_lock;	/* Mutex around each procflow */
#else
	pthread_barrier_t pf_bar_sync;	/* Barrier for threads to meet on  */
	pthread_barrier_t pf_bar_wait;	/* Barrier for threads to sleep on */
#endif
	void		*fo_private;	/* Flowop private scratch pad area */
	flag_t          pf_threads_defined_flag;
	struct procflow	*pf_next;
	pid_t		pf_pid;
	pthread_t	pf_tid;
	struct threadflow *pf_threads;
	int		pf_attrs;
    int pf_tf_instances; /* Number of threadflows for this proc */
	avd_t		pf_nice;
} procflow_t;

procflow_t *procflow_define(char *name, procflow_t *inherit, avd_t instances);
int	procflow_init(void);
void	procflow_shutdown(void);
int	procflow_exec(char *name, int instance);
void	procflow_usage(void);
int	procflow_allstarted(void);
void procflow_suspend(void);
void procflow_resume(void);
void procflow_wait_threads(int delay);
void procflow_barrier(int delay);

#endif	/* _FB_PROCFLOW_H */

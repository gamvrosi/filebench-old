
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 29 "parser_gram.y"


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <limits.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <locale.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#ifdef HAVE_STDINT_H
#include <stdint.h>
#endif
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#ifdef HAVE_LIBTECLA
#include <libtecla.h>
#endif
#include "parsertypes.h"
#include "filebench.h"
#include "utils.h"
#include "stats.h"
#include "vars.h"
#include "eventgen.h"
#ifdef HAVE_LIBTECLA
#include "auto_comp.h"
#endif
#include "multi_client_sync.h"

/* yacc and lex externals */
extern FILE *yyin;
extern int yydebug;
extern void yyerror(char *s);
extern int yylex(void);

/* GetLine resource object */
#ifdef HAVE_LIBTECLA
static GetLine *gl;
#endif

/* executable name to execute worker processes later */
char *execname;

static int dofile = DOFILE_FALSE;

static char *fbbasepath = FILEBENCHDIR;
static char cwd[MAXPATHLEN];
static pidlist_t *pidlist;
static int filecreate_done;

/* utilities */
static cmd_t *alloc_cmd(void);
static attr_t *alloc_attr(void);
static attr_t *alloc_lvar_attr(var_t *var);
static attr_t *get_attr(cmd_t *cmd, int64_t name);
static attr_t *get_attr_fileset(cmd_t *cmd, int64_t name);
static attr_t *get_attr_integer(cmd_t *cmd, int64_t name);
static attr_t *get_attr_bool(cmd_t *cmd, int64_t name);
static void get_attr_lvars(cmd_t *cmd, flowop_t *flowop);
static list_t *alloc_list();
static probtabent_t *alloc_probtabent(void);
static void add_lvar_to_list(var_t *newlvar, var_t **lvar_list);

/* Info Commands */
static void parser_list(cmd_t *);
static void parser_flowop_list(cmd_t *);
static void parser_list_cvar_types(void);
static void parser_list_cvar_type_parameters(char *);

/* Define Commands */
static void parser_proc_define(cmd_t *);
static void parser_thread_define(cmd_t *, procflow_t *, int instances);
static void parser_flowop_define(cmd_t *, threadflow_t *, flowop_t **, int);
static void parser_file_define(cmd_t *);
static void parser_fileset_define(cmd_t *);
static void parser_var_assign_random(char *, cmd_t *);
static void parser_composite_flowop_define(cmd_t *);
static void parser_var_assign_custom(char *, cmd_t *);

/* Import Commands */
static void parser_file_import(cmd_t *);
static void parser_fileset_import(cmd_t *);

/* Create Commands */
static void parser_proc_create(cmd_t *);
static void parser_fileset_create(cmd_t *);

/* Shutdown Commands */
static void parser_proc_shutdown(cmd_t *);
static void parser_filebench_shutdown(cmd_t *cmd);
static void parser_fileset_shutdown(cmd_t *cmd);

/* Other Commands */
static void parser_echo(cmd_t *cmd);
static void parser_fscheck(cmd_t *cmd);
static void parser_fsflush(cmd_t *cmd);
static void parser_log(cmd_t *cmd);
static void parser_statscmd(cmd_t *cmd);
static void parser_statsdump(cmd_t *cmd);
static void parser_statsxmldump(cmd_t *cmd);
static void parser_statsmultidump(cmd_t *cmd);
static void parser_system(cmd_t *cmd);
static void parser_statssnap(cmd_t *cmd);
static void parser_directory(cmd_t *cmd);
static void parser_eventgen(cmd_t *cmd);
static void parser_enable_mc(cmd_t *cmd);
static void parser_domultisync(cmd_t *cmd);
static void parser_run(cmd_t *cmd);
static void parser_run_variable(cmd_t *cmd);
static void parser_psrun(cmd_t *cmd);
static void parser_sleep(cmd_t *cmd);
static void parser_sleep_variable(cmd_t *cmd);
static void parser_warmup(cmd_t *cmd);
static void parser_warmup_variable(cmd_t *cmd);
static void arg_parse(const char *command);
static void parser_abort(int arg);
static void parser_version(cmd_t *cmd);
static void parser_osprof_enable(cmd_t *cmd);
static void parser_osprof_disable(cmd_t *cmd);



/* Line 189 of yacc.c  */
#line 200 "parser_gram.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FSC_LIST = 258,
     FSC_DEFINE = 259,
     FSC_QUIT = 260,
     FSC_DEBUG = 261,
     FSC_CREATE = 262,
     FSC_SLEEP = 263,
     FSC_STATS = 264,
     FSC_SET = 265,
     FSC_SHUTDOWN = 266,
     FSC_LOG = 267,
     FSC_SYSTEM = 268,
     FSC_FLOWOP = 269,
     FSC_EVENTGEN = 270,
     FSC_ECHO = 271,
     FSC_RUN = 272,
     FSC_PSRUN = 273,
     FSC_WARMUP = 274,
     FSC_NOUSESTATS = 275,
     FSC_FSCHECK = 276,
     FSC_FSFLUSH = 277,
     FSC_VERSION = 278,
     FSC_ENABLE = 279,
     FSC_DOMULTISYNC = 280,
     FSC_IMPORT = 281,
     FSV_STRING = 282,
     FSV_VAL_INT = 283,
     FSV_VAL_NEGINT = 284,
     FSV_VAL_BOOLEAN = 285,
     FSV_VARIABLE = 286,
     FSV_WHITESTRING = 287,
     FSV_RANDUNI = 288,
     FSV_RANDTAB = 289,
     FSV_URAND = 290,
     FSV_RAND48 = 291,
     FSE_FILE = 292,
     FSE_PROC = 293,
     FSE_THREAD = 294,
     FSE_CLEAR = 295,
     FSE_SNAP = 296,
     FSE_DUMP = 297,
     FSE_DIRECTORY = 298,
     FSE_COMMAND = 299,
     FSE_FILESET = 300,
     FSE_XMLDUMP = 301,
     FSE_RAND = 302,
     FSE_MODE = 303,
     FSE_MULTI = 304,
     FSE_MULTIDUMP = 305,
     FSK_SEPLST = 306,
     FSK_OPENLST = 307,
     FSK_CLOSELST = 308,
     FSK_OPENPAR = 309,
     FSK_CLOSEPAR = 310,
     FSK_ASSIGN = 311,
     FSK_IN = 312,
     FSK_QUOTE = 313,
     FSA_SIZE = 314,
     FSA_PREALLOC = 315,
     FSA_PARALLOC = 316,
     FSA_PATH = 317,
     FSA_REUSE = 318,
     FSA_PROCESS = 319,
     FSA_MEMSIZE = 320,
     FSA_RATE = 321,
     FSA_CACHED = 322,
     FSA_READONLY = 323,
     FSA_TRUSTTREE = 324,
     FSA_IOSIZE = 325,
     FSA_FILE = 326,
     FSA_WSS = 327,
     FSA_NAME = 328,
     FSA_RANDOM = 329,
     FSA_INSTANCES = 330,
     FSA_DSYNC = 331,
     FSA_TARGET = 332,
     FSA_ITERS = 333,
     FSA_NICE = 334,
     FSA_VALUE = 335,
     FSA_BLOCKING = 336,
     FSA_HIGHWATER = 337,
     FSA_DIRECTIO = 338,
     FSA_DIRWIDTH = 339,
     FSA_FD = 340,
     FSA_SRCFD = 341,
     FSA_ROTATEFD = 342,
     FSA_ENTRIES = 343,
     FSA_DIRDEPTHRV = 344,
     FSA_DIRGAMMA = 345,
     FSA_USEISM = 346,
     FSA_TYPE = 347,
     FSA_RANDTABLE = 348,
     FSA_RANDSRC = 349,
     FSA_ROUND = 350,
     FSA_LEAFDIRS = 351,
     FSA_INDEXED = 352,
     FSA_FSTYPE = 353,
     FSA_RANDSEED = 354,
     FSA_RANDGAMMA = 355,
     FSA_RANDMEAN = 356,
     FSA_MIN = 357,
     FSA_MAX = 358,
     FSA_MASTER = 359,
     FSA_CLIENT = 360,
     FSS_TYPE = 361,
     FSS_SEED = 362,
     FSS_GAMMA = 363,
     FSS_MEAN = 364,
     FSS_MIN = 365,
     FSS_SRC = 366,
     FSS_ROUND = 367,
     FSA_LVAR_ASSIGN = 368,
     FSA_ALLDONE = 369,
     FSA_FIRSTDONE = 370,
     FSA_TIMEOUT = 371,
     FSC_OSPROF_ENABLE = 372,
     FSC_OSPROF_DISABLE = 373,
     FSA_NOREADAHEAD = 374,
     FSA_IOPRIO = 375,
     FSA_WRITEONLY = 376,
     FSE_CVAR = 377,
     FSA_PARAMETERS = 378
   };
#endif
/* Tokens.  */
#define FSC_LIST 258
#define FSC_DEFINE 259
#define FSC_QUIT 260
#define FSC_DEBUG 261
#define FSC_CREATE 262
#define FSC_SLEEP 263
#define FSC_STATS 264
#define FSC_SET 265
#define FSC_SHUTDOWN 266
#define FSC_LOG 267
#define FSC_SYSTEM 268
#define FSC_FLOWOP 269
#define FSC_EVENTGEN 270
#define FSC_ECHO 271
#define FSC_RUN 272
#define FSC_PSRUN 273
#define FSC_WARMUP 274
#define FSC_NOUSESTATS 275
#define FSC_FSCHECK 276
#define FSC_FSFLUSH 277
#define FSC_VERSION 278
#define FSC_ENABLE 279
#define FSC_DOMULTISYNC 280
#define FSC_IMPORT 281
#define FSV_STRING 282
#define FSV_VAL_INT 283
#define FSV_VAL_NEGINT 284
#define FSV_VAL_BOOLEAN 285
#define FSV_VARIABLE 286
#define FSV_WHITESTRING 287
#define FSV_RANDUNI 288
#define FSV_RANDTAB 289
#define FSV_URAND 290
#define FSV_RAND48 291
#define FSE_FILE 292
#define FSE_PROC 293
#define FSE_THREAD 294
#define FSE_CLEAR 295
#define FSE_SNAP 296
#define FSE_DUMP 297
#define FSE_DIRECTORY 298
#define FSE_COMMAND 299
#define FSE_FILESET 300
#define FSE_XMLDUMP 301
#define FSE_RAND 302
#define FSE_MODE 303
#define FSE_MULTI 304
#define FSE_MULTIDUMP 305
#define FSK_SEPLST 306
#define FSK_OPENLST 307
#define FSK_CLOSELST 308
#define FSK_OPENPAR 309
#define FSK_CLOSEPAR 310
#define FSK_ASSIGN 311
#define FSK_IN 312
#define FSK_QUOTE 313
#define FSA_SIZE 314
#define FSA_PREALLOC 315
#define FSA_PARALLOC 316
#define FSA_PATH 317
#define FSA_REUSE 318
#define FSA_PROCESS 319
#define FSA_MEMSIZE 320
#define FSA_RATE 321
#define FSA_CACHED 322
#define FSA_READONLY 323
#define FSA_TRUSTTREE 324
#define FSA_IOSIZE 325
#define FSA_FILE 326
#define FSA_WSS 327
#define FSA_NAME 328
#define FSA_RANDOM 329
#define FSA_INSTANCES 330
#define FSA_DSYNC 331
#define FSA_TARGET 332
#define FSA_ITERS 333
#define FSA_NICE 334
#define FSA_VALUE 335
#define FSA_BLOCKING 336
#define FSA_HIGHWATER 337
#define FSA_DIRECTIO 338
#define FSA_DIRWIDTH 339
#define FSA_FD 340
#define FSA_SRCFD 341
#define FSA_ROTATEFD 342
#define FSA_ENTRIES 343
#define FSA_DIRDEPTHRV 344
#define FSA_DIRGAMMA 345
#define FSA_USEISM 346
#define FSA_TYPE 347
#define FSA_RANDTABLE 348
#define FSA_RANDSRC 349
#define FSA_ROUND 350
#define FSA_LEAFDIRS 351
#define FSA_INDEXED 352
#define FSA_FSTYPE 353
#define FSA_RANDSEED 354
#define FSA_RANDGAMMA 355
#define FSA_RANDMEAN 356
#define FSA_MIN 357
#define FSA_MAX 358
#define FSA_MASTER 359
#define FSA_CLIENT 360
#define FSS_TYPE 361
#define FSS_SEED 362
#define FSS_GAMMA 363
#define FSS_MEAN 364
#define FSS_MIN 365
#define FSS_SRC 366
#define FSS_ROUND 367
#define FSA_LVAR_ASSIGN 368
#define FSA_ALLDONE 369
#define FSA_FIRSTDONE 370
#define FSA_TIMEOUT 371
#define FSC_OSPROF_ENABLE 372
#define FSC_OSPROF_DISABLE 373
#define FSA_NOREADAHEAD 374
#define FSA_IOPRIO 375
#define FSA_WRITEONLY 376
#define FSE_CVAR 377
#define FSA_PARAMETERS 378




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 155 "parser_gram.y"

	int64_t		 ival;
	unsigned char	 bval;
	char *		 sval;
	fs_u		 val;
	avd_t		 avd;
	cmd_t		*cmd;
	attr_t		*attr;
	list_t		*list;
	probtabent_t	*rndtb;



/* Line 214 of yacc.c  */
#line 496 "parser_gram.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 508 "parser_gram.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   319

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  124
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  93
/* YYNRULES -- Number of rules.  */
#define YYNRULES  278
/* YYNRULES -- Number of states.  */
#define YYNSTATES  379

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   378

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     9,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    34,    36,    38,
      40,    42,    44,    46,    48,    50,    52,    54,    56,    58,
      60,    62,    64,    67,    70,    73,    75,    77,    79,    82,
      85,    88,    90,    92,    94,    97,   100,   103,   106,   109,
     112,   115,   118,   121,   123,   126,   129,   132,   135,   138,
     141,   143,   145,   147,   149,   154,   159,   166,   171,   179,
     187,   192,   197,   202,   206,   209,   212,   216,   220,   224,
     228,   232,   234,   236,   239,   245,   247,   250,   257,   260,
     264,   268,   272,   276,   279,   282,   285,   288,   291,   294,
     296,   299,   302,   304,   306,   309,   312,   316,   320,   323,
     326,   328,   330,   332,   334,   336,   338,   342,   344,   348,
     352,   354,   358,   360,   362,   366,   368,   372,   376,   378,
     382,   384,   386,   390,   398,   402,   404,   408,   412,   420,
     422,   426,   428,   432,   436,   438,   440,   444,   448,   450,
     452,   456,   460,   464,   466,   468,   472,   476,   478,   480,
     484,   488,   492,   496,   498,   500,   502,   504,   506,   508,
     510,   512,   514,   516,   518,   520,   522,   524,   526,   528,
     530,   532,   534,   536,   538,   540,   542,   544,   546,   548,
     550,   552,   554,   556,   558,   560,   562,   564,   566,   568,
     570,   572,   574,   576,   578,   580,   582,   584,   586,   588,
     590,   592,   594,   596,   598,   600,   602,   604,   606,   608,
     610,   612,   614,   616,   618,   620,   622,   624,   626,   628,
     630,   632,   634,   636,   638,   640,   642,   644,   646,   648,
     650,   652,   654,   656,   658,   660,   662,   664,   666,   668,
     670,   672,   674,   676,   678,   680,   682,   686,   690,   694,
     698,   702,   708,   712,   716,   718,   725,   728,   730,   734,
     738,   740,   742,   744,   746,   748,   750,   753,   755
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     125,     0,    -1,   125,   126,    -1,   125,     1,    -1,    -1,
     154,    -1,   155,    -1,   156,    -1,   211,    -1,   143,    -1,
     127,    -1,   157,    -1,   129,    -1,   140,    -1,   141,    -1,
     139,    -1,   142,    -1,   161,    -1,   162,    -1,   144,    -1,
     158,    -1,   160,    -1,   159,    -1,   149,    -1,   128,    -1,
     130,    -1,   131,    -1,   132,    -1,   133,    -1,   134,    -1,
     150,    -1,    15,    -1,   127,   184,    -1,    13,   138,    -1,
      16,   138,    -1,    23,    -1,   117,    -1,   118,    -1,    24,
      49,    -1,   133,   186,    -1,    25,   188,    -1,    31,    -1,
      27,    -1,   135,    -1,   136,   135,    -1,    58,    31,    -1,
      58,    32,    -1,   137,    32,    -1,   137,    31,    -1,   138,
      32,    -1,   138,    31,    -1,   138,    58,    -1,   137,    58,
      -1,     3,    -1,   139,    14,    -1,    21,   189,    -1,   140,
     189,    -1,    22,   189,    -1,    12,   138,    -1,     6,    28,
      -1,   145,    -1,   146,    -1,   147,    -1,   148,    -1,    10,
      31,    56,    28,    -1,    10,    31,    56,    30,    -1,    10,
      31,    56,    58,    32,    58,    -1,    10,    31,    56,    27,
      -1,    10,    31,    56,    47,    54,   174,    55,    -1,    10,
      31,    56,   122,    54,   212,    55,    -1,    10,    48,     5,
     116,    -1,    10,    48,     5,   114,    -1,    10,    48,     5,
     115,    -1,    10,    48,    20,    -1,     9,    41,    -1,     9,
      40,    -1,     9,    43,   136,    -1,     9,    44,   138,    -1,
       9,    42,   138,    -1,     9,    46,   138,    -1,     9,    50,
     138,    -1,     5,    -1,   163,    -1,   151,   163,    -1,    39,
     180,    52,   151,    53,    -1,   152,    -1,   153,   152,    -1,
       4,    38,   178,    52,   153,    53,    -1,   154,   178,    -1,
       4,    37,   166,    -1,     4,    45,   167,    -1,    26,    37,
     170,    -1,    26,    45,   171,    -1,     7,   164,    -1,    11,
     164,    -1,    19,    28,    -1,    19,    31,    -1,     8,    28,
      -1,     8,    31,    -1,     8,    -1,    17,    28,    -1,    17,
      31,    -1,    17,    -1,    18,    -1,    18,    29,    -1,    18,
      28,    -1,    18,    29,    28,    -1,    18,    28,    28,    -1,
      14,   165,    -1,   163,   182,    -1,    38,    -1,    39,    -1,
      45,    -1,    37,    -1,    27,    -1,   168,    -1,   166,    51,
     168,    -1,   169,    -1,   167,    51,   169,    -1,   193,    56,
     215,    -1,   193,    -1,   194,    56,   215,    -1,   194,    -1,
     172,    -1,   170,    51,   172,    -1,   173,    -1,   171,    51,
     173,    -1,   195,    56,   215,    -1,   195,    -1,   196,    56,
     215,    -1,   196,    -1,   175,    -1,   174,    51,   175,    -1,
     174,    51,    93,    56,    52,   177,    53,    -1,   197,    56,
     215,    -1,   197,    -1,    92,    56,   198,    -1,    94,    56,
     200,    -1,    52,   216,    51,   216,    51,   216,    53,    -1,
     176,    -1,   177,    51,   176,    -1,   179,    -1,   178,    51,
     179,    -1,   192,    56,   215,    -1,   192,    -1,   181,    -1,
     180,    51,   181,    -1,   203,    56,   215,    -1,   203,    -1,
     183,    -1,   182,    51,   183,    -1,   182,    51,   210,    -1,
     190,    56,   215,    -1,   190,    -1,   185,    -1,   184,    51,
     185,    -1,   191,    56,   215,    -1,   191,    -1,   187,    -1,
     186,    51,   187,    -1,   206,    56,   215,    -1,    80,    56,
     215,    -1,   207,    56,    27,    -1,   204,    -1,   205,    -1,
      79,    -1,    73,    -1,    75,    -1,    73,    -1,    62,    -1,
      59,    -1,    60,    -1,    61,    -1,    63,    -1,    68,    -1,
      69,    -1,    67,    -1,   121,    -1,    73,    -1,    62,    -1,
      88,    -1,    59,    -1,    84,    -1,    89,    -1,    60,    -1,
      61,    -1,    63,    -1,    68,    -1,    69,    -1,    90,    -1,
      67,    -1,    96,    -1,   121,    -1,    73,    -1,    62,    -1,
      68,    -1,    69,    -1,    67,    -1,   121,    -1,    73,    -1,
      62,    -1,    88,    -1,    59,    -1,    60,    -1,    68,    -1,
      69,    -1,    67,    -1,    96,    -1,   121,    -1,    73,    -1,
      99,    -1,   100,    -1,   101,    -1,   102,    -1,    95,    -1,
     199,    -1,    33,    -1,    34,    -1,   100,    -1,   201,    -1,
      35,    -1,    36,    -1,    92,    -1,   123,    -1,   102,    -1,
     103,    -1,    95,    -1,    64,    -1,    73,    -1,    65,    -1,
      91,    -1,    75,    -1,   120,    -1,    72,    -1,    71,    -1,
      73,    -1,    74,    -1,    85,    -1,    86,    -1,    87,    -1,
      76,    -1,    83,    -1,    97,    -1,    77,    -1,    78,    -1,
      80,    -1,    81,    -1,    82,    -1,    70,    -1,   119,    -1,
      66,    -1,   104,    -1,   105,    -1,    62,    -1,    98,    -1,
     209,    -1,   208,    51,   209,    -1,   208,    51,   210,    -1,
     214,    56,   215,    -1,    31,    56,    30,    -1,    31,    56,
      28,    -1,    31,    56,    58,    32,    58,    -1,    31,    56,
      27,    -1,    31,    56,    31,    -1,    31,    -1,     4,    14,
     208,    52,   151,    53,    -1,   211,   208,    -1,   213,    -1,
     212,    51,   213,    -1,   202,    56,   215,    -1,    73,    -1,
      78,    -1,    27,    -1,    28,    -1,    30,    -1,    31,    -1,
      31,    27,    -1,    28,    -1,    31,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   252,   252,   259,   264,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   286,   287,   288,   289,   290,   291,
     292,   294,   300,   305,   314,   323,   330,   337,   344,   351,
     356,   365,   372,   380,   384,   399,   406,   414,   432,   449,
     467,   484,   487,   492,   498,   503,   511,   516,   525,   533,
     543,   543,   543,   543,   545,   556,   566,   575,   586,   598,
     610,   620,   630,   640,   652,   660,   667,   675,   683,   690,
     697,   706,   713,   716,   734,   746,   749,   767,   776,   781,
     789,   799,   808,   818,   837,   856,   863,   871,   878,   885,
     893,   900,   907,   915,   923,   932,   941,   949,   958,   964,
     969,   970,   971,   972,   974,   977,   981,   994,   998,  1011,
    1016,  1025,  1030,  1040,  1044,  1057,  1061,  1074,  1079,  1088,
    1093,  1103,  1107,  1120,  1139,  1144,  1150,  1155,  1161,  1171,
    1175,  1190,  1194,  1208,  1213,  1221,  1225,  1239,  1244,  1252,
    1256,  1269,  1283,  1288,  1296,  1300,  1314,  1319,  1327,  1331,
    1345,  1351,  1357,  1365,  1367,  1370,  1371,  1372,  1375,  1376,
    1377,  1378,  1379,  1380,  1381,  1382,  1383,  1384,  1387,  1388,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1401,  1404,  1405,  1406,  1407,  1408,  1409,  1412,
    1413,  1414,  1415,  1416,  1417,  1418,  1419,  1420,  1421,  1424,
    1425,  1426,  1427,  1428,  1429,  1431,  1439,  1440,  1441,  1443,
    1451,  1452,  1455,  1456,  1457,  1458,  1459,  1462,  1463,  1464,
    1465,  1466,  1467,  1470,  1471,  1472,  1473,  1474,  1475,  1476,
    1477,  1478,  1479,  1480,  1481,  1482,  1483,  1484,  1485,  1486,
    1489,  1492,  1493,  1496,  1497,  1499,  1503,  1516,  1530,  1536,
    1541,  1546,  1551,  1556,  1561,  1567,  1575,  1581,  1585,  1599,
    1606,  1607,  1609,  1614,  1618,  1622,  1626,  1636,  1639
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FSC_LIST", "FSC_DEFINE", "FSC_QUIT",
  "FSC_DEBUG", "FSC_CREATE", "FSC_SLEEP", "FSC_STATS", "FSC_SET",
  "FSC_SHUTDOWN", "FSC_LOG", "FSC_SYSTEM", "FSC_FLOWOP", "FSC_EVENTGEN",
  "FSC_ECHO", "FSC_RUN", "FSC_PSRUN", "FSC_WARMUP", "FSC_NOUSESTATS",
  "FSC_FSCHECK", "FSC_FSFLUSH", "FSC_VERSION", "FSC_ENABLE",
  "FSC_DOMULTISYNC", "FSC_IMPORT", "FSV_STRING", "FSV_VAL_INT",
  "FSV_VAL_NEGINT", "FSV_VAL_BOOLEAN", "FSV_VARIABLE", "FSV_WHITESTRING",
  "FSV_RANDUNI", "FSV_RANDTAB", "FSV_URAND", "FSV_RAND48", "FSE_FILE",
  "FSE_PROC", "FSE_THREAD", "FSE_CLEAR", "FSE_SNAP", "FSE_DUMP",
  "FSE_DIRECTORY", "FSE_COMMAND", "FSE_FILESET", "FSE_XMLDUMP", "FSE_RAND",
  "FSE_MODE", "FSE_MULTI", "FSE_MULTIDUMP", "FSK_SEPLST", "FSK_OPENLST",
  "FSK_CLOSELST", "FSK_OPENPAR", "FSK_CLOSEPAR", "FSK_ASSIGN", "FSK_IN",
  "FSK_QUOTE", "FSA_SIZE", "FSA_PREALLOC", "FSA_PARALLOC", "FSA_PATH",
  "FSA_REUSE", "FSA_PROCESS", "FSA_MEMSIZE", "FSA_RATE", "FSA_CACHED",
  "FSA_READONLY", "FSA_TRUSTTREE", "FSA_IOSIZE", "FSA_FILE", "FSA_WSS",
  "FSA_NAME", "FSA_RANDOM", "FSA_INSTANCES", "FSA_DSYNC", "FSA_TARGET",
  "FSA_ITERS", "FSA_NICE", "FSA_VALUE", "FSA_BLOCKING", "FSA_HIGHWATER",
  "FSA_DIRECTIO", "FSA_DIRWIDTH", "FSA_FD", "FSA_SRCFD", "FSA_ROTATEFD",
  "FSA_ENTRIES", "FSA_DIRDEPTHRV", "FSA_DIRGAMMA", "FSA_USEISM",
  "FSA_TYPE", "FSA_RANDTABLE", "FSA_RANDSRC", "FSA_ROUND", "FSA_LEAFDIRS",
  "FSA_INDEXED", "FSA_FSTYPE", "FSA_RANDSEED", "FSA_RANDGAMMA",
  "FSA_RANDMEAN", "FSA_MIN", "FSA_MAX", "FSA_MASTER", "FSA_CLIENT",
  "FSS_TYPE", "FSS_SEED", "FSS_GAMMA", "FSS_MEAN", "FSS_MIN", "FSS_SRC",
  "FSS_ROUND", "FSA_LVAR_ASSIGN", "FSA_ALLDONE", "FSA_FIRSTDONE",
  "FSA_TIMEOUT", "FSC_OSPROF_ENABLE", "FSC_OSPROF_DISABLE",
  "FSA_NOREADAHEAD", "FSA_IOPRIO", "FSA_WRITEONLY", "FSE_CVAR",
  "FSA_PARAMETERS", "$accept", "commands", "command", "eventgen_command",
  "system_command", "echo_command", "version_command",
  "osprof_enable_command", "osprof_disable_command", "enable_command",
  "multisync_command", "var_string", "var_string_list", "whitevar_string",
  "whitevar_string_list", "list_command", "fscheck_command",
  "fsflush_command", "log_command", "debug_command", "set_command",
  "set_variable", "set_random_variable", "set_custom_variable", "set_mode",
  "stats_command", "quit_command", "flowop_list", "thread", "thread_list",
  "proc_define_command", "files_define_command", "files_import_command",
  "create_command", "shutdown_command", "warmup_command", "sleep_command",
  "run_command", "psrun_command", "flowop_command", "entity", "name",
  "file_define_attr_ops", "fileset_define_attr_ops", "file_define_attr_op",
  "fileset_define_attr_op", "file_import_attr_ops",
  "fileset_import_attr_ops", "file_import_attr_op",
  "fileset_import_attr_op", "randvar_attr_ops", "randvar_attr_op",
  "probtabentry", "probtabentry_list", "p_attr_ops", "p_attr_op",
  "t_attr_ops", "t_attr_op", "fo_attr_ops", "fo_attr_op", "ev_attr_ops",
  "ev_attr_op", "enable_multi_ops", "enable_multi_op", "multisync_op",
  "fscheck_attr_op", "fo_attr_name", "ev_attr_name", "attrs_define_proc",
  "attr_define_file", "attr_define_fileset", "attr_import_file",
  "attr_import_fileset", "randvar_attr_name", "randvar_attr_typop",
  "randtype_name", "randvar_attr_srcop", "randsrc_name", "cvar_attr_name",
  "attrs_define_thread", "attrs_flowop", "attrs_eventgen", "em_attr_name",
  "fscheck_attr_name", "comp_attr_ops", "comp_attr_op", "comp_lvar_def",
  "fo_define_command", "cvar_attr_ops", "cvar_attr_op",
  "attrs_define_comp", "attr_value", "var_int_val", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   124,   125,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   129,   130,   131,   132,   133,   133,
     134,   135,   135,   136,   136,   137,   137,   138,   138,   138,
     138,   138,   138,   139,   139,   140,   140,   141,   142,   143,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   147,
     148,   148,   148,   148,   149,   149,   149,   149,   149,   149,
     149,   150,   151,   151,   152,   153,   153,   154,   154,   155,
     155,   156,   156,   157,   158,   159,   159,   160,   160,   160,
     161,   161,   161,   162,   162,   162,   162,   162,   163,   163,
     164,   164,   164,   164,   165,   166,   166,   167,   167,   168,
     168,   169,   169,   170,   170,   171,   171,   172,   172,   173,
     173,   174,   174,   174,   175,   175,   175,   175,   176,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   182,   183,   183,   184,   184,   185,   185,   186,   186,
     187,   188,   189,   190,   191,   192,   192,   192,   193,   193,
     193,   193,   193,   193,   193,   193,   193,   193,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   194,   195,   195,   195,   195,   195,   195,   196,
     196,   196,   196,   196,   196,   196,   196,   196,   196,   197,
     197,   197,   197,   197,   197,   198,   199,   199,   199,   200,
     201,   201,   202,   202,   202,   202,   202,   203,   203,   203,
     203,   203,   203,   204,   204,   204,   204,   204,   204,   204,
     204,   204,   204,   204,   204,   204,   204,   204,   204,   204,
     205,   206,   206,   207,   207,   208,   208,   208,   209,   210,
     210,   210,   210,   210,   210,   211,   211,   212,   212,   213,
     214,   214,   215,   215,   215,   215,   215,   216,   216
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     1,     1,     1,     2,     2,
       2,     1,     1,     1,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     4,     4,     6,     4,     7,     7,
       4,     4,     4,     3,     2,     2,     3,     3,     3,     3,
       3,     1,     1,     2,     5,     1,     2,     6,     2,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     1,
       2,     2,     1,     1,     2,     2,     3,     3,     2,     2,
       1,     1,     1,     1,     1,     1,     3,     1,     3,     3,
       1,     3,     1,     1,     3,     1,     3,     3,     1,     3,
       1,     1,     3,     7,     3,     1,     3,     3,     7,     1,
       3,     1,     3,     3,     1,     1,     3,     3,     1,     1,
       3,     3,     3,     1,     1,     3,     3,     1,     1,     3,
       3,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     5,     3,     3,     1,     6,     2,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     2,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     1,     3,    53,     0,    81,     0,     0,    99,
       0,     0,     0,     0,     0,    31,     0,   102,   103,     0,
       0,     0,    35,     0,     0,     0,    36,    37,     2,    10,
      24,    12,    25,    26,    27,    28,    29,    15,    13,    14,
      16,     9,    19,    60,    61,    62,    63,    23,    30,     5,
       6,     7,    11,    20,    22,    21,    17,    18,     8,     0,
       0,     0,     0,    59,   113,   110,   111,   112,    93,    97,
      98,    75,    74,     0,     0,     0,     0,     0,     0,     0,
      94,     0,     0,    58,    33,    34,   100,   101,   105,   104,
      95,    96,   253,   254,    55,     0,    57,    38,     0,    40,
       0,     0,   250,    32,   154,   157,   164,   251,   252,    39,
     158,     0,    54,    56,   166,   167,   165,    88,   141,   144,
     270,   271,   266,   255,     0,     0,   170,   171,   172,   169,
     173,   176,   174,   175,   168,   177,    89,   115,   120,     0,
     181,   184,   185,   179,   186,   190,   187,   188,   178,   182,
     180,   183,   189,   191,   192,    90,   117,   122,    78,    42,
      41,    43,    76,    77,    79,    80,     0,     0,    73,    45,
      46,    48,    47,    52,    50,    49,    51,   107,   106,     0,
       0,   194,   197,   195,   196,   193,   198,    91,   123,   128,
     202,   203,   200,   206,   204,   205,   199,   201,   207,   208,
      92,   125,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    67,    64,
      65,     0,     0,     0,    71,    72,    70,   162,   272,   273,
     274,   275,   161,     0,     0,     0,     0,   155,   156,   159,
     160,   142,   143,   264,   256,   257,   258,     0,     0,    82,
     116,   119,     0,    85,     0,   118,   121,     0,     0,     0,
     276,   124,   127,   126,   129,     0,   114,   108,   265,    83,
     248,   234,   233,   235,   236,   240,   243,   244,   245,   246,
     247,   241,   237,   238,   239,   242,   249,   109,   149,   153,
     163,   227,   229,   228,   231,   230,   232,     0,   145,   148,
      87,    86,   209,     0,     0,   214,   210,   211,   212,   213,
       0,   131,   135,    66,   222,   226,   224,   225,   223,     0,
       0,   267,   262,   260,   259,   263,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    68,     0,     0,     0,    69,
       0,   150,   151,   152,   146,     0,   147,   216,   217,   218,
     136,   215,   220,   221,   137,   219,     0,   132,   134,   269,
     268,   261,    84,     0,     0,     0,   139,     0,   277,   278,
       0,     0,   133,     0,   140,     0,     0,     0,   138
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    28,    29,    30,    31,    32,    33,    34,    35,
      36,   161,   162,    82,    83,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,   248,   253,   254,
      49,    50,    51,    52,    53,    54,    55,    56,    57,   249,
      68,   267,   136,   155,   137,   156,   187,   200,   188,   201,
     310,   311,   366,   367,   117,   118,   297,   298,   287,   288,
     103,   104,   109,   110,    99,    94,   289,   105,   119,   138,
     157,   189,   202,   312,   350,   351,   354,   355,   319,   299,
     290,   106,   111,    95,   122,   123,   245,    58,   320,   321,
     124,   232,   370
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -248
static const yytype_int16 yypact[] =
{
    -248,    33,  -248,  -248,  -248,   178,  -248,     7,   -22,    35,
     216,   -28,   -22,    14,    14,  -248,    14,    68,    77,   141,
     -38,   -38,  -248,    16,    32,    50,  -248,  -248,  -248,    78,
    -248,  -248,  -248,  -248,  -248,    59,  -248,   105,   -38,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,    18,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,   -47,   -47,
      79,    18,    41,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,    14,    80,    14,    14,    14,    72,     5,
    -248,   205,   122,   156,   156,   156,  -248,  -248,   108,   121,
    -248,  -248,  -248,  -248,  -248,   112,  -248,  -248,   114,  -248,
      53,    98,  -248,   124,  -248,   129,  -248,  -248,  -248,   126,
    -248,   133,  -248,  -248,  -248,  -248,  -248,   142,  -248,   135,
    -248,  -248,   187,  -248,   195,   198,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   192,  -248,   209,   212,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,   210,  -248,   211,   156,  -248,
    -248,  -248,    80,   156,   156,   156,    34,   115,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,   219,
     190,  -248,  -248,  -248,  -248,  -248,  -248,   221,  -248,   218,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
     222,  -248,   220,    78,   190,    59,   190,    18,   190,    45,
     190,   261,    79,   190,   238,    41,   190,  -248,  -248,  -248,
    -248,   224,   247,   226,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   254,  -248,    53,   190,    98,   190,  -248,  -248,  -248,
    -248,  -248,  -248,   227,  -248,  -248,  -248,   255,    -6,   125,
    -248,  -248,    70,  -248,   -32,  -248,  -248,   153,   228,    81,
    -248,  -248,  -248,  -248,  -248,   151,  -248,  -248,  -248,   125,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,   233,  -248,   229,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,   217,  -248,   231,
    -248,  -248,  -248,   232,   234,  -248,  -248,  -248,  -248,  -248,
      62,  -248,   236,  -248,  -248,  -248,  -248,  -248,  -248,   237,
     104,  -248,  -248,  -248,  -248,  -248,   257,    -3,   190,    70,
     261,   190,   -15,   235,   140,  -248,   190,   190,    81,  -248,
     239,  -248,  -248,  -248,  -248,     0,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,   240,  -248,  -248,  -248,
    -248,  -248,  -248,   242,   243,   196,  -248,   -40,  -248,  -248,
     248,   243,  -248,   196,  -248,   249,   196,   245,  -248
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   139,  -248,  -248,    13,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,   -39,    48,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -247,
     291,  -248,  -248,  -248,    92,    90,  -248,  -248,    73,    74,
    -248,   -27,   -63,  -248,   250,   103,  -248,   -17,  -248,   -14,
    -248,   111,  -248,   110,  -248,   -16,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,   258,   107,    -9,  -248,  -248,   -19,
    -248,  -204,  -148
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     238,   269,   240,    78,   242,    96,   246,   252,   247,   251,
     167,   371,   256,   372,   247,    64,    65,    66,   347,   348,
      79,   300,   113,    67,    92,   168,   120,    84,   243,    85,
     262,   121,   264,     2,     3,    63,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,   268,    15,    16,
      17,    18,    19,   362,    20,    21,    22,    23,    24,    25,
      93,   218,   219,    69,   220,    97,    70,   270,   271,   272,
     273,   274,    81,   275,   276,   277,   243,   278,   279,   280,
     281,   221,   282,   283,   284,   349,   158,   100,   163,   164,
     165,   114,   222,   115,   285,   101,    86,   116,   269,    87,
     140,   141,   142,   143,   144,    88,    89,   159,   145,   146,
     147,   160,    98,   334,   148,   181,   286,   335,   120,   112,
     182,   183,   184,   121,   343,   149,   185,   346,   166,   150,
     151,   152,   358,   359,   291,   292,   177,   153,   126,   127,
     128,   129,   130,   293,   102,   294,   131,   132,   133,   178,
      26,    27,   134,   171,   172,   338,   223,   190,   191,   339,
     192,   295,   154,   107,   108,   193,   194,   195,   179,    90,
     180,   196,    91,   314,   186,   203,   315,   205,   322,   323,
     173,   324,   325,   316,   317,   204,   197,   174,   175,   206,
     296,   208,    59,   207,   198,   270,   271,   272,   273,   274,
     135,   275,   276,   277,   318,   278,   279,   280,   281,   326,
     282,   283,   284,   302,   176,    60,    61,   228,   229,   199,
     230,   231,   285,    62,   368,   375,   302,   369,   377,   224,
     225,   226,   303,   356,   304,   305,   169,   170,   209,   306,
     307,   308,   309,   212,   286,   303,   227,   304,   305,   209,
     211,   210,   306,   307,   308,   309,    71,    72,    73,    74,
      75,   215,    76,   207,   214,   213,    77,   216,   329,   330,
     352,   353,   233,   235,   234,   247,   236,   252,   257,   258,
     259,   260,   266,   265,   327,   328,   313,   331,   332,   340,
     333,   345,   336,   337,   364,   365,   363,   361,   378,   373,
     376,   217,   301,    80,   250,   255,   261,   357,   374,   263,
     241,   139,   344,   341,   237,   239,   244,   125,   342,   360
};

static const yytype_uint16 yycheck[] =
{
     204,   248,   206,    31,   208,    21,   210,    39,    14,   213,
       5,    51,   216,    53,    14,    37,    38,    39,    33,    34,
      48,    53,    38,    45,    62,    20,    73,    14,    31,    16,
     234,    78,   236,     0,     1,    28,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    53,    15,    16,
      17,    18,    19,    53,    21,    22,    23,    24,    25,    26,
      98,    27,    28,    28,    30,    49,    31,    70,    71,    72,
      73,    74,    58,    76,    77,    78,    31,    80,    81,    82,
      83,    47,    85,    86,    87,   100,    73,    37,    75,    76,
      77,    73,    58,    75,    97,    45,    28,    79,   345,    31,
      59,    60,    61,    62,    63,    28,    29,    27,    67,    68,
      69,    31,    80,    51,    73,    62,   119,    55,    73,    14,
      67,    68,    69,    78,   328,    84,    73,   331,    56,    88,
      89,    90,   336,   337,    64,    65,    28,    96,    59,    60,
      61,    62,    63,    73,    66,    75,    67,    68,    69,    28,
     117,   118,    73,    31,    32,    51,   122,    59,    60,    55,
      62,    91,   121,   104,   105,    67,    68,    69,    56,    28,
      56,    73,    31,    92,   121,    51,    95,    51,    27,    28,
      58,    30,    31,   102,   103,    56,    88,    31,    32,    56,
     120,    56,    14,    51,    96,    70,    71,    72,    73,    74,
     121,    76,    77,    78,   123,    80,    81,    82,    83,    58,
      85,    86,    87,    73,    58,    37,    38,    27,    28,   121,
      30,    31,    97,    45,    28,   373,    73,    31,   376,   114,
     115,   116,    92,    93,    94,    95,    31,    32,    51,    99,
     100,   101,   102,    51,   119,    92,    27,    94,    95,    51,
      52,    56,    99,   100,   101,   102,    40,    41,    42,    43,
      44,    51,    46,    51,    52,    56,    50,    56,    51,    52,
      35,    36,    51,    51,    56,    14,    56,    39,    54,    32,
      54,    27,    27,    56,    51,    56,    58,    56,    56,    32,
      56,   330,    56,    56,    52,    52,    56,    58,    53,    51,
      51,   162,   254,    12,   212,   215,   233,   334,   371,   235,
     207,    61,   329,   327,   203,   205,   209,    59,   327,   338
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,   125,     0,     1,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    15,    16,    17,    18,    19,
      21,    22,    23,    24,    25,    26,   117,   118,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   211,    14,
      37,    38,    45,    28,    37,    38,    39,    45,   164,    28,
      31,    40,    41,    42,    43,    44,    46,    50,    31,    48,
     164,    58,   137,   138,   138,   138,    28,    31,    28,    29,
      28,    31,    62,    98,   189,   207,   189,    49,    80,   188,
      37,    45,    66,   184,   185,   191,   205,   104,   105,   186,
     187,   206,    14,   189,    73,    75,    79,   178,   179,   192,
      73,    78,   208,   209,   214,   208,    59,    60,    61,    62,
      63,    67,    68,    69,    73,   121,   166,   168,   193,   178,
      59,    60,    61,    62,    63,    67,    68,    69,    73,    84,
      88,    89,    90,    96,   121,   167,   169,   194,   138,    27,
      31,   135,   136,   138,   138,   138,    56,     5,    20,    31,
      32,    31,    32,    58,    31,    32,    58,    28,    28,    56,
      56,    62,    67,    68,    69,    73,   121,   170,   172,   195,
      59,    60,    62,    67,    68,    69,    73,    88,    96,   121,
     171,   173,   196,    51,    56,    51,    56,    51,    56,    51,
      56,    52,    51,    56,    52,    51,    56,   135,    27,    28,
      30,    47,    58,   122,   114,   115,   116,    27,    27,    28,
      30,    31,   215,    51,    56,    51,    56,   185,   215,   187,
     215,   179,   215,    31,   209,   210,   215,    14,   151,   163,
     168,   215,    39,   152,   153,   169,   215,    54,    32,    54,
      27,   172,   215,   173,   215,    56,    27,   165,    53,   163,
      70,    71,    72,    73,    74,    76,    77,    78,    80,    81,
      82,    83,    85,    86,    87,    97,   119,   182,   183,   190,
     204,    64,    65,    73,    75,    91,   120,   180,   181,   203,
      53,   152,    73,    92,    94,    95,    99,   100,   101,   102,
     174,   175,   197,    58,    92,    95,   102,   103,   123,   202,
     212,   213,    27,    28,    30,    31,    58,    51,    56,    51,
      52,    56,    56,    56,    51,    55,    56,    56,    51,    55,
      32,   183,   210,   215,   181,   151,   215,    33,    34,   100,
     198,   199,    35,    36,   200,   201,    93,   175,   215,   215,
     213,    58,    53,    56,    52,    52,   176,   177,    28,    31,
     216,    51,    53,    51,   176,   216,    51,   216,    53
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 253 "parser_gram.y"
    {
	if ((yyvsp[(2) - (2)].cmd)->cmd)
		(yyvsp[(2) - (2)].cmd)->cmd((yyvsp[(2) - (2)].cmd));

	free((yyvsp[(2) - (2)].cmd));
}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 260 "parser_gram.y"
    {
	if (dofile == DOFILE_TRUE)
		YYABORT;
}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 295 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_eventgen;
}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 301 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 306 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
	(yyval.cmd)->cmd = parser_system;
}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 315 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
	(yyval.cmd)->cmd = parser_echo;
}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 324 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_version;
}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 331 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_osprof_enable;
}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 338 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_osprof_disable;
}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 345 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd = parser_enable_mc;
}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 352 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 357 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd = parser_domultisync;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 366 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 373 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 381 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (1)].list);
}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 385 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;

	list_end->list_next = (yyvsp[(2) - (2)].list);

	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 400 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 407 "parser_gram.y"
    {
	if (((yyval.list) = alloc_list()) == NULL)
			YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 415 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 433 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 450 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add string */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);

}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 468 "parser_gram.y"
    {
	list_t *list = NULL;
	list_t *list_end = NULL;

	/* Add variable */
	if (((yyval.list) = alloc_list()) == NULL)
		YYERROR;

	(yyval.list)->list_string = avd_str_alloc((yyvsp[(2) - (2)].sval));

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].list); list != NULL;
	    list = list->list_next)
		list_end = list;
	list_end->list_next = (yyval.list);
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 485 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 488 "parser_gram.y"
    {
	(yyval.list) = (yyvsp[(1) - (2)].list);
}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 493 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_list;
}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 499 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd = &parser_flowop_list;
}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 504 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_fscheck;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 512 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list->attr_next = (yyvsp[(2) - (2)].attr);
}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 517 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_fsflush;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 526 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_log;
	(yyval.cmd)->cmd_param_list = (yyvsp[(2) - (2)].list);
}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 534 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = NULL;
	filebench_shm->shm_debug_level = (yyvsp[(2) - (2)].ival);
	if (filebench_shm->shm_debug_level > 9)
		yydebug = 1;
}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 546 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_integer((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].ival));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 557 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_boolean((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].bval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 567 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	var_assign_string((yyvsp[(2) - (6)].sval), (yyvsp[(5) - (6)].sval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 67:

/* Line 1455 of yacc.c  */
#line 576 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	var_assign_string((yyvsp[(2) - (4)].sval), (yyvsp[(4) - (4)].sval));

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 68:

/* Line 1455 of yacc.c  */
#line 587 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(6) - (7)].attr);
	(yyval.cmd)->cmd = NULL;

	parser_var_assign_random((yyvsp[(2) - (7)].sval), (yyval.cmd));
}
    break;

  case 69:

/* Line 1455 of yacc.c  */
#line 599 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd_attr_list = (yyvsp[(6) - (7)].attr);
	(yyval.cmd)->cmd = NULL;

	parser_var_assign_custom((yyvsp[(2) - (7)].sval), (yyval.cmd));
}
    break;

  case 70:

/* Line 1455 of yacc.c  */
#line 611 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_TIMEOUT;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 71:

/* Line 1455 of yacc.c  */
#line 621 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_QALLDONE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 72:

/* Line 1455 of yacc.c  */
#line 631 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_shm->shm_rmode = FILEBENCH_MODE_Q1STDONE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 73:

/* Line 1455 of yacc.c  */
#line 641 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	filebench_log(LOG_INFO, "Disabling CPU usage statistics");
	filebench_shm->shm_mmode |= FILEBENCH_MODE_NOUSAGE;

	(yyval.cmd)->cmd = NULL;
}
    break;

  case 74:

/* Line 1455 of yacc.c  */
#line 653 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&parser_statssnap;
	break;

}
    break;

  case 75:

/* Line 1455 of yacc.c  */
#line 661 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&stats_clear;

}
    break;

  case 76:

/* Line 1455 of yacc.c  */
#line 668 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = (void (*)(struct cmd *))&parser_directory;

}
    break;

  case 77:

/* Line 1455 of yacc.c  */
#line 676 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statscmd;

}
    break;

  case 78:

/* Line 1455 of yacc.c  */
#line 684 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsdump;
}
    break;

  case 79:

/* Line 1455 of yacc.c  */
#line 691 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsxmldump;
}
    break;

  case 80:

/* Line 1455 of yacc.c  */
#line 698 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;

	(yyval.cmd)->cmd_param_list = (yyvsp[(3) - (3)].list);
	(yyval.cmd)->cmd = parser_statsmultidump;
}
    break;

  case 81:

/* Line 1455 of yacc.c  */
#line 707 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_filebench_shutdown;
}
    break;

  case 82:

/* Line 1455 of yacc.c  */
#line 714 "parser_gram.y"
    {
	(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
}
    break;

  case 83:

/* Line 1455 of yacc.c  */
#line 717 "parser_gram.y"
    {
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].cmd); list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = (yyvsp[(2) - (2)].cmd);

	filebench_log(LOG_DEBUG_IMPL,
	    "flowop_list adding cmd %zx to list %zx", (yyvsp[(2) - (2)].cmd), (yyvsp[(1) - (2)].cmd));

	(yyval.cmd) = (yyvsp[(1) - (2)].cmd);
}
    break;

  case 84:

/* Line 1455 of yacc.c  */
#line 735 "parser_gram.y"
    {
	/*
	 * Allocate a cmd node per thread, with a
	 * list of flowops attached to the cmd_list
	 */
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_list = (yyvsp[(4) - (5)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(2) - (5)].attr);
}
    break;

  case 85:

/* Line 1455 of yacc.c  */
#line 747 "parser_gram.y"
    {
	(yyval.cmd) = (yyvsp[(1) - (1)].cmd);
}
    break;

  case 86:

/* Line 1455 of yacc.c  */
#line 750 "parser_gram.y"
    {
	cmd_t *list = NULL;
	cmd_t *list_end = NULL;

	/* Find end of list */
	for (list = (yyvsp[(1) - (2)].cmd); list != NULL;
	    list = list->cmd_next)
		list_end = list;

	list_end->cmd_next = (yyvsp[(2) - (2)].cmd);

	filebench_log(LOG_DEBUG_IMPL,
	    "thread_list adding cmd %zx to list %zx", (yyvsp[(2) - (2)].cmd), (yyvsp[(1) - (2)].cmd));

	(yyval.cmd) = (yyvsp[(1) - (2)].cmd);
}
    break;

  case 87:

/* Line 1455 of yacc.c  */
#line 768 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_proc_define;
	(yyval.cmd)->cmd_list = (yyvsp[(5) - (6)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (6)].attr);

}
    break;

  case 88:

/* Line 1455 of yacc.c  */
#line 777 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 89:

/* Line 1455 of yacc.c  */
#line 782 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_file_define;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (3)].attr);
}
    break;

  case 90:

/* Line 1455 of yacc.c  */
#line 790 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_fileset_define;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (3)].attr);
}
    break;

  case 91:

/* Line 1455 of yacc.c  */
#line 800 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_file_import;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (3)].attr);
}
    break;

  case 92:

/* Line 1455 of yacc.c  */
#line 809 "parser_gram.y"
    {
	(yyval.cmd) = alloc_cmd();
	if (!(yyval.cmd))
		YYERROR;

	(yyval.cmd)->cmd = &parser_fileset_import;
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (3)].attr);
}
    break;

  case 93:

/* Line 1455 of yacc.c  */
#line 819 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	switch ((yyvsp[(2) - (2)].ival)) {
	case FSE_PROC:
		(yyval.cmd)->cmd = &parser_proc_create;
		break;
	case FSE_FILESET:
	case FSE_FILE:
		(yyval.cmd)->cmd = &parser_fileset_create;
		break;
	default:
		filebench_log(LOG_ERROR, "unknown entity", (yyvsp[(2) - (2)].ival));
		YYERROR;
	}

}
    break;

  case 94:

/* Line 1455 of yacc.c  */
#line 838 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	switch ((yyvsp[(2) - (2)].ival)) {
	case FSE_PROC:
		(yyval.cmd)->cmd = &parser_proc_shutdown;
		break;
	case FSE_FILE:
	case FSE_FILESET:
		(yyval.cmd)->cmd = &parser_fileset_shutdown;
		break;
	default:
		filebench_log(LOG_ERROR, "unknown entity", (yyvsp[(2) - (2)].ival));
		YYERROR;
	}

}
    break;

  case 95:

/* Line 1455 of yacc.c  */
#line 857 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_warmup;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 96:

/* Line 1455 of yacc.c  */
#line 864 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_warmup_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 97:

/* Line 1455 of yacc.c  */
#line 872 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 98:

/* Line 1455 of yacc.c  */
#line 879 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 99:

/* Line 1455 of yacc.c  */
#line 886 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_sleep;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 100:

/* Line 1455 of yacc.c  */
#line 894 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run;
	(yyval.cmd)->cmd_qty = (yyvsp[(2) - (2)].ival);
}
    break;

  case 101:

/* Line 1455 of yacc.c  */
#line 901 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run_variable;
	(yyval.cmd)->cmd_tgt1 = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 102:

/* Line 1455 of yacc.c  */
#line 908 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_run;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 103:

/* Line 1455 of yacc.c  */
#line 916 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = 0;
	(yyval.cmd)->cmd_qty = 0;
}
    break;

  case 104:

/* Line 1455 of yacc.c  */
#line 924 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (2)].ival);
	(yyval.cmd)->cmd_qty = 0;

}
    break;

  case 105:

/* Line 1455 of yacc.c  */
#line 933 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (2)].ival);
	(yyval.cmd)->cmd_qty = 0;

}
    break;

  case 106:

/* Line 1455 of yacc.c  */
#line 942 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (3)].ival);
	(yyval.cmd)->cmd_qty = (yyvsp[(3) - (3)].ival);
}
    break;

  case 107:

/* Line 1455 of yacc.c  */
#line 950 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = parser_psrun;
	(yyval.cmd)->cmd_qty1 = (yyvsp[(2) - (3)].ival);
	(yyval.cmd)->cmd_qty = (yyvsp[(3) - (3)].ival);
}
    break;

  case 108:

/* Line 1455 of yacc.c  */
#line 959 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd_name = fb_stralloc((yyvsp[(2) - (2)].sval));
}
    break;

  case 109:

/* Line 1455 of yacc.c  */
#line 965 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 110:

/* Line 1455 of yacc.c  */
#line 969 "parser_gram.y"
    {(yyval.ival) = FSE_PROC;}
    break;

  case 111:

/* Line 1455 of yacc.c  */
#line 970 "parser_gram.y"
    {(yyval.ival) = FSE_THREAD;}
    break;

  case 112:

/* Line 1455 of yacc.c  */
#line 971 "parser_gram.y"
    {(yyval.ival) = FSE_FILESET;}
    break;

  case 113:

/* Line 1455 of yacc.c  */
#line 972 "parser_gram.y"
    {(yyval.ival) = FSE_FILE;}
    break;

  case 115:

/* Line 1455 of yacc.c  */
#line 978 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 116:

/* Line 1455 of yacc.c  */
#line 982 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 117:

/* Line 1455 of yacc.c  */
#line 995 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 118:

/* Line 1455 of yacc.c  */
#line 999 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 119:

/* Line 1455 of yacc.c  */
#line 1012 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 120:

/* Line 1455 of yacc.c  */
#line 1017 "parser_gram.y"
    {
	(yyval.attr) = alloc_attr();
	if (!(yyval.attr))
		YYERROR;

	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 121:

/* Line 1455 of yacc.c  */
#line 1026 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 122:

/* Line 1455 of yacc.c  */
#line 1031 "parser_gram.y"
    {
	(yyval.attr) = alloc_attr();
	if (!(yyval.attr))
		YYERROR;

	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 123:

/* Line 1455 of yacc.c  */
#line 1041 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 124:

/* Line 1455 of yacc.c  */
#line 1045 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 125:

/* Line 1455 of yacc.c  */
#line 1058 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 126:

/* Line 1455 of yacc.c  */
#line 1062 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr; attr = attr->attr_next)
		list_end = attr;

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 127:

/* Line 1455 of yacc.c  */
#line 1075 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 128:

/* Line 1455 of yacc.c  */
#line 1080 "parser_gram.y"
    {
	(yyval.attr) = alloc_attr();
	if (!(yyval.attr))
		YYERROR;

	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 129:

/* Line 1455 of yacc.c  */
#line 1089 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 130:

/* Line 1455 of yacc.c  */
#line 1094 "parser_gram.y"
    {
	(yyval.attr) = alloc_attr();
	if (!(yyval.attr))
		YYERROR;

	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 131:

/* Line 1455 of yacc.c  */
#line 1104 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 132:

/* Line 1455 of yacc.c  */
#line 1108 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 133:

/* Line 1455 of yacc.c  */
#line 1121 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (7)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	
	if ((attr = alloc_attr()) == NULL)
		YYERROR;

	attr->attr_name = FSA_RANDTABLE;
	attr->attr_obj = (void *)(yyvsp[(6) - (7)].rndtb);
	list_end->attr_next = attr;
	(yyval.attr) = (yyvsp[(1) - (7)].attr);
}
    break;

  case 134:

/* Line 1455 of yacc.c  */
#line 1140 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 135:

/* Line 1455 of yacc.c  */
#line 1145 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 136:

/* Line 1455 of yacc.c  */
#line 1151 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_TYPE;
}
    break;

  case 137:

/* Line 1455 of yacc.c  */
#line 1156 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_RANDSRC;
}
    break;

  case 138:

/* Line 1455 of yacc.c  */
#line 1162 "parser_gram.y"
    {
	if (((yyval.rndtb) = alloc_probtabent()) == NULL)
		YYERROR;
	(yyval.rndtb)->pte_percent = (yyvsp[(2) - (7)].avd);
	(yyval.rndtb)->pte_segmin  = (yyvsp[(4) - (7)].avd);
	(yyval.rndtb)->pte_segmax  = (yyvsp[(6) - (7)].avd);
}
    break;

  case 139:

/* Line 1455 of yacc.c  */
#line 1172 "parser_gram.y"
    {
	(yyval.rndtb) = (yyvsp[(1) - (1)].rndtb);
}
    break;

  case 140:

/* Line 1455 of yacc.c  */
#line 1176 "parser_gram.y"
    {
	probtabent_t *pte = NULL;
	probtabent_t *ptelist_end = NULL;

	for (pte = (yyvsp[(1) - (3)].rndtb); pte != NULL;
	    pte = pte->pte_next)
		ptelist_end = pte; /* Find end of prob table entry list */

	ptelist_end->pte_next = (yyvsp[(3) - (3)].rndtb);

	(yyval.rndtb) = (yyvsp[(1) - (3)].rndtb);
}
    break;

  case 141:

/* Line 1455 of yacc.c  */
#line 1191 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 142:

/* Line 1455 of yacc.c  */
#line 1195 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 143:

/* Line 1455 of yacc.c  */
#line 1209 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 144:

/* Line 1455 of yacc.c  */
#line 1214 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 145:

/* Line 1455 of yacc.c  */
#line 1222 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 146:

/* Line 1455 of yacc.c  */
#line 1226 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 147:

/* Line 1455 of yacc.c  */
#line 1240 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 148:

/* Line 1455 of yacc.c  */
#line 1245 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 149:

/* Line 1455 of yacc.c  */
#line 1253 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 150:

/* Line 1455 of yacc.c  */
#line 1257 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 151:

/* Line 1455 of yacc.c  */
#line 1270 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 152:

/* Line 1455 of yacc.c  */
#line 1284 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 153:

/* Line 1455 of yacc.c  */
#line 1289 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 154:

/* Line 1455 of yacc.c  */
#line 1297 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 155:

/* Line 1455 of yacc.c  */
#line 1301 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 156:

/* Line 1455 of yacc.c  */
#line 1315 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 157:

/* Line 1455 of yacc.c  */
#line 1320 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_name = (yyvsp[(1) - (1)].ival);
}
    break;

  case 158:

/* Line 1455 of yacc.c  */
#line 1328 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 159:

/* Line 1455 of yacc.c  */
#line 1332 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 160:

/* Line 1455 of yacc.c  */
#line 1346 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 161:

/* Line 1455 of yacc.c  */
#line 1352 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = FSA_VALUE;
}
    break;

  case 162:

/* Line 1455 of yacc.c  */
#line 1358 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_str_alloc((yyvsp[(3) - (3)].sval));
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 165:

/* Line 1455 of yacc.c  */
#line 1370 "parser_gram.y"
    { (yyval.ival) = FSA_NICE;}
    break;

  case 166:

/* Line 1455 of yacc.c  */
#line 1371 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 167:

/* Line 1455 of yacc.c  */
#line 1372 "parser_gram.y"
    { (yyval.ival) = FSA_INSTANCES;}
    break;

  case 168:

/* Line 1455 of yacc.c  */
#line 1375 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 169:

/* Line 1455 of yacc.c  */
#line 1376 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 170:

/* Line 1455 of yacc.c  */
#line 1377 "parser_gram.y"
    { (yyval.ival) = FSA_SIZE;}
    break;

  case 171:

/* Line 1455 of yacc.c  */
#line 1378 "parser_gram.y"
    { (yyval.ival) = FSA_PREALLOC;}
    break;

  case 172:

/* Line 1455 of yacc.c  */
#line 1379 "parser_gram.y"
    { (yyval.ival) = FSA_PARALLOC;}
    break;

  case 173:

/* Line 1455 of yacc.c  */
#line 1380 "parser_gram.y"
    { (yyval.ival) = FSA_REUSE;}
    break;

  case 174:

/* Line 1455 of yacc.c  */
#line 1381 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY;}
    break;

  case 175:

/* Line 1455 of yacc.c  */
#line 1382 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE;}
    break;

  case 176:

/* Line 1455 of yacc.c  */
#line 1383 "parser_gram.y"
    { (yyval.ival) = FSA_CACHED;}
    break;

  case 177:

/* Line 1455 of yacc.c  */
#line 1384 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY;}
    break;

  case 178:

/* Line 1455 of yacc.c  */
#line 1387 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 179:

/* Line 1455 of yacc.c  */
#line 1388 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 180:

/* Line 1455 of yacc.c  */
#line 1389 "parser_gram.y"
    { (yyval.ival) = FSA_ENTRIES;}
    break;

  case 181:

/* Line 1455 of yacc.c  */
#line 1390 "parser_gram.y"
    { (yyval.ival) = FSA_SIZE;}
    break;

  case 182:

/* Line 1455 of yacc.c  */
#line 1391 "parser_gram.y"
    { (yyval.ival) = FSA_DIRWIDTH;}
    break;

  case 183:

/* Line 1455 of yacc.c  */
#line 1392 "parser_gram.y"
    { (yyval.ival) = FSA_DIRDEPTHRV;}
    break;

  case 184:

/* Line 1455 of yacc.c  */
#line 1393 "parser_gram.y"
    { (yyval.ival) = FSA_PREALLOC;}
    break;

  case 185:

/* Line 1455 of yacc.c  */
#line 1394 "parser_gram.y"
    { (yyval.ival) = FSA_PARALLOC;}
    break;

  case 186:

/* Line 1455 of yacc.c  */
#line 1395 "parser_gram.y"
    { (yyval.ival) = FSA_REUSE;}
    break;

  case 187:

/* Line 1455 of yacc.c  */
#line 1396 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY;}
    break;

  case 188:

/* Line 1455 of yacc.c  */
#line 1397 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE;}
    break;

  case 189:

/* Line 1455 of yacc.c  */
#line 1398 "parser_gram.y"
    { (yyval.ival) = FSA_DIRGAMMA;}
    break;

  case 190:

/* Line 1455 of yacc.c  */
#line 1399 "parser_gram.y"
    { (yyval.ival) = FSA_CACHED;}
    break;

  case 191:

/* Line 1455 of yacc.c  */
#line 1400 "parser_gram.y"
    { (yyval.ival) = FSA_LEAFDIRS;}
    break;

  case 192:

/* Line 1455 of yacc.c  */
#line 1401 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY;}
    break;

  case 193:

/* Line 1455 of yacc.c  */
#line 1404 "parser_gram.y"
    { (yyval.ival) = FSA_NAME; }
    break;

  case 194:

/* Line 1455 of yacc.c  */
#line 1405 "parser_gram.y"
    { (yyval.ival) = FSA_PATH; }
    break;

  case 195:

/* Line 1455 of yacc.c  */
#line 1406 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY; }
    break;

  case 196:

/* Line 1455 of yacc.c  */
#line 1407 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE; }
    break;

  case 197:

/* Line 1455 of yacc.c  */
#line 1408 "parser_gram.y"
    { (yyval.ival) = FSA_CACHED; }
    break;

  case 198:

/* Line 1455 of yacc.c  */
#line 1409 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY; }
    break;

  case 199:

/* Line 1455 of yacc.c  */
#line 1412 "parser_gram.y"
    { (yyval.ival) = FSA_NAME; }
    break;

  case 200:

/* Line 1455 of yacc.c  */
#line 1413 "parser_gram.y"
    { (yyval.ival) = FSA_PATH; }
    break;

  case 201:

/* Line 1455 of yacc.c  */
#line 1414 "parser_gram.y"
    { (yyval.ival) = FSA_ENTRIES; }
    break;

  case 202:

/* Line 1455 of yacc.c  */
#line 1415 "parser_gram.y"
    { (yyval.ival) = FSA_SIZE; }
    break;

  case 203:

/* Line 1455 of yacc.c  */
#line 1416 "parser_gram.y"
    { (yyval.ival) = FSA_PREALLOC; }
    break;

  case 204:

/* Line 1455 of yacc.c  */
#line 1417 "parser_gram.y"
    { (yyval.ival) = FSA_READONLY; }
    break;

  case 205:

/* Line 1455 of yacc.c  */
#line 1418 "parser_gram.y"
    { (yyval.ival) = FSA_TRUSTTREE; }
    break;

  case 206:

/* Line 1455 of yacc.c  */
#line 1419 "parser_gram.y"
    { (yyval.ival) = FSA_CACHED; }
    break;

  case 207:

/* Line 1455 of yacc.c  */
#line 1420 "parser_gram.y"
    { (yyval.ival) = FSA_LEAFDIRS; }
    break;

  case 208:

/* Line 1455 of yacc.c  */
#line 1421 "parser_gram.y"
    { (yyval.ival) = FSA_WRITEONLY; }
    break;

  case 209:

/* Line 1455 of yacc.c  */
#line 1424 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 210:

/* Line 1455 of yacc.c  */
#line 1425 "parser_gram.y"
    { (yyval.ival) = FSA_RANDSEED;}
    break;

  case 211:

/* Line 1455 of yacc.c  */
#line 1426 "parser_gram.y"
    { (yyval.ival) = FSA_RANDGAMMA;}
    break;

  case 212:

/* Line 1455 of yacc.c  */
#line 1427 "parser_gram.y"
    { (yyval.ival) = FSA_RANDMEAN;}
    break;

  case 213:

/* Line 1455 of yacc.c  */
#line 1428 "parser_gram.y"
    { (yyval.ival) = FSA_MIN;}
    break;

  case 214:

/* Line 1455 of yacc.c  */
#line 1429 "parser_gram.y"
    { (yyval.ival) = FSA_ROUND;}
    break;

  case 215:

/* Line 1455 of yacc.c  */
#line 1432 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 216:

/* Line 1455 of yacc.c  */
#line 1439 "parser_gram.y"
    { (yyval.ival) = FSV_RANDUNI;}
    break;

  case 217:

/* Line 1455 of yacc.c  */
#line 1440 "parser_gram.y"
    { (yyval.ival) = FSV_RANDTAB;}
    break;

  case 218:

/* Line 1455 of yacc.c  */
#line 1441 "parser_gram.y"
    { (yyval.ival) = FSA_RANDGAMMA;}
    break;

  case 219:

/* Line 1455 of yacc.c  */
#line 1444 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 220:

/* Line 1455 of yacc.c  */
#line 1451 "parser_gram.y"
    { (yyval.ival) = FSV_URAND;}
    break;

  case 221:

/* Line 1455 of yacc.c  */
#line 1452 "parser_gram.y"
    { (yyval.ival) = FSV_RAND48;}
    break;

  case 222:

/* Line 1455 of yacc.c  */
#line 1455 "parser_gram.y"
    { (yyval.ival) = FSA_TYPE;}
    break;

  case 223:

/* Line 1455 of yacc.c  */
#line 1456 "parser_gram.y"
    { (yyval.ival) = FSA_PARAMETERS;}
    break;

  case 224:

/* Line 1455 of yacc.c  */
#line 1457 "parser_gram.y"
    { (yyval.ival) = FSA_MIN;}
    break;

  case 225:

/* Line 1455 of yacc.c  */
#line 1458 "parser_gram.y"
    { (yyval.ival) = FSA_MAX;}
    break;

  case 226:

/* Line 1455 of yacc.c  */
#line 1459 "parser_gram.y"
    { (yyval.ival) = FSA_ROUND;}
    break;

  case 227:

/* Line 1455 of yacc.c  */
#line 1462 "parser_gram.y"
    { (yyval.ival) = FSA_PROCESS;}
    break;

  case 228:

/* Line 1455 of yacc.c  */
#line 1463 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 229:

/* Line 1455 of yacc.c  */
#line 1464 "parser_gram.y"
    { (yyval.ival) = FSA_MEMSIZE;}
    break;

  case 230:

/* Line 1455 of yacc.c  */
#line 1465 "parser_gram.y"
    { (yyval.ival) = FSA_USEISM;}
    break;

  case 231:

/* Line 1455 of yacc.c  */
#line 1466 "parser_gram.y"
    { (yyval.ival) = FSA_INSTANCES;}
    break;

  case 232:

/* Line 1455 of yacc.c  */
#line 1467 "parser_gram.y"
    { (yyval.ival) = FSA_IOPRIO;}
    break;

  case 233:

/* Line 1455 of yacc.c  */
#line 1470 "parser_gram.y"
    { (yyval.ival) = FSA_WSS;}
    break;

  case 234:

/* Line 1455 of yacc.c  */
#line 1471 "parser_gram.y"
    { (yyval.ival) = FSA_FILE;}
    break;

  case 235:

/* Line 1455 of yacc.c  */
#line 1472 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 236:

/* Line 1455 of yacc.c  */
#line 1473 "parser_gram.y"
    { (yyval.ival) = FSA_RANDOM;}
    break;

  case 237:

/* Line 1455 of yacc.c  */
#line 1474 "parser_gram.y"
    { (yyval.ival) = FSA_FD;}
    break;

  case 238:

/* Line 1455 of yacc.c  */
#line 1475 "parser_gram.y"
    { (yyval.ival) = FSA_SRCFD;}
    break;

  case 239:

/* Line 1455 of yacc.c  */
#line 1476 "parser_gram.y"
    { (yyval.ival) = FSA_ROTATEFD;}
    break;

  case 240:

/* Line 1455 of yacc.c  */
#line 1477 "parser_gram.y"
    { (yyval.ival) = FSA_DSYNC;}
    break;

  case 241:

/* Line 1455 of yacc.c  */
#line 1478 "parser_gram.y"
    { (yyval.ival) = FSA_DIRECTIO;}
    break;

  case 242:

/* Line 1455 of yacc.c  */
#line 1479 "parser_gram.y"
    { (yyval.ival) = FSA_INDEXED;}
    break;

  case 243:

/* Line 1455 of yacc.c  */
#line 1480 "parser_gram.y"
    { (yyval.ival) = FSA_TARGET;}
    break;

  case 244:

/* Line 1455 of yacc.c  */
#line 1481 "parser_gram.y"
    { (yyval.ival) = FSA_ITERS;}
    break;

  case 245:

/* Line 1455 of yacc.c  */
#line 1482 "parser_gram.y"
    { (yyval.ival) = FSA_VALUE;}
    break;

  case 246:

/* Line 1455 of yacc.c  */
#line 1483 "parser_gram.y"
    { (yyval.ival) = FSA_BLOCKING;}
    break;

  case 247:

/* Line 1455 of yacc.c  */
#line 1484 "parser_gram.y"
    { (yyval.ival) = FSA_HIGHWATER;}
    break;

  case 248:

/* Line 1455 of yacc.c  */
#line 1485 "parser_gram.y"
    { (yyval.ival) = FSA_IOSIZE;}
    break;

  case 249:

/* Line 1455 of yacc.c  */
#line 1486 "parser_gram.y"
    { (yyval.ival) = FSA_NOREADAHEAD;}
    break;

  case 250:

/* Line 1455 of yacc.c  */
#line 1489 "parser_gram.y"
    { (yyval.ival) = FSA_RATE;}
    break;

  case 251:

/* Line 1455 of yacc.c  */
#line 1492 "parser_gram.y"
    { (yyval.ival) = FSA_MASTER;}
    break;

  case 252:

/* Line 1455 of yacc.c  */
#line 1493 "parser_gram.y"
    { (yyval.ival) = FSA_CLIENT;}
    break;

  case 253:

/* Line 1455 of yacc.c  */
#line 1496 "parser_gram.y"
    { (yyval.ival) = FSA_PATH;}
    break;

  case 254:

/* Line 1455 of yacc.c  */
#line 1497 "parser_gram.y"
    { (yyval.ival) = FSA_FSTYPE;}
    break;

  case 255:

/* Line 1455 of yacc.c  */
#line 1500 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 256:

/* Line 1455 of yacc.c  */
#line 1504 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 257:

/* Line 1455 of yacc.c  */
#line 1517 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 258:

/* Line 1455 of yacc.c  */
#line 1531 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 259:

/* Line 1455 of yacc.c  */
#line 1537 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_boolean((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].bval)))) == NULL)
		YYERROR;
}
    break;

  case 260:

/* Line 1455 of yacc.c  */
#line 1542 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_integer((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].ival)))) == NULL)
		YYERROR;
}
    break;

  case 261:

/* Line 1455 of yacc.c  */
#line 1547 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_string((yyvsp[(1) - (5)].sval), (yyvsp[(4) - (5)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 262:

/* Line 1455 of yacc.c  */
#line 1552 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_string((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 263:

/* Line 1455 of yacc.c  */
#line 1557 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_assign_var((yyvsp[(1) - (3)].sval), (yyvsp[(3) - (3)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 264:

/* Line 1455 of yacc.c  */
#line 1562 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_lvar_attr(var_lvar_alloc_local((yyvsp[(1) - (1)].sval)))) == NULL)
		YYERROR;
}
    break;

  case 265:

/* Line 1455 of yacc.c  */
#line 1568 "parser_gram.y"
    {
	if (((yyval.cmd) = alloc_cmd()) == NULL)
		YYERROR;
	(yyval.cmd)->cmd = &parser_composite_flowop_define;
	(yyval.cmd)->cmd_list = (yyvsp[(5) - (6)].cmd);
	(yyval.cmd)->cmd_attr_list = (yyvsp[(3) - (6)].attr);
}
    break;

  case 266:

/* Line 1455 of yacc.c  */
#line 1576 "parser_gram.y"
    {
	(yyvsp[(1) - (2)].cmd)->cmd_attr_list = (yyvsp[(2) - (2)].attr);
}
    break;

  case 267:

/* Line 1455 of yacc.c  */
#line 1582 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(1) - (1)].attr);
}
    break;

  case 268:

/* Line 1455 of yacc.c  */
#line 1586 "parser_gram.y"
    {
	attr_t *attr = NULL;
	attr_t *list_end = NULL;

	for (attr = (yyvsp[(1) - (3)].attr); attr != NULL;
	    attr = attr->attr_next)
		list_end = attr; /* Find end of list */

	list_end->attr_next = (yyvsp[(3) - (3)].attr);

	(yyval.attr) = (yyvsp[(1) - (3)].attr);
}
    break;

  case 269:

/* Line 1455 of yacc.c  */
#line 1600 "parser_gram.y"
    {
	(yyval.attr) = (yyvsp[(3) - (3)].attr);
	(yyval.attr)->attr_name = (yyvsp[(1) - (3)].ival);
}
    break;

  case 270:

/* Line 1455 of yacc.c  */
#line 1606 "parser_gram.y"
    { (yyval.ival) = FSA_NAME;}
    break;

  case 271:

/* Line 1455 of yacc.c  */
#line 1607 "parser_gram.y"
    { (yyval.ival) = FSA_ITERS;}
    break;

  case 272:

/* Line 1455 of yacc.c  */
#line 1610 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_str_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 273:

/* Line 1455 of yacc.c  */
#line 1614 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 274:

/* Line 1455 of yacc.c  */
#line 1618 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_bool_alloc((yyvsp[(1) - (1)].bval));
}
    break;

  case 275:

/* Line 1455 of yacc.c  */
#line 1622 "parser_gram.y"
    {
	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_var_alloc((yyvsp[(1) - (1)].sval));
}
    break;

  case 276:

/* Line 1455 of yacc.c  */
#line 1626 "parser_gram.y"
    {
	avd_t obj;

	if (((yyval.attr) = alloc_attr()) == NULL)
		YYERROR;
	(yyval.attr)->attr_avd = avd_var_alloc((yyvsp[(1) - (2)].sval));
	obj = avd_str_alloc((yyvsp[(2) - (2)].sval));
	(yyval.attr)->attr_obj = (void*) &obj;
}
    break;

  case 277:

/* Line 1455 of yacc.c  */
#line 1637 "parser_gram.y"
    {
	(yyval.avd) = avd_int_alloc((yyvsp[(1) - (1)].ival));
}
    break;

  case 278:

/* Line 1455 of yacc.c  */
#line 1640 "parser_gram.y"
    {
	(yyval.avd) = avd_var_alloc((yyvsp[(1) - (1)].sval));
}
    break;



/* Line 1455 of yacc.c  */
#line 4704 "parser_gram.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1644 "parser_gram.y"


/*
 * The following C routines implement the various commands defined in the above
 * yacc parser code. The yacc portion checks the syntax of the commands found in
 * a workload file (or typed interactively) and parses the commands' parameters
 * into lists. The lists are then passed in a cmd_t struct for each command to
 * its related routine in the following section for actual execution.  This
 * section also includes a few utility routines and the main entry point for the
 * program.
 */

#define	USAGE1	\
"Usage:\n" \
"filebench: interprets WML script and generates apporpriate workload\n" \
"Options:\n" \
"   [-h] Display verbose help\n" \
"   [-f <filename>] use specified file as an input instead of stdin\n"

#define	PARSER_CMDS \
"create [files|filesets|processes]\n" \
"stats [clear|snap]\n" \
"stats command \"shell command $var1,$var2...\"\n" \
"stats directory <directory>\n" \
"sleep <sleep-value>\n" \
"quit\n\n" \
"Variables:\n" \
"set $var = value\n" \
"    $var   - regular variables\n" \
"    ${var} - internal special variables\n" \
"    $(var) - environment variables\n\n"

#define	PARSER_EXAMPLE \
"Example:\n\n" \
"#!" FILEBENCHDIR "/bin/filebench -f\n" \
"\n" \
"define file name=bigfile,path=bigfile,size=1g,prealloc,reuse\n" \
"define process name=randomizer\n" \
"{\n" \
"  thread random-thread procname=randomizer\n"	\
"  {\n" \
"    flowop read name=random-read,filename=bigfile,iosize=16k,random\n" \
"  }\n" \
"}\n" \
"create files\n" \
"create processes\n" \
"stats clear\n" \
"sleep 30\n" \
"stats snap\n"

/*
 * Displays brief or verbose help for Filebench.
 */
static void
usage(int help)
{
	if (help >= 1)
		(void) fprintf(stderr, USAGE1);

	if (help >= 2) {
		(void) fprintf(stderr,
		    "\n'f' language definition:\n\n");
		fileset_usage();
		procflow_usage();
		threadflow_usage();
		flowoplib_usage();
		eventgen_usage();
		(void) fprintf(stderr, PARSER_CMDS);
		(void) fprintf(stderr, PARSER_EXAMPLE);
	}

	exit(1);
}

/*
 * mmap() call with MAP_FIXED argument does not guarantee
 * that the allocated memory region is not overlapped with
 * the previously existant mappings. According to POSIX, old mappings
 * are just disregarded. There is no generic way to detect
 * overlap. If overlap occurs strange runtime errors might happen,
 * because we might overlap stack, libraries, anything else.
 *
 * Since we always fork+exec same binary (filebench), theoretically
 * all the mappings should be the same, so no overlap should happen.
 * However, if virtual address space randomization is enabled on the target
 * machine - overlap is very likely (especially if workload defines a lot of
 * processes).  We observed numerous segmentation faults on CentOS because of
 * that.
 *
 * The function below checks if virtual address space randomization is
 * enabled on Linux. In case it is enabled, we print a warning and continue
 * execution.
 */
static void
check_va_randomization()
{
	char buf[4];
	int val;
	int ret;
	int fd;

	fd = open("/proc/sys/kernel/randomize_va_space", O_RDONLY);
	if (fd == -1) {
		/*
		 * probably this file just doesn't exist, so we conclude that the
		 * system does not support virtual address space randomization
		 * and silently return.
		 */
		return;
	}

	ret = read(fd, buf, sizeof(buf));
	if (ret == -1) {
		filebench_log(LOG_FATAL, "Coud not read from "
			"/proc/sys/kernel/randomize_va_space file!");
		return;
	}

	sscanf(buf, "%d", &val);
	if (val != 0) {
		filebench_log(LOG_FATAL, "IMPORTANT: Virtual address space "
			"randomization is enabled on this machine!\n"
			"It is highly recommended to disable randomization "
			"to provide stable Filebench runs.\n"
			"Echo 0 to /proc/sys/kernel/randomize_va_space file "
			"to disable the randomization.");

	}
}

#ifdef HAVE_PROC_SYS_KERNEL_SHMMAX
/*
 * Increase the maximum shared memory segment size till some large value.  We do
 * not restore it to the old value when the Filebench run is over. If we could
 * not change the value - we continue execution.
 */
void
fb_set_shmmax(void)
{
	FILE *f;
	int ret;

	f = fopen("/proc/sys/kernel/shmmax", "r+");
	if (!f) {
		filebench_log(LOG_FATAL, "WARNING: Could not open "
				"/proc/sys/kernel/shmmax file!\n"
				"It means that you probably ran Filebench not "
				"as a root. Filebench will not increase shared\n"
				"region limits in this case, which can lead "
				"to the failures on certain workloads.");
		return; 
	}

	/* writing new value */
#define SOME_LARGE_SHMAX "268435456" /* 256 MB */
	ret = fwrite(SOME_LARGE_SHMAX, sizeof(SOME_LARGE_SHMAX), 1, f);
	if (ret != 1) 
		filebench_log(LOG_ERROR, "Coud not write to "
				"/proc/sys/kernel/shmmax file!");
#undef SOME_LARGE_SHMAX

	return;
}
#else /* HAVE_PROC_SYS_KERNEL_SHMMAX */
void
fb_set_shmmax(void)
{
	return;
}
#endif /* HAVE_PROC_SYS_KERNEL_SHMMAX */

#ifdef HAVE_SETRLIMIT
/*
 * Increase the limit of opened files.
 *
 * We first set the limit to the hardlimit reported by the kernel; this call
 * will always succeed.  Then we try to set the limit to some large number of
 * files (unfortunately we can't set this ulimit to infinity), this will only
 * succeed if the process is ran by root.  Therefore, we always set the maximum
 * possible value for the limit for this given process (well, only if hardlimit
 * is greater then the large number of files defined by us, it is not true).
 *
 * Increasing this limit is especially important when we use thread model,
 * because opened files are accounted per-process, not per-thread.
 */
void
fb_set_rlimit(void)
{
	struct rlimit rlp;

	(void)getrlimit(RLIMIT_NOFILE, &rlp);
	rlp.rlim_cur = rlp.rlim_max;
	(void)setrlimit(RLIMIT_NOFILE, &rlp);
#define SOME_LARGE_NUMBER_OF_FILES 50000
	rlp.rlim_cur = rlp.rlim_max = SOME_LARGE_NUMBER_OF_FILES;
#undef SOME_LARGE_NUMBER_OF_FILES
	(void)setrlimit(RLIMIT_NOFILE, &rlp);
	return;
}
#else /* HAVE_SETRLIMIT */
void
fb_set_rlimit(void)
{
	return;
}
#endif /* HAVE_SETRLIMIT */

/*
 * Entry point for Filebench. Processes command line arguments. The -f option
 * will read in a workload file (the full name and extension must must be
 * given). The -a, -s, -m and -i options are used by the worker process to
 * receive the name, the base address of shared memory, its path, and the
 * process' instance number, respectively. This information is supplied by the
 * master process when it execs worker processes. If the worker process
 * arguments are passed then main will call the procflow_exec() routine which
 * creates worker threadflows and flowops and executes the procflow's portion of
 * the workload model until completion. If worker process arguments are not
 * passed to the process, then it becomes the master process for a filebench
 * run. It initializes the various filebench components and either executes the
 * supplied workload file, or enters interactive mode.
 */
int
main(int argc, char *argv[])
{
	const char cmd_options[] = "m:s:a:i:hf:c:";
	int opt;
	char *procname = NULL;
	int instance;
	void *shmaddr;
	char *cwdret;
	char *fscriptname = NULL;
#ifdef HAVE_LIBTECLA
	char *line;
#else /* HAVE_LIBTECLA */
	char line[1024];
#endif
	int ret;
	int ls_cvars = 0;
	char *cvar_type = NULL;

 	/*
	 * We don't want getopt() to print error messages because
	 * sometimes what it percieves as an error is actually not
	 * an error.  For example, "-c" option might have or might
	 * not have an argument.  If opterr is non-zero, getopt()
	 * prints an error message when "-c"'s argument is missing.
	 */
	opterr = 0;

	 /* parsing the parameters */
	while ((opt = getopt(argc, argv, cmd_options)) > 0) {
		switch (opt) {
		/* public parameters */
		case 'h':
			usage(2);
			break;
		case 'c':	/* list cvar types or their parameters */
			cvar_type = optarg;
			ls_cvars = 1;
			break;
		case 'f':
			if (!optarg)
				usage(1);

			yyin = fopen(optarg, "r");
			if (!yyin) {
				filebench_log(LOG_FATAL,
				    "Cannot open file %s!", optarg);
				exit(1);
			}

			dofile = DOFILE_TRUE;
			fscriptname = optarg;
			break;
		/* private parameters: when filebench calls itself */
		case 'a':
			if (!optarg)
				usage(1);

			procname = optarg;
			break;
		case 's':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%p", &shmaddr);
			break;
		case 'm':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%s", shmpath);
			break;
		case 'i':
			if (!optarg)
				usage(1);
			sscanf(optarg, "%d", &instance);
			break;
		case '?':
			if (optopt == 'c') {
				ls_cvars = 1;
				break;
			}
		default:
			usage(1);
			break;
		}
	}

	/*
	 * Init things common to all processes: master and workers
	 */
	my_pid = getpid();
	fb_set_rlimit();
	fb_urandom_init();
	clock_init();

	if (procname) {
		/* A child Filebench instance */
		if (ipc_attach(shmaddr) < 0) {
			filebench_log(LOG_FATAL, "Cannot attach shm for %s",
			    procname);
			exit(1);
		}
		
		/* get correct function pointer for each working process */
		filebench_plugin_funcvecinit();
		
		/* Load custom variable libraries and re-validate handles. */
		ret = init_cvar_libraries();
		if (ret)
			exit(1);

		ret = revalidate_cvar_handles();
		if (ret)
			exit(1);

		/* execute corresponding procflow */
		if (procflow_exec(procname, instance) < 0) {
			filebench_log(LOG_FATAL, "Cannot startup process %s",
			    procname);
			exit(1);
		}

		exit(0);
	}

	/*
	 * Master process
	 */
	printf("Filebench Version %s\n", FILEBENCH_VERSION);
	check_va_randomization();

	/* saving executable name to exec it later as worker processes */
	execname = argv[0];

	/* saving current working directory */
	cwdret = getcwd(cwd, MAXPATHLEN);
	if (cwdret != cwd) {
		filebench_log(LOG_FATAL, "Cannot save current "
					 "working directory!");
		exit(1);
	}

	fb_set_shmmax();

	ipc_init();

	if (fscriptname)
		(void)strcpy(filebench_shm->shm_fscriptname, fscriptname);

	flowop_init();
	stats_init();
	eventgen_init();
	
	/* Initialize custom variables. */
	ret = init_cvar_library_info(FILEBENCHDIR "/cvars");
	if (ret)
		filebench_shutdown(1);

	ret = init_cvar_libraries();
	if (ret)
		filebench_shutdown(1);

	if (ls_cvars) {
		if (cvar_type)
			parser_list_cvar_type_parameters(cvar_type);
		else
			parser_list_cvar_types();
		exit(1);
	}

	signal(SIGINT, parser_abort);

	if (dofile == DOFILE_TRUE)
		yyparse();
	else {
#ifdef HAVE_LIBTECLA
		if ((gl = new_GetLine(MAX_LINE_LEN, MAX_CMD_HIST)) == NULL) {
			filebench_log(LOG_ERROR,
			    "Failed to create GetLine object");
			filebench_shutdown(1);
		}

		if (gl_customize_completion(gl, NULL, command_complete)) {
			filebench_log(LOG_ERROR,
			    "Failed to register auto-completion function");
			filebench_shutdown(1);
		}

		while ((line = gl_get_line(gl, FILEBENCH_PROMPT, NULL, -1))) {
			arg_parse(line);
			yyparse();
		}

		del_GetLine(gl);
#else
		while (!feof(stdin)) {
			printf(FILEBENCH_PROMPT);
			fflush(stdout);
			if (fgets(line, sizeof (line), stdin) == NULL) {
				if (errno == EINTR)
					continue;
				else
					break;
			}
			arg_parse(line);
			yyparse();
		}
		printf("\n");
#endif	/* HAVE_LIBTECLA */
	}

	parser_filebench_shutdown((cmd_t *)0);

	return 0;
}

/*
 * arg_parse() puts the parser into command parsing mode. Create a tmpfile
 * and instruct the parser to read instructions from this location by setting
 * yyin to the value returned by tmpfile. Write the command into the file.
 * Then seek back to to the start of the file so that the parser can read
 * the instructions.
 */
static void
arg_parse(const char *command)
{
	if ((yyin = tmpfile()) == NULL) {
		filebench_log(LOG_FATAL,
		    "Exiting: Cannot create tmpfile: %s", strerror(errno));
		exit(1);
	}

	if (fwrite(command, strlen(command), 1, yyin) != 1)
		filebench_log(LOG_FATAL,
		    "Cannot write tmpfile: %s", strerror(errno));

	if (fseek(yyin, 0, SEEK_SET) != 0)
		filebench_log(LOG_FATAL,
		    "Cannot seek tmpfile: %s", strerror(errno));
}

/*
 * Converts a list of var_strings or ordinary strings to a single ordinary
 * string. It returns a pointer to the string (in malloc'd memory) if found,
 * or NULL otherwise.
 */
char *
parser_list2string(list_t *list)
{
	list_t *l;
	char *string;
	char *tmp;

	string = malloc(MAXPATHLEN);
	if (!string) {
		filebench_log(LOG_ERROR, "Failed to allocate memory");
		return NULL;
	}

	*string = 0;

	/* Format args */
	for (l = list; l != NULL; l = l->list_next) {

		char *lstr = avd_get_str(l->list_string);

		filebench_log(LOG_DEBUG_SCRIPT, "converting string '%s'", lstr);

		/* see if it is a random variable */
		if (l->list_integer) {
			fbint_t param_name;

			tmp = NULL;
			param_name = avd_get_int(l->list_integer);

			switch (param_name) {
			case FSS_TYPE:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_TYPE);
				break;

			case FSS_SRC:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SRC);
				break;

			case FSS_SEED:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_SEED);
				break;

			case FSS_MIN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MIN);
				break;

			case FSS_MEAN:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_MEAN);
				break;

			case FSS_GAMMA:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_GAMMA);
				break;

			case FSS_ROUND:
				tmp = var_randvar_to_string(lstr,
				    RAND_PARAM_ROUND);
				break;
			}

			if (tmp) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		} else {
			/* perhaps a normal variable? */
			if ((tmp = var_to_string(lstr)) != NULL) {
				(void) strcat(string, tmp);
				free(tmp);
			} else {
				(void) strcat(string, lstr);
			}
		}
	}

	return string;
}

/*
 * If the list just contains a single string starting with '$', then find
 * or create the named var and return the var's var_string component.
 * Otherwise, convert the list to a string, and allocate a var_string
 * containing a copy of that string. On failure either returns NULL
 * or shuts down the run.
 */
avd_t
parser_list2varstring(list_t *list)
{
	char *lstr = avd_get_str(list->list_string);

	/* Special case - variable name */
	if ((list->list_next == NULL) && (*lstr == '$'))
		return avd_var_alloc(lstr);

	return (avd_str_alloc(parser_list2string(list)));
}

/*
 * Looks for the var named in list_string of the first element of the
 * supplied list. If found, returns the var_val portion of the var in
 * an attribute value descriptor. If the var is not found, cannot be
 * allocated, the supplied list is NULL, or the list_string filed is
 * empty, returns NULL.
 */
avd_t
parser_list2avd(list_t *list)
{
	avd_t avd;
	char *lstr;

	if (list && ((lstr = avd_get_str(list->list_string)) != NULL)) {
		avd = avd_var_alloc(lstr);
		return (avd);
	}

	return (NULL);
}

/*
 * Sets the event generator rate from the attribute supplied with the
 * command. If the attribute doesn't exist the routine does nothing.
 */
static void
parser_eventgen(cmd_t *cmd)
{
	attr_t *attr;

	/* Get the rate from attribute */
	if ((attr = get_attr_integer(cmd, FSA_RATE))) {
		if (attr->attr_avd) {
			eventgen_setrate(attr->attr_avd);
		}
	}
}

/*
 * Lists the fileset name, path name and average size for all defined
 * filesets.
 */
static void
parser_list(cmd_t *cmd)
{
	(void) fileset_iter(fileset_print);
}

/*
 * Lists the flowop name and instance number for all flowops.
 */
static void
parser_flowop_list(cmd_t *cmd)
{
	flowop_printall();
}

/*
 * Calls procflow_define() to allocate "instances" number of  procflow(s)
 * (processes) with the supplied name. The default number of instances is
 * one. An optional priority level attribute can be supplied and is stored in
 * pf_nice. Finally the routine loops through the list of inner commands, if
 * any, which are defines for threadflows, and passes them one at a time to
 * parser_thread_define() to allocate threadflow entities for the process(es).
 */
static void
parser_proc_define(cmd_t *cmd)
{
	procflow_t *procflow;
	char *name = NULL;
	attr_t *attr;
	avd_t var_instances;
	fbint_t instances;
	cmd_t *inner_cmd;

	/* Get the name of the process */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define proc: proc specifies no name");
		filebench_shutdown(1);
	}

	/* Get the memory size from attribute */
	if ((attr = get_attr_integer(cmd, FSA_INSTANCES))) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "proc_define: Instances attr cannot be random");
			filebench_shutdown(1);
		}
		var_instances = attr->attr_avd;
		instances = avd_get_int(var_instances);
		filebench_log(LOG_DEBUG_IMPL,
		    "Setting instances = %llu", (u_longlong_t)instances);
	} else {
		filebench_log(LOG_DEBUG_IMPL,
		    "Defaulting to instances = 1");
		var_instances = avd_int_alloc(1);
		instances = 1;
	}

	if ((procflow = procflow_define(name, NULL, var_instances)) == NULL) {
		filebench_log(LOG_ERROR,
		    "Failed to instantiate %d %s process(es)\n",
		    instances, name);
		filebench_shutdown(1);
	}

	/* Get the pri from attribute */
	if ((attr = get_attr_integer(cmd, FSA_NICE))) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "proc_define: priority cannot be random");
			filebench_shutdown(1);
		}
		filebench_log(LOG_DEBUG_IMPL, "Setting pri = %llu",
		    (u_longlong_t)avd_get_int(attr->attr_avd));
		procflow->pf_nice = attr->attr_avd;
	} else
		procflow->pf_nice = avd_int_alloc(0);


	/* Create the list of threads for this process  */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_thread_define(inner_cmd, procflow, instances);
	}
}

/*
 * Calls threadflow_define() to allocate "instances" number of  threadflow(s)
 * (threads) with the supplied name. The default number of instances is
 * one. Two other optional attributes may be supplied, one to set the memory
 * size, stored in tf_memsize, and to select the use of Interprocess Shared
 * Memory, which sets the THREADFLOW_USEISM flag in tf_attrs. Finally
 * the routine loops through the list of inner commands, if any, which are
 * defines for flowops, and passes them one at a time to
 * parser_flowop_define() to allocate flowop entities for the threadflows.
 */
static void
parser_thread_define(cmd_t *cmd, procflow_t *procflow, int procinstances)
{
	threadflow_t *threadflow, template;
	attr_t *attr;
	avd_t instances;
	cmd_t *inner_cmd;
	char *name = NULL;

	memset(&template, 0, sizeof (threadflow_t));

	/* Get the name of the thread */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define thread: thread in process %s specifies no name",
		    procflow->pf_name);
		filebench_shutdown(1);
	}

	/* Get the number of instances from attribute */
	if ((attr = get_attr_integer(cmd, FSA_INSTANCES))) {
		instances = attr->attr_avd;
	} else
		instances = avd_int_alloc(1);

	/* Get the memory size from attribute */
	if ((attr = get_attr_integer(cmd, FSA_MEMSIZE))) {
		template.tf_memsize = attr->attr_avd;
	} else
		template.tf_memsize = avd_int_alloc(0);

	/* Get ioprio parameters from attribute */
	if ((attr = get_attr_integer(cmd, FSA_IOPRIO))) {
		template.tf_ioprio = attr->attr_avd;
	} else
		template.tf_ioprio = avd_int_alloc(8);

	if ((threadflow = threadflow_define(procflow, name,
	    &template, instances)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define thread: Failed to instantiate thread\n");
		filebench_shutdown(1);
	}

	/* Use ISM Memory? */
	if ((attr = get_attr(cmd, FSA_USEISM))) {
		threadflow->tf_attrs |= THREADFLOW_USEISM;
	}

	/* Create the list of flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_flowop_define(inner_cmd, threadflow,
		    &threadflow->tf_thrd_fops, FLOW_MASTER);
	}
}

/*
 * Fills in the attributes for a newly allocated flowop
 */
static void
parser_flowop_get_attrs(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;

	/* Get the filename from attribute */
	if ((attr = get_attr(cmd, FSA_FILE))) {
		flowop->fo_filename = attr->attr_avd;
		if (flowop->fo_filename == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: no filename specfied");
			filebench_shutdown(1);
		}
	} else {
		/* no filename attribute specified */
		flowop->fo_filename = NULL;
	}

	/* Get the iosize of the op */
	if ((attr = get_attr_integer(cmd, FSA_IOSIZE)))
		flowop->fo_iosize = attr->attr_avd;
	else
		flowop->fo_iosize = avd_int_alloc(0);

	/* Get the working set size of the op */
	if ((attr = get_attr_integer(cmd, FSA_WSS)))
		flowop->fo_wss = attr->attr_avd;
	else
		flowop->fo_wss = avd_int_alloc(0);

	/* Random I/O? */
	if ((attr = get_attr_bool(cmd, FSA_RANDOM)))
		flowop->fo_random = attr->attr_avd;
	else
		flowop->fo_random = avd_bool_alloc(FALSE);

	/* Sync I/O? */
	if ((attr = get_attr_bool(cmd, FSA_DSYNC)))
		flowop->fo_dsync = attr->attr_avd;
	else
		flowop->fo_dsync = avd_bool_alloc(FALSE);

	/* Target, for wakeup etc */
	if ((attr = get_attr(cmd, FSA_TARGET)))
		(void) strcpy(flowop->fo_targetname,
		    avd_get_str(attr->attr_avd));

	/* Value */
	if ((attr = get_attr_integer(cmd, FSA_VALUE)))
		flowop->fo_value = attr->attr_avd;
	else
		flowop->fo_value = avd_int_alloc(0);

	/* FD */
	if ((attr = get_attr_integer(cmd, FSA_FD))) {
		flowop->fo_fdnumber = avd_get_int(attr->attr_avd);
		if (flowop->fo_filename != NULL)
			filebench_log(LOG_DEBUG_SCRIPT, "It is not "
			    "advisable to supply both an fd number "
			    "and a fileset name in most cases");
	}

	/* Rotatefd? */
	if ((attr = get_attr_bool(cmd, FSA_ROTATEFD)))
		flowop->fo_rotatefd = attr->attr_avd;
	else
		flowop->fo_rotatefd = avd_bool_alloc(FALSE);

	/* SRC FD, for copies etc... */
	if ((attr = get_attr_integer(cmd, FSA_SRCFD)))
		flowop->fo_srcfdnumber = avd_get_int(attr->attr_avd);

	/* Blocking operation? */
	if ((attr = get_attr_bool(cmd, FSA_BLOCKING)))
		flowop->fo_blocking = attr->attr_avd;
	else
		flowop->fo_blocking = avd_bool_alloc(FALSE);

	/* Direct I/O Operation */
	if ((attr = get_attr_bool(cmd, FSA_DIRECTIO)))
		flowop->fo_directio = attr->attr_avd;
	else
		flowop->fo_directio = avd_bool_alloc(FALSE);

	/* Highwater mark */
	if ((attr = get_attr_integer(cmd, FSA_HIGHWATER))) {
		flowop->fo_highwater = attr->attr_avd;
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "define flowop: Highwater attr cannot be random");
			filebench_shutdown(1);
		}
	} else {
		flowop->fo_highwater = avd_int_alloc(1);
	}

	/* find file or leaf directory by index number */
	if ((attr = get_attr_integer(cmd, FSA_INDEXED)))
		flowop->fo_fileindex = attr->attr_avd;
	else
		flowop->fo_fileindex = NULL;

	/* Read Ahead Diable */
	if ((attr = get_attr_bool(cmd, FSA_NOREADAHEAD)))
		flowop->fo_noreadahead = attr->attr_avd;
	else
		flowop->fo_noreadahead = avd_bool_alloc(FALSE);


}

/*
 * defines the FLOW_MASTER flowops within a FLOW_MASTER instance of
 * a composit flowop. Default attributes from the FLOW_INNER_DEF instances
 * of the composit flowop's inner flowops are used if set. Otherwise
 * default attributes from the FLOW_MASTER instance of the composit flowop
 * are used, which may include defaults from the original FLOW_DEFINITION
 * of the composit flowop.
 */
static void
parser_inner_flowop_define(threadflow_t *thread, flowop_t *comp0_flow,
			   flowop_t *comp_mstr_flow)
{
	flowop_t *inner_flowtype, *inner_flowop;

	/* follow flowop list, creating composit names */
	inner_flowtype = comp0_flow->fo_comp_fops;
	comp_mstr_flow->fo_comp_fops = NULL;

	while (inner_flowtype) {
		char fullname[MAXPATHLEN];

		/* create composite_name.name for new flowop */
		snprintf(fullname, MAXPATHLEN, "%s.%s",
		    comp_mstr_flow->fo_name, inner_flowtype->fo_name);

		if ((inner_flowop = flowop_define(thread, fullname,
		    inner_flowtype, &comp_mstr_flow->fo_comp_fops,
		    FLOW_MASTER, 0)) == NULL) {
			filebench_log(LOG_ERROR,
			    "define flowop: Failed to instantiate flowop %s\n",
			    fullname);
			filebench_shutdown(1);
		}

		/* if applicable, update filename attribute */
		if (inner_flowop->fo_filename) {
			char *name;

			/* fix up avd_t */
			avd_update(&inner_flowop->fo_filename,
			    comp_mstr_flow->fo_lvar_list);

			/* see if ready to get the file or fileset */
			name = avd_get_str(inner_flowop->fo_filename);
			if (name) {

				inner_flowop->fo_fileset = fileset_find(name);

				if (inner_flowop->fo_fileset == NULL) {
					filebench_log(LOG_ERROR,
					    "inr flowop %s: file %s not found",
					    inner_flowop->fo_name, name);
					filebench_shutdown(1);
				}
			}
		}

		/* update attributes from local variables */
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);

		/* if the inner flowop is a composit flowop, recurse */
		if (inner_flowtype->fo_type == FLOW_TYPE_COMPOSITE) {
			var_t *newlvar, *proto_lvars, *lvar_ptr;

			proto_lvars = inner_flowop->fo_lvar_list;
			inner_flowop->fo_lvar_list = 0;

			for (lvar_ptr = inner_flowtype->fo_lvar_list; lvar_ptr;
			    lvar_ptr = lvar_ptr->var_next) {

				if ((newlvar = var_lvar_alloc_local(
				    lvar_ptr->var_name)) != NULL) {

					add_lvar_to_list(newlvar,
					    &inner_flowop->fo_lvar_list);

					var_update_comp_lvars(newlvar,
					    proto_lvars,
					    comp_mstr_flow->fo_lvar_list);
				}
			}
		  
			parser_inner_flowop_define(thread,
			    inner_flowtype,
			    inner_flowop);

			inner_flowtype = inner_flowtype->fo_exec_next;
			continue;
		}

		avd_update(&inner_flowop->fo_iosize,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_wss,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_iters,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_value,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_random,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_dsync,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_rotatefd,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_blocking,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_directio,
		    comp_mstr_flow->fo_lvar_list);
		avd_update(&inner_flowop->fo_highwater,
		    comp_mstr_flow->fo_lvar_list);

		inner_flowtype = inner_flowtype->fo_exec_next;
	}
}

/*
 * Calls flowop_define() to allocate a flowop with the supplied name.
 * The allocated flowop inherits attributes from a base flowop of the
 * same type.  If the new flowop has a file or fileset attribute specified,
 * it must specify a defined fileobj or fileset or an error will be logged.
 * The new flowop may  also have the following attributes set by
 * the program:
 *  - file size (fo_iosize)
 *  - working set size (fo_wss)
 *  - do random io (fo_random)
 *  - do synchronous io (fo_dsync)
 *  - perform each operation multiple times before advancing (fo_iter)
 *  - target name (fo_targetname)
 *  - An integer value (fo_value)
 *  - a file descriptor (fo_fd)
 *  - specify to rotate file descriptors (fo_rotatefd)
 *  - a source fd (fo_srcfdnumber)
 *  - specify a blocking operation (fo_blocking)
 *  - specify a highwater mark (fo_highwater)
 *
 * After all the supplied attributes are stored in their respective locations
 * in the flowop object, the flowop's init function is called. No errors are
 * returned, but the filebench run will be terminated if the flowtype is not
 * specified, a name for the new flowop is not supplied, the flowop_define
 * call fails, or a file or fileset name is supplied but the corresponding
 * fileobj or fileset cannot be located.
 */
static void
parser_flowop_define(cmd_t *cmd, threadflow_t *thread,
    flowop_t **flowoplist_hdp, int category)
{
	flowop_t *flowop, *flowop_type;
	char *type = (char *)cmd->cmd_name;
	char *name = NULL;
	attr_t *attr;

	/* Get the inherited flowop */
	flowop_type = flowop_find(type);
	if (flowop_type == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop type %s not found",
		    type);
		filebench_shutdown(1);
	}

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: flowop %s specifies no name",
		    flowop_type->fo_name);
		filebench_shutdown(1);
	}

	if ((flowop = flowop_define(thread, name,
	    flowop_type, flowoplist_hdp, category, 0)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* Iterations */
	if ((attr = get_attr_integer(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);


	/* if this is a use of a composit flowop, create inner FLOW MASTERS */
	if (flowop_type->fo_type == FLOW_TYPE_COMPOSITE) {
		get_attr_lvars(cmd, flowop);
		if (category == FLOW_MASTER)
			parser_inner_flowop_define(thread,
			    flowop_type, flowop);
	}
	else {
		parser_flowop_get_attrs(cmd, flowop);
	}
}

static void
parser_composite_flowop_define(cmd_t *cmd)
{
	flowop_t *flowop;
	cmd_t *inner_cmd;
	char *name = NULL;
	attr_t *attr;

	/* Get the name of the flowop */
	if ((attr = get_attr(cmd, FSA_NAME))) {
		name = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "define flowop: Composit flowop specifies no name");

		filebench_shutdown(1);
	}

	if ((flowop = flowop_new_composite_define(name)) == NULL) {
		filebench_log(LOG_ERROR,
		    "define flowop: Failed to instantiate flowop %s\n",
		    cmd->cmd_name);
		filebench_shutdown(1);
	}

	/* place any local var_t variables on the flowop's local list */
	get_attr_lvars(cmd, flowop);

	/* Iterations */
	if ((attr = get_attr_integer(cmd, FSA_ITERS)))
		flowop->fo_iters = attr->attr_avd;
	else
		flowop->fo_iters = avd_int_alloc(1);

	/* define inner flowops */
	for (inner_cmd = cmd->cmd_list; inner_cmd != NULL;
	    inner_cmd = inner_cmd->cmd_next) {
		parser_flowop_define(inner_cmd, NULL,
		    &flowop->fo_comp_fops, FLOW_INNER_DEF);
	}
}

/*
 * Calls fileset_alloc() to allocate a fileset with the supplied name and
 * initializes the fileset's pathname attribute, and optionally the
 * fileset_cached, fileset_reuse, fileset_prealloc and fileset_size attributes.
 */
static fileset_t *
parser_fileset_init_common(cmd_t *cmd)
{
	fileset_t *fileset;
	avd_t name;
	attr_t *attr;

	/*
	 * Make sure all plugin flowops are initialized.
	 * Defaults to local fs for now
	 */
	flowop_plugin_flowinit();

	/* Get the name of the file */
	if ((attr = get_attr_fileset(cmd, FSA_NAME))) {
		name = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR,
		    "define fileset: file or fileset specifies no name");
		return (NULL);
	}

	fileset = fileset_alloc(name);
	if (!fileset) {
		filebench_log(LOG_ERROR,
		    "define file: failed to instantiate file %s\n",
		    avd_get_str(name));
		return (NULL);
	}

	if ((attr = get_attr(cmd, FSA_PATH)))  {
		fileset->fs_path = attr->attr_avd;
		if (attr->attr_obj)
			fileset->fs_pathstr =
				(avd_t) *((avd_t *) attr->attr_obj);
		else
			fileset->fs_pathstr = avd_str_alloc("");
	} else {
		filebench_log(LOG_ERROR, "Cannot interpret path");
		return (NULL);
	}

	/* How much should we preallocate? */
	if ((attr = get_attr_integer(cmd, FSA_PREALLOC)) &&
	    attr->attr_avd) {
		if (AVD_IS_RANDOM(attr->attr_avd)) {
			filebench_log(LOG_ERROR,
			    "define fileset: Prealloc attr cannot be random");
			filebench_shutdown(1);
		}
		fileset->fs_preallocpercent = attr->attr_avd;
	} else if (attr && !attr->attr_avd) {
		fileset->fs_preallocpercent = avd_int_alloc(100);
	} else {
		fileset->fs_preallocpercent = avd_int_alloc(0);
	}

	/* Should we preallocate? */
	if ((attr = get_attr_bool(cmd, FSA_PREALLOC)))
		fileset->fs_prealloc = attr->attr_avd;
	else
		fileset->fs_prealloc = avd_bool_alloc(FALSE);

	/* Should we prealloc in parallel? */
	if ((attr = get_attr_bool(cmd, FSA_PARALLOC)))
		fileset->fs_paralloc = attr->attr_avd;
	else
		fileset->fs_paralloc = avd_bool_alloc(FALSE);

	/* Should we allow writes to the file? */
	if ((attr = get_attr_bool(cmd, FSA_READONLY)))
		fileset->fs_readonly = attr->attr_avd;
	else
		fileset->fs_readonly = avd_bool_alloc(FALSE);

	if ((attr = get_attr_bool(cmd, FSA_WRITEONLY)))
		fileset->fs_writeonly = attr->attr_avd;
	else
		fileset->fs_writeonly = avd_bool_alloc(FALSE);

	if ((avd_get_bool(fileset->fs_readonly) == TRUE) &&
		(avd_get_bool(fileset->fs_writeonly) == TRUE)) {
		filebench_log(LOG_ERROR, "fileset can't be read-only and "
					"write-only at the same time!");
		return NULL;
	}

	/* Should we reuse the existing file? */
	if ((attr = get_attr_bool(cmd, FSA_REUSE)))
		fileset->fs_reuse = attr->attr_avd;
	else
		fileset->fs_reuse = avd_bool_alloc(FALSE);

	/* Should we check for files actual existance? */
	if ((attr = get_attr_bool(cmd, FSA_TRUSTTREE)))
		fileset->fs_trust_tree = attr->attr_avd;
	else
		fileset->fs_trust_tree = avd_bool_alloc(FALSE);

	/* Should we leave in cache? */
	if ((attr = get_attr_bool(cmd, FSA_CACHED)))
		fileset->fs_cached = attr->attr_avd;
	else
		fileset->fs_cached = avd_bool_alloc(FALSE);

	/* Get the mean or absolute size of the file */
	if ((attr = get_attr_integer(cmd, FSA_SIZE)))
		fileset->fs_size = attr->attr_avd;
	else
		fileset->fs_size = avd_int_alloc(0);

	return (fileset);
}

/*
 * Calls parser_fileset_init_common() to allocate a fileset with one entry and
 * optionally the fileset_prealloc. sets the fileset_entries, fileset_dirwidth,
 * and fileset_dirgamma attributes to appropriate values for emulating the old
 * "fileobj" entity
 */
static void
parser_file_define(cmd_t *cmd)
{
	fileset_t *fileset = parser_fileset_init_common(cmd);

	if (!fileset) {
		filebench_log(LOG_ERROR,
		    "define file: failed to instantiate file");
		filebench_shutdown(1);
		return;
	}

	/* fileset is emulating a single file */
	fileset->fs_attrs = FILESET_IS_FILE;

	/* Set the size of the fileset to 1, no leafdirs */
	fileset->fs_entries = avd_int_alloc(1);
	fileset->fs_leafdirs = avd_int_alloc(0);

	/* Set the mean dir width to more than 1 */
	fileset->fs_dirwidth = avd_int_alloc(10);

	/* Set the dir gamma to 0 */
	fileset->fs_dirgamma = avd_int_alloc(0);
}

/*
 * Calls parser_fileset_init_common() to allocate a fileset with the supplied
 * name and initializes the fileset's fileset_preallocpercent, fileset_prealloc,
 * fileset_entries, fileset_dirwidth, and fileset_dirgamma attributes.
 */
static void
parser_fileset_define(cmd_t *cmd)
{
	fileset_t *fileset = parser_fileset_init_common(cmd);
	attr_t *attr;

	if (!fileset) {
		filebench_log(LOG_ERROR,
		    "define fileset: failed to instantiate fileset");
		filebench_shutdown(1);
		return;
	}

	/* Get the number of files in the fileset */
	if ((attr = get_attr_integer(cmd, FSA_ENTRIES))) {
		fileset->fs_entries = attr->attr_avd;
	} else {
		fileset->fs_entries = avd_int_alloc(0);
	}

	/* Get the number of leafdirs in the fileset */
	if ((attr = get_attr_integer(cmd, FSA_LEAFDIRS))) {
		fileset->fs_leafdirs = attr->attr_avd;
	} else {
		fileset->fs_leafdirs = avd_int_alloc(0);
	}

	/* Get the mean dir width of the fileset */
	if ((attr = get_attr_integer(cmd, FSA_DIRWIDTH))) {
		fileset->fs_dirwidth = attr->attr_avd;
	} else {
		filebench_log(LOG_ERROR, "Fileset has zero directory width");
		fileset->fs_dirwidth = avd_int_alloc(0);
	}

	/* Get the dir depth */
	if ((attr = get_attr_integer(cmd, FSA_DIRDEPTHRV))) {
		fileset->fs_dirdepthrv = attr->attr_avd;
	} else {
		fileset->fs_dirdepthrv = NULL;
	}

	/* Get the gamma value for dir depth distributions */
	if ((attr = get_attr_integer(cmd, FSA_DIRGAMMA))) {
		fileset->fs_dirgamma = attr->attr_avd;
	} else
		fileset->fs_dirgamma = avd_int_alloc(1500);
}

 /*
 * Calls parser_fileset_init_common() to allocate a fileset with one entry and
 * optionally the fileset_prealloc. sets the fileset_entries, fileset_dirwidth,
 * and fileset_dirgamma attributes to appropriate values
 */
static void
parser_file_import(cmd_t *cmd)
{
	fileset_t *fileset = parser_fileset_init_common(cmd);

	if (!fileset) {
		filebench_log(LOG_ERROR,
			"import file: failed to instantiate file");
		filebench_shutdown(1);
		return;
	}

	/* fileset is emulating a single file */
	fileset->fs_attrs = FILESET_IS_FILE;

	/* Set the size of the fileset to 1, no leafdirs */
	fileset->fs_entries = avd_int_alloc(1);
	fileset->fs_leafdirs = avd_int_alloc(0);

	/* Mark this file as imported */
	fileset->fs_import = 1;
}

/*
 * Calls parser_fileset_init_common() to allocate a fileset with the supplied
 * name and initializes the fileset's fileset_preallocpercent,
 * fileset_prealloc, fileset_entries, fileset_dirwidth, and fileset_dirgamma
 * attributes.
 */
static void
parser_fileset_import(cmd_t *cmd)
{
	fileset_t *fileset = parser_fileset_init_common(cmd);
	attr_t *attr;

	if (!fileset) {
		filebench_log(LOG_ERROR,
			"import fileset: failed to instantiate fileset");
		filebench_shutdown(1);
		return;
	}

	/* Get the number of files in the fileset */
	attr = get_attr_integer(cmd, FSA_ENTRIES);
	if (attr)
		fileset->fs_entries = attr->attr_avd;
	else
		fileset->fs_entries = avd_int_alloc(0);

	/* We must define either entries, or prealloc */
	if (avd_get_bool(fileset->fs_prealloc) == FALSE &&
		(avd_get_int(fileset->fs_entries) == 0)) {
		filebench_log(LOG_ERROR,
			"import fileset: %d includes no files",
			avd_get_str(fileset->fs_name));
		filebench_shutdown(1);
		return;
	}

	/* Mark this fileset as imported */
	fileset->fs_import = 1;
}

/*
 * Creates and starts all defined procflow processes. The call to
 * procflow_init() results in creation of the requested number of
 * process instances for each previously defined procflow. The
 * child processes exec() a new instance of filebench, passing it
 * the instance number and address of the shared memory region.
 * The child processes will then create their threads and flowops.
 * The routine then unlocks the run_lock to allow all the processes'
 * threads to start and  waits for all of them to begin execution.
 * Finally, it records the start time and resets the event generation
 * system.
 */
static void
parser_proc_create(cmd_t *cmd)
{
	filebench_shm->shm_1st_err = 0;
	filebench_shm->shm_f_abort = FILEBENCH_OK;

	(void) pthread_rwlock_rdlock(&filebench_shm->shm_run_lock);

	if (procflow_init() != 0) {
		filebench_log(LOG_ERROR, "Failed to create processes\n");
		filebench_shutdown(1);
	}

	/* Wait for all threads to start */
	if (procflow_allstarted() != 0) {
		filebench_log(LOG_ERROR, "Could not start run");
		return;
	}

	/* Release the read lock, allowing threads to start */
	(void) pthread_rwlock_unlock(&filebench_shm->shm_run_lock);

	if (filebench_shm->shm_required &&
	    (ipc_ismcreate(filebench_shm->shm_required) < 0)) {
		filebench_log(LOG_ERROR, "Could not allocate shared memory");
		return;
	}

	filebench_shm->shm_starttime = gethrtime();
	eventgen_reset();
}

/*
 * Calls fileset_createsets() to populate all filesets and create all
 * associated, initially existant,  files and subdirectories.
 * If errors are encountered, calls filebench_shutdown() to exit Filebench.
 */
static void
parser_fileset_create(cmd_t *cmd)
{
	if (!filecreate_done) {
		filecreate_done = 1;

		if (fileset_createsets()) {
			filebench_log(LOG_ERROR, "Failed to create filesets");
			filebench_shutdown(1);
		}
	} else {
		filebench_log(LOG_INFO,
		    "Attempting to create fileset more than once, ignoring");
	}

}

/*
 * Deletes the files and directories that represent files and filesets on the
 * storage medium.
 */
static void
parser_fileset_shutdown(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Shutting down filesets");
	fileset_delete_all_filesets();
}

/*
 * Shuts down all processes and their associated threads. When finished
 * it deletes interprocess shared memory and resets the event generator.
 * It does not exit the filebench program though.
 */
static void
parser_proc_shutdown(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Shutting down processes");
	filecreate_done = 0;
	procflow_shutdown();
	if (filebench_shm->shm_required)
		ipc_ismdelete();
	eventgen_reset();
}

/*
 * Ends filebench run after first destoring any interprocess
 * shared memory. The call to filebench_shutdown()
 * also causes filebench to exit.
 */
static void
parser_filebench_shutdown(cmd_t *cmd)
{
	int f_abort = filebench_shm->shm_f_abort;

	ipc_fini();

	if (f_abort == FILEBENCH_ABORT_ERROR)
		filebench_shutdown(1);
	else
		filebench_shutdown(0);
}

/*
 * This is used for timing runs. Pauses the master thread in one second
 * intervals until the supplied ptime runs out or the f_abort flag
 * is raised. If given a time of zero, it will pause until f_abort is raised.
 */
static int
parser_pause(int ptime)
{
	int timeslept = 0;

	if (ptime) {
		while (timeslept < ptime) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	} else {
		/* initial runtime of 0 means run till abort */
		/* CONSTCOND */
		while (1) {
			(void) sleep(1);
			timeslept++;
			if (filebench_shm->shm_f_abort)
				break;
		}
	}

	return (timeslept);
}

#define TIMED_RUNTIME_DEFAULT 60 /* In seconds */
#define PERIOD_DEFAULT 10 /* In seconds */

/*
 * Do a file bench run. Calls routines to create file sets, files, and
 * processes. It resets the statistics counters, then sleeps for the runtime
 * passed as an argument to it on the command line in 1 second increments.
 * When it is finished sleeping, it collects a snapshot of the statistics
 * and ends the run.
 */
static void
parser_run(cmd_t *cmd)
{
	int runtime;
	int timeslept;

	runtime = cmd->cmd_qty;

	parser_fileset_create(cmd);
	parser_proc_create(cmd);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
	parser_filebench_shutdown((cmd_t *)0);
}

static void
parser_psrun(cmd_t *cmd)
{
	int runtime;
	int period;
	int timeslept = 0;
	int reset_stats = 0;

	runtime = cmd->cmd_qty;

	/*
	 * If period is negative then
	 * we want to reset statistics
	 * at the end of the every period
	 */
	if (cmd->cmd_qty1 < 0) {
		period = -cmd->cmd_qty1;
		reset_stats = 1;	
	} else if (cmd->cmd_qty1 > 0) {
		period = cmd->cmd_qty1;
		reset_stats = 0;
	} else { /* (cmd->cmd_qty1) == 0 */
		period = PERIOD_DEFAULT;
		reset_stats = 0;
	}

	parser_fileset_create(cmd);
	parser_proc_create(cmd);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	while (1) {
		/* sleep the remaining time if a period is smaller */
		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT)
			period = period > (runtime - timeslept) ?
						(runtime - timeslept) : period;

		timeslept += parser_pause(period);

		if (filebench_shm->shm_f_abort)
			break;

		if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT &&
							timeslept >= runtime)
			break;

		parser_statssnap(cmd);

		if (reset_stats)
			stats_clear();
	}

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Similar to parser_run, but gets the sleep time from a variable
 * whose name is supplied as an argument to the command.
 */
static void
parser_run_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int runtime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	runtime = avd_get_int(integer);

	parser_fileset_create(cmd);
	parser_proc_create(cmd);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");
	stats_clear();

	/* If it is a timed mode and timeout is not specified use default */
	if (filebench_shm->shm_rmode == FILEBENCH_MODE_TIMEOUT && !runtime)
		runtime = TIMED_RUNTIME_DEFAULT;

	timeslept = parser_pause(runtime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
	parser_statssnap(cmd);
	parser_proc_shutdown(cmd);
	parser_filebench_shutdown((cmd_t *)0);
}

/*
 * Establishes multi-client synchronization socket with synch server.
 */
static void
parser_enable_mc(cmd_t *cmd)
{
	attr_t *attr;
	char *master;
	char *client;

	if ((attr= get_attr(cmd, FSA_MASTER))) {
		master = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no master specified");
		return;
	}

	if ((attr= get_attr(cmd, FSA_CLIENT))) {
		client = avd_get_str(attr->attr_avd);
	} else {
		filebench_log(LOG_ERROR,
		    "enable multi: no client specified");
		return;
	}

	mc_sync_open_sock(master, 8001, client);
}

/*
 * Exchanges multi-client synchronization message with synch server.
 */
static void
parser_domultisync(cmd_t *cmd)
{
	attr_t *attr;
	fbint_t value;

	if ((attr = get_attr(cmd, FSA_VALUE)))
		value = avd_get_int(attr->attr_avd);
	else
		value = 1;

	mc_sync_synchronize((int)value);
}

/*
 * Sleeps for cmd->cmd_qty seconds, one second at a time.
 */
static void
parser_warmup(cmd_t *cmd)
{
	int sleeptime;

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	sleeptime = cmd->cmd_qty;
	filebench_log(LOG_INFO, "Warming up...");

	(void) parser_pause(sleeptime);
}

/*
 * Same as parser_sleep, except the sleep time is obtained from a variable
 * whose name is passed to it as an argument on the command line.
 */
static void
parser_warmup_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int sleeptime;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	sleeptime = avd_get_int(integer);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Warming up...");

	(void) parser_pause(sleeptime);
}

/*
 * Sleeps for cmd->cmd_qty seconds, one second at a time.
 */
static void
parser_sleep(cmd_t *cmd)
{
	int sleeptime;
	int timeslept;

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	sleeptime = cmd->cmd_qty;
	filebench_log(LOG_INFO, "Running...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
}

/*
 * Same as parser_sleep, except the sleep time is obtained from a variable
 * whose name is passed to it as an argument on the command line.
 */
static void
parser_sleep_variable(cmd_t *cmd)
{
	avd_t integer = avd_var_alloc(cmd->cmd_tgt1);
	int sleeptime;
	int timeslept;

	if (integer == NULL) {
		filebench_log(LOG_ERROR, "Unknown variable %s",
		cmd->cmd_tgt1);
		return;
	}

	sleeptime = avd_get_int(integer);

	/* check for startup errors */
	if (filebench_shm->shm_f_abort)
		return;

	filebench_log(LOG_INFO, "Running...");

	timeslept = parser_pause(sleeptime);

	filebench_log(LOG_INFO, "Run took %d seconds...", timeslept);
}

/*
 * Parser log prints the values of a list of variables to the log file.
 * The list of variables is placed on the command line, separated
 * by comas and the entire list is enclosed in quotes.
 * For example, if $dir contains "/export/home/tmp" and $filesize = 1048576,
 * then typing: log "$dir, $filesize" prints: log /export/home/tmp, 1048576
 */
static void
parser_log(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE, "log %s", string);
	filebench_log(LOG_LOG, "%s", string);
}

/*
 * Implements the stats directory command. changes the directory for
 * dumping statistics to supplied directory path. For example:
 * 	stats directory /tmp
 * changes the stats directory to "/tmp".
 */
static void
parser_directory(cmd_t *cmd)
{
	char newdir[MAXPATHLEN];
	char *dir;
	int ret;

	if ((dir = parser_list2string(cmd->cmd_param_list)) == NULL) {
		filebench_log(LOG_ERROR, "Cannot interpret directory");
		return;
	}

	*newdir = 0;
	/* Change dir relative to cwd if path not fully qualified */
	if (*dir != '/') {
		(void) strcat(newdir, cwd);
		(void) strcat(newdir, "/");
	}
	(void) strcat(newdir, dir);
	(void) mkdir(newdir, 0755);
	filebench_log(LOG_VERBOSE, "Change dir to %s", newdir);
	ret = chdir(newdir);
	free(dir);
}

#define	PIPE_PARENT 1
#define	PIPE_CHILD  0

/*
 * Runs the quoted unix command as a background process. Intended for
 * running statistics gathering utilities such as mpstat while the filebench
 * workload is running. Also records the pid's of the background processes
 * so that parser_statssnap() can terminate them when the run completes.
 */
static void
parser_statscmd(cmd_t *cmd)
{
	char *string;
	pid_t pid;
	pidlist_t *pidlistent;
	int pipe_fd[2];
	int newstdout;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	if ((pipe(pipe_fd)) < 0) {
		filebench_log(LOG_ERROR, "statscmd pipe failed");
		return;
	}

#ifdef HAVE_FORK1
	if ((pid = fork1()) < 0) {
		filebench_log(LOG_ERROR, "statscmd fork failed");
		return;
	}
#elif HAVE_FORK
	if ((pid = fork()) < 0) {
		filebench_log(LOG_ERROR, "statscmd fork failed");
		return;
	}
#else
	Crash! - Need code to deal with no fork1!
#endif /* HAVE_FORK1 */

	if (pid == 0) {

		setsid();

		filebench_log(LOG_VERBOSE,
		    "Backgrounding %s", string);
		/*
		 * Child
		 * - close stdout
		 * - dup to create new stdout
		 * - close pipe fds
		 */
		(void) close(1);

		if ((newstdout = dup(pipe_fd[PIPE_CHILD])) < 0) {
			filebench_log(LOG_ERROR,
			    "statscmd dup failed: %s",
			    strerror(errno));
		}

		(void) close(pipe_fd[PIPE_PARENT]);
		(void) close(pipe_fd[PIPE_CHILD]);

		if (system(string) < 0) {
			filebench_log(LOG_ERROR,
			    "statscmd exec failed: %s",
			    strerror(errno));
		}
		/* Failed! */
		exit(1);

	} else {

		/* Record pid in pidlist for subsequent reaping by stats snap */
		if ((pidlistent = (pidlist_t *)malloc(sizeof (pidlist_t)))
		    == NULL) {
			filebench_log(LOG_ERROR, "pidlistent malloc failed");
			return;
		}

		pidlistent->pl_pid = pid;
		pidlistent->pl_fd = pipe_fd[PIPE_PARENT];
		(void) close(pipe_fd[PIPE_CHILD]);

		/* Add fileobj to global list */
		if (pidlist == NULL) {
			pidlist = pidlistent;
			pidlistent->pl_next = NULL;
		} else {
			pidlistent->pl_next = pidlist;
			pidlist = pidlistent;
		}
	}
}

/*
 * Launches a shell to run the unix command supplied in the argument.
 * The command should be enclosed in quotes, as in:
 * 	system "rm xyz"
 * which would run the "rm" utility to delete the file "xyz".
 */
static void
parser_system(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Running '%s'", string);

	if (system(string) < 0) {
		filebench_log(LOG_ERROR,
		    "system exec failed: %s",
		    strerror(errno));
		filebench_shutdown(1);
	}
	free(string);
}

/*
 * Echos string supplied with command to the log.
 */
static void
parser_echo(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_INFO, "%s", string);
}

static void parser_fscheck(cmd_t *cmd) {
	return;
}

#if 0
/* XXX: do not support this command for now */
/*
 * Checks to see if the specified data directory exists and it's mounted file
 * system is the correct type.
 */
static void
parser_fscheck(cmd_t *cmd)
{
	int fstype_idx;
	char *pathname = NULL;
	char *filesys = "tmpfs";
	char string[MAXPATHLEN];
	struct statvfs64 statbuf;
	attr_t *attr;

	if (cmd->cmd_attr_list == NULL)
		return;

	for (attr = cmd->cmd_attr_list; attr; attr = attr->attr_next) {

		switch(attr->attr_name) {
		case FSA_PATH:
			pathname = avd_get_str(attr->attr_avd);
			break;
		case FSA_FSTYPE:
			filesys = avd_get_str(attr->attr_avd);
			break;
		}
	}

	if (pathname == NULL)
		return;

	if (statvfs64(pathname, &statbuf) < 0) {
		filebench_log(LOG_ERROR,
		    "%s error with supplied data path name: %s; exiting",
		    strerror(errno), pathname);
		filebench_shutdown(1);
		return;
	}

	if (strncmp(filesys, statbuf.f_basetype, FSTYPSZ) != 0) {
		filebench_log(LOG_ERROR,
		    "File System is of type %s, NOT %s as indicated",
		    statbuf.f_basetype, filesys);
		filebench_shutdown(1);
		return;
	}
}
#endif

/*
 * Checks to see if any filesets need to have their caches flushed, and
 * if so invokes the fs_flush script.
 */
static void
parser_fsflush(cmd_t *cmd)
{
	fileset_t *fileset;
	char **fspathlist;
	char pathname[MAXPATHLEN];
	char *filesys = NULL;
	char string[MAXPATHLEN];
	attr_t *attr;
	int fsidx;

	if ((attr = cmd->cmd_attr_list) == NULL)
		return;

	/* Get supplied file system type */
	if (attr->attr_name == FSA_FSTYPE)
		filesys = avd_get_str(attr->attr_avd);

	if (filesys == NULL) {
		filebench_log(LOG_ERROR,
		    "FSFLUSH command lacks file system type");
		return;
	}

	/* Check all filesets for any that remain cached and count them*/
	fsidx = 0;
	for (fileset = filebench_shm->shm_filesetlist; fileset != NULL;
	     fileset = fileset->fs_next) {

		if (avd_get_bool(fileset->fs_cached))
			return;

		fsidx++;
	}

	/* allocated space for fileset path pointers */
	fspathlist = (char **)malloc(fsidx * sizeof(char *));

	/* If flushing still required, flush all filesets */
	fsidx = 0;
	for (fileset = filebench_shm->shm_filesetlist; fileset != NULL;
	     fileset = fileset->fs_next) {
		int idx;

		if (avd_get_str(fileset->fs_path) == NULL)
			return;

		(void) fb_strlcpy(pathname, avd_get_str(fileset->fs_path),
		    MAXPATHLEN);
		if (avd_get_str(fileset->fs_pathstr) != NULL) {
			(void) fb_strlcat(pathname, "/", MAXPATHLEN);
			(void) fb_strlcat(pathname,
			    avd_get_str(fileset->fs_pathstr), MAXPATHLEN);
		}

		for (idx = 0; idx < fsidx; idx++) {
			if (strcmp(pathname, fspathlist[idx]) == 0)
				break;
		}

		if (fsidx == idx) {

			/* found a new path */
			fspathlist[fsidx++] = pathname;

			/* now flush it */
			snprintf(string, MAXPATHLEN,
			    "%s/scripts/fs_flush %s %s", fbbasepath,
			    filesys, pathname);

			if (system(string) < 0) {
				filebench_log(LOG_ERROR,
				    "exec of fs_flush script failed: %s",
				    strerror(errno));
				filebench_shutdown(1);
			}
		}
	}
}

/*
 * Prints out the version of Filebench.
 */
static void
parser_version(cmd_t *cmd)
{
	filebench_log(LOG_INFO, "Filebench Version: %s", FILEBENCH_VERSION);
}

/*
 * Sets osprof_enabled option
 */
static void
parser_osprof_enable(cmd_t *cmd)
{
	filebench_shm->osprof_enabled = 1;
	filebench_log(LOG_INFO, "OSprof enabled");
}

/*
 * Resets osprof_enabled option
 */
static void
parser_osprof_disable(cmd_t *cmd)
{
	filebench_shm->osprof_enabled = 0;
	filebench_log(LOG_INFO, "OSprof disabled");
}

/*
 * Updates the global dump filename with the filename supplied
 * as the command's argument. Then dumps the statistics of each
 * worker flowop into the dump file, followed by a summary of
 * overall totals.
 */
static void
parser_statsdump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_dump(string);

	free(string);
}

/*
 * Same as statsdump, but outputs in a computer friendly format.
 */
static void
parser_statsmultidump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_multidump(string);

	free(string);
}

/*
 * Same as parser_statsdump, but in xml format.
 */
static void
parser_statsxmldump(cmd_t *cmd)
{
	char *string;

	if (cmd->cmd_param_list == NULL)
		return;

	string = parser_list2string(cmd->cmd_param_list);

	if (string == NULL)
		return;

	filebench_log(LOG_VERBOSE,
	    "Stats dump to file '%s'", string);

	stats_xmldump(string);

	free(string);
}

/*
 * Kills off background statistics collection processes, then takes a snapshot
 * of the filebench run's collected statistics using stats_snap() from
 * stats.c.
 */
static void
parser_statssnap(cmd_t *cmd)
{
	pidlist_t *pidlistent;
	int stat;
	pid_t pid;

	for (pidlistent = pidlist; pidlistent != NULL;
	    pidlistent = pidlistent->pl_next) {
		filebench_log(LOG_VERBOSE, "Killing session %d for pid %d",
		    getsid(pidlistent->pl_pid),
		    pidlistent->pl_pid);
		if (pidlistent->pl_fd)
			(void) close(pidlistent->pl_fd);
#ifdef HAVE_SIGSEND
		sigsend(P_SID, getsid(pidlistent->pl_pid), SIGTERM);
#else
		(void) kill(-1, SIGTERM);
#endif

		/* Close pipe */
		if (pidlistent->pl_fd)
			(void) close(pidlistent->pl_fd);

		/* Wait for cmd and all its children */
		while ((pid = waitpid(pidlistent->pl_pid * -1, &stat, 0)) > 0)
			filebench_log(LOG_DEBUG_IMPL,
			"Waited for pid %d", (int)pid);
	}

	for (pidlistent = pidlist; pidlistent != NULL;
	    pidlistent = pidlistent->pl_next) {
		free(pidlistent);
	}

	pidlist = NULL;
	stats_snap();
}

/*
 * Shutdown filebench.
 */
static void
parser_abort(int arg)
{
	(void) sigignore(SIGINT);
	filebench_log(LOG_INFO, "Aborting...");
	filebench_shutdown(1);
}

/*
 * define a random variable and initialize the distribution parameters
 */
static void
parser_var_assign_random(char *name, cmd_t *cmd)
{
	randdist_t	*rndp;
	attr_t		*attr;

	rndp = randdist_alloc();
	if (!rndp) {
		filebench_log(LOG_ERROR,
			"failed to alloc random distribution object\n");
		return;
	}

	rndp->rnd_type = 0;

	/* Get the source of the random numbers */
	if ((attr = get_attr_integer(cmd, FSA_RANDSRC))) {
		int randsrc = (int)avd_get_int(attr->attr_avd);

		switch (randsrc) {
		case FSV_URAND:
			rndp->rnd_type |= RAND_SRC_URANDOM;
			break;
		case FSV_RAND48:
			rndp->rnd_type |= RAND_SRC_GENERATOR;
			break;
		}
	} else {
		/* default to rand48 random number generator */
		rndp->rnd_type |= RAND_SRC_GENERATOR;
	}

	/* Get the min value of the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_MIN)))
		rndp->rnd_min = attr->attr_avd;
	else
		rndp->rnd_min = avd_int_alloc(0);

	/* Get the roundoff value for the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_ROUND)))
		rndp->rnd_round = attr->attr_avd;
	else
		rndp->rnd_round = avd_int_alloc(0);

	/* Get the seed for the random variable */
	if ((attr = get_attr_integer(cmd, FSA_RANDSEED)))
		rndp->rnd_seed = attr->attr_avd;
	else
		rndp->rnd_seed = avd_int_alloc(0);

	/* Get a tablular probablility distribution if there is one */
	if ((attr = get_attr(cmd, FSA_RANDTABLE))) {
		rndp->rnd_probtabs = (probtabent_t *)(attr->attr_obj);
		rndp->rnd_type |= RAND_TYPE_TABLE;

		/* no need for the rest of the attributes */
		goto randdist_init;
	} else {
		rndp->rnd_probtabs = NULL;
	}

	/* Get the type for the random variable */
	if ((attr = get_attr(cmd, FSA_TYPE))) {
		int disttype = (int)avd_get_int(attr->attr_avd);

		switch (disttype) {
		case FSV_RANDUNI:
			rndp->rnd_type |= RAND_TYPE_UNIFORM;
			break;
		case FSA_RANDGAMMA:
			rndp->rnd_type |= RAND_TYPE_GAMMA;
			break;
		case FSV_RANDTAB:
			filebench_log(LOG_ERROR,
			    "Table distribution type without prob table");
			break;
		}
	} else {
		/* default to gamma distribution type */
		rndp->rnd_type |= RAND_TYPE_GAMMA;
	}

	/* Get the gamma value of the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_RANDGAMMA)))
		rndp->rnd_gamma = attr->attr_avd;
	else
		rndp->rnd_gamma = avd_int_alloc(1500);

	/* Get the mean value of the random distribution */
	if ((attr = get_attr_integer(cmd, FSA_RANDMEAN))) {
		rndp->rnd_mean = attr->attr_avd;
	} else if ((rndp->rnd_type & RAND_TYPE_MASK) == RAND_TYPE_GAMMA) {
		rndp->rnd_mean = NULL;
	} else {
		rndp->rnd_mean = avd_int_alloc(0);
	}

randdist_init:
	var_assign_random(name, rndp);

	randdist_init(rndp);
}

/*
 * alloc_cmd() allocates the required resources for a cmd_t. On failure, a
 * filebench_log is issued and NULL is returned.
 */
static cmd_t *
alloc_cmd(void)
{
	cmd_t *cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd) {
		filebench_log(LOG_ERROR, "Alloc cmd failed");
		return NULL;
	}

	memset(cmd, 0, sizeof (cmd_t));

	return cmd;
}

/*
 * Allocates an attr_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the attr_t.
 */
static attr_t *
alloc_attr(void)
{
	attr_t *attr;

	attr = malloc(sizeof(*attr));
	if (!attr)
		return (NULL);

	(void) memset(attr, 0, sizeof(*attr));

	return (attr);
}

/*
 * Allocates a probtabent_t structure and zeros it. Returns NULL on failure, or
 * a pointer to the probtabent_t.
 */
static probtabent_t *
alloc_probtabent(void)
{
	probtabent_t *rte;

	if ((rte = malloc(sizeof (probtabent_t))) == NULL) {
		return (NULL);
	}

	(void) memset(rte, 0, sizeof (probtabent_t));
	return (rte);
}

/*
 * Allocates an attr_t structure and puts the supplied var_t into
 * its attr_avd location, and sets its name to FSA_LVAR_ASSIGN
 */
static attr_t *
alloc_lvar_attr(var_t *var)
{
	attr_t *attr;

	if ((attr = alloc_attr()) == NULL)
		return (NULL);

	attr->attr_name = FSA_LVAR_ASSIGN;
	attr->attr_avd = (avd_t)var;

	return (attr);
}


/*
 * Searches the attribute list for the command for the named attribute type.
 * The attribute list is created by the parser from the list of attributes
 * supplied with certain commands, such as the define and flowop commands.
 * Returns a pointer to the attribute structure if the named attribute is
 * found, otherwise returns NULL. If the attribute includes a parameter list,
 * the list is converted to a string and stored in the attr_avd field of
 * the returned attr_t struct.
 */
static attr_t *
get_attr_fileset(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		filebench_log(LOG_DEBUG_IMPL,
		    "attr %d = %d %llx?",
		    attr->attr_name,
		    name,
		    attr->attr_avd);

		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		filebench_log(LOG_DEBUG_SCRIPT, "attr is param list");
		rtn->attr_avd = parser_list2varstring(rtn->attr_param_list);
	}

	return (rtn);
}


/*
 * Searches the attribute list for the command for the named attribute type.
 * The attribute list is created by the parser from the list of attributes
 * supplied with certain commands, such as the define and flowop commands.
 * Returns a pointer to the attribute structure if the named attribute is
 * found, otherwise returns NULL. If the attribute includes a parameter list,
 * the list is converted to a string and stored in the attr_avd field of
 * the returned attr_t struct.
 */
static attr_t *
get_attr(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;
	char *string;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		filebench_log(LOG_DEBUG_IMPL,
		    "attr %d = %d %llx?",
		    attr->attr_name,
		    name,
		    attr->attr_avd);

		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		filebench_log(LOG_DEBUG_SCRIPT, "attr is param list");
		string = parser_list2string(rtn->attr_param_list);
		if (string != NULL) {
			rtn->attr_avd = avd_str_alloc(string);
			filebench_log(LOG_DEBUG_SCRIPT,
			    "attr string %s", string);
		}
	}

	return (rtn);
}

/*
 * Similar to get_attr, but converts the parameter string supplied with the
 * named attribute to an integer and stores the integer in the attr_avd
 * portion of the returned attr_t struct.
 */
static attr_t *
get_attr_integer(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list)
		rtn->attr_avd = parser_list2avd(rtn->attr_param_list);

	return (rtn);
}

/*
 * Similar to get_attr, but converts the parameter string supplied with the
 * named attribute to an integer and stores the integer in the attr_avd
 * portion of the returned attr_t struct. If no parameter string is supplied
 * then it defaults to TRUE (1).
 */
static attr_t *
get_attr_bool(cmd_t *cmd, int64_t name)
{
	attr_t *attr;
	attr_t *rtn = NULL;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {
		if (attr->attr_name == name)
			rtn = attr;
	}

	if (rtn == NULL)
		return (NULL);

	if (rtn->attr_param_list) {
		rtn->attr_avd = parser_list2avd(rtn->attr_param_list);

	} else if (rtn->attr_avd == NULL) {
		rtn->attr_avd = avd_bool_alloc(TRUE);
	}

	/* boolean attributes cannot point to random variables */
	if (AVD_IS_RANDOM(rtn->attr_avd)) {
		filebench_log(LOG_ERROR,
		    "define flowop: Boolean attr %s cannot be random", name);
		filebench_shutdown(1);
		return (NULL);
	}

	return (rtn);
}

/*
 * removes the newly allocated local var from the shared local var
 * list, then puts it at the head of the private local var list
 * supplied as the second argument.
 */
static void
add_lvar_to_list(var_t *newlvar, var_t **lvar_list)
{
	var_t *prev;

	/* remove from shared local list, if there */
	if (newlvar == filebench_shm->shm_var_loc_list) {
		/* on top of list, just grap */
		filebench_shm->shm_var_loc_list = newlvar->var_next;
	} else {
		/* find newvar on list and remove */
		for (prev = filebench_shm->shm_var_loc_list; prev;
		    prev = prev->var_next) {
			if (prev->var_next == newlvar)
				prev->var_next = newlvar->var_next;
		}
	}
	newlvar->var_next = NULL;

	/* add to flowop private local list at head */
	newlvar->var_next = *lvar_list;
	*lvar_list = newlvar;
}

/*
 * Searches the attribute list for the command for any allocated local
 * variables. The attribute list is created by the parser from the list of
 * attributes supplied with certain commands, such as the define and flowop
 * commands. Places all found local vars onto the flowop's local variable
 * list. 
 */
static void
get_attr_lvars(cmd_t *cmd, flowop_t *flowop)
{
	attr_t *attr;
	var_t *orig_lvar_list;

	/* save the local var list */
	orig_lvar_list = flowop->fo_lvar_list;

	for (attr = cmd->cmd_attr_list; attr != NULL;
	    attr = attr->attr_next) {

		if (attr->attr_name == FSA_LVAR_ASSIGN) {
			var_t *newvar;

			if ((newvar = (var_t *)attr->attr_avd) == NULL)
				continue;

			add_lvar_to_list(newvar, &flowop->fo_lvar_list);
			var_update_comp_lvars(newvar, orig_lvar_list, NULL);
		}
	}
}

/*
 * Allocates memory for a list_t structure, initializes it to zero, and
 * returns a pointer to it. On failure, returns NULL.
 */
static list_t *
alloc_list()
{
	list_t *list;

	if ((list = malloc(sizeof (list_t))) == NULL) {
		return (NULL);
	}

	(void) memset(list, 0, sizeof (list_t));
	return (list);
}

/*
 * Define a custom variable and validate its parameters.
 * TODO: Clean up state when things go wrong.
 */
static void
parser_var_assign_custom(char *name, cmd_t *cmd)
{
	cvar_t	*cvar;
	attr_t	*attr;
	char	*type;
	char	*parameters;
	int 	ret;

	attr = get_attr(cmd, FSA_TYPE);
	if (attr)
		type = avd_get_str(attr->attr_avd);
	else {
		filebench_log(LOG_ERROR, "define cvar: no type specified");
		filebench_shutdown(1);
		return;
	}

	cvar = cvar_alloc();
	if (!cvar) {
		filebench_log(LOG_ERROR, "Failed to allocate custom variable");
		filebench_shutdown(1);
		return;
	}

	/* Initialize the custom variable mutex. */
	(void) pthread_mutex_init(&cvar->cvar_lock,
			ipc_mutexattr(IPC_MUTEX_NORMAL));

	/* Get the min, max and round values for the custom variable. */
	if ((attr = get_attr(cmd, FSA_MIN)))
		cvar->min = avd_get_dbl(attr->attr_avd);
	else
		cvar->min = DBL_MIN;

	if ((attr = get_attr(cmd, FSA_MAX)))
		cvar->max = avd_get_dbl(attr->attr_avd);
	else
		cvar->max = DBL_MAX;

	if ((attr = get_attr(cmd, FSA_ROUND)))
		cvar->round = avd_get_dbl(attr->attr_avd);
	else
		cvar->round = 0;

	attr = get_attr(cmd, FSA_PARAMETERS);
	if (attr)
		parameters = avd_get_str(attr->attr_avd);
	else
		parameters = NULL;

	ret = init_cvar_handle(cvar, type, parameters);
	if (ret) {
		filebench_log(LOG_FATAL, "define cvar: failed for custom variable %s",
		    name);
		filebench_shutdown(1);
		return;
	}

	var_assign_custom(name, cvar);
}

void parser_list_cvar_types(void)
{
	cvar_library_info_t *t;

	if (!filebench_shm->shm_cvar_lib_info_list) {
		printf("No custom variables supported.\n");
		return;
	}

	printf("Custom variable types supported:\n");
	for (t = filebench_shm->shm_cvar_lib_info_list; t; t = t->next)
		printf("  %s\n", t->type);

	return;
}

void parser_list_cvar_type_parameters(char *type)
{
	const char *version = NULL;
	const char *usage = NULL;

	cvar_library_info_t *t;

	for (t = filebench_shm->shm_cvar_lib_info_list; t != NULL; t = t->next) {
		if (!strcmp(type, t->type))
			break;
	}

	if (!t) {
		printf("Unknown custom variable type %s.", type);
		return;
	}

	printf("Custom variable type: %s\n", t->type);
	printf("Supporting library: %s\n", t->filename);

	if (cvar_libraries[t->index]->cvar_op.cvar_version)
		version = cvar_libraries[t->index]->cvar_op.cvar_version();
	
	if (cvar_libraries[t->index]->cvar_op.cvar_usage)
		usage = cvar_libraries[t->index]->cvar_op.cvar_usage();

	
	if (version)
		printf("Version: %s\n", version);
	else
		printf("Oops. No version information provided.\n");
	
	if (usage)
		printf("Usage:\n%s\n", usage);
	else
		printf("Oops. No usage information provided.\n");
	
	return;
}


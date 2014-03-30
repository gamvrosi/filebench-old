
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
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

/* Line 1676 of yacc.c  */
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



/* Line 1676 of yacc.c  */
#line 312 "parser_gram.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;



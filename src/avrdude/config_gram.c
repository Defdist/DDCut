/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     K_READ = 258,
     K_WRITE = 259,
     K_READ_LO = 260,
     K_READ_HI = 261,
     K_WRITE_LO = 262,
     K_WRITE_HI = 263,
     K_LOADPAGE_LO = 264,
     K_LOADPAGE_HI = 265,
     K_LOAD_EXT_ADDR = 266,
     K_WRITEPAGE = 267,
     K_CHIP_ERASE = 268,
     K_PGM_ENABLE = 269,
     K_MEMORY = 270,
     K_PAGE_SIZE = 271,
     K_PAGED = 272,
     K_ARDUINO = 273,
     K_AVRFTDI = 274,
     K_BAUDRATE = 275,
     K_BS2 = 276,
     K_BUFF = 277,
     K_BUSPIRATE = 278,
     K_CHIP_ERASE_DELAY = 279,
     K_DEDICATED = 280,
     K_DEFAULT_PARALLEL = 281,
     K_DEFAULT_PROGRAMMER = 282,
     K_DEFAULT_SERIAL = 283,
     K_DEFAULT_BITCLOCK = 284,
     K_DESC = 285,
     K_DEVICECODE = 286,
     K_DRAGON_DW = 287,
     K_DRAGON_HVSP = 288,
     K_DRAGON_ISP = 289,
     K_DRAGON_JTAG = 290,
     K_DRAGON_PDI = 291,
     K_DRAGON_PP = 292,
     K_STK500_DEVCODE = 293,
     K_AVR910_DEVCODE = 294,
     K_EEPROM = 295,
     K_ERRLED = 296,
     K_FLASH = 297,
     K_ID = 298,
     K_IO = 299,
     K_JTAG_MKI = 300,
     K_JTAG_MKII = 301,
     K_JTAG_MKII_AVR32 = 302,
     K_JTAG_MKII_DW = 303,
     K_JTAG_MKII_ISP = 304,
     K_JTAG_MKII_PDI = 305,
     K_LOADPAGE = 306,
     K_MAX_WRITE_DELAY = 307,
     K_MIN_WRITE_DELAY = 308,
     K_MISO = 309,
     K_MOSI = 310,
     K_NUM_PAGES = 311,
     K_NVM_BASE = 312,
     K_OFFSET = 313,
     K_PAGEL = 314,
     K_PAR = 315,
     K_PARALLEL = 316,
     K_PART = 317,
     K_PGMLED = 318,
     K_PROGRAMMER = 319,
     K_PSEUDO = 320,
     K_PWROFF_AFTER_WRITE = 321,
     K_RDYLED = 322,
     K_READBACK_P1 = 323,
     K_READBACK_P2 = 324,
     K_READMEM = 325,
     K_RESET = 326,
     K_RETRY_PULSE = 327,
     K_SERBB = 328,
     K_SERIAL = 329,
     K_SCK = 330,
     K_SIGNATURE = 331,
     K_SIZE = 332,
     K_STK500 = 333,
     K_STK500HVSP = 334,
     K_STK500PP = 335,
     K_STK500V2 = 336,
     K_STK500GENERIC = 337,
     K_STK600 = 338,
     K_STK600HVSP = 339,
     K_STK600PP = 340,
     K_AVR910 = 341,
     K_USBASP = 342,
     K_USBDEV = 343,
     K_USBSN = 344,
     K_USBTINY = 345,
     K_USBPID = 346,
     K_USBPRODUCT = 347,
     K_USBVENDOR = 348,
     K_USBVID = 349,
     K_BUTTERFLY = 350,
     K_BUTTERFLY_MK = 351,
     K_TYPE = 352,
     K_VCC = 353,
     K_VFYLED = 354,
     K_WIRING = 355,
     K_NO = 356,
     K_YES = 357,
     K_TIMEOUT = 358,
     K_STABDELAY = 359,
     K_CMDEXEDELAY = 360,
     K_HVSPCMDEXEDELAY = 361,
     K_SYNCHLOOPS = 362,
     K_BYTEDELAY = 363,
     K_POLLVALUE = 364,
     K_POLLINDEX = 365,
     K_PREDELAY = 366,
     K_POSTDELAY = 367,
     K_POLLMETHOD = 368,
     K_MODE = 369,
     K_DELAY = 370,
     K_BLOCKSIZE = 371,
     K_READSIZE = 372,
     K_HVENTERSTABDELAY = 373,
     K_PROGMODEDELAY = 374,
     K_LATCHCYCLES = 375,
     K_TOGGLEVTG = 376,
     K_POWEROFFDELAY = 377,
     K_RESETDELAYMS = 378,
     K_RESETDELAYUS = 379,
     K_HVLEAVESTABDELAY = 380,
     K_RESETDELAY = 381,
     K_SYNCHCYCLES = 382,
     K_HVCMDEXEDELAY = 383,
     K_CHIPERASEPULSEWIDTH = 384,
     K_CHIPERASEPOLLTIMEOUT = 385,
     K_CHIPERASETIME = 386,
     K_PROGRAMFUSEPULSEWIDTH = 387,
     K_PROGRAMFUSEPOLLTIMEOUT = 388,
     K_PROGRAMLOCKPULSEWIDTH = 389,
     K_PROGRAMLOCKPOLLTIMEOUT = 390,
     K_PP_CONTROLSTACK = 391,
     K_HVSP_CONTROLSTACK = 392,
     K_ALLOWFULLPAGEBITSTREAM = 393,
     K_ENABLEPAGEPROGRAMMING = 394,
     K_HAS_JTAG = 395,
     K_HAS_DW = 396,
     K_HAS_PDI = 397,
     K_HAS_TPI = 398,
     K_IDR = 399,
     K_IS_AVR32 = 400,
     K_RAMPZ = 401,
     K_SPMCR = 402,
     K_EECR = 403,
     K_FLASH_INSTR = 404,
     K_EEPROM_INSTR = 405,
     TKN_COMMA = 406,
     TKN_EQUAL = 407,
     TKN_SEMI = 408,
     TKN_TILDE = 409,
     TKN_NUMBER = 410,
     TKN_STRING = 411,
     TKN_ID = 412
   };
#endif
/* Tokens.  */
#define K_READ 258
#define K_WRITE 259
#define K_READ_LO 260
#define K_READ_HI 261
#define K_WRITE_LO 262
#define K_WRITE_HI 263
#define K_LOADPAGE_LO 264
#define K_LOADPAGE_HI 265
#define K_LOAD_EXT_ADDR 266
#define K_WRITEPAGE 267
#define K_CHIP_ERASE 268
#define K_PGM_ENABLE 269
#define K_MEMORY 270
#define K_PAGE_SIZE 271
#define K_PAGED 272
#define K_ARDUINO 273
#define K_AVRFTDI 274
#define K_BAUDRATE 275
#define K_BS2 276
#define K_BUFF 277
#define K_BUSPIRATE 278
#define K_CHIP_ERASE_DELAY 279
#define K_DEDICATED 280
#define K_DEFAULT_PARALLEL 281
#define K_DEFAULT_PROGRAMMER 282
#define K_DEFAULT_SERIAL 283
#define K_DEFAULT_BITCLOCK 284
#define K_DESC 285
#define K_DEVICECODE 286
#define K_DRAGON_DW 287
#define K_DRAGON_HVSP 288
#define K_DRAGON_ISP 289
#define K_DRAGON_JTAG 290
#define K_DRAGON_PDI 291
#define K_DRAGON_PP 292
#define K_STK500_DEVCODE 293
#define K_AVR910_DEVCODE 294
#define K_EEPROM 295
#define K_ERRLED 296
#define K_FLASH 297
#define K_ID 298
#define K_IO 299
#define K_JTAG_MKI 300
#define K_JTAG_MKII 301
#define K_JTAG_MKII_AVR32 302
#define K_JTAG_MKII_DW 303
#define K_JTAG_MKII_ISP 304
#define K_JTAG_MKII_PDI 305
#define K_LOADPAGE 306
#define K_MAX_WRITE_DELAY 307
#define K_MIN_WRITE_DELAY 308
#define K_MISO 309
#define K_MOSI 310
#define K_NUM_PAGES 311
#define K_NVM_BASE 312
#define K_OFFSET 313
#define K_PAGEL 314
#define K_PAR 315
#define K_PARALLEL 316
#define K_PART 317
#define K_PGMLED 318
#define K_PROGRAMMER 319
#define K_PSEUDO 320
#define K_PWROFF_AFTER_WRITE 321
#define K_RDYLED 322
#define K_READBACK_P1 323
#define K_READBACK_P2 324
#define K_READMEM 325
#define K_RESET 326
#define K_RETRY_PULSE 327
#define K_SERBB 328
#define K_SERIAL 329
#define K_SCK 330
#define K_SIGNATURE 331
#define K_SIZE 332
#define K_STK500 333
#define K_STK500HVSP 334
#define K_STK500PP 335
#define K_STK500V2 336
#define K_STK500GENERIC 337
#define K_STK600 338
#define K_STK600HVSP 339
#define K_STK600PP 340
#define K_AVR910 341
#define K_USBASP 342
#define K_USBDEV 343
#define K_USBSN 344
#define K_USBTINY 345
#define K_USBPID 346
#define K_USBPRODUCT 347
#define K_USBVENDOR 348
#define K_USBVID 349
#define K_BUTTERFLY 350
#define K_BUTTERFLY_MK 351
#define K_TYPE 352
#define K_VCC 353
#define K_VFYLED 354
#define K_WIRING 355
#define K_NO 356
#define K_YES 357
#define K_TIMEOUT 358
#define K_STABDELAY 359
#define K_CMDEXEDELAY 360
#define K_HVSPCMDEXEDELAY 361
#define K_SYNCHLOOPS 362
#define K_BYTEDELAY 363
#define K_POLLVALUE 364
#define K_POLLINDEX 365
#define K_PREDELAY 366
#define K_POSTDELAY 367
#define K_POLLMETHOD 368
#define K_MODE 369
#define K_DELAY 370
#define K_BLOCKSIZE 371
#define K_READSIZE 372
#define K_HVENTERSTABDELAY 373
#define K_PROGMODEDELAY 374
#define K_LATCHCYCLES 375
#define K_TOGGLEVTG 376
#define K_POWEROFFDELAY 377
#define K_RESETDELAYMS 378
#define K_RESETDELAYUS 379
#define K_HVLEAVESTABDELAY 380
#define K_RESETDELAY 381
#define K_SYNCHCYCLES 382
#define K_HVCMDEXEDELAY 383
#define K_CHIPERASEPULSEWIDTH 384
#define K_CHIPERASEPOLLTIMEOUT 385
#define K_CHIPERASETIME 386
#define K_PROGRAMFUSEPULSEWIDTH 387
#define K_PROGRAMFUSEPOLLTIMEOUT 388
#define K_PROGRAMLOCKPULSEWIDTH 389
#define K_PROGRAMLOCKPOLLTIMEOUT 390
#define K_PP_CONTROLSTACK 391
#define K_HVSP_CONTROLSTACK 392
#define K_ALLOWFULLPAGEBITSTREAM 393
#define K_ENABLEPAGEPROGRAMMING 394
#define K_HAS_JTAG 395
#define K_HAS_DW 396
#define K_HAS_PDI 397
#define K_HAS_TPI 398
#define K_IDR 399
#define K_IS_AVR32 400
#define K_RAMPZ 401
#define K_SPMCR 402
#define K_EECR 403
#define K_FLASH_INSTR 404
#define K_EEPROM_INSTR 405
#define TKN_COMMA 406
#define TKN_EQUAL 407
#define TKN_SEMI 408
#define TKN_TILDE 409
#define TKN_NUMBER 410
#define TKN_STRING 411
#define TKN_ID 412




/* Copy the first part of user declarations.  */
#line 22 "config_gram.y"


#include "ac_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "avrdude.h"

#include "config.h"
#include "lists.h"
#include "par.h"
#include "serbb.h"
#include "pindefs.h"
#include "ppi.h"
#include "pgm.h"
#include "stk500.h"
#include "arduino.h"
#include "buspirate.h"
#include "stk500v2.h"
#include "wiring.h"
#include "stk500generic.h"
#include "avr910.h"
#include "butterfly.h"
#include "usbasp.h"
#include "usbtiny.h"
#include "avr.h"
#include "jtagmkI.h"
#include "jtagmkII.h"
#include "avrftdi.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

int yylex(void);
int yyerror(char * errmsg);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);
 


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

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 466 "config_gram.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
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
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   402

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  158
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  179
/* YYNRULES -- Number of states.  */
#define YYNSTATES  404

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   412

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
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     4,     6,     8,    11,    14,    17,    22,
      27,    32,    37,    38,    42,    43,    47,    49,    53,    55,
      59,    62,    66,    70,    74,    78,    82,    86,    90,    94,
      98,   102,   106,   110,   114,   118,   122,   126,   130,   134,
     138,   142,   146,   150,   154,   158,   162,   166,   170,   174,
     178,   182,   186,   190,   194,   198,   202,   206,   210,   214,
     218,   222,   226,   230,   234,   238,   242,   246,   250,   254,
     258,   262,   266,   271,   276,   281,   286,   291,   296,   301,
     306,   308,   310,   312,   314,   316,   318,   320,   322,   324,
     326,   328,   330,   333,   337,   339,   341,   343,   345,   347,
     349,   353,   357,   361,   365,   369,   375,   379,   383,   387,
     391,   395,   399,   403,   407,   411,   415,   419,   423,   427,
     431,   435,   439,   443,   447,   451,   455,   459,   463,   467,
     471,   475,   479,   483,   487,   491,   495,   499,   503,   507,
     511,   515,   519,   523,   527,   531,   535,   539,   543,   547,
     551,   555,   559,   563,   567,   571,   575,   579,   580,   585,
     589,   591,   593,   596,   600,   604,   608,   612,   616,   620,
     624,   628,   632,   636,   640,   644,   648,   652,   656,   660
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
     159,     0,    -1,    -1,   160,    -1,   161,    -1,   160,   161,
      -1,   162,   153,    -1,   164,   153,    -1,    27,   152,   156,
     153,    -1,    26,   152,   156,   153,    -1,    28,   152,   156,
     153,    -1,    29,   152,   155,   153,    -1,    -1,    64,   163,
     168,    -1,    -1,    62,   165,   171,    -1,   156,    -1,   166,
     151,   156,    -1,   155,    -1,   167,   151,   155,    -1,   169,
     153,    -1,   168,   169,   153,    -1,    43,   152,   166,    -1,
      97,   152,    60,    -1,    97,   152,    73,    -1,    97,   152,
      78,    -1,    97,   152,    81,    -1,    97,   152,   100,    -1,
      97,   152,    79,    -1,    97,   152,    80,    -1,    97,   152,
      82,    -1,    97,   152,    18,    -1,    97,   152,    19,    -1,
      97,   152,    23,    -1,    97,   152,    83,    -1,    97,   152,
      84,    -1,    97,   152,    85,    -1,    97,   152,    86,    -1,
      97,   152,    87,    -1,    97,   152,    90,    -1,    97,   152,
      95,    -1,    97,   152,    96,    -1,    97,   152,    45,    -1,
      97,   152,    46,    -1,    97,   152,    47,    -1,    97,   152,
      48,    -1,    97,   152,    49,    -1,    97,   152,    50,    -1,
      97,   152,    32,    -1,    97,   152,    33,    -1,    97,   152,
      34,    -1,    97,   152,    35,    -1,    97,   152,    36,    -1,
      97,   152,    37,    -1,    30,   152,   156,    -1,    98,   152,
     167,    -1,    22,   152,   167,    -1,    88,   152,   156,    -1,
      94,   152,   155,    -1,    91,   152,   155,    -1,    89,   152,
     156,    -1,    93,   152,   156,    -1,    92,   152,   156,    -1,
      20,   152,   155,    -1,    71,   152,   155,    -1,    75,   152,
     155,    -1,    55,   152,   155,    -1,    54,   152,   155,    -1,
      41,   152,   155,    -1,    67,   152,   155,    -1,    63,   152,
     155,    -1,    99,   152,   155,    -1,    71,   152,   154,   155,
      -1,    75,   152,   154,   155,    -1,    55,   152,   154,   155,
      -1,    54,   152,   154,   155,    -1,    41,   152,   154,   155,
      -1,    67,   152,   154,   155,    -1,    63,   152,   154,   155,
      -1,    99,   152,   154,   155,    -1,     3,    -1,     4,    -1,
       5,    -1,     6,    -1,     7,    -1,     8,    -1,     9,    -1,
      10,    -1,    11,    -1,    12,    -1,    13,    -1,    14,    -1,
     175,   153,    -1,   171,   175,   153,    -1,    25,    -1,    44,
      -1,   177,    -1,    65,    -1,    71,    -1,    75,    -1,    43,
     152,   156,    -1,    30,   152,   156,    -1,    31,   152,   155,
      -1,    38,   152,   155,    -1,    39,   152,   155,    -1,    76,
     152,   155,   155,   155,    -1,   136,   152,   167,    -1,   137,
     152,   167,    -1,   149,   152,   167,    -1,   150,   152,   167,
      -1,    24,   152,   155,    -1,    59,   152,   155,    -1,    21,
     152,   155,    -1,    71,   152,   172,    -1,   103,   152,   155,
      -1,   104,   152,   155,    -1,   105,   152,   155,    -1,   106,
     152,   155,    -1,   107,   152,   155,    -1,   108,   152,   155,
      -1,   109,   152,   155,    -1,   110,   152,   155,    -1,   111,
     152,   155,    -1,   112,   152,   155,    -1,   113,   152,   155,
      -1,   118,   152,   155,    -1,   119,   152,   155,    -1,   120,
     152,   155,    -1,   121,   152,   155,    -1,   122,   152,   155,
      -1,   123,   152,   155,    -1,   124,   152,   155,    -1,   125,
     152,   155,    -1,   126,   152,   155,    -1,   129,   152,   155,
      -1,   130,   152,   155,    -1,   131,   152,   155,    -1,   132,
     152,   155,    -1,   133,   152,   155,    -1,   134,   152,   155,
      -1,   135,   152,   155,    -1,   127,   152,   155,    -1,   140,
     152,   177,    -1,   141,   152,   177,    -1,   142,   152,   177,
      -1,   143,   152,   177,    -1,   145,   152,   177,    -1,   138,
     152,   177,    -1,   139,   152,   177,    -1,   144,   152,   155,
      -1,   146,   152,   155,    -1,   147,   152,   155,    -1,   148,
     152,   155,    -1,    57,   152,   155,    -1,    74,   152,   177,
      -1,    61,   152,   173,    -1,    72,   152,   174,    -1,    -1,
      15,   156,   176,   178,    -1,   170,   152,   166,    -1,   102,
      -1,   101,    -1,   179,   153,    -1,   178,   179,   153,    -1,
      17,   152,   177,    -1,    77,   152,   155,    -1,    16,   152,
     155,    -1,    56,   152,   155,    -1,    58,   152,   155,    -1,
      53,   152,   155,    -1,    52,   152,   155,    -1,    66,   152,
     177,    -1,    68,   152,   155,    -1,    69,   152,   155,    -1,
     114,   152,   155,    -1,   115,   152,   155,    -1,   116,   152,
     155,    -1,   117,   152,   155,    -1,   110,   152,   155,    -1,
     170,   152,   166,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   247,   247,   248,   252,   253,   258,   260,   262,   268,
     274,   280,   289,   288,   314,   313,   375,   376,   381,   382,
     387,   388,   393,   404,   410,   416,   422,   428,   434,   440,
     446,   452,   458,   464,   470,   476,   482,   488,   494,   500,
     506,   512,   518,   524,   529,   535,   541,   547,   553,   559,
     565,   571,   577,   583,   589,   595,   612,   628,   635,   641,
     647,   655,   663,   671,   677,   679,   681,   682,   683,   684,
     685,   686,   688,   690,   692,   693,   694,   695,   696,   697,
     702,   703,   704,   705,   706,   707,   708,   709,   710,   711,
     712,   713,   718,   719,   724,   724,   728,   728,   732,   732,
     736,   743,   750,   760,   767,   774,   785,   827,   869,   901,
     933,   939,   945,   951,   961,   967,   973,   979,   985,   991,
     997,  1003,  1009,  1015,  1021,  1027,  1033,  1039,  1045,  1051,
    1057,  1063,  1069,  1075,  1081,  1087,  1093,  1099,  1105,  1111,
    1117,  1123,  1129,  1139,  1149,  1159,  1169,  1179,  1189,  1199,
    1205,  1211,  1217,  1223,  1229,  1239,  1258,  1282,  1281,  1293,
    1310,  1310,  1315,  1316,  1321,  1327,  1334,  1340,  1346,  1352,
    1358,  1364,  1370,  1376,  1383,  1389,  1395,  1401,  1407,  1414
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_READ", "K_WRITE", "K_READ_LO",
  "K_READ_HI", "K_WRITE_LO", "K_WRITE_HI", "K_LOADPAGE_LO",
  "K_LOADPAGE_HI", "K_LOAD_EXT_ADDR", "K_WRITEPAGE", "K_CHIP_ERASE",
  "K_PGM_ENABLE", "K_MEMORY", "K_PAGE_SIZE", "K_PAGED", "K_ARDUINO",
  "K_AVRFTDI", "K_BAUDRATE", "K_BS2", "K_BUFF", "K_BUSPIRATE",
  "K_CHIP_ERASE_DELAY", "K_DEDICATED", "K_DEFAULT_PARALLEL",
  "K_DEFAULT_PROGRAMMER", "K_DEFAULT_SERIAL", "K_DEFAULT_BITCLOCK",
  "K_DESC", "K_DEVICECODE", "K_DRAGON_DW", "K_DRAGON_HVSP", "K_DRAGON_ISP",
  "K_DRAGON_JTAG", "K_DRAGON_PDI", "K_DRAGON_PP", "K_STK500_DEVCODE",
  "K_AVR910_DEVCODE", "K_EEPROM", "K_ERRLED", "K_FLASH", "K_ID", "K_IO",
  "K_JTAG_MKI", "K_JTAG_MKII", "K_JTAG_MKII_AVR32", "K_JTAG_MKII_DW",
  "K_JTAG_MKII_ISP", "K_JTAG_MKII_PDI", "K_LOADPAGE", "K_MAX_WRITE_DELAY",
  "K_MIN_WRITE_DELAY", "K_MISO", "K_MOSI", "K_NUM_PAGES", "K_NVM_BASE",
  "K_OFFSET", "K_PAGEL", "K_PAR", "K_PARALLEL", "K_PART", "K_PGMLED",
  "K_PROGRAMMER", "K_PSEUDO", "K_PWROFF_AFTER_WRITE", "K_RDYLED",
  "K_READBACK_P1", "K_READBACK_P2", "K_READMEM", "K_RESET",
  "K_RETRY_PULSE", "K_SERBB", "K_SERIAL", "K_SCK", "K_SIGNATURE", "K_SIZE",
  "K_STK500", "K_STK500HVSP", "K_STK500PP", "K_STK500V2",
  "K_STK500GENERIC", "K_STK600", "K_STK600HVSP", "K_STK600PP", "K_AVR910",
  "K_USBASP", "K_USBDEV", "K_USBSN", "K_USBTINY", "K_USBPID",
  "K_USBPRODUCT", "K_USBVENDOR", "K_USBVID", "K_BUTTERFLY",
  "K_BUTTERFLY_MK", "K_TYPE", "K_VCC", "K_VFYLED", "K_WIRING", "K_NO",
  "K_YES", "K_TIMEOUT", "K_STABDELAY", "K_CMDEXEDELAY",
  "K_HVSPCMDEXEDELAY", "K_SYNCHLOOPS", "K_BYTEDELAY", "K_POLLVALUE",
  "K_POLLINDEX", "K_PREDELAY", "K_POSTDELAY", "K_POLLMETHOD", "K_MODE",
  "K_DELAY", "K_BLOCKSIZE", "K_READSIZE", "K_HVENTERSTABDELAY",
  "K_PROGMODEDELAY", "K_LATCHCYCLES", "K_TOGGLEVTG", "K_POWEROFFDELAY",
  "K_RESETDELAYMS", "K_RESETDELAYUS", "K_HVLEAVESTABDELAY", "K_RESETDELAY",
  "K_SYNCHCYCLES", "K_HVCMDEXEDELAY", "K_CHIPERASEPULSEWIDTH",
  "K_CHIPERASEPOLLTIMEOUT", "K_CHIPERASETIME", "K_PROGRAMFUSEPULSEWIDTH",
  "K_PROGRAMFUSEPOLLTIMEOUT", "K_PROGRAMLOCKPULSEWIDTH",
  "K_PROGRAMLOCKPOLLTIMEOUT", "K_PP_CONTROLSTACK", "K_HVSP_CONTROLSTACK",
  "K_ALLOWFULLPAGEBITSTREAM", "K_ENABLEPAGEPROGRAMMING", "K_HAS_JTAG",
  "K_HAS_DW", "K_HAS_PDI", "K_HAS_TPI", "K_IDR", "K_IS_AVR32", "K_RAMPZ",
  "K_SPMCR", "K_EECR", "K_FLASH_INSTR", "K_EEPROM_INSTR", "TKN_COMMA",
  "TKN_EQUAL", "TKN_SEMI", "TKN_TILDE", "TKN_NUMBER", "TKN_STRING",
  "TKN_ID", "$accept", "configuration", "config", "def", "prog_def", "@1",
  "part_def", "@2", "string_list", "num_list", "prog_parms", "prog_parm",
  "opcode", "part_parms", "reset_disposition", "parallel_modes",
  "retry_lines", "part_parm", "@3", "yesno", "mem_specs", "mem_spec", 0
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
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   158,   159,   159,   160,   160,   161,   161,   161,   161,
     161,   161,   163,   162,   165,   164,   166,   166,   167,   167,
     168,   168,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     169,   169,   169,   169,   169,   169,   169,   169,   169,   169,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   171,   172,   172,   173,   173,   174,   174,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   176,   175,   175,
     177,   177,   178,   178,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     1,     1,     2,     2,     2,     4,     4,
       4,     4,     0,     3,     0,     3,     1,     3,     1,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     4,     4,     4,     4,     4,     4,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       1,     1,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     0,     0,    14,    12,     0,     3,     4,
       0,     0,     0,     0,     0,     0,     0,     0,     1,     5,
       6,     7,     0,     0,     0,     0,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    15,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    13,
       0,     9,     8,    10,    11,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    92,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,   112,
     110,   101,   102,   103,   104,   100,   153,   111,    97,   161,
     160,   155,    96,    94,    95,   113,    98,    99,   156,   154,
       0,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   141,   134,   135,   136,   137,   138,   139,   140,    18,
     106,   107,   147,   148,   142,   143,   144,   145,   149,   146,
     150,   151,   152,   108,   109,    16,   159,    93,    63,    56,
      54,     0,    68,    22,     0,    67,     0,    66,     0,    70,
       0,    69,     0,    64,     0,    65,    57,    60,    59,    62,
      61,    58,    31,    32,    33,    48,    49,    50,    51,    52,
      53,    42,    43,    44,    45,    46,    47,    23,    24,    25,
      28,    29,    26,    30,    34,    35,    36,    37,    38,    39,
      40,    41,    27,    55,     0,    71,    21,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,    76,    75,
      74,    78,    77,    72,    73,    79,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   162,   105,    19,    17,   166,   164,   170,
     169,   167,   168,   171,   172,   173,   165,   178,   174,   175,
     176,   177,   179,   163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     7,     8,     9,    10,    17,    11,    16,   276,   260,
     119,   120,    96,    97,   225,   221,   228,    98,   208,   222,
     353,   354
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -203
static const yytype_int16 yypact[] =
{
       1,  -150,  -126,  -121,  -114,  -203,  -203,    59,     1,  -203,
     -89,   -84,   -85,   -82,   -79,   -62,    37,   239,  -203,  -203,
    -203,  -203,   -58,   -56,   -48,   -47,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,   -54,   -45,
     -42,   -40,   -37,   -36,   -35,   -30,   -29,   -28,   -27,   -26,
     -25,   -24,   -23,   -21,   -20,   -19,   -18,   -17,   -16,   -15,
     -14,   -13,     0,     2,    13,    38,    39,    42,    43,    44,
      45,    46,    47,    48,    49,    56,    57,    58,    60,    61,
      62,    69,    70,    71,    72,    73,    74,    75,    76,    79,
      80,    81,    83,    84,    85,    86,    87,    37,    88,    90,
      92,    93,    94,    95,   106,   110,   111,   112,   115,   116,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   239,
     128,  -203,  -203,  -203,  -203,  -203,    -2,   129,    55,   130,
     131,   132,   133,   135,   136,   -12,   -22,   -52,   -97,   137,
     140,   141,   142,   143,   144,   145,   146,   148,   149,   150,
     152,   153,   154,   156,   157,   158,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   171,   174,   179,   179,
     -97,   -97,   -97,   -97,   -97,   -97,   180,   -97,   184,   185,
     186,   179,   179,   187,   172,  -203,   189,   179,   190,  -130,
     187,  -100,   -72,   -69,   -67,   -63,   -55,   191,   192,   194,
     195,   196,   198,   170,   179,   -51,   197,  -203,     4,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
     199,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
      89,    89,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,    89,    89,  -203,   204,  -203,  -203,    89,
    -203,   201,  -203,   204,   202,  -203,   203,  -203,   205,  -203,
     206,  -203,   207,  -203,   208,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,    89,   209,  -203,  -203,   193,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,     4,   228,   229,   230,   231,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,   233,   -97,   234,   235,
     236,   237,   -97,   238,   240,   241,   242,   243,   244,   245,
     246,   187,   249,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,   204,  -203
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -203,  -203,  -203,   275,  -203,  -203,  -203,  -203,  -189,  -103,
    -203,    11,  -202,  -203,  -203,  -203,  -203,   262,  -203,  -138,
    -203,   -65
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint16 yytable[] =
{
     229,   283,    12,   223,   219,   220,   352,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,   226,
     337,   338,   224,   227,   281,   282,    13,     1,     2,     3,
       4,    14,   262,   263,   264,   265,   266,   267,    15,   269,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,   218,   284,   285,   339,   340,    39,    18,
     341,    40,   342,     5,    20,     6,   261,    41,    42,    21,
     343,    22,   344,   345,    23,    43,    44,    24,   273,   274,
      45,   346,   286,   287,   279,   288,   289,   290,   291,   219,
     220,   292,   293,    25,    46,   121,    47,   122,    48,   294,
     295,   333,   125,   334,   335,   123,   124,   126,    49,    50,
     127,    51,   128,    52,   347,   129,   130,   131,   348,   349,
     350,   351,   132,   133,   134,   135,   136,   137,   138,   139,
     206,   140,   141,   142,   143,   144,   145,   146,   147,   148,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,   352,   149,   209,   150,    64,    65,    66,    67,    68,
      69,    70,    71,    72,    73,   151,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,   302,   303,
     152,   153,   402,   304,   154,   155,   156,   157,   158,   159,
     160,   161,   305,   306,   307,   308,   309,   310,   162,   163,
     164,   211,   165,   166,   167,   311,   312,   313,   314,   315,
     316,   168,   169,   170,   171,   172,   173,   174,   175,   388,
     317,   176,   177,   178,   393,   179,   180,   181,   182,   183,
     356,   185,   186,   318,   187,   188,   189,   190,   319,   320,
     321,   322,   323,   324,   325,   326,   327,   328,   191,    99,
     329,   100,   192,   193,   194,   330,   331,   195,   196,   101,
     332,   197,   198,   199,   200,   201,   202,   203,   204,   205,
     102,   207,   103,    19,   210,   212,   213,   214,   382,   215,
     216,   217,   230,   104,   105,   231,   232,   233,   234,   235,
     236,   237,   106,   238,   239,   240,   107,   241,   242,   243,
     108,   244,   245,   246,   109,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   277,   257,   110,   111,   258,
     112,   113,   114,   115,   259,   268,   116,   117,   118,   270,
     271,   272,     0,   275,   278,   366,   280,   296,   297,   298,
     336,   299,   300,   301,   355,   357,   358,   359,   360,   184,
     361,   362,   363,   364,   365,   367,   368,   369,   370,   371,
     372,   373,   374,   375,   376,   377,   378,   379,   380,   381,
       0,   383,     0,     0,   384,   385,     0,   386,   387,   389,
     390,   391,   392,   394,     0,   395,   396,   397,   398,   399,
     400,   401,   403
};

static const yytype_int16 yycheck[] =
{
     138,   190,   152,    25,   101,   102,   208,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    71,
      16,    17,    44,    75,   154,   155,   152,    26,    27,    28,
      29,   152,   170,   171,   172,   173,   174,   175,   152,   177,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    65,   154,   155,    52,    53,    21,     0,
      56,    24,    58,    62,   153,    64,   169,    30,    31,   153,
      66,   156,    68,    69,   156,    38,    39,   156,   181,   182,
      43,    77,   154,   155,   187,   154,   155,   154,   155,   101,
     102,   154,   155,   155,    57,   153,    59,   153,    61,   154,
     155,   204,   156,   154,   155,   153,   153,   152,    71,    72,
     152,    74,   152,    76,   110,   152,   152,   152,   114,   115,
     116,   117,   152,   152,   152,   152,   152,   152,   152,   152,
     119,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     103,   104,   105,   106,   107,   108,   109,   110,   111,   112,
     113,   353,   152,   155,   152,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   152,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,    18,    19,
     152,   152,   381,    23,   152,   152,   152,   152,   152,   152,
     152,   152,    32,    33,    34,    35,    36,    37,   152,   152,
     152,   156,   152,   152,   152,    45,    46,    47,    48,    49,
      50,   152,   152,   152,   152,   152,   152,   152,   152,   367,
      60,   152,   152,   152,   372,   152,   152,   152,   152,   152,
     151,   153,   152,    73,   152,   152,   152,   152,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,   152,    20,
      90,    22,   152,   152,   152,    95,    96,   152,   152,    30,
     100,   152,   152,   152,   152,   152,   152,   152,   152,   152,
      41,   153,    43,     8,   155,   155,   155,   155,   353,   156,
     155,   155,   155,    54,    55,   155,   155,   155,   155,   155,
     155,   155,    63,   155,   155,   155,    67,   155,   155,   155,
      71,   155,   155,   155,    75,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   153,   155,    88,    89,   155,
      91,    92,    93,    94,   155,   155,    97,    98,    99,   155,
     155,   155,    -1,   156,   155,   152,   156,   156,   156,   155,
     153,   156,   156,   155,   155,   151,   155,   155,   155,    97,
     155,   155,   155,   155,   155,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
      -1,   153,    -1,    -1,   155,   155,    -1,   156,   155,   155,
     155,   155,   155,   155,    -1,   155,   155,   155,   155,   155,
     155,   155,   153
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    26,    27,    28,    29,    62,    64,   159,   160,   161,
     162,   164,   152,   152,   152,   152,   165,   163,     0,   161,
     153,   153,   156,   156,   156,   155,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    21,
      24,    30,    31,    38,    39,    43,    57,    59,    61,    71,
      72,    74,    76,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   118,   119,   120,   121,   122,   123,
     124,   125,   126,   127,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   170,   171,   175,    20,
      22,    30,    41,    43,    54,    55,    63,    67,    71,    75,
      88,    89,    91,    92,    93,    94,    97,    98,    99,   168,
     169,   153,   153,   153,   153,   156,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   175,   153,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   169,   153,   176,   155,
     155,   156,   155,   155,   155,   156,   155,   155,    65,   101,
     102,   173,   177,    25,    44,   172,    71,    75,   174,   177,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     155,   155,   155,   155,   155,   155,   155,   155,   155,   155,
     167,   167,   177,   177,   177,   177,   177,   177,   155,   177,
     155,   155,   155,   167,   167,   156,   166,   153,   155,   167,
     156,   154,   155,   166,   154,   155,   154,   155,   154,   155,
     154,   155,   154,   155,   154,   155,   156,   156,   155,   156,
     156,   155,    18,    19,    23,    32,    33,    34,    35,    36,
      37,    45,    46,    47,    48,    49,    50,    60,    73,    78,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    90,
      95,    96,   100,   167,   154,   155,   153,    16,    17,    52,
      53,    56,    58,    66,    68,    69,    77,   110,   114,   115,
     116,   117,   170,   178,   179,   155,   151,   151,   155,   155,
     155,   155,   155,   155,   155,   155,   152,   152,   152,   152,
     152,   152,   152,   152,   152,   152,   152,   152,   152,   152,
     152,   152,   179,   153,   155,   155,   156,   155,   177,   155,
     155,   155,   155,   177,   155,   155,   155,   155,   155,   155,
     155,   155,   166,   153
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
        case 8:
#line 262 "config_gram.y"
    {
    strncpy(default_programmer, (yyvsp[(3) - (4)])->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 9:
#line 268 "config_gram.y"
    {
    strncpy(default_parallel, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 10:
#line 274 "config_gram.y"
    {
    strncpy(default_serial, (yyvsp[(3) - (4)])->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 11:
#line 280 "config_gram.y"
    {
    default_bitclock = (yyvsp[(3) - (4)])->value.number;
    free_token((yyvsp[(3) - (4)]));
  }
    break;

  case 12:
#line 289 "config_gram.y"
    { current_prog = pgm_new();
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
    break;

  case 13:
#line 294 "config_gram.y"
    { 
      if (lsize(current_prog->id) == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      if (current_prog->type[0] == 0) {
        fprintf(stderr, "%s: error at %s:%d: programmer type not specified\n",
                progname, infile, lineno);
        exit(1);
      }
      PUSH(programmers, current_prog); 
      current_prog = NULL; 
    }
    break;

  case 14:
#line 314 "config_gram.y"
    {
      current_part = avr_new_part();
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
    break;

  case 15:
#line 320 "config_gram.y"
    { 
      LNODEID ln;
      AVRMEM * m;

      if (current_part->id[0] == 0) {
        fprintf(stderr,
                "%s: error at %s:%d: required parameter id not specified\n",
                progname, infile, lineno);
        exit(1);
      }

      /*
       * perform some sanity checking, and compute the number of bits
       * to shift a page for constructing the page address for
       * page-addressed memories.
       */
      for (ln=lfirst(current_part->mem); ln; ln=lnext(ln)) {
        m = ldata(ln);
        if (m->paged) {
          if (m->page_size == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify page_size for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->num_pages == 0) {
            fprintf(stderr, 
                    "%s: error at %s:%d: must specify num_pages for paged "
                    "memory\n",
                    progname, infile, lineno);
            exit(1);
          }
          if (m->size != m->page_size * m->num_pages) {
            fprintf(stderr, 
                    "%s: error at %s:%d: page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)\n",
                    progname, infile, lineno,
                    m->page_size, 
                    m->num_pages, 
                    m->page_size * m->num_pages,
                    m->size);
            exit(1);
          }

        }
      }

      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
    break;

  case 16:
#line 375 "config_gram.y"
    { ladd(string_list, (yyvsp[(1) - (1)])); }
    break;

  case 17:
#line 376 "config_gram.y"
    { ladd(string_list, (yyvsp[(3) - (3)])); }
    break;

  case 18:
#line 381 "config_gram.y"
    { ladd(number_list, (yyvsp[(1) - (1)])); }
    break;

  case 19:
#line 382 "config_gram.y"
    { ladd(number_list, (yyvsp[(3) - (3)])); }
    break;

  case 22:
#line 393 "config_gram.y"
    {
    { 
      TOKEN * t;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        ladd(current_prog->id, dup_string(t->value.string));
        free_token(t);
      }
    }
  }
    break;

  case 23:
#line 404 "config_gram.y"
    {
    { 
      par_initpgm(current_prog);
    }
  }
    break;

  case 24:
#line 410 "config_gram.y"
    {
    {
      serbb_initpgm(current_prog);
    }
  }
    break;

  case 25:
#line 416 "config_gram.y"
    {
    { 
      stk500_initpgm(current_prog);
    }
  }
    break;

  case 26:
#line 422 "config_gram.y"
    {
    {
      stk500v2_initpgm(current_prog);
    }
  }
    break;

  case 27:
#line 428 "config_gram.y"
    {
    {
      wiring_initpgm(current_prog);
    }
  }
    break;

  case 28:
#line 434 "config_gram.y"
    {
    {
      stk500hvsp_initpgm(current_prog);
    }
  }
    break;

  case 29:
#line 440 "config_gram.y"
    {
    {
      stk500pp_initpgm(current_prog);
    }
  }
    break;

  case 30:
#line 446 "config_gram.y"
    {
    {
      stk500generic_initpgm(current_prog);
    }
  }
    break;

  case 31:
#line 452 "config_gram.y"
    {
    { 
      arduino_initpgm(current_prog);
    }
  }
    break;

  case 32:
#line 458 "config_gram.y"
    {
    {
      avrftdi_initpgm(current_prog);
    }
  }
    break;

  case 33:
#line 464 "config_gram.y"
    {
    {
      buspirate_initpgm(current_prog);
    }
  }
    break;

  case 34:
#line 470 "config_gram.y"
    {
    {
      stk600_initpgm(current_prog);
    }
  }
    break;

  case 35:
#line 476 "config_gram.y"
    {
    {
      stk600hvsp_initpgm(current_prog);
    }
  }
    break;

  case 36:
#line 482 "config_gram.y"
    {
    {
      stk600pp_initpgm(current_prog);
    }
  }
    break;

  case 37:
#line 488 "config_gram.y"
    {
    { 
      avr910_initpgm(current_prog);
    }
  }
    break;

  case 38:
#line 494 "config_gram.y"
    {
    {
      usbasp_initpgm(current_prog);
    }
  }
    break;

  case 39:
#line 500 "config_gram.y"
    {
    {
      usbtiny_initpgm(current_prog);
    }
  }
    break;

  case 40:
#line 506 "config_gram.y"
    {
    { 
      butterfly_initpgm(current_prog);
    }
  }
    break;

  case 41:
#line 512 "config_gram.y"
    {
    { 
      butterfly_mk_initpgm(current_prog);
    }
  }
    break;

  case 42:
#line 518 "config_gram.y"
    {
    {
      jtagmkI_initpgm(current_prog);
    }
  }
    break;

  case 43:
#line 524 "config_gram.y"
    {
    {
      jtagmkII_initpgm(current_prog);
    }
  }
    break;

  case 44:
#line 529 "config_gram.y"
    {
    {
      jtagmkII_avr32_initpgm(current_prog);
    }
  }
    break;

  case 45:
#line 535 "config_gram.y"
    {
    {
      jtagmkII_dw_initpgm(current_prog);
    }
  }
    break;

  case 46:
#line 541 "config_gram.y"
    {
    {
      stk500v2_jtagmkII_initpgm(current_prog);
    }
  }
    break;

  case 47:
#line 547 "config_gram.y"
    {
    {
      jtagmkII_pdi_initpgm(current_prog);
    }
  }
    break;

  case 48:
#line 553 "config_gram.y"
    {
    {
      jtagmkII_dragon_dw_initpgm(current_prog);
    }
  }
    break;

  case 49:
#line 559 "config_gram.y"
    {
    {
      stk500v2_dragon_hvsp_initpgm(current_prog);
    }
  }
    break;

  case 50:
#line 565 "config_gram.y"
    {
    {
      stk500v2_dragon_isp_initpgm(current_prog);
    }
  }
    break;

  case 51:
#line 571 "config_gram.y"
    {
    {
      jtagmkII_dragon_initpgm(current_prog);
    }
  }
    break;

  case 52:
#line 577 "config_gram.y"
    {
    {
      jtagmkII_dragon_pdi_initpgm(current_prog);
    }
  }
    break;

  case 53:
#line 583 "config_gram.y"
    {
    {
      stk500v2_dragon_pp_initpgm(current_prog);
    }
  }
    break;

  case 54:
#line 589 "config_gram.y"
    {
    strncpy(current_prog->desc, (yyvsp[(3) - (3)])->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token((yyvsp[(3) - (3)]));
  }
    break;

  case 55:
#line 595 "config_gram.y"
    {
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_VCC] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_VCC] |= (1 << pin);

        free_token(t);
      }
    }
  }
    break;

  case 56:
#line 612 "config_gram.y"
    {
    { 
      TOKEN * t;
      int pin;

      current_prog->pinno[PPI_AVR_BUFF] = 0;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
        pin = t->value.number;
        current_prog->pinno[PPI_AVR_BUFF] |= (1 << pin);

        free_token(t);
      }
    }
  }
    break;

  case 57:
#line 628 "config_gram.y"
    {
    {
      strncpy(current_prog->usbdev, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbdev[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 58:
#line 635 "config_gram.y"
    {
    {
      current_prog->usbvid = (yyvsp[(3) - (3)])->value.number;
    }
  }
    break;

  case 59:
#line 641 "config_gram.y"
    {
    {
      current_prog->usbpid = (yyvsp[(3) - (3)])->value.number;
    }
  }
    break;

  case 60:
#line 647 "config_gram.y"
    {
    {
      strncpy(current_prog->usbsn, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbsn[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 61:
#line 655 "config_gram.y"
    {
    {
      strncpy(current_prog->usbvendor, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbvendor[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 62:
#line 663 "config_gram.y"
    {
    {
      strncpy(current_prog->usbproduct, (yyvsp[(3) - (3)])->value.string, PGM_USBSTRINGLEN);
      current_prog->usbproduct[PGM_USBSTRINGLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 63:
#line 671 "config_gram.y"
    {
    {
      current_prog->baudrate = (yyvsp[(3) - (3)])->value.number;
    }
  }
    break;

  case 64:
#line 677 "config_gram.y"
    { free_token((yyvsp[(1) - (3)])); 
                                  assign_pin(PIN_AVR_RESET, (yyvsp[(3) - (3)]), 0); }
    break;

  case 65:
#line 679 "config_gram.y"
    { free_token((yyvsp[(1) - (3)])); 
                                  assign_pin(PIN_AVR_SCK, (yyvsp[(3) - (3)]), 0); }
    break;

  case 66:
#line 681 "config_gram.y"
    { assign_pin(PIN_AVR_MOSI, (yyvsp[(3) - (3)]), 0); }
    break;

  case 67:
#line 682 "config_gram.y"
    { assign_pin(PIN_AVR_MISO, (yyvsp[(3) - (3)]), 0); }
    break;

  case 68:
#line 683 "config_gram.y"
    { assign_pin(PIN_LED_ERR, (yyvsp[(3) - (3)]), 0); }
    break;

  case 69:
#line 684 "config_gram.y"
    { assign_pin(PIN_LED_RDY, (yyvsp[(3) - (3)]), 0); }
    break;

  case 70:
#line 685 "config_gram.y"
    { assign_pin(PIN_LED_PGM, (yyvsp[(3) - (3)]), 0); }
    break;

  case 71:
#line 686 "config_gram.y"
    { assign_pin(PIN_LED_VFY, (yyvsp[(3) - (3)]), 0); }
    break;

  case 72:
#line 688 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); 
                                  assign_pin(PIN_AVR_RESET, (yyvsp[(4) - (4)]), 1); }
    break;

  case 73:
#line 690 "config_gram.y"
    { free_token((yyvsp[(1) - (4)])); 
                                  assign_pin(PIN_AVR_SCK, (yyvsp[(4) - (4)]), 1); }
    break;

  case 74:
#line 692 "config_gram.y"
    { assign_pin(PIN_AVR_MOSI, (yyvsp[(4) - (4)]), 1); }
    break;

  case 75:
#line 693 "config_gram.y"
    { assign_pin(PIN_AVR_MISO, (yyvsp[(4) - (4)]), 1); }
    break;

  case 76:
#line 694 "config_gram.y"
    { assign_pin(PIN_LED_ERR, (yyvsp[(4) - (4)]), 1); }
    break;

  case 77:
#line 695 "config_gram.y"
    { assign_pin(PIN_LED_RDY, (yyvsp[(4) - (4)]), 1); }
    break;

  case 78:
#line 696 "config_gram.y"
    { assign_pin(PIN_LED_PGM, (yyvsp[(4) - (4)]), 1); }
    break;

  case 79:
#line 697 "config_gram.y"
    { assign_pin(PIN_LED_VFY, (yyvsp[(4) - (4)]), 1); }
    break;

  case 100:
#line 737 "config_gram.y"
    {
      strncpy(current_part->id, (yyvsp[(3) - (3)])->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 101:
#line 744 "config_gram.y"
    {
      strncpy(current_part->desc, (yyvsp[(3) - (3)])->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 102:
#line 750 "config_gram.y"
    {
    {
      fprintf(stderr, 
              "%s: error at %s:%d: devicecode is deprecated, use "
              "stk500_devcode instead\n",
              progname, infile, lineno);
      exit(1);
    }
  }
    break;

  case 103:
#line 760 "config_gram.y"
    {
    {
      current_part->stk500_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 104:
#line 767 "config_gram.y"
    {
    {
      current_part->avr910_devcode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
  }
    break;

  case 105:
#line 774 "config_gram.y"
    {
    {
      current_part->signature[0] = (yyvsp[(3) - (5)])->value.number;
      current_part->signature[1] = (yyvsp[(4) - (5)])->value.number;
      current_part->signature[2] = (yyvsp[(5) - (5)])->value.number;
      free_token((yyvsp[(3) - (5)]));
      free_token((yyvsp[(4) - (5)]));
      free_token((yyvsp[(5) - (5)]));
    }
  }
    break;

  case 106:
#line 785 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_PP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 107:
#line 827 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      if (current_part->ctl_stack_type != CTL_STACK_NONE)
	{
	  fprintf(stderr,
		  "%s: error at line %d of %s: "
		  "control stack already defined\n",
		  progname, lineno, infile);
	  exit(1);
	}

      current_part->ctl_stack_type = CTL_STACK_HVSP;
      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in control stack\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 108:
#line 869 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < FLASH_INSTR_SIZE)
	  {
	    current_part->flash_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in flash instructions\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 109:
#line 901 "config_gram.y"
    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < EEPROM_INSTR_SIZE)
	  {
	    current_part->eeprom_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  fprintf(stderr,
                  "%s: Warning: line %d of %s: "
		  "too many bytes in EEPROM instructions\n",
                  progname, lineno, infile);
        }
    }
  }
    break;

  case 110:
#line 934 "config_gram.y"
    {
      current_part->chip_erase_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 111:
#line 940 "config_gram.y"
    {
      current_part->pagel = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 112:
#line 946 "config_gram.y"
    {
      current_part->bs2 = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 113:
#line 952 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if ((yyvsp[(3) - (3)])->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]));
    }
    break;

  case 114:
#line 962 "config_gram.y"
    {
      current_part->timeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 115:
#line 968 "config_gram.y"
    {
      current_part->stabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 116:
#line 974 "config_gram.y"
    {
      current_part->cmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 117:
#line 980 "config_gram.y"
    {
      current_part->hvspcmdexedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 118:
#line 986 "config_gram.y"
    {
      current_part->synchloops = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 119:
#line 992 "config_gram.y"
    {
      current_part->bytedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 120:
#line 998 "config_gram.y"
    {
      current_part->pollvalue = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 121:
#line 1004 "config_gram.y"
    {
      current_part->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 122:
#line 1010 "config_gram.y"
    {
      current_part->predelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 123:
#line 1016 "config_gram.y"
    {
      current_part->postdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 124:
#line 1022 "config_gram.y"
    {
      current_part->pollmethod = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 125:
#line 1028 "config_gram.y"
    {
      current_part->hventerstabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 126:
#line 1034 "config_gram.y"
    {
      current_part->progmodedelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 127:
#line 1040 "config_gram.y"
    {
      current_part->latchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 128:
#line 1046 "config_gram.y"
    {
      current_part->togglevtg = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 129:
#line 1052 "config_gram.y"
    {
      current_part->poweroffdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 130:
#line 1058 "config_gram.y"
    {
      current_part->resetdelayms = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 131:
#line 1064 "config_gram.y"
    {
      current_part->resetdelayus = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 132:
#line 1070 "config_gram.y"
    {
      current_part->hvleavestabdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 133:
#line 1076 "config_gram.y"
    {
      current_part->resetdelay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 134:
#line 1082 "config_gram.y"
    {
      current_part->chiperasepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 135:
#line 1088 "config_gram.y"
    {
      current_part->chiperasepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 136:
#line 1094 "config_gram.y"
    {
      current_part->chiperasetime = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 137:
#line 1100 "config_gram.y"
    {
      current_part->programfusepulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 138:
#line 1106 "config_gram.y"
    {
      current_part->programfusepolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 139:
#line 1112 "config_gram.y"
    {
      current_part->programlockpulsewidth = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 140:
#line 1118 "config_gram.y"
    {
      current_part->programlockpolltimeout = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 141:
#line 1124 "config_gram.y"
    {
      current_part->synchcycles = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 142:
#line 1130 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 143:
#line 1140 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 144:
#line 1150 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 145:
#line 1160 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 146:
#line 1170 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= AVRPART_AVR32;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 147:
#line 1180 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 148:
#line 1190 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 149:
#line 1200 "config_gram.y"
    {
      current_part->idr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 150:
#line 1206 "config_gram.y"
    {
      current_part->rampz = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 151:
#line 1212 "config_gram.y"
    {
      current_part->spmcr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 152:
#line 1218 "config_gram.y"
    {
      current_part->eecr = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 153:
#line 1224 "config_gram.y"
    {
      current_part->nvm_base = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 154:
#line 1230 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if ((yyvsp[(3) - (3)])->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 155:
#line 1240 "config_gram.y"
    {
      if ((yyvsp[(3) - (3)])->primary == K_YES) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[(3) - (3)])->primary == K_NO) {
        current_part->flags &= ~AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if ((yyvsp[(3) - (3)])->primary == K_PSEUDO) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags |= AVRPART_PSEUDOPARALLEL;
      }


      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 156:
#line 1259 "config_gram.y"
    {
      switch ((yyvsp[(3) - (3)])->primary) {
        case K_RESET :
          current_part->retry_pulse = PIN_AVR_RESET;
          break;
        case K_SCK :
          current_part->retry_pulse = PIN_AVR_SCK;
          break;
      }

      free_token((yyvsp[(1) - (3)]));
    }
    break;

  case 157:
#line 1282 "config_gram.y"
    { 
      current_mem = avr_new_memtype(); 
      strcpy(current_mem->desc, strdup((yyvsp[(2) - (2)])->value.string)); 
      free_token((yyvsp[(2) - (2)])); 
    }
    break;

  case 158:
#line 1288 "config_gram.y"
    { 
      ladd(current_part->mem, current_mem); 
      current_mem = NULL; 
    }
    break;

  case 159:
#line 1293 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_part->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;

  case 164:
#line 1322 "config_gram.y"
    {
      current_mem->paged = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 165:
#line 1328 "config_gram.y"
    {
      current_mem->size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 166:
#line 1335 "config_gram.y"
    {
      current_mem->page_size = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 167:
#line 1341 "config_gram.y"
    {
      current_mem->num_pages = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 168:
#line 1347 "config_gram.y"
    {
      current_mem->offset = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 169:
#line 1353 "config_gram.y"
    {
      current_mem->min_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 170:
#line 1359 "config_gram.y"
    {
      current_mem->max_write_delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 171:
#line 1365 "config_gram.y"
    {
      current_mem->pwroff_after_write = (yyvsp[(3) - (3)])->primary == K_YES ? 1 : 0;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 172:
#line 1371 "config_gram.y"
    {
      current_mem->readback[0] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 173:
#line 1377 "config_gram.y"
    {
      current_mem->readback[1] = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 174:
#line 1384 "config_gram.y"
    {
      current_mem->mode = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 175:
#line 1390 "config_gram.y"
    {
      current_mem->delay = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 176:
#line 1396 "config_gram.y"
    {
      current_mem->blocksize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 177:
#line 1402 "config_gram.y"
    {
      current_mem->readsize = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 178:
#line 1408 "config_gram.y"
    {
      current_mem->pollindex = (yyvsp[(3) - (3)])->value.number;
      free_token((yyvsp[(3) - (3)]));
    }
    break;

  case 179:
#line 1414 "config_gram.y"
    {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode((yyvsp[(1) - (3)]));
      op = avr_new_opcode();
      parse_cmdbits(op);
      current_mem->op[opnum] = op;

      free_token((yyvsp[(1) - (3)]));
    }
  }
    break;


/* Line 1267 of yacc.c.  */
#line 3524 "config_gram.c"
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
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
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


#line 1430 "config_gram.y"


#if 0
static char * vtypestr(int type)
{
  switch (type) {
    case V_NUM : return "NUMERIC";
    case V_STR : return "STRING";
    default:
      return "<UNKNOWN>";
  }
}
#endif


static int assign_pin(int pinno, TOKEN * v, int invert)
{
  int value;

  value = v->value.number;

  if ((value <= 0) || (value >= 18)) {
    fprintf(stderr, 
            "%s: error at line %d of %s: pin must be in the "
            "range 1-17\n",
            progname, lineno, infile);
    exit(1);
  }
  if (invert)
    value |= PIN_INVERSE;

  current_prog->pinno[pinno] = value;

  return 0;
}


static int which_opcode(TOKEN * opcode)
{
  switch (opcode->primary) {
    case K_READ        : return AVR_OP_READ; break;
    case K_WRITE       : return AVR_OP_WRITE; break;
    case K_READ_LO     : return AVR_OP_READ_LO; break;
    case K_READ_HI     : return AVR_OP_READ_HI; break;
    case K_WRITE_LO    : return AVR_OP_WRITE_LO; break;
    case K_WRITE_HI    : return AVR_OP_WRITE_HI; break;
    case K_LOADPAGE_LO : return AVR_OP_LOADPAGE_LO; break;
    case K_LOADPAGE_HI : return AVR_OP_LOADPAGE_HI; break;
    case K_LOAD_EXT_ADDR : return AVR_OP_LOAD_EXT_ADDR; break;
    case K_WRITEPAGE   : return AVR_OP_WRITEPAGE; break;
    case K_CHIP_ERASE  : return AVR_OP_CHIP_ERASE; break;
    case K_PGM_ENABLE  : return AVR_OP_PGM_ENABLE; break;
    default :
      fprintf(stderr, 
              "%s: error at %s:%d: invalid opcode\n",
              progname, infile, lineno);
      exit(1);
      break;
  }
}


static int parse_cmdbits(OPCODE * op)
{
  TOKEN * t;
  int bitno;
  char ch;
  char * e;
  char * q;
  int len;
  char * s, *brkt = NULL;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (s != NULL) {

      bitno--;
      if (bitno < 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: too many opcode bits for instruction\n",
                progname, infile, lineno);
        exit(1);
      }

      len = strlen(s);

      if (len == 0) {
        fprintf(stderr, 
                "%s: error at %s:%d: invalid bit specifier \"\"\n",
                progname, infile, lineno);
        exit(1);
      }

      ch = s[0];

      if (len == 1) {
        switch (ch) {
          case '1':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 1;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case '0':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'x':
            op->bit[bitno].type  = AVR_CMDBIT_IGNORE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'a':
            op->bit[bitno].type  = AVR_CMDBIT_ADDRESS;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = 8*(bitno/8) + bitno % 8;
            break;
          case 'i':
            op->bit[bitno].type  = AVR_CMDBIT_INPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'o':
            op->bit[bitno].type  = AVR_CMDBIT_OUTPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          default :
            fprintf(stderr, 
                    "%s: error at %s:%d: invalid bit specifier '%c'\n",
                    progname, infile, lineno, ch);
            exit(1);
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            fprintf(stderr, 
                    "%s: error at %s:%d: can't parse bit number from \"%s\"\n",
                    progname, infile, lineno, q);
            exit(1);
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          fprintf(stderr, 
                  "%s: error at %s:%d: invalid bit specifier \"%s\"\n",
                  progname, infile, lineno, s);
          exit(1);
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    }

    free_token(t);

  }  /* while */

  return 0;
}




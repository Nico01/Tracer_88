/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "as.y" /* yacc.c:339  */

#include <stdio.h>
#include <ctype.h>
#include <signal.h>

struct outhead {
    unsigned short oh_magic;
    unsigned short oh_stamp;
    unsigned short oh_flags;
    unsigned short oh_nsect;
    unsigned short oh_nrelo;
    unsigned short oh_nname;
    long oh_nemit;
    long oh_nchar;
};

struct outsect {
    long os_base;
    long os_size;
    long os_foff;
    long os_flen;
    long os_lign;
};

struct outrelo {
    char or_type;
    char or_sect;
    unsigned short or_nami;
    long or_addr;
};

struct outname {
    union {
      char *on_ptr;
      long on_off;
    } on_u;

    unsigned short on_type;
    unsigned short on_desc;
    long on_valu;
};

struct expr_t {
    short typ;
    long val;
};

typedef struct expr_t expr_t;

struct item_t {
    struct item_t *i_next;
    short i_type;
    long i_valu;
    char *i_name;
};

struct common_t {
    struct common_t *c_next;
    struct item_t *c_it;
    long c_size;
};

typedef struct common_t common_t;

typedef struct item_t item_t;

struct sect_t {
    short s_flag;
    unsigned short s_base;
    unsigned short s_size;
    unsigned short s_comm;
    unsigned short s_zero;
    unsigned short s_lign;
    long s_foff;
    item_t *s_item;
    unsigned short s_gain;
};

typedef struct sect_t sect_t;

extern FILE *fopen();

extern short pass;
extern short peekc;
extern short unresolved;
extern long lineno;
extern short hllino;
extern short nerrors;
extern short sflag ;

extern char *progname;
extern char *modulename;
extern common_t *commons;

extern short uflag;
extern short dflag;
extern long relonami;
extern short bflag;

extern char *aoutpath ;
extern char temppath[50];

extern FILE *input;
extern FILE *tempfile;
extern FILE *outFile;

extern char *stringbuf;
extern int  stringlen;

extern sect_t sect[64];

extern sect_t *DOTSCT;
extern unsigned short DOTVAL;
extern short DOTTYP;

extern unsigned short nname;

extern item_t *hashtab[(2*307        )];
extern short hashindex;

extern item_t *fb_ptr[4*10];

extern int nbits;
extern int bitindex;

extern short listmode;
extern short listtemp;
extern short listflag;
extern short listcolm;
extern short listeoln;

extern FILE *listfile;
extern char listpath[50];

extern item_t keytab[];
extern struct outhead outhead;

extern char *remember();
extern item_t *fb_shift();
extern item_t *fb_alloc();
extern item_t *item_alloc();
extern item_t *item_search();

extern long load();

extern FILE *ffcreat();
extern FILE *fftemp();

int yylex(void);

void newequate(item_t *ip, int typ);
void newident(item_t *ip, int typ);
void newlabel(item_t *ip);
void newsect(item_t *ip);
void newbase(long base);
void newcomm(item_t *ip, long val);
void switchsect(int newtyp);
void align(long bytes);
long new_string(char *s);
void newsymb(char *name, int type, int desc, long valu);
void new_common(item_t *ip);
void newrelo(int s, int n);

int store(item_t *ip, long val);
char *remember(char *s);
int combine(int typ1, int typ2, int op);
int small(int fitsmall, int gain);
void emit1(int arg);
void emit2(int arg);
void emit4(long arg);
void emitx(long val, int n);
void emitstr(int zero);
void yyerror(char *str);
int printx(int ndig, long val);
void nosect(void);
void wr_fatal(void);
void fatal(char *s, ...);
void assert1(void);
void assert2(char *file, int line);
void serror(char *s, ...);
void warning(char *s, ...);
void diag(char *tail, char *s, ...);
void nofit(void);
void listline(int textline);

void ea_1(int param);
void ea_2(int param);
void regsize(int sz);
void indexed(void);
void branch(int opc, expr_t exp);
void pushop(int opc);
void addop(int opc);
void rolop(int opc);
void incop(int opc);
void callop(int opc);
void xchg(int opc);
void test(int opc);
void mov(int opc);
void imul(int opc);


extern char *mktemp();
/*
extern char    *malloc();
extern char    *realloc();
extern char    *calloc();
*/

extern char *getenv();
extern char *strncpy();

extern int mrg_1, mrg_2;
extern expr_t exp_1, exp_2;

extern int rel_1, rel_2;

extern char sr_m[8];
extern char dr_m[8][8];

static item_t *last_it, *o_it;

#line 288 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif


/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    STRING = 258,
    IDENT = 259,
    FBSYM = 260,
    CODE1 = 261,
    CODE2 = 262,
    CODE4 = 263,
    NUMBER0 = 264,
    NUMBER1 = 265,
    NUMBER2 = 266,
    NUMBER3 = 267,
    NUMBER = 268,
    DOT = 269,
    EXTERN = 270,
    DATA = 271,
    ASCII = 272,
    SECTION = 273,
    COMMON = 274,
    BASE = 275,
    SYMB = 276,
    SYMD = 277,
    ALIGN = 278,
    ASSERT = 279,
    SPACE = 280,
    LINE = 281,
    FILe = 282,
    LIST = 283,
    OP_EQ = 284,
    OP_NE = 285,
    OP_LE = 286,
    OP_GE = 287,
    OP_LL = 288,
    OP_RR = 289,
    OP_OO = 290,
    OP_AA = 291,
    R16 = 292,
    R8 = 293,
    RSEG = 294,
    PREFIX = 295,
    NOOP_1 = 296,
    NOOP_2 = 297,
    JOP = 298,
    PUSHOP = 299,
    IOOP = 300,
    ADDOP = 301,
    ROLOP = 302,
    INCOP = 303,
    NOTOP = 304,
    CALLOP = 305,
    CALFOP = 306,
    LEAOP = 307,
    ARPLOP = 308,
    ESC = 309,
    INT = 310,
    RET = 311,
    XCHG = 312,
    TEST = 313,
    MOV = 314,
    IMUL = 315,
    ENTER = 316,
    EXTOP = 317,
    EXTOP1 = 318,
    ST = 319
  };
#endif
/* Tokens.  */
#define STRING 258
#define IDENT 259
#define FBSYM 260
#define CODE1 261
#define CODE2 262
#define CODE4 263
#define NUMBER0 264
#define NUMBER1 265
#define NUMBER2 266
#define NUMBER3 267
#define NUMBER 268
#define DOT 269
#define EXTERN 270
#define DATA 271
#define ASCII 272
#define SECTION 273
#define COMMON 274
#define BASE 275
#define SYMB 276
#define SYMD 277
#define ALIGN 278
#define ASSERT 279
#define SPACE 280
#define LINE 281
#define FILe 282
#define LIST 283
#define OP_EQ 284
#define OP_NE 285
#define OP_LE 286
#define OP_GE 287
#define OP_LL 288
#define OP_RR 289
#define OP_OO 290
#define OP_AA 291
#define R16 292
#define R8 293
#define RSEG 294
#define PREFIX 295
#define NOOP_1 296
#define NOOP_2 297
#define JOP 298
#define PUSHOP 299
#define IOOP 300
#define ADDOP 301
#define ROLOP 302
#define INCOP 303
#define NOTOP 304
#define CALLOP 305
#define CALFOP 306
#define LEAOP 307
#define ARPLOP 308
#define ESC 309
#define INT 310
#define RET 311
#define XCHG 312
#define TEST 313
#define MOV 314
#define IMUL 315
#define ENTER 316
#define EXTOP 317
#define EXTOP1 318
#define ST 319

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 223 "as.y" /* yacc.c:355  */

    short y_word;
    long y_valu;
    expr_t y_expr;
    item_t *y_item;

#line 460 "y.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);



/* Copy the second part of user declarations.  */

#line 475 "y.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   608

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  108
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   319

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      78,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,    79,     2,    46,    39,     2,
      84,    85,    44,    42,    81,    43,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    76,    77,
      40,    80,    41,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    82,     2,    83,    38,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    37,     2,    47,     2,     2,     2,
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
      35,    36,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   317,   317,   319,   321,   328,   330,   332,   334,   335,
     338,   344,   352,   354,   364,   371,   373,   375,   377,   381,
     381,   421,   435,   449,   460,   461,   463,   469,   470,   474,
     476,   480,   488,   497,   501,   503,   508,   514,   516,   520,
     524,   528,   532,   536,   540,   544,   548,   552,   556,   560,
     564,   568,   572,   576,   580,   589,   598,   602,   606,   610,
     615,   616,   618,   626,   627,   632,   633,   638,   640,   641,
     644,   646,   648,   650,   652,   659,   663,   665,   667,   669,
     671,   673,   675,   677,   688,   690,   694,   696,   698,   702,
     706,   711,   718,   720,   727,   729,   731,   742,   746,   748,
     753,   755,   758,   759,   761,   763,   765,   770,   775
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "STRING", "IDENT", "FBSYM", "CODE1",
  "CODE2", "CODE4", "NUMBER0", "NUMBER1", "NUMBER2", "NUMBER3", "NUMBER",
  "DOT", "EXTERN", "DATA", "ASCII", "SECTION", "COMMON", "BASE", "SYMB",
  "SYMD", "ALIGN", "ASSERT", "SPACE", "LINE", "FILe", "LIST", "OP_EQ",
  "OP_NE", "OP_LE", "OP_GE", "OP_LL", "OP_RR", "OP_OO", "OP_AA", "'|'",
  "'^'", "'&'", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", "'~'",
  "R16", "R8", "RSEG", "PREFIX", "NOOP_1", "NOOP_2", "JOP", "PUSHOP",
  "IOOP", "ADDOP", "ROLOP", "INCOP", "NOTOP", "CALLOP", "CALFOP", "LEAOP",
  "ARPLOP", "ESC", "INT", "RET", "XCHG", "TEST", "MOV", "IMUL", "ENTER",
  "EXTOP", "EXTOP1", "ST", "':'", "';'", "'\\n'", "'#'", "'='", "','",
  "'['", "']'", "'('", "')'", "$accept", "program", "operation", "$@1",
  "externlist", "datalist", "expr", "id_fb", "absexp", "optabs1",
  "optabs2", "prefix", "oper", "mem", "bases", "ea_2", "ea_1", "ea_ea", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   124,    94,    38,
      60,    62,    43,    45,    42,    47,    37,   126,   292,   293,
     294,   295,   296,   297,   298,   299,   300,   301,   302,   303,
     304,   305,   306,   307,   308,   309,   310,   311,   312,   313,
     314,   315,   316,   317,   318,   319,    58,    59,    10,    35,
      61,    44,    91,    93,    40,    41
};
# endif

#define YYPACT_NINF -173

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-173)))

#define YYTABLE_NINF -93

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -173,   287,  -173,   -73,   -60,  -173,  -173,  -173,   -57,    11,
     234,    30,    34,    37,   234,    39,    43,   132,   234,   234,
     132,    44,  -173,    40,   -75,   415,  -173,  -173,   234,  -173,
    -173,   -26,  -173,  -173,  -173,  -173,  -173,  -173,   234,   234,
     234,   234,   -18,   474,  -173,  -173,  -173,   -13,   474,  -173,
     -12,   -11,  -173,  -173,   474,  -173,  -173,  -173,    68,  -173,
    -173,  -173,  -173,  -173,   234,    31,   203,    31,    31,    31,
      31,    31,   113,    27,   113,   234,   234,   149,    31,    31,
      31,    31,   234,    28,    31,  -173,   474,    73,  -173,  -173,
    -173,   419,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,   234,   234,   234,   234,   234,   234,
     234,   234,   234,   234,    32,   474,  -173,  -173,  -173,   219,
     363,  -173,  -173,  -173,  -173,  -173,   474,    25,  -173,  -173,
    -173,  -173,  -173,   345,  -173,    26,   363,    41,    42,  -173,
     474,  -173,  -173,  -173,    25,  -173,    47,    48,  -173,  -173,
    -173,   474,   562,   562,   156,   156,    15,    15,   394,   492,
     510,   528,   546,   156,   156,   -22,   -22,  -173,  -173,  -173,
    -173,   474,    49,  -173,    23,   288,    64,  -173,    31,   234,
     113,    72,   113,   234,    31,    50,   234,    54,  -173,  -173,
     474,  -173,  -173,  -173,  -173,  -173,   234,    50,  -173,    76,
    -173,  -173,    56,  -173
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     1,     0,     0,     5,     6,     7,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,     0,     0,     0,    11,     3,     0,     4,
      29,    24,    33,    36,    60,    61,    34,    59,     0,     0,
       0,     0,    27,    31,    35,    28,    15,     0,    62,    17,
       0,     0,    64,    25,    18,    26,    22,    23,     0,     8,
       9,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    67,    13,     0,    56,    57,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    72,   104,   103,   105,     0,
     106,   102,    98,   107,    73,    75,    74,     0,    76,    77,
      78,    81,    82,     0,    84,     0,     0,     0,     0,    91,
      93,    94,    95,    96,    80,    79,     0,     0,    89,    30,
      37,    32,    43,    44,    47,    48,    50,    49,    38,    39,
      40,    41,    42,    45,    46,    51,    52,    53,    54,    55,
      16,    19,     0,    10,     0,     0,     0,    99,     0,     0,
       0,     0,     0,     0,     0,    65,     0,   100,    97,   108,
      83,    86,    87,    90,    85,    88,     0,    65,    21,     0,
      66,    20,     0,   101
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,  -173,  -173,  -173,  -173,   -10,  -173,    29,   105,
     -65,  -173,  -173,   -61,  -119,  -172,   -44,   -29
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,    24,   185,    31,    42,   120,    44,    52,    53,
     197,    25,    85,   121,   122,   123,   127,   128
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   177,    59,    60,    48,    26,   189,    48,    54,    48,
      48,   134,   195,   137,   177,    30,    27,   177,    86,    29,
      28,   124,   108,   109,   110,   130,   131,   132,    88,    89,
      90,    91,    32,    45,    33,    34,    35,   144,    46,   129,
     148,    47,    50,    49,    36,    37,    51,    57,    55,   141,
     142,   143,   145,    58,   115,    87,   126,   106,   107,   108,
     109,   110,   133,    92,   136,    48,    48,   140,   111,   112,
     113,   114,    48,    38,    39,   135,   147,   149,    40,   116,
     117,   118,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
     169,    48,   171,    48,   138,   139,   178,   180,   187,   175,
     173,   146,   174,    41,    32,   119,    33,    34,    35,   191,
     192,   193,   181,   182,   202,    56,    36,    37,   183,   184,
     186,   196,   201,    32,     0,    33,    34,    35,   199,     0,
     170,   203,   172,     0,     0,    36,    37,     0,     0,     0,
      32,     0,    33,    34,    35,    38,    39,     0,     0,     0,
      40,     0,    36,    37,     0,     0,     0,     0,     0,   190,
     136,     0,   136,    48,    38,    39,    48,     0,     0,    40,
       0,     0,     0,     0,     0,     0,    48,     0,     0,    97,
      98,    38,    39,     0,     0,    41,    40,   119,   106,   107,
     108,   109,   110,     0,    32,     0,    33,    34,    35,   -63,
     -63,     0,   194,     0,    41,   198,    36,    37,     0,     0,
      32,     0,    33,    34,    35,   200,   -92,   -92,     0,     0,
       0,    41,    36,    37,     0,    32,     0,    33,    34,    35,
       0,     0,     0,     0,     0,    38,    39,    36,    37,     0,
      40,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    38,    39,     0,     0,     0,    40,   174,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,     0,     0,
       0,    40,     0,     0,     0,    41,     0,     2,     3,     0,
       0,     4,     0,     5,     6,     7,     0,     0,     0,     0,
       8,    41,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    41,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,     0,     0,     0,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,   -68,
     -68,   -68,     0,     0,   -12,   -12,    23,     0,     0,     0,
       0,     0,     0,   188,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,    93,    94,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   179,     0,    93,    94,    95,    96,    97,    98,   176,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,     0,     0,   176,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   150,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,    93,    94,    95,    96,    97,    98,     0,     0,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,    93,
      94,    95,    96,    97,    98,     0,     0,     0,   102,   103,
     104,   105,   106,   107,   108,   109,   110,    93,    94,    95,
      96,    97,    98,     0,     0,     0,     0,   103,   104,   105,
     106,   107,   108,   109,   110,    93,    94,    95,    96,    97,
      98,     0,     0,     0,     0,     0,   104,   105,   106,   107,
     108,   109,   110,    95,    96,    97,    98,     0,     0,     0,
       0,     0,   104,   105,   106,   107,   108,   109,   110
};

static const yytype_int16 yycheck[] =
{
      10,   120,    77,    78,    14,    78,   178,    17,    18,    19,
      20,    72,   184,    74,   133,     4,    76,   136,    28,    76,
      80,    65,    44,    45,    46,    69,    70,    71,    38,    39,
      40,    41,     1,     3,     3,     4,     5,    81,     4,    68,
      84,     4,     3,    14,    13,    14,     3,     3,    19,    78,
      79,    80,    81,    13,    64,    81,    66,    42,    43,    44,
      45,    46,    72,    81,    74,    75,    76,    77,    81,    81,
      81,     3,    82,    42,    43,    48,    48,     4,    47,    48,
      49,    50,    92,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,    75,    76,    81,    81,    85,   119,
      78,    82,    48,    82,     1,    84,     3,     4,     5,   180,
      48,   182,    81,    81,    48,    20,    13,    14,    81,    81,
      81,    81,   197,     1,    -1,     3,     4,     5,    84,    -1,
     111,    85,   113,    -1,    -1,    13,    14,    -1,    -1,    -1,
       1,    -1,     3,     4,     5,    42,    43,    -1,    -1,    -1,
      47,    -1,    13,    14,    -1,    -1,    -1,    -1,    -1,   179,
     180,    -1,   182,   183,    42,    43,   186,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,   196,    -1,    -1,    33,
      34,    42,    43,    -1,    -1,    82,    47,    84,    42,    43,
      44,    45,    46,    -1,     1,    -1,     3,     4,     5,    77,
      78,    -1,   183,    -1,    82,   186,    13,    14,    -1,    -1,
       1,    -1,     3,     4,     5,   196,    77,    78,    -1,    -1,
      -1,    82,    13,    14,    -1,     1,    -1,     3,     4,     5,
      -1,    -1,    -1,    -1,    -1,    42,    43,    13,    14,    -1,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    82,    -1,     0,     1,    -1,
      -1,     4,    -1,     6,     7,     8,    -1,    -1,    -1,    -1,
      13,    82,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    82,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    51,    52,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,    -1,    -1,    77,    78,    79,    -1,    -1,    -1,
      -1,    -1,    -1,    85,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    29,    30,    31,    32,    33,    34,    84,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    84,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    83,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    29,    30,    31,    32,    33,    34,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    29,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      44,    45,    46,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    44,    45,    46
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    87,     0,     1,     4,     6,     7,     8,    13,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    79,    88,    97,    78,    76,    80,    76,
       4,    90,     1,     3,     4,     5,    13,    14,    42,    43,
      47,    82,    91,    92,    93,     3,     4,     4,    92,    94,
       3,     3,    94,    95,    92,    94,    95,     3,    13,    77,
      78,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    98,    92,    81,    92,    92,
      92,    92,    81,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    81,    81,    81,     3,    92,    48,    49,    50,    84,
      92,    99,   100,   101,   102,    48,    92,   102,   103,   103,
     102,   102,   102,    92,    99,    48,    92,    99,    94,    94,
      92,   103,   103,   103,   102,   103,    94,    48,   102,     4,
      83,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      94,    92,    94,    78,    48,    92,    84,   100,    81,    76,
      81,    81,    81,    81,    81,    89,    81,    85,    85,   101,
      92,    99,    48,    99,    94,   101,    81,    96,    94,    84,
      94,    96,    48,    85
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    88,    88,    88,    88,    88,    88,    88,    89,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    90,
      90,    91,    91,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    93,    94,    95,    95,    96,    96,    88,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    98,    98,    98,    98,    98,    99,    99,    99,
     100,   100,   101,   101,   101,   101,   101,   102,   103
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     3,     2,     2,     2,     3,     3,
       5,     3,     0,     3,     1,     2,     4,     2,     2,     0,
       7,     6,     2,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     3,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     2,     2,     1,
       1,     1,     1,     0,     1,     0,     2,     2,     0,     2,
       1,     1,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     4,     2,     4,     4,     4,     4,     2,
       4,     2,     1,     2,     2,     2,     2,     3,     1,     2,
       3,     6,     1,     1,     1,     1,     1,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 320 "as.y" /* yacc.c:1646  */
    {    newident((yyvsp[-1].y_item), DOTTYP); newlabel((yyvsp[-1].y_item));}
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 322 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[-1].y_valu) < 0 || (yyvsp[-1].y_valu) > 9) {
                    serror("bad f/b label");
                    (yyvsp[-1].y_valu) = 0;
                }
                newlabel(fb_shift((int)(yyvsp[-1].y_valu)));
            }
#line 1788 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 329 "as.y" /* yacc.c:1646  */
    { emit1((int)(yyvsp[0].y_valu)); if (listflag) listline(0); else if (listtemp) { listflag = listtemp; listeoln = 1; };}
#line 1794 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 331 "as.y" /* yacc.c:1646  */
    { emit2((int)(yyvsp[0].y_valu)); if (listflag) listline(0); else if (listtemp) { listflag = listtemp; listeoln = 1; };}
#line 1800 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 333 "as.y" /* yacc.c:1646  */
    { emit4((long)(yyvsp[0].y_valu)); if (listflag) listline(0); else if (listtemp) { listflag = listtemp; listeoln = 1; };}
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 336 "as.y" /* yacc.c:1646  */
    { lineno++; if (listflag) listline(1); else if (listtemp) { listflag = listtemp; listeoln = 1; };
            {if (!(relonami == 0)) assert2("/home/ceriel/evert/comm2.y", 129);};}
#line 1813 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 339 "as.y" /* yacc.c:1646  */
    {    lineno = (yyvsp[-2].y_valu);
                if (modulename) strncpy(modulename, stringbuf, 200    -1);
                if (listflag) listline(1); else if (listtemp) { listflag = listtemp; listeoln = 1; };
                {if (!(relonami == 0)) assert2("/home/ceriel/evert/comm2.y", 133);};
            }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 345 "as.y" /* yacc.c:1646  */
    {    serror("syntax error"); yyerrok;
                lineno++; if (listflag) listline(1); else if (listtemp) { listflag = listtemp; listeoln = 1; };
                {if (!(relonami == 0)) assert2("/home/ceriel/evert/comm2.y", 137);};
            }
#line 1832 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 355 "as.y" /* yacc.c:1646  */
    {

                if (listflag & 1)
                    listcolm += printx(4, (yyvsp[0].y_expr).val);

                newequate((yyvsp[-2].y_item), (yyvsp[0].y_expr).typ);
                store((yyvsp[-2].y_item), (yyvsp[0].y_expr).val);
            }
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 365 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_word))
                    listtemp = listmode;
                else if ((dflag & 01000) == 0)
                    listtemp = 0;
            }
#line 1855 "y.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 372 "as.y" /* yacc.c:1646  */
    {    newsect((yyvsp[0].y_item));}
#line 1861 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 374 "as.y" /* yacc.c:1646  */
    {    newcomm((yyvsp[-2].y_item), (yyvsp[0].y_valu));}
#line 1867 "y.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 376 "as.y" /* yacc.c:1646  */
    {    if (pass == 0) newbase((yyvsp[0].y_valu));}
#line 1873 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 378 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_expr).val == 0 && pass == 2)
                    warning("assertion failed");
            }
#line 1881 "y.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 381 "as.y" /* yacc.c:1646  */
    { o_it = last_it; }
#line 1887 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 383 "as.y" /* yacc.c:1646  */
    {    if ((sflag & 010    ) && (pass != 0)) {

                    if (
                        pass == 2
                        &&
                        ((yyvsp[-3].y_expr).typ & 0x007F            ) == 0x0000
                       ) {
                        serror("expression undefined");
                        relonami = -1;
                    }
                    if (
                        (pass != 0)
                        &&
                        ((yyvsp[-3].y_expr).typ & 0x1000            )
                       ) {





                        (yyvsp[-3].y_expr).typ = 0x007F                        ;
                        (yyvsp[-3].y_expr).val = new_string(o_it->i_name);
                        relonami = 0;
                    }


                    newsymb(
                        *stringbuf ? stringbuf : (char *) 0,
                        (short)(
                            ((yyvsp[-3].y_expr).typ & (0x0080            |0x007F            ))
                            |
                            ((unsigned short)(yyvsp[-1].y_valu)<<8)
                        ),
                        (short)(yyvsp[0].y_valu),
                        (yyvsp[-3].y_expr).val
                    );
                }
            }
#line 1930 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 422 "as.y" /* yacc.c:1646  */
    {    if ((sflag & 010    ) && (pass != 0)) {
                    newsymb(
                        *stringbuf ? stringbuf : (char *) 0,
                        (short)(
                            (DOTTYP & (0x0080            |0x007F            ))
                            |
                            ((unsigned short)(yyvsp[-2].y_valu)<<8)
                        ),
                        (short)(yyvsp[0].y_valu),
                        (long)DOTVAL
                    );
                }
            }
#line 1948 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 436 "as.y" /* yacc.c:1646  */
    {    if ((sflag & 020    ) && (pass != 0)) {
                    if ((yyvsp[0].y_valu))
                        hllino = (short)(yyvsp[0].y_valu);
                    else
                        hllino++;
                    newsymb(
                        (char *)0,
                        (DOTTYP | 0x0200            ),
                        hllino,
                        (long)DOTVAL
                    );
                }
            }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 450 "as.y" /* yacc.c:1646  */
    {    if ((sflag & 020    ) && (pass != 0)) {
                    hllino = 0;
                    newsymb(
                        stringbuf,
                        (DOTTYP | 0x0300            ),
                        0,
                        (long)DOTVAL
                    );
                }
            }
#line 1981 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 462 "as.y" /* yacc.c:1646  */
    {    align((yyvsp[0].y_valu));}
#line 1987 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 464 "as.y" /* yacc.c:1646  */
    {    if (DOTSCT == NULL)
                    nosect();
                DOTVAL += (yyvsp[0].y_valu);
                DOTSCT->s_zero += (yyvsp[0].y_valu);
            }
#line 1997 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 471 "as.y" /* yacc.c:1646  */
    {    emitstr((yyvsp[-1].y_word));}
#line 2003 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 475 "as.y" /* yacc.c:1646  */
    {    (yyvsp[0].y_item)->i_type |= 0x0080            ;}
#line 2009 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 477 "as.y" /* yacc.c:1646  */
    {    (yyvsp[0].y_item)->i_type |= 0x0080            ;}
#line 2015 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 481 "as.y" /* yacc.c:1646  */
    {

                if (1 != 0 && (pass != 0))
                    newrelo((yyvsp[0].y_expr).typ, (int)(yyvsp[-1].y_word)|(0));

                emitx((yyvsp[0].y_expr).val, (int)(yyvsp[-1].y_word));
            }
#line 2027 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 489 "as.y" /* yacc.c:1646  */
    {

                if (1 != 0 && (pass != 0))
                    newrelo((yyvsp[0].y_expr).typ, (int)(yyvsp[-3].y_word)|(0));

                emitx((yyvsp[0].y_expr).val, (int)(yyvsp[-3].y_word));
            }
#line 2039 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 498 "as.y" /* yacc.c:1646  */
    {    serror("expr syntax err");
                (yyval.y_expr).val = 0; (yyval.y_expr).typ = 0x0000            ;
            }
#line 2047 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 502 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = (yyvsp[0].y_valu); (yyval.y_expr).typ = 0x0001            ;}
#line 2053 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 504 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = load((yyvsp[0].y_item));
                last_it = (yyvsp[0].y_item);
                (yyval.y_expr).typ = (yyvsp[0].y_item)->i_type & ~0x0080            ;
            }
#line 2062 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 509 "as.y" /* yacc.c:1646  */
    {    if (stringlen != 1)
                    serror("too many chars");
                (yyval.y_expr).val = stringbuf[0];
                (yyval.y_expr).typ = 0x0001            ;
            }
#line 2072 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 515 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr) = (yyvsp[-1].y_expr);}
#line 2078 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 517 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val || (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2086 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 521 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val && (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2094 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 525 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val | (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2102 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 529 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val ^ (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2110 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 533 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val & (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2118 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 537 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val == (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2126 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 541 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val != (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2134 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 545 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val < (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2142 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 549 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val > (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2150 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 553 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val <= (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2158 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 557 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val >= (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '>');
            }
#line 2166 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 561 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val >> (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2174 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 565 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val << (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2182 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 569 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val + (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '+');
            }
#line 2190 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 573 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val - (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, '-');
            }
#line 2198 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 577 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val * (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2206 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 581 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_expr).val == 0) {
                    if (pass == 2)
                        serror("divide by zero");
                    (yyval.y_expr).val = 0;
                } else
                    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val / (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2219 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 590 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_expr).val == 0) {
                    if (pass == 2)
                        serror("divide by zero");
                    (yyval.y_expr).val = 0;
                } else
                    (yyval.y_expr).val = ((yyvsp[-2].y_expr).val % (yyvsp[0].y_expr).val);
                (yyval.y_expr).typ = combine((yyvsp[-2].y_expr).typ, (yyvsp[0].y_expr).typ, 0);
            }
#line 2232 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 599 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = (yyvsp[0].y_expr).val;
                (yyval.y_expr).typ = combine(0x0001            , (yyvsp[0].y_expr).typ, 0);
            }
#line 2240 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 603 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = -(yyvsp[0].y_expr).val;
                (yyval.y_expr).typ = combine(0x0001            , (yyvsp[0].y_expr).typ, 0);
            }
#line 2248 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 607 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = ~(yyvsp[0].y_expr).val;
                (yyval.y_expr).typ = combine(0x0001            , (yyvsp[0].y_expr).typ, 0);
            }
#line 2256 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 611 "as.y" /* yacc.c:1646  */
    {    (yyval.y_expr).val = DOTVAL;
                (yyval.y_expr).typ = DOTTYP|0x0400;
            }
#line 2264 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 619 "as.y" /* yacc.c:1646  */
    {    if (((yyvsp[0].y_expr).typ & ~0x0080            ) != 0x0001            )
                    serror("must be absolute");
                (yyval.y_valu) = (yyvsp[0].y_expr).val;
            }
#line 2273 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 626 "as.y" /* yacc.c:1646  */
    {    (yyval.y_valu) = 0;}
#line 2279 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 628 "as.y" /* yacc.c:1646  */
    {    (yyval.y_valu) = (yyvsp[0].y_valu);}
#line 2285 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 632 "as.y" /* yacc.c:1646  */
    {    (yyval.y_valu) = 0;}
#line 2291 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 634 "as.y" /* yacc.c:1646  */
    {    (yyval.y_valu) = (yyvsp[0].y_valu);}
#line 2297 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 642 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[0].y_word));}
#line 2303 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 645 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[0].y_word));}
#line 2309 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 647 "as.y" /* yacc.c:1646  */
    {    emit2((yyvsp[0].y_word));}
#line 2315 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 649 "as.y" /* yacc.c:1646  */
    {    branch((yyvsp[-1].y_word),(yyvsp[0].y_expr));}
#line 2321 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 651 "as.y" /* yacc.c:1646  */
    {    pushop((yyvsp[-1].y_word));}
#line 2327 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 653 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[-1].y_word));

                newrelo((yyvsp[0].y_expr).typ, 1);

                emit1((yyvsp[0].y_expr).val);
            }
#line 2338 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 660 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_word)!=2) serror("register error");
                emit1((yyvsp[-1].y_word)+010);
            }
#line 2346 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 664 "as.y" /* yacc.c:1646  */
    {    addop((yyvsp[-1].y_word));}
#line 2352 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 666 "as.y" /* yacc.c:1646  */
    {    rolop((yyvsp[-1].y_word));}
#line 2358 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 668 "as.y" /* yacc.c:1646  */
    {    incop((yyvsp[-1].y_word));}
#line 2364 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 670 "as.y" /* yacc.c:1646  */
    {    imul((yyvsp[-1].y_word));}
#line 2370 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 672 "as.y" /* yacc.c:1646  */
    {    regsize((yyvsp[-1].y_word)); emit1(0366|((yyvsp[-1].y_word)&1)); ea_1((yyvsp[-1].y_word)&070);}
#line 2376 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 674 "as.y" /* yacc.c:1646  */
    {    regsize((yyvsp[-1].y_word)); emit1(0366|((yyvsp[-1].y_word)&1)); ea_1((yyvsp[-1].y_word)&070);}
#line 2382 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 676 "as.y" /* yacc.c:1646  */
    {    callop((yyvsp[-1].y_word)&0xFFFF);}
#line 2388 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 678 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[-3].y_word)>>8);

                newrelo((yyvsp[0].y_expr).typ, 2            );

                emit2((yyvsp[0].y_expr).val);

                newrelo((yyvsp[-2].y_expr).typ, 2            );

                emit2((yyvsp[-2].y_expr).val);
            }
#line 2403 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 689 "as.y" /* yacc.c:1646  */
    {    emit1(0377); ea_2((yyvsp[-1].y_word)&0xFF);}
#line 2409 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 691 "as.y" /* yacc.c:1646  */
    {    if (!((((((yyvsp[-2].y_valu)) + 0x8000L) & ~0xFFFFL) == 0))) nofit(); if (!((((((yyvsp[0].y_valu)) + 0x80) & ~((int)0xFF)) == 0))) nofit();
                emit1((yyvsp[-3].y_word)); emit2((int)(yyvsp[-2].y_valu)); emit1((int)(yyvsp[0].y_valu));
            }
#line 2417 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 695 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[-3].y_word)); ea_2((yyvsp[-2].y_word)<<3);}
#line 2423 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 697 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[-3].y_word)); ea_2((yyvsp[0].y_word)<<3);}
#line 2429 "y.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 699 "as.y" /* yacc.c:1646  */
    {    emit1(0xF); emit1((yyvsp[-3].y_word));
                ea_2((yyvsp[-2].y_word)<<3);
            }
#line 2437 "y.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 703 "as.y" /* yacc.c:1646  */
    {    regsize(1); emit1(0xF); emit1((yyvsp[-1].y_word)&07);
                ea_1((yyvsp[-1].y_word)&070);
            }
#line 2445 "y.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 707 "as.y" /* yacc.c:1646  */
    {    if (!((((yyvsp[-2].y_valu) & 077) == (yyvsp[-2].y_valu)))) nofit();
                emit1(0330 | (yyvsp[-2].y_valu)>>3);
                ea_2(((yyvsp[-2].y_valu)&7)<<3);
            }
#line 2454 "y.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 712 "as.y" /* yacc.c:1646  */
    {    if ((yyvsp[0].y_valu)==3)
                    emit1(0314);
                else {
                    emit1(0315); emit1((yyvsp[0].y_valu));
                }
            }
#line 2465 "y.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 719 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[0].y_word));}
#line 2471 "y.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 721 "as.y" /* yacc.c:1646  */
    {    emit1((yyvsp[-1].y_word)-1);

                newrelo((yyvsp[0].y_expr).typ, 2            );

                emit2((yyvsp[0].y_expr).val);
            }
#line 2482 "y.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 728 "as.y" /* yacc.c:1646  */
    {    xchg((yyvsp[-1].y_word));}
#line 2488 "y.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 730 "as.y" /* yacc.c:1646  */
    {    test((yyvsp[-1].y_word));}
#line 2494 "y.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 732 "as.y" /* yacc.c:1646  */
    {    mov((yyvsp[-1].y_word));}
#line 2500 "y.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 743 "as.y" /* yacc.c:1646  */
    {    mrg_2 = 6; exp_2 = (yyvsp[-1].y_expr);
                {rel_2 =  relonami;  relonami = 0;};
            }
#line 2508 "y.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 747 "as.y" /* yacc.c:1646  */
    {    exp_2.val = 0; exp_2.typ = 0x0001            ; indexed();}
#line 2514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 749 "as.y" /* yacc.c:1646  */
    {    exp_2 = (yyvsp[-1].y_expr); indexed();
                {rel_2 =  relonami;  relonami = 0;};
            }
#line 2522 "y.tab.c" /* yacc.c:1646  */
    break;

  case 100:
#line 754 "as.y" /* yacc.c:1646  */
    {    mrg_2 = sr_m[(yyvsp[-1].y_word)];}
#line 2528 "y.tab.c" /* yacc.c:1646  */
    break;

  case 101:
#line 756 "as.y" /* yacc.c:1646  */
    {    mrg_2 = dr_m[(yyvsp[-4].y_word)][(yyvsp[-1].y_word)];}
#line 2534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 103:
#line 760 "as.y" /* yacc.c:1646  */
    {    mrg_2 = (yyvsp[0].y_word) | 0300;}
#line 2540 "y.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 762 "as.y" /* yacc.c:1646  */
    {    mrg_2 = (yyvsp[0].y_word) | 0310;}
#line 2546 "y.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 764 "as.y" /* yacc.c:1646  */
    {    mrg_2 = (yyvsp[0].y_word) | 020;}
#line 2552 "y.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 766 "as.y" /* yacc.c:1646  */
    {    mrg_2 = 040; exp_2 = (yyvsp[0].y_expr);
                {rel_2 =  relonami;  relonami = 0;};
            }
#line 2560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 771 "as.y" /* yacc.c:1646  */
    {    mrg_1 = mrg_2; exp_1 = exp_2;
                {rel_1 =  rel_2;  rel_2 = 0;};
            }
#line 2568 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2572 "y.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
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
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 778 "as.y" /* yacc.c:1906  */


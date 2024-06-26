/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 11 "plp5.y"


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>


using namespace std;

#include "TablaSimbolos.h"
#include "TablaTipos.h"
#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;


extern int yylex();
extern char *yytext;
extern FILE *yyin;

int yyerror(char *s);

TablaSimbolos *tsa=new TablaSimbolos(NULL);
TablaTipos *tt=new TablaTipos();

string operador, s1, s2;  // string auxiliares

const int ERRYADECL=10,
	ERRNODECL=11,
	ERRDIM=12,
	ERRFALTAN=13,
	ERRSOBRAN=14,
	ERR_NOENTERO=15,
	ERR_NOCABE=100,
	ERR_MAXTMP=101;
	
void errorSemantico(int nerror,char *lexema,int fila,int columna);

int MAX_VAR_DIR = 16000;
int MAX_TMP_DIR = 16383; 

int newVarDir = 0;
int newTempDir = 16000;

int newLabel = 0;



#line 122 "plp5.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PLP5_TAB_H_INCLUDED
# define YY_YY_PLP5_TAB_H_INCLUDED
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
    main_f = 258,
    entero = 259,
    real = 260,
    escribe = 261,
    lee = 262,
    si = 263,
    sino = 264,
    mientras = 265,
    para = 266,
    id = 267,
    nentero = 268,
    nreal = 269,
    coma = 270,
    pyc = 271,
    pari = 272,
    pard = 273,
    oprel = 274,
    opas = 275,
    opmd = 276,
    asig = 277,
    referencia = 278,
    cori = 279,
    cord = 280,
    llavei = 281,
    llaved = 282,
    formato = 283,
    incrdecr = 284
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PLP5_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

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

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
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
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   97

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  30
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  46
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  103

#define YYUNDEFTOK  2
#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
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
      25,    26,    27,    28,    29
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    80,    84,    87,    91,    94,    99,   101,
      99,   116,   118,   122,   122,   129,   129,   131,   137,   137,
     175,   178,   178,   198,   200,   204,   208,   211,   270,   308,
     339,   357,   376,   394,   456,   520,   529,   587,   596,   649,
     658,   674,   685,   696,   705,   720,   720
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "main_f", "entero", "real", "escribe",
  "lee", "si", "sino", "mientras", "para", "id", "nentero", "nreal",
  "coma", "pyc", "pari", "pard", "oprel", "opas", "opmd", "asig",
  "referencia", "cori", "cord", "llavei", "llaved", "formato", "incrdecr",
  "$accept", "X", "S", "FVM", "Tipo", "Bloque", "$@1", "$@2", "BDecl",
  "DVar", "@3", "LIdent", "@4", "Variable", "@5", "V", "@6", "SeqInstr",
  "Instr", "Expr", "Esimple", "Term", "Factor", "Ref", "@7", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284
};
# endif

#define YYPACT_NINF (-70)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      37,    13,   -70,    18,   -70,   -70,   -70,    37,    41,   -70,
      24,   -70,    29,   -70,    30,   -70,     5,    31,   -70,   -70,
     -70,   -70,    49,   -70,    24,   -70,    39,   -70,    45,   -70,
     -70,   -70,     1,    31,    46,    48,    50,    51,    53,   -70,
     -70,   -70,    44,   -70,   -19,   -70,    47,    52,    12,    12,
      54,   -70,    12,   -70,    57,    58,   -70,   -70,    12,    33,
      56,    60,   -70,    55,    35,    61,    19,    12,    12,    59,
      38,     1,    12,    12,    12,     1,    12,   -70,     8,    42,
      62,   -70,    68,    56,    60,   -70,   -70,    14,   -70,    69,
      -3,     1,    12,   -70,    70,   -70,    21,   -70,    66,    63,
      71,     1,   -70
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     6,     7,     0,     2,     3,    13,     0,     0,     1,
       0,     4,     0,    18,     0,    17,     0,    20,    15,    14,
       8,     5,     0,    19,     0,    12,     0,    16,    24,    21,
       6,    11,     9,    20,     0,     0,     0,     0,     0,    44,
      25,    26,     0,    23,     0,    22,     0,     0,     0,     0,
       0,    10,     0,    45,     0,     0,    41,    42,     0,     0,
      35,    37,    39,    40,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,     0,
       0,    43,    30,    34,    36,    38,    32,     0,    46,     0,
       0,     0,     0,    28,     0,    31,     0,    29,     0,     0,
       0,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -70,   -70,   -70,    77,   -70,    72,   -70,   -70,   -70,    65,
     -70,   -70,   -70,    67,   -70,    64,   -70,   -70,   -69,   -48,
     -53,    17,    20,   -32,   -70
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,    41,    25,    42,    28,     7,
      10,    14,    24,    15,    17,    23,    33,    32,    43,    59,
      60,    61,    62,    63,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      44,    64,    82,    52,    66,    53,    86,    34,    35,    36,
      70,    37,    38,    39,    78,    94,     8,    40,     9,    83,
      79,    53,    95,    87,    39,    56,    57,    20,    73,    58,
      92,    20,   102,    88,    73,    77,    13,    98,    72,    44,
      72,     1,     2,    44,    96,    18,    19,    16,    90,    30,
       2,    71,    72,    75,    72,    22,    81,    72,    12,    44,
      89,    72,    26,    46,    29,    47,    65,    48,    49,    44,
      50,    51,    68,    69,    39,    54,    73,    91,    99,    53,
      55,    74,    80,    76,    11,    93,    97,     0,    21,   101,
      84,    27,   100,    31,    85,     0,     0,    45
};

static const yytype_int8 yycheck[] =
{
      32,    49,    71,    22,    52,    24,    75,     6,     7,     8,
      58,    10,    11,    12,    67,    18,     3,    16,     0,    72,
      68,    24,    91,    76,    12,    13,    14,    26,    20,    17,
      16,    26,   101,    25,    20,    16,    12,    16,    19,    71,
      19,     4,     5,    75,    92,    15,    16,    18,    80,     4,
       5,    18,    19,    18,    19,    24,    18,    19,    17,    91,
      18,    19,    13,    17,    25,    17,    12,    17,    17,   101,
      17,    27,    15,    15,    12,    28,    20,     9,    12,    24,
      28,    21,    23,    22,     7,    16,    16,    -1,    16,    18,
      73,    24,    29,    28,    74,    -1,    -1,    33
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     4,     5,    31,    32,    33,    34,    39,     3,     0,
      40,    33,    17,    12,    41,    43,    18,    44,    15,    16,
      26,    35,    24,    45,    42,    36,    13,    43,    38,    25,
       4,    39,    47,    46,     6,     7,     8,    10,    11,    12,
      16,    35,    37,    48,    53,    45,    17,    17,    17,    17,
      17,    27,    22,    24,    28,    28,    13,    14,    17,    49,
      50,    51,    52,    53,    49,    12,    49,    54,    15,    15,
      49,    18,    19,    20,    21,    18,    22,    16,    50,    49,
      23,    18,    48,    50,    51,    52,    48,    50,    25,    18,
      53,     9,    16,    16,    18,    48,    49,    16,    16,    12,
      29,    18,    48
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    30,    31,    32,    33,    33,    34,    34,    36,    37,
      35,    38,    38,    40,    39,    42,    41,    41,    44,    43,
      45,    46,    45,    47,    47,    48,    48,    48,    48,    48,
      48,    48,    48,    48,    49,    49,    50,    50,    51,    51,
      52,    52,    52,    52,    53,    54,    53
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     5,     1,     1,     0,     0,
       6,     2,     0,     0,     4,     0,     4,     1,     0,     3,
       0,     0,     5,     2,     0,     1,     1,     4,     7,     8,
       5,     7,     5,    12,     3,     1,     3,     1,     3,     1,
       1,     1,     1,     3,     1,     0,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
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
  case 2:
#line 69 "plp5.y"
        {
    int token = yylex();
    if (token == 0) // si es fin de fichero, yylex() devuelve 0
    {
        printf("%s\n",yyvsp[0].cod.c_str());
    }
    else
    yyerror("");
}
#line 1443 "plp5.tab.c"
    break;

  case 3:
#line 80 "plp5.y"
          {
    yyval.cod = yyvsp[0].cod + "\nhalt\n";
}
#line 1451 "plp5.tab.c"
    break;

  case 4:
#line 84 "plp5.y"
               {
    yyval.cod = yyvsp[-1].cod + yyvsp[0].cod;

}
#line 1460 "plp5.tab.c"
    break;

  case 5:
#line 87 "plp5.y"
                                   {
    yyval.cod = "; MAIN\n" + yyvsp[0].cod;
}
#line 1468 "plp5.tab.c"
    break;

  case 6:
#line 91 "plp5.y"
                 {
    yyval.cod = "int";
    yyval.tipo = ENTERO;
}
#line 1477 "plp5.tab.c"
    break;

  case 7:
#line 94 "plp5.y"
         {
    yyval.cod = "float";
    yyval.tipo = REAL;
}
#line 1486 "plp5.tab.c"
    break;

  case 8:
#line 99 "plp5.y"
                 {
    tsa = new TablaSimbolos(tsa);
}
#line 1494 "plp5.tab.c"
    break;

  case 9:
#line 101 "plp5.y"
                 {
    //std::cout << newVarDir << std::endl;
    int tam_tsa = 0;
    for(Simbolo s: tsa->simbolos){
        tam_tsa += tt->getTamanyoRecursivo(s.tipo);
    }
    tsa = tsa->getAmbitoAnterior();
    newVarDir -= tam_tsa; // se vacian las pos de memoria
    //std::cout << newVarDir << std::endl;
    
}
#line 1510 "plp5.tab.c"
    break;

  case 10:
#line 111 "plp5.y"
          {
    // se crearia nuevo ambito aqui y al quitarlo borrar todas las pos de memoria
    yyval.cod = "; {\n"+ yyvsp[-3].cod + yyvsp[-2].cod +"; }\n";
}
#line 1519 "plp5.tab.c"
    break;

  case 11:
#line 116 "plp5.y"
                     {
    yyval.cod = yyvsp[-1].cod + yyvsp[0].cod;
}
#line 1527 "plp5.tab.c"
    break;

  case 12:
#line 118 "plp5.y"
    {
    yyval.cod = "";
}
#line 1535 "plp5.tab.c"
    break;

  case 13:
#line 122 "plp5.y"
               {
    yyval.tipo = yyvsp[0].tipo;
}
#line 1543 "plp5.tab.c"
    break;

  case 14:
#line 124 "plp5.y"
             {
    yyval.cod = "; Tipo: " + yyvsp[-3].cod + "\n" + yyvsp[-1].cod;
    // hay que mandar el tipo como tipoh
}
#line 1552 "plp5.tab.c"
    break;

  case 15:
#line 129 "plp5.y"
                      {yyval.tipo = yyvsp[-2].tipo;}
#line 1558 "plp5.tab.c"
    break;

  case 16:
#line 129 "plp5.y"
                                                    {
    yyval.cod = yyvsp[-3].cod + yyvsp[0].cod;
}
#line 1566 "plp5.tab.c"
    break;

  case 17:
#line 131 "plp5.y"
             {
    yyval.cod = yyvsp[0].cod;
}
#line 1574 "plp5.tab.c"
    break;

  case 18:
#line 137 "plp5.y"
              {
    yyval.tipo = yyvsp[-1].tipo;
    if(tsa->buscarAmbito(yyvsp[0].lexema)!=NULL){
        errorSemantico(ERRYADECL, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
    }
}
#line 1585 "plp5.tab.c"
    break;

  case 19:
#line 142 "plp5.y"
    {
    /*Aqui se heredaria el tipo y se guardaria cada una de los SIMBS 
    Also se guardarian los tipos int y float si no estuviesen
    Hay 16k pos para vars, int y float ocupan 1, los arrays depende del tamaño
    Si supera 15999 - ERROR
    16k a 16383 - vars temporales, aqui tambien ERROR si se pasa

    1. V vacio?
    2.1 SI - se guarda con tipo heredado
    2.2 NO - se guarda con el tipo definido que se devlveria desde V
    En cualquier caso seria V.tipo
    */
    int fullTam = tt->getTamanyoRecursivo(yyvsp[0].tipo);
    if(newVarDir + fullTam >= MAX_VAR_DIR) 
        errorSemantico(ERR_NOCABE, yyvsp[-2].lexema, yyvsp[-2].nlin, yyvsp[-2].ncol);

    Simbolo s;
    s.nombre = yyvsp[-2].lexema;
    s.tipo = yyvsp[0].tipo;
    s.tam = tt->tipos[yyvsp[0].tipo].tamanyo; //* este no es tam recursivo
    s.dir = newVarDir;
    newVarDir += fullTam;
    tsa->nuevoSimbolo(s); //! cuidao, parecde que sigue haciendo la duplicacion de dfincions WTF

    //std::cout << "; "<< s.nombre << " d:" << s.dir << " tp:" << s.tipo << " tm:" << s.tam << " " << std::endl;

    yyval.cod = "; ";
    yyval.cod += yyvsp[-2].lexema + yyvsp[0].cod + " => \n";
    yyval.cod += ";  dir:" + std::to_string(s.dir) + " tp:" + std::to_string(s.tipo) + " tm:" + std::to_string(s.tam) + " \n" ;

}
#line 1621 "plp5.tab.c"
    break;

  case 20:
#line 175 "plp5.y"
       {
    yyval.tipo = yyvsp[0].tipo;

}
#line 1630 "plp5.tab.c"
    break;

  case 21:
#line 178 "plp5.y"
                      {yyval.tipo = yyvsp[-3].tipo;}
#line 1636 "plp5.tab.c"
    break;

  case 22:
#line 178 "plp5.y"
                                             {
    int tam = std::stoi(yyvsp[-3].lexema);
    if(tam<=0) errorSemantico(ERRDIM, yyvsp[-3].lexema, yyvsp[-3].nlin, yyvsp[-3].ncol);

    yyval.tipo = tt->nuevoTipoArray(
        tam, // tamaño
        yyvsp[0].tipo// tipo base
    );

    //std::cout << "- tipo: " << $$.tipo  << "- tam: " << tt->tipos[$$.tipo].tamanyo << " - base: " << tt->tipos[$$.tipo].tipoBase << std::endl;
    yyval.cod = "[";
    yyval.cod += yyvsp[-3].lexema;
    yyval.cod += "]";
    yyval.cod += yyvsp[0].cod;
}
#line 1656 "plp5.tab.c"
    break;

  case 23:
#line 198 "plp5.y"
                          {
    yyval.cod = yyvsp[-1].cod + yyvsp[0].cod;
}
#line 1664 "plp5.tab.c"
    break;

  case 24:
#line 200 "plp5.y"
    {
    yyval.cod = "\n";
}
#line 1672 "plp5.tab.c"
    break;

  case 25:
#line 204 "plp5.y"
            {
    //! nada?
    yyval.cod = ";pyc\n";

}
#line 1682 "plp5.tab.c"
    break;

  case 26:
#line 208 "plp5.y"
           {
    yyval.cod = yyvsp[0].cod;

}
#line 1691 "plp5.tab.c"
    break;

  case 27:
#line 211 "plp5.y"
                      {
    // id = E ;
    yyval.cod = yyvsp[-3].cod + yyvsp[-1].cod;

    string dir3 = std::to_string(yyvsp[-1].dir);
    if(yyvsp[-1].simb!=""){
        // p. ej: a = b;
        // la ref de $1. no viene full calculada
        // la de b si
        yyval.cod += "mov " + dir3 + " A\n";

        Simbolo* s = tsa->buscar(yyvsp[-3].simb);
        yyval.cod += "mov " + std::to_string(yyvsp[-3].dir) + " B \n";
        
        yyval.cod += "; Asignacion para "+ yyvsp[-3].simb +"="+ yyvsp[-1].simb +"\n";
        //$$.cod += "wri A \n";
        //$$.cod += "wrl \n";
        //$$.cod += "wri B \n";
        //$$.cod += "wrl \n";
        
        yyval.cod += "mov @A @B+"+std::to_string(s->dir)+"\n";
        
        //$$.cod += "wrr @B+"+std::to_string(s->dir)+"\n";
        //$$.cod += "wrl \n";

        if(yyvsp[-3].tipo!=yyvsp[-1].tipo){
            yyval.cod += "; Arregla tipos\n";
            
            yyval.cod += "mov @B+"+std::to_string(s->dir)+" A\n";
            if(yyvsp[-3].tipo==ENTERO){
                yyval.cod += "rtoi\n";
            }else{
                yyval.cod += "itor\n";
            }
            yyval.cod += "mov A @B+"+std::to_string(s->dir)+"\n";
        }
        if(yyvsp[-3].tipo==ENTERO && yyvsp[-1].tipo ==REAL){
        }else if(yyvsp[-3].tipo==REAL && yyvsp[-1].tipo ==ENTERO){
        }

    }else{
            
        Simbolo* s = tsa->buscar(yyvsp[-3].simb);
        yyval.cod += "; Se calcula la pos total para la Ref de la asignacion\n";
        yyval.cod += "mov " + std::to_string(yyvsp[-3].dir) + " A \n";
        yyval.cod += "addi #"+ std::to_string(s->dir) + " \n"; // suma dirbase a la pos en el array
        //std::cout << ";var " << $1.simb << s->dir << std::endl;

        if(yyvsp[-3].tipo==ENTERO && yyvsp[-1].tipo ==REAL){
            yyval.cod += "rtoi\n";
        }else if(yyvsp[-3].tipo==REAL && yyvsp[-1].tipo ==ENTERO){
            yyval.cod += "itor\n";
        }

        yyval.cod += "; Asignacion para "+ yyvsp[-3].simb +"\n";
        yyval.cod += "mov " + dir3 + " @A \n";

    }

}
#line 1756 "plp5.tab.c"
    break;

  case 28:
#line 270 "plp5.y"
                                            {
    // hacer conversiones para los formatos, also escribe siempre hace wrl AL FINAL, como si tuvies un \n
    //     - wri fuente Imprime el valor (entero) de fuente.
    //     - wrr fuente Imprime el valor (real) de fuente.
    //     - wrc fuente Imprime el carácter representado por los 8 bits más bajos del valor entero 
    //     - wrl Imprime un salto de LInea

    yyval.cod = yyvsp[-2].cod;

    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
    }

    string f = "i";
    yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
    if(std::string(yyvsp[-4].lexema).find("d") != std::string::npos){
        if(yyvsp[-2].tipo == REAL){
            yyval.cod += "rtoi\n";
        }
    }else if(std::string(yyvsp[-4].lexema).find("g") != std::string::npos){
        f = "r";
        if(yyvsp[-2].tipo == ENTERO){
            yyval.cod += "itor\n";
        }
    } 
    // if(std::string($3.lexema).find("c") != std::string::npos){
    //    f = "c";
    //    if($5.tipo == REAL){
    //        $$.cod += "itor\n";
    //    }
    //} 

    yyval.cod += "wr";
    yyval.cod += f;
    yyval.cod += " A\n";
    yyval.cod += "wrl\n";

}
#line 1800 "plp5.tab.c"
    break;

  case 29:
#line 308 "plp5.y"
                                                  {
    //     - rdi destino Lee un entero de la consola y lo carga en destino.
    //     - rdr destino Lee un real de la consola y lo carga en destino.
    //     - rdc destino Lee un carácter de la consola y carga su código ASCII en destino.
    
    yyval.cod = yyvsp[-2].cod;

    yyval.cod += "mov " + std::to_string(yyvsp[-3].dir) + " B\n";

    string f = "i";
    string conversion ="";
    
    if(std::string(yyvsp[-5].lexema).find("d") != std::string::npos){
        if(yyvsp[-2].tipo == REAL){
            conversion = "rtoi\n";
        }
    }else if(std::string(yyvsp[-5].lexema).find("g") != std::string::npos){
        f = "r";
        if(yyvsp[-2].tipo == ENTERO){
            conversion = "itor\n";
        }
    } 

    Simbolo* s = tsa->buscar(yyvsp[-2].simb);


    yyval.cod += "rd" + f+ " ";
    yyval.cod += "@B+" + std::to_string(s->dir); // pos en array + pos en memoria
    yyval.cod += "\n";
    yyval.cod += conversion;

}
#line 1837 "plp5.tab.c"
    break;

  case 30:
#line 339 "plp5.y"
                            {
    // if y while cumplen lo de if(134) -> True, if(0) -> false


    string elseLabel = "L"+std::to_string(newLabel++);

    yyval.cod = yyvsp[-2].cod;
    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
    }
    
    yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
    yyval.cod += "; ---------------------IF\n";
    yyval.cod += "jz "+elseLabel+" \n";
    yyval.cod += yyvsp[0].cod;
    yyval.cod += elseLabel+" \n";

}
#line 1861 "plp5.tab.c"
    break;

  case 31:
#line 357 "plp5.y"
                                       {
    string elseLabel = "L"+std::to_string(newLabel++);
    string endifLabel = "L"+std::to_string(newLabel++);

    yyval.cod = yyvsp[-4].cod;
    if(yyvsp[-4].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-4].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-4].dir) + " \n";
    }
    yyval.cod += "mov " + std::to_string(yyvsp[-4].dir) + " A\n";
    yyval.cod += "; ---------------------IF\n";
    yyval.cod += "jz "+elseLabel+" \n";
    yyval.cod += yyvsp[-2].cod;
    yyval.cod += "jmp "+endifLabel+" \n";
    yyval.cod += "; ---------------------ELSE\n";
    yyval.cod += elseLabel+" \n";
    yyval.cod += yyvsp[0].cod;
    yyval.cod += endifLabel+" \n";

}
#line 1886 "plp5.tab.c"
    break;

  case 32:
#line 376 "plp5.y"
                                  {
    string startLabel = "L"+std::to_string(newLabel++);
    string endLabel = "L"+std::to_string(newLabel++);

    // en cada iter se evalua la Expr ($3)
    yyval.cod += startLabel+" \n";
    yyval.cod += yyvsp[-2].cod;
    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
    }
    yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
    yyval.cod += "; ---------------------WHILE\n";
    yyval.cod += "jz "+endLabel+" \n";
    yyval.cod += yyvsp[0].cod;
    yyval.cod += "jmp "+startLabel+" \n";
    yyval.cod += endLabel+" \n";

}
#line 1910 "plp5.tab.c"
    break;

  case 33:
#line 394 "plp5.y"
                                                                  {
    //         3        5           7       9     10         12
    /*
        Se tiene que comprobar en el for
        1. identificador existe
        2. tiene que ser entero antes de asignar
        3. lo mismo con el 2 id
        id1 y id2 pueden ser distintos pero a nadie le importa
    */
    Simbolo* s1 = tsa->buscar(yyvsp[-9].simb);
    if(s1->tipo!=ENTERO)
        errorSemantico(ERR_NOENTERO, yyvsp[-9].lexema, yyvsp[-9].nlin, yyvsp[-9].ncol);
    yyval.cod = yyvsp[-7].cod;
    if(yyvsp[-7].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-7].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-7].dir) + " \n";
    }
    string startLabel = "L"+std::to_string(newLabel++);
    string endLabel = "L"+std::to_string(newLabel++);

    yyval.cod += startLabel+"\n";
    yyval.cod += yyvsp[-5].cod;
    if(yyvsp[-5].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-5].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-5].dir) + " \n";
    }

    yyval.cod += "mov " + std::to_string(yyvsp[-5].dir) + " A\n";
    yyval.cod += "jz "+endLabel+"\n";
    

    Simbolo* s2 = tsa->buscar(yyvsp[-3].simb);
    if(s2->tipo!=ENTERO)
        errorSemantico(ERR_NOENTERO, yyvsp[-3].lexema, yyvsp[-3].nlin, yyvsp[-3].ncol);

    yyval.cod = "; ---------------------FOR\n";
    yyval.cod += yyvsp[0].cod;
    yyval.cod += "mov " + std::to_string(yyvsp[-7].dir) + " A\n";
    string instruccion;
    if(strcmp(yyvsp[-2].lexema, "++")== 0){
        instruccion = "addi";
    }else{
        instruccion = "subi";
    }
    yyval.cod += instruccion + " "+ std::to_string(s1->tipo) + "\n";
    yyval.cod += "mov A " + std::to_string(yyvsp[-3].dir) + " ; Incrdecr FOR\n";
    yyval.cod += "jmp "+startLabel+"\n";
    yyval.cod += endLabel+"\n";

}
#line 1965 "plp5.tab.c"
    break;

  case 34:
#line 456 "plp5.y"
                           {
    yyval.cod = yyvsp[-2].cod + yyvsp[0].cod; 

    string operacion = "";

    if(strcmp(yyvsp[-1].lexema, "==")==0){
        operacion = "eql";
    } else if(strcmp(yyvsp[-1].lexema, "!=")==0){
        operacion = "neq";
    } else if(strcmp(yyvsp[-1].lexema, "<")==0){
        operacion = "lss";
    } else if(strcmp(yyvsp[-1].lexema, "<=")==0){
        operacion = "leq";
    } else if(strcmp(yyvsp[-1].lexema, ">")==0){
        operacion = "gtr";
    } else if(strcmp(yyvsp[-1].lexema, ">=")==0){
        operacion = "geq";
    } 

 
    yyval.cod += "; ---------------------OPREL\n";
    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
    }
    if(yyvsp[0].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[0].dir) + " \n";
    }

    if(yyvsp[-2].tipo != yyvsp[0].tipo){
        if(yyvsp[-2].tipo == ENTERO){ // si son distintos cambia solo el entero
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[-2].dir) + "\n";
        }
        yyval.tipo = REAL;

    }else{ // si son iguales no se requiere cambio de tipo
        if(yyvsp[-2].tipo == ENTERO){
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "i " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = ENTERO;
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = REAL;
        }
    }

    int tmp = newTempDir++;
    yyval.dir = tmp;
    if(yyval.tipo==REAL){
        yyval.tipo = ENTERO;
    }
    yyval.cod += "mov A " + std::to_string(tmp) + " \n";
    yyval.simb = "";

}
#line 2035 "plp5.tab.c"
    break;

  case 35:
#line 520 "plp5.y"
            {
    yyval.cod = yyvsp[0].cod;
    yyval.tipo = yyvsp[0].tipo;
    yyval.dir = yyvsp[0].dir;
    yyval.simb = yyvsp[0].simb;

}
#line 2047 "plp5.tab.c"
    break;

  case 36:
#line 529 "plp5.y"
                              {
    yyval.cod = yyvsp[-2].cod + yyvsp[0].cod; 
    string operacion = (strcmp(yyvsp[-1].lexema, "+")==0)? "add": "sub";

    yyval.cod += "; ---------------------OPAS\n";

    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
        //if($1.tipo==ENTERO)
        //$$.cod += "wri " + std::to_string($1.dir) + "\n";
        //else
        //$$.cod += "wrr " + std::to_string($1.dir) + "\n";
    }
    if(yyvsp[0].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[0].dir) + " \n";
        //if($3.tipo==ENTERO)
        //$$.cod += "wri " + std::to_string($3.dir) + "\n";
        //else
        //$$.cod += "wrr " + std::to_string($3.dir) + "\n";
    }

    if(yyvsp[-2].tipo != yyvsp[0].tipo){
        if(yyvsp[-2].tipo == ENTERO){ // si son distintos cambia solo el entero
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[-2].dir) + "\n";
        }
        //$$.cod += "wrr A\n";
        yyval.tipo = REAL;

    }else{ // si son iguales no se requiere cambio de tipo
        if(yyvsp[-2].tipo == ENTERO){
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "i " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = ENTERO;
        //$$.cod += "wri A\n";
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = REAL;
        //$$.cod += "wrr A\n";
        }
    }


    int tmp = newTempDir++;
    yyval.dir = tmp,
    yyval.cod += "mov A " + std::to_string(tmp) + " \n";
    yyval.simb = "";

}
#line 2111 "plp5.tab.c"
    break;

  case 37:
#line 587 "plp5.y"
         {
    yyval.cod = yyvsp[0].cod;
    yyval.tipo = yyvsp[0].tipo;
    yyval.dir = yyvsp[0].dir;
    yyval.simb = yyvsp[0].simb;

}
#line 2123 "plp5.tab.c"
    break;

  case 38:
#line 596 "plp5.y"
                         {
    // div entre enteros : > entero, si 1 es real se convierte el otro
    yyval.cod = yyvsp[-2].cod + yyvsp[0].cod; 
    
    string operacion = (strcmp(yyvsp[-1].lexema, "*")==0)? "mul": "div";

    yyval.cod += "; ---------------------OPMD\n";

    // si cualquiera de los dos es referencia
    // se sacan los valores de la var y se meten en la tmp
    if(yyvsp[-2].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[-2].dir) + " \n";
    }
    if(yyvsp[0].simb!=""){
        yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " B\n";
        yyval.cod += "mov @B+0 " + std::to_string(yyvsp[0].dir) + " \n";
    }

    if(yyvsp[-2].tipo != yyvsp[0].tipo){
        if(yyvsp[-2].tipo == ENTERO){ // si son distintos cambia solo el entero
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " A\n";
            yyval.cod += "itor\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[-2].dir) + "\n";
        }
        yyval.tipo = REAL;
        //$$.cod += "wrr A\n";

    }else{ // si son iguales no se requiere cambio de tipo
        if(yyvsp[-2].tipo == ENTERO){
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "i " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = ENTERO;
        //$$.cod += "wri A\n";
        }else {
            yyval.cod += "mov " + std::to_string(yyvsp[-2].dir) + " A\n";
            yyval.cod += operacion + "r " + std::to_string(yyvsp[0].dir) + "\n";
            yyval.tipo = REAL;
        //$$.cod += "wrr A\n";
        }
    }


    int tmp = newTempDir++;
    yyval.dir = tmp,
    yyval.cod += "mov A " + std::to_string(tmp) + " \n";
    yyval.simb = "";
    

}
#line 2182 "plp5.tab.c"
    break;

  case 39:
#line 649 "plp5.y"
           {
    yyval.cod = yyvsp[0].cod;
    yyval.tipo = yyvsp[0].tipo;
    yyval.dir = yyvsp[0].dir;
    yyval.simb = yyvsp[0].simb;

}
#line 2194 "plp5.tab.c"
    break;

  case 40:
#line 658 "plp5.y"
              {
    if(!ES_TIPO_BASICO(yyvsp[0].tipo)){
        errorSemantico(ERRFALTAN, yyval.lexema, yyval.nlin, yyval.ncol); //! aqui habria que marcar en id o en ], osea, en -1?
    }
    // aqui se devolveria una dir tmp con la DIR de la pos del array
    // sumar a simb.dir y ya estaria?
    Simbolo* s = tsa->buscar(yyvsp[0].simb);
    yyval.cod = yyvsp[0].cod;
    yyval.cod += "; Se calcula la pos total para la Ref\n";
    yyval.cod += "mov " + std::to_string(yyvsp[0].dir) + " A \n";
    yyval.cod += "addi #"+ std::to_string(s->dir) + " \n"; // suma dirbase a la pos en el array
    yyval.cod += "mov A " + std::to_string(yyvsp[0].dir) + " \n";
    yyval.dir = yyvsp[0].dir;
    yyval.tipo = yyvsp[0].tipo;
    yyval.simb = yyvsp[0].simb;

}
#line 2216 "plp5.tab.c"
    break;

  case 41:
#line 674 "plp5.y"
            {
    int tmp = newTempDir++;
    yyval.dir = tmp;
    yyval.tipo = ENTERO;
    yyval.cod = "mov #";
    yyval.cod += yyvsp[0].lexema;
    yyval.cod += " ";
    yyval.cod += std::to_string(tmp);
    yyval.cod += "\n";
    yyval.simb = "";

}
#line 2233 "plp5.tab.c"
    break;

  case 42:
#line 685 "plp5.y"
          {
    int tmp = newTempDir++;
    yyval.dir = tmp;
    yyval.tipo = REAL;
    yyval.cod = "mov $";
    yyval.cod += yyvsp[0].lexema;
    yyval.cod += " ";
    yyval.cod += std::to_string(tmp);
    yyval.cod += "\n";
    yyval.simb = "";

}
#line 2250 "plp5.tab.c"
    break;

  case 43:
#line 696 "plp5.y"
                   {
    yyval.cod = yyvsp[-1].cod;
    yyval.tipo = yyvsp[-1].tipo;
    yyval.dir = yyvsp[-1].dir;
    yyval.simb = "";
    //* algo mas?
}
#line 2262 "plp5.tab.c"
    break;

  case 44:
#line 705 "plp5.y"
          {
    Simbolo* s = tsa->buscar(yyvsp[0].lexema);
    if(s == NULL){
        errorSemantico(ERRNODECL, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
    }
    int tmp = newTempDir++;
    yyval.dir = tmp;

    yyval.cod = "mov #0 " + std::to_string(tmp); // t0 = 0
    yyval.cod += "; t0 para: ";
    yyval.cod += yyvsp[0].lexema;
    yyval.cod += "\n";
    yyval.tipo = s->tipo;
    yyval.simb = yyvsp[0].lexema;

}
#line 2283 "plp5.tab.c"
    break;

  case 45:
#line 720 "plp5.y"
             {
    if(ES_TIPO_BASICO(yyvsp[-1].tipo)){
        errorSemantico(ERRSOBRAN, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
    }

    yyval.simb = yyvsp[-1].simb;

}
#line 2296 "plp5.tab.c"
    break;

  case 46:
#line 727 "plp5.y"
                {
    /*
        mismos ERRORES en arrray que en clase si sobran o fatan []
        el indice debe ser siempre un int, sino ERROR en ]
    */
    if(yyvsp[-1].tipo != ENTERO){
        errorSemantico(ERR_NOENTERO, yyvsp[0].lexema, yyvsp[0].nlin, yyvsp[0].ncol);
    }

    int tmp = newTempDir++;
    yyval.dir = tmp;
    // ti = ti-1 * tam + pos
    yyval.cod = yyvsp[-4].cod;
    yyval.cod += "; Calcula n para array\n";
    yyval.cod += yyvsp[-1].cod; // Esimple devuelve el num necesario para seguir calculando
    yyval.cod += "; Calcula Ti\n";
    yyval.cod += "mov " + std::to_string(yyvsp[-4].dir)+ " A\n"; // mete el ti-1 en A
    yyval.cod += "muli #" + std::to_string(tt->tipos[yyvsp[-4].tipo].tamanyo) + "\n"; // ti-1 * tam
    yyval.cod += "addi " + std::to_string(yyvsp[-1].dir) + "\n"; // + pos // guardada en una dir tmp
    //$$.cod += "";
    yyval.cod += "mov A " + std::to_string(tmp) + "\n"; // guarda ti en una nueva tmp


    yyval.tipo = tt->tipos[yyvsp[-4].tipo].tipoBase; // coge el nuevo tipo
}
#line 2326 "plp5.tab.c"
    break;


#line 2330 "plp5.tab.c"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 758 "plp5.y"

/* ####################################################################################################### */
/* ####################################################################################################### */
/* ####################################################################################################### */
/* CODIGO */

	
void errorSemantico(int nerror,char *lexema,int fila,int columna)
{
    fprintf(stderr,"Error semantico (%d,%d): en '%s', ",fila,columna,lexema);
    switch (nerror) {
             case ERRYADECL: fprintf(stderr,"simbolo ya declarado\n");
               break;
             case ERRNODECL: fprintf(stderr,"identificador no declarado\n");
               break;
             case ERRDIM: fprintf(stderr,"la dimension debe ser mayor que cero\n");
               break;
             case ERRFALTAN: fprintf(stderr,"faltan indices\n");
               break;
             case ERRSOBRAN: fprintf(stderr,"sobran indices\n");
               break;
             case ERR_NOENTERO: fprintf(stderr,"debe ser de tipo entero\n");
               break;

             case ERR_NOCABE:fprintf(stderr,"la variable ya no cabe en memoria\n");
               break;
             case ERR_MAXTMP:fprintf(stderr,"no hay espacio para variables temporales\n");
               break;
    }
    exit(-1);
}




int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,0,0,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    return 0;
}

int main(int argc,char *argv[])
{
    FILE *fent;

    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}


















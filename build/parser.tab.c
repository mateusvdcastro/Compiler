/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "syntax_tree.h"

#define YYSTYPE NODEPOINTER
#define MAX_NODES 1000

static int yylex(void);
void yyerror (char *s);

NODEPOINTER nodes[MAX_NODES];
NODEPOINTER syntaxTree;

enum yytokentype auxError;

int nodeCount = 0;
int syntax_errors = 0;

#line 92 "./build/parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_ABREPARENTESES = 5,             /* ABREPARENTESES  */
  YYSYMBOL_FECHAPARENTESES = 6,            /* FECHAPARENTESES  */
  YYSYMBOL_ABRECOLCHETES = 7,              /* ABRECOLCHETES  */
  YYSYMBOL_FECHACOLCHETES = 8,             /* FECHACOLCHETES  */
  YYSYMBOL_ABRECHAVES = 9,                 /* ABRECHAVES  */
  YYSYMBOL_FECHACHAVES = 10,               /* FECHACHAVES  */
  YYSYMBOL_ATRIB = 11,                     /* ATRIB  */
  YYSYMBOL_COMMA = 12,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 13,                 /* SEMICOLON  */
  YYSYMBOL_SOMA = 14,                      /* SOMA  */
  YYSYMBOL_SUB = 15,                       /* SUB  */
  YYSYMBOL_MULT = 16,                      /* MULT  */
  YYSYMBOL_DIV = 17,                       /* DIV  */
  YYSYMBOL_EQ = 18,                        /* EQ  */
  YYSYMBOL_NEQ = 19,                       /* NEQ  */
  YYSYMBOL_LT = 20,                        /* LT  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_LET = 22,                       /* LET  */
  YYSYMBOL_GET = 23,                       /* GET  */
  YYSYMBOL_INT = 24,                       /* INT  */
  YYSYMBOL_VOID = 25,                      /* VOID  */
  YYSYMBOL_WHILE = 26,                     /* WHILE  */
  YYSYMBOL_ELSE = 27,                      /* ELSE  */
  YYSYMBOL_IF = 28,                        /* IF  */
  YYSYMBOL_RETURN = 29,                    /* RETURN  */
  YYSYMBOL_ERRO = 30,                      /* ERRO  */
  YYSYMBOL_IFX = 31,                       /* IFX  */
  YYSYMBOL_YYACCEPT = 32,                  /* $accept  */
  YYSYMBOL_program = 33,                   /* program  */
  YYSYMBOL_declaration_list = 34,          /* declaration_list  */
  YYSYMBOL_declaration = 35,               /* declaration  */
  YYSYMBOL_var_declaration = 36,           /* var_declaration  */
  YYSYMBOL_type_specifier = 37,            /* type_specifier  */
  YYSYMBOL_fun_declaration = 38,           /* fun_declaration  */
  YYSYMBOL_fun_id = 39,                    /* fun_id  */
  YYSYMBOL_params = 40,                    /* params  */
  YYSYMBOL_param_list = 41,                /* param_list  */
  YYSYMBOL_param = 42,                     /* param  */
  YYSYMBOL_compound_decl = 43,             /* compound_decl  */
  YYSYMBOL_local_declarations = 44,        /* local_declarations  */
  YYSYMBOL_statement_list = 45,            /* statement_list  */
  YYSYMBOL_statement = 46,                 /* statement  */
  YYSYMBOL_expression_decl = 47,           /* expression_decl  */
  YYSYMBOL_selection_decl = 48,            /* selection_decl  */
  YYSYMBOL_iteration_decl = 49,            /* iteration_decl  */
  YYSYMBOL_return_decl = 50,               /* return_decl  */
  YYSYMBOL_expression = 51,                /* expression  */
  YYSYMBOL_var = 52,                       /* var  */
  YYSYMBOL_simple_expression = 53,         /* simple_expression  */
  YYSYMBOL_relational = 54,                /* relational  */
  YYSYMBOL_relational_operand = 55,        /* relational_operand  */
  YYSYMBOL_sum_expression = 56,            /* sum_expression  */
  YYSYMBOL_sum = 57,                       /* sum  */
  YYSYMBOL_term = 58,                      /* term  */
  YYSYMBOL_mult = 59,                      /* mult  */
  YYSYMBOL_factor = 60,                    /* factor  */
  YYSYMBOL_activation = 61,                /* activation  */
  YYSYMBOL_args = 62,                      /* args  */
  YYSYMBOL_arg_list = 63                   /* arg_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  32
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  111

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   286


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
      25,    26,    27,    28,    29,    30,    31
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    32,    32,    38,    47,    53,    57,    63,    80,    87,
     110,   118,   125,   134,   148,   159,   162,   172,   180,   184,
     197,   213,   224,   232,   237,   245,   250,   253,   256,   259,
     262,   268,   271,   273,   280,   294,   311,   327,   334,   348,
     361,   366,   377,   393,   401,   406,   411,   416,   420,   424,
     428,   432,   439,   446,   451,   455,   462,   469,   474,   480,
     489,   491,   493,   495,   508,   518,   520,   525,   535
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID",
  "ABREPARENTESES", "FECHAPARENTESES", "ABRECOLCHETES", "FECHACOLCHETES",
  "ABRECHAVES", "FECHACHAVES", "ATRIB", "COMMA", "SEMICOLON", "SOMA",
  "SUB", "MULT", "DIV", "EQ", "NEQ", "LT", "GT", "LET", "GET", "INT",
  "VOID", "WHILE", "ELSE", "IF", "RETURN", "ERRO", "IFX", "$accept",
  "program", "declaration_list", "declaration", "var_declaration",
  "type_specifier", "fun_declaration", "fun_id", "params", "param_list",
  "param", "compound_decl", "local_declarations", "statement_list",
  "statement", "expression_decl", "selection_decl", "iteration_decl",
  "return_decl", "expression", "var", "simple_expression", "relational",
  "relational_operand", "sum_expression", "sum", "term", "mult", "factor",
  "activation", "args", "arg_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-78)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-17)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
     -21,   -78,   -78,    11,   -21,   -78,   -78,    44,   -78,   -78,
     -78,    -6,     9,    31,    55,   -78,    41,   -78,    40,   -78,
      63,    66,    69,    68,    64,   -78,    62,    70,    71,   -21,
     -78,    73,   -78,   -78,   -78,   -78,   -21,   -78,    45,     5,
       9,    65,   -78,    23,    54,   -78,   -78,    74,    77,    37,
      78,   -78,   -78,   -78,   -78,   -78,   -78,    72,    75,    33,
      52,    53,   -78,   -78,   -78,    54,    81,    54,    54,   -78,
      76,    54,   -78,    54,   -78,   -78,   -78,   -78,   -78,   -78,
      54,   -78,   -78,   -78,    54,   -78,   -78,    54,    80,   -78,
      84,    85,   -78,   -78,    86,    82,   -78,   -78,    52,    53,
     -78,   -78,    34,    34,   -78,    54,   -78,    57,   -78,    34,
     -78
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    11,    12,     0,     2,     4,     5,     0,     6,     1,
       3,     0,    14,     0,     0,     8,     0,     7,     0,    10,
       0,    12,     0,     0,    15,    18,     0,    19,     0,     0,
       9,     0,    23,    13,    17,    20,    25,    22,     0,     0,
       0,     0,    63,    41,     0,    21,    32,     0,     0,     0,
       0,    27,    24,    26,    28,    29,    30,     0,    61,    40,
      44,    53,    57,    62,    33,     0,     0,     0,     0,    37,
       0,    66,    31,     0,    46,    47,    48,    49,    50,    51,
       0,    45,    54,    55,     0,    58,    59,     0,     0,    60,
       0,     0,    38,    68,     0,    65,    39,    61,    43,    52,
      56,    42,     0,     0,    64,     0,    36,    34,    67,     0,
      35
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -78,   -78,   -78,    89,    59,   -17,   -78,    90,   -78,   -78,
      67,    79,   -78,   -78,   -77,   -78,   -78,   -78,   -78,   -44,
     -67,   -78,   -78,   -78,    18,   -78,    15,   -78,    13,   -78,
     -78,   -78
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,     8,    50,    23,    24,
      25,    51,    36,    39,    52,    53,    54,    55,    56,    57,
      58,    59,    80,    81,    60,    84,    61,    87,    62,    63,
      94,    95
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      66,    22,    14,     1,     2,    70,    41,    15,    42,    43,
      44,     9,    22,    97,    32,    45,    16,    97,    46,    38,
      97,    88,    17,    90,    91,   106,   107,    93,   -14,    96,
      65,    47,   110,    48,    49,    41,    18,    42,    43,    44,
      42,    43,    44,    32,    20,    11,    11,    46,    12,    40,
      69,    74,    75,    76,    77,    78,    79,    42,    43,    44,
      47,   108,    48,    49,     1,    21,    82,    83,    19,    85,
      86,    26,   -16,    27,    28,    30,    29,    31,    64,    67,
      32,    35,    68,    71,   109,    72,    73,    89,   101,    92,
     102,   103,   104,    10,   105,    37,    34,    13,    98,    99,
     100,     0,     0,     0,     0,     0,     0,    33
};

static const yytype_int8 yycheck[] =
{
      44,    18,     8,    24,    25,    49,     1,    13,     3,     4,
       5,     0,    29,    80,     9,    10,     7,    84,    13,    36,
      87,    65,    13,    67,    68,   102,   103,    71,     5,    73,
       7,    26,   109,    28,    29,     1,     5,     3,     4,     5,
       3,     4,     5,     9,     3,     1,     1,    13,     4,     4,
      13,    18,    19,    20,    21,    22,    23,     3,     4,     5,
      26,   105,    28,    29,    24,    25,    14,    15,    13,    16,
      17,     8,     6,     4,     6,    13,    12,     7,    13,     5,
       9,     8,     5,     5,    27,    13,    11,     6,     8,    13,
       6,     6,     6,     4,    12,    36,    29,     7,    80,    84,
      87,    -1,    -1,    -1,    -1,    -1,    -1,    28
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    24,    25,    33,    34,    35,    36,    37,    38,     0,
      35,     1,     4,    39,     8,    13,     7,    13,     5,    13,
       3,    25,    37,    40,    41,    42,     8,     4,     6,    12,
      13,     7,     9,    43,    42,     8,    44,    36,    37,    45,
       4,     1,     3,     4,     5,    10,    13,    26,    28,    29,
      39,    43,    46,    47,    48,    49,    50,    51,    52,    53,
      56,    58,    60,    61,    13,     7,    51,     5,     5,    13,
      51,     5,    13,    11,    18,    19,    20,    21,    22,    23,
      54,    55,    14,    15,    57,    16,    17,    59,    51,     6,
      51,    51,    13,    51,    62,    63,    51,    52,    56,    58,
      60,     8,     6,     6,     6,    12,    46,    46,    51,    27,
      46
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    32,    33,    34,    34,    35,    35,    36,    36,    36,
      36,    37,    37,    38,    39,    40,    40,    41,    41,    42,
      42,    43,    44,    44,    45,    45,    46,    46,    46,    46,
      46,    47,    47,    47,    48,    48,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    54,    55,    55,    55,    55,
      55,    55,    56,    56,    57,    57,    58,    58,    59,    59,
      60,    60,    60,    60,    61,    62,    62,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     3,     3,     6,
       4,     1,     1,     6,     1,     1,     1,     3,     1,     2,
       4,     4,     2,     0,     2,     0,     1,     1,     1,     1,
       1,     2,     1,     2,     5,     7,     5,     2,     3,     3,
       1,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     1,     3,     1,     1,     1,
       3,     1,     1,     1,     4,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: declaration_list  */
#line 32 "src/parser.y"
                                                   {
						printf("PROGRAM\n");
						syntaxTree = yyvsp[0];
					}
#line 1221 "./build/parser.tab.c"
    break;

  case 3: /* declaration_list: declaration_list declaration  */
#line 38 "src/parser.y"
                                                       {
						if (yyvsp[-1] != NULL){
							yyval = yyvsp[-1];
							addSibling(yyval, yyvsp[0]);
						} else {
							yyval = yyvsp[0];
						}
						printf("DECLARATION_LIST\n");
					}
#line 1235 "./build/parser.tab.c"
    break;

  case 4: /* declaration_list: declaration  */
#line 47 "src/parser.y"
                                                      {
						printf("DECLARATION_LIST\n");
						yyval = yyvsp[0];
					}
#line 1244 "./build/parser.tab.c"
    break;

  case 5: /* declaration: var_declaration  */
#line 53 "src/parser.y"
                                                  {
						printf("VAR_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1253 "./build/parser.tab.c"
    break;

  case 6: /* declaration: fun_declaration  */
#line 57 "src/parser.y"
                                                          {
						printf("FUN_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1262 "./build/parser.tab.c"
    break;

  case 7: /* var_declaration: type_specifier ID SEMICOLON  */
#line 63 "src/parser.y"
                                                      {
						printf("VAR_DECLARATION\n");

						yyval = yyvsp[-2];
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = VarDeclK;

						NODEPOINTER aux = newNode();

						strcpy(aux->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop ID

						addChild(yyval, aux); // ID

						nodes[nodeCount++] = yyval;
					}
#line 1284 "./build/parser.tab.c"
    break;

  case 8: /* var_declaration: type_specifier error SEMICOLON  */
#line 80 "src/parser.y"
                                                                         {
						yyerrok;
						printf("VAR_DECLARATION ERROR RECOVERED\n");
						if (yyvsp[-2] != NULL) freeTree(yyvsp[-2]);
						yyval = NULL;

					}
#line 1296 "./build/parser.tab.c"
    break;

  case 9: /* var_declaration: type_specifier ID ABRECOLCHETES NUM FECHACOLCHETES SEMICOLON  */
#line 87 "src/parser.y"
                                                                                                       {
						printf("VAR_DECLARATION ARRAY\n");

						yyval = yyvsp[-5];
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = VetDeclK;

						NODEPOINTER aux = newNode();
						NODEPOINTER aux2 = newNode();

						strcpy(aux->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop ID

						strcpy(aux2->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL); // Pop NUM


						addChild(yyval, aux2); // NUM
						addChild(yyval, aux); // ID

						nodes[nodeCount++] = yyval;
					}
#line 1324 "./build/parser.tab.c"
    break;

  case 10: /* var_declaration: type_specifier error FECHACOLCHETES SEMICOLON  */
#line 110 "src/parser.y"
                                                                                        {
						yyerrok;
						printf("VAR_DECLARATION ERROR RECOVERED\n");
						if (yyvsp[-3] != NULL) freeTree(yyvsp[-3]);
						yyval = NULL;
					}
#line 1335 "./build/parser.tab.c"
    break;

  case 11: /* type_specifier: INT  */
#line 118 "src/parser.y"
                              {
						yyval = newNode();
						strcpy(yyval->lexeme, "INT");
						yyval->lineNum = lineNum;

						nodes[nodeCount++] = yyval;
					}
#line 1347 "./build/parser.tab.c"
    break;

  case 12: /* type_specifier: VOID  */
#line 125 "src/parser.y"
                                               {
						yyval = newNode();
						strcpy(yyval->lexeme, "VOID");
						yyval->lineNum = lineNum;

						nodes[nodeCount++] = yyval;
					}
#line 1359 "./build/parser.tab.c"
    break;

  case 13: /* fun_declaration: type_specifier fun_id ABREPARENTESES params FECHAPARENTESES compound_decl  */
#line 134 "src/parser.y"
                                                                                                    {
						printf("FUN_DECLARATION\n");

						yyval = yyvsp[-5];

						addChild(yyval, yyvsp[-2]); // params
						addChild(yyval, yyvsp[-4]); // fun_id
						addChild(yyval, yyvsp[0]); // compound_decl

						yyval->nodeKind = StmtK;
						yyval->stmtKind = FunDeclK;
					}
#line 1376 "./build/parser.tab.c"
    break;

  case 14: /* fun_id: ID  */
#line 148 "src/parser.y"
                                     {
						yyval = newNode();

						strcpy(yyval->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						yyval->lineNum = lineNum;

						nodes[nodeCount++] = yyval;
					}
#line 1391 "./build/parser.tab.c"
    break;

  case 15: /* params: param_list  */
#line 159 "src/parser.y"
                                             {
						yyval = yyvsp[0];
					}
#line 1399 "./build/parser.tab.c"
    break;

  case 16: /* params: VOID  */
#line 162 "src/parser.y"
                                               {
						yyval = newNode();
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = ParamVoid;
						strcpy(yyval->lexeme, "VOID");

						nodes[nodeCount++] = yyval;
					}
#line 1413 "./build/parser.tab.c"
    break;

  case 17: /* param_list: param_list COMMA param  */
#line 172 "src/parser.y"
                                                         {
						if (yyvsp[-2] != NULL){
							yyval = yyvsp[-2];
							addSibling(yyval, yyvsp[0]);
						} else {
							yyval = yyvsp[0];
						}
					}
#line 1426 "./build/parser.tab.c"
    break;

  case 18: /* param_list: param  */
#line 180 "src/parser.y"
                                                {
						yyval = yyvsp[0];
					}
#line 1434 "./build/parser.tab.c"
    break;

  case 19: /* param: type_specifier ID  */
#line 184 "src/parser.y"
                                                    {
						yyval = yyvsp[-1];
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = VarParamK;
						NODEPOINTER aux = newNode();
						strcpy(yyval->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						addChild(yyval, aux);
						nodes[nodeCount++] = yyval;

					}
#line 1452 "./build/parser.tab.c"
    break;

  case 20: /* param: type_specifier ID ABRECOLCHETES FECHACOLCHETES  */
#line 197 "src/parser.y"
                                                                                         {
						printf("PARAMETER ARRAY\n");
						yyval = yyvsp[-3];
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = VetParamK;
						NODEPOINTER aux = newNode();

						strcpy(yyval->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						addChild(yyval, aux);
						nodes[nodeCount++] = yyval;
					}
#line 1471 "./build/parser.tab.c"
    break;

  case 21: /* compound_decl: ABRECHAVES local_declarations statement_list FECHACHAVES  */
#line 213 "src/parser.y"
                                                                                   {
						printf("COMPOUND_DECLARATION\n");
						if (yyvsp[-2] != NULL){
							yyval = yyvsp[-2];
							addSibling(yyval, yyvsp[-1]);
						} else {
							yyval = yyvsp[-1];
						}
					}
#line 1485 "./build/parser.tab.c"
    break;

  case 22: /* local_declarations: local_declarations var_declaration  */
#line 224 "src/parser.y"
                                                             {
						if (yyvsp[-1] != NULL){
							yyval = yyvsp[-1];
							addSibling(yyval, yyvsp[0]);
						} else {
							yyval = yyvsp[0];
						}
					}
#line 1498 "./build/parser.tab.c"
    break;

  case 23: /* local_declarations: %empty  */
#line 232 "src/parser.y"
                                                 {
						yyval = NULL;
					}
#line 1506 "./build/parser.tab.c"
    break;

  case 24: /* statement_list: statement_list statement  */
#line 237 "src/parser.y"
                                                   {
						if (yyvsp[-1] != NULL){
							yyval = yyvsp[-1];
							addSibling(yyval, yyvsp[0]);
						} else {
							yyval = yyvsp[0];
						}
					}
#line 1519 "./build/parser.tab.c"
    break;

  case 25: /* statement_list: %empty  */
#line 245 "src/parser.y"
                                                 {
						yyval = NULL;
					}
#line 1527 "./build/parser.tab.c"
    break;

  case 26: /* statement: expression_decl  */
#line 250 "src/parser.y"
                                                  {
						printf("EXPRESSION_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1536 "./build/parser.tab.c"
    break;

  case 27: /* statement: compound_decl  */
#line 253 "src/parser.y"
                                                          {
						printf("COMPOUND_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1545 "./build/parser.tab.c"
    break;

  case 28: /* statement: selection_decl  */
#line 256 "src/parser.y"
                                                           {
						printf("SELECTION_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1554 "./build/parser.tab.c"
    break;

  case 29: /* statement: iteration_decl  */
#line 259 "src/parser.y"
                                                           {
						printf("ITERATION_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1563 "./build/parser.tab.c"
    break;

  case 30: /* statement: return_decl  */
#line 262 "src/parser.y"
                                                        {
						printf("RETURN_DECLARATION\n");
						yyval = yyvsp[0];
					}
#line 1572 "./build/parser.tab.c"
    break;

  case 31: /* expression_decl: expression SEMICOLON  */
#line 268 "src/parser.y"
                                               {
						printf("EXPRESSION_DECLARATION\n");
						yyval = yyvsp[-1];
					}
#line 1581 "./build/parser.tab.c"
    break;

  case 32: /* expression_decl: SEMICOLON  */
#line 271 "src/parser.y"
                                                      {
						yyval = NULL;
					}
#line 1589 "./build/parser.tab.c"
    break;

  case 33: /* expression_decl: error SEMICOLON  */
#line 273 "src/parser.y"
                                                            {
						yyerrok;
						printf("EXPRESSION_DECLARATION ERROR RECOVERED\n");
						yyval = NULL;
					}
#line 1599 "./build/parser.tab.c"
    break;

  case 34: /* selection_decl: IF ABREPARENTESES expression FECHAPARENTESES statement  */
#line 280 "src/parser.y"
                                                                                           {
						printf("SELECTION_DECLARATION\n");

						yyval = newNode();
						strcpy(yyval->lexeme, "IF");
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = IfK;

						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);

						nodes[nodeCount++] = yyval;
					}
#line 1618 "./build/parser.tab.c"
    break;

  case 35: /* selection_decl: IF ABREPARENTESES expression FECHAPARENTESES statement ELSE statement  */
#line 294 "src/parser.y"
                                                                                                                {
						printf("SELECTION_DECLARATION\n");

						yyval = newNode();
						strcpy(yyval->lexeme, "IF");
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = IfK;

						addChild(yyval, yyvsp[-4]);
						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);

						nodes[nodeCount++] = yyval;
					}
#line 1638 "./build/parser.tab.c"
    break;

  case 36: /* iteration_decl: WHILE ABREPARENTESES expression FECHAPARENTESES statement  */
#line 311 "src/parser.y"
                                                                                    {
						printf("ITERATION_DECLARATION\n");

						yyval = newNode();
						strcpy(yyval->lexeme, "WHILE");
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = WhileK;

						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);

						nodes[nodeCount++] = yyval;
					}
#line 1657 "./build/parser.tab.c"
    break;

  case 37: /* return_decl: RETURN SEMICOLON  */
#line 327 "src/parser.y"
                                                   {
						yyval = newNode();
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = ReturnVoidK;
						strcpy(yyval->lexeme, "ReturnVoidK");
						nodes[nodeCount++] = yyval;
					}
#line 1670 "./build/parser.tab.c"
    break;

  case 38: /* return_decl: RETURN expression SEMICOLON  */
#line 334 "src/parser.y"
                                                                        {
						yyval = newNode();
						yyval->nodeKind = StmtK;
						yyval->lineNum = lineNum;
						yyval->stmtKind = ReturnInK;

						strcpy(yyval->lexeme, "ReturnInK");

						addChild(yyval, yyvsp[-1]);

						nodes[nodeCount++] = yyval;
					}
#line 1687 "./build/parser.tab.c"
    break;

  case 39: /* expression: var ATRIB expression  */
#line 348 "src/parser.y"
                                                       {
						yyval = newNode();
						strcpy(yyval->lexeme, "=");
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = AssignK;

						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);

						printf("EXPRESSION ATRIB\n");
						nodes[nodeCount++] = yyval;
					}
#line 1705 "./build/parser.tab.c"
    break;

  case 40: /* expression: simple_expression  */
#line 361 "src/parser.y"
                                                            {
						yyval = yyvsp[0];
					}
#line 1713 "./build/parser.tab.c"
    break;

  case 41: /* var: ID  */
#line 366 "src/parser.y"
                                             {
						yyval = newNode();
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = IdK;

						strcpy(yyval->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);

						nodes[nodeCount++] = yyval;
					}
#line 1729 "./build/parser.tab.c"
    break;

  case 42: /* var: ID ABRECOLCHETES expression FECHACOLCHETES  */
#line 377 "src/parser.y"
                                                                                     {
						yyval = newNode();

						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = VetK;

						strcpy(yyval->lexeme, lexStack.stack[lexStack.top]);
						pop(&lexStack, NULL);
						
						addChild(yyval, yyvsp[-1]);

						nodes[nodeCount++] = yyval;
					}
#line 1748 "./build/parser.tab.c"
    break;

  case 43: /* simple_expression: simple_expression relational sum_expression  */
#line 393 "src/parser.y"
                                                                      {
						yyval = yyvsp[-1];
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = OpRel;
						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);
					}
#line 1761 "./build/parser.tab.c"
    break;

  case 44: /* simple_expression: sum_expression  */
#line 401 "src/parser.y"
                                                         {
						yyval = yyvsp[0];
					}
#line 1769 "./build/parser.tab.c"
    break;

  case 45: /* relational: relational_operand  */
#line 406 "src/parser.y"
                                                     {
						yyval = yyvsp[0];
					}
#line 1777 "./build/parser.tab.c"
    break;

  case 46: /* relational_operand: EQ  */
#line 411 "src/parser.y"
                        {
						yyval = newNode();
						strcpy(yyval->lexeme, "==");
						nodes[nodeCount++] = yyval;
					}
#line 1787 "./build/parser.tab.c"
    break;

  case 47: /* relational_operand: NEQ  */
#line 416 "src/parser.y"
                                              {
						yyval = newNode();
						strcpy(yyval->lexeme, "!=");
						nodes[nodeCount++] = yyval;
					}
#line 1797 "./build/parser.tab.c"
    break;

  case 48: /* relational_operand: LT  */
#line 420 "src/parser.y"
                                               {
						yyval = newNode();
						strcpy(yyval->lexeme, "<");
						nodes[nodeCount++] = yyval;
					}
#line 1807 "./build/parser.tab.c"
    break;

  case 49: /* relational_operand: GT  */
#line 424 "src/parser.y"
                                               {
						yyval = newNode();
						strcpy(yyval->lexeme, ">");
						nodes[nodeCount++] = yyval;
					}
#line 1817 "./build/parser.tab.c"
    break;

  case 50: /* relational_operand: LET  */
#line 428 "src/parser.y"
                                                {
						yyval = newNode();
						strcpy(yyval->lexeme, "<=");
						nodes[nodeCount++] = yyval;
					}
#line 1827 "./build/parser.tab.c"
    break;

  case 51: /* relational_operand: GET  */
#line 432 "src/parser.y"
                                                {
						yyval = newNode();
						strcpy(yyval->lexeme, ">=");
						nodes[nodeCount++] = yyval;
					}
#line 1837 "./build/parser.tab.c"
    break;

  case 52: /* sum_expression: sum_expression sum term  */
#line 439 "src/parser.y"
                                                  {
						yyval = yyvsp[-1];
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);
					}
#line 1849 "./build/parser.tab.c"
    break;

  case 53: /* sum_expression: term  */
#line 446 "src/parser.y"
                                               {
						yyval = yyvsp[0];
					}
#line 1857 "./build/parser.tab.c"
    break;

  case 54: /* sum: SOMA  */
#line 451 "src/parser.y"
                                               {
						yyval = newNode();
						strcpy(yyval->lexeme, "+");
						nodes[nodeCount++] = yyval;
					}
#line 1867 "./build/parser.tab.c"
    break;

  case 55: /* sum: SUB  */
#line 455 "src/parser.y"
                                                {
						yyval = newNode();
						strcpy(yyval->lexeme, "-");
						nodes[nodeCount++] = yyval;
					}
#line 1877 "./build/parser.tab.c"
    break;

  case 56: /* term: term mult factor  */
#line 462 "src/parser.y"
                                                   {
						yyval = yyvsp[-1];
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = OpK;
						addChild(yyval, yyvsp[-2]);
						addChild(yyval, yyvsp[0]);
					}
#line 1890 "./build/parser.tab.c"
    break;

  case 57: /* term: factor  */
#line 469 "src/parser.y"
                                                   {
						yyval = yyvsp[0];
					}
#line 1898 "./build/parser.tab.c"
    break;

  case 58: /* mult: MULT  */
#line 474 "src/parser.y"
                                       {
						yyval = newNode();

						strcpy(yyval->lexeme, "*");

						nodes[nodeCount++] = yyval;
					}
#line 1910 "./build/parser.tab.c"
    break;

  case 59: /* mult: DIV  */
#line 480 "src/parser.y"
                                                {
						yyval = newNode();

						strcpy(yyval->lexeme, "/");

						nodes[nodeCount++] = yyval;
					}
#line 1922 "./build/parser.tab.c"
    break;

  case 60: /* factor: ABREPARENTESES expression FECHAPARENTESES  */
#line 489 "src/parser.y"
                                                                            {
						yyval = yyvsp[-1];
					}
#line 1930 "./build/parser.tab.c"
    break;

  case 61: /* factor: var  */
#line 491 "src/parser.y"
                                                {
						yyval = yyvsp[0];
					}
#line 1938 "./build/parser.tab.c"
    break;

  case 62: /* factor: activation  */
#line 493 "src/parser.y"
                                                       {
						yyval = yyvsp[0];
					}
#line 1946 "./build/parser.tab.c"
    break;

  case 63: /* factor: NUM  */
#line 495 "src/parser.y"
                                                {
						yyval = newNode();
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = ConstK;

						pop(&lexStack, yyval->lexeme);
						printf("FACTOR NUM: %s\n", yyval->lexeme);

						nodes[nodeCount++] = yyval;
					}
#line 1962 "./build/parser.tab.c"
    break;

  case 64: /* activation: fun_id ABREPARENTESES args FECHAPARENTESES  */
#line 508 "src/parser.y"
                                                                             {
						printf("ACTIVATION\n");
						yyval = yyvsp[-3];
						yyval->nodeKind = ExpK;
						yyval->lineNum = lineNum;
						yyval->expKind = AtivK;
						addChild(yyval, yyvsp[-1]);
					}
#line 1975 "./build/parser.tab.c"
    break;

  case 65: /* args: arg_list  */
#line 518 "src/parser.y"
                                           {
						yyval = yyvsp[0];
					}
#line 1983 "./build/parser.tab.c"
    break;

  case 66: /* args: %empty  */
#line 520 "src/parser.y"
                                                   {
						yyval = NULL;
					}
#line 1991 "./build/parser.tab.c"
    break;

  case 67: /* arg_list: arg_list COMMA expression  */
#line 525 "src/parser.y"
                                                            {
						if (yyvsp[-2] != NULL){
							yyval = yyvsp[-2];
							addSibling(yyval, yyvsp[0]);
						} else {
							yyval = yyvsp[0];
						}

						printf("ARG_LIST COMMA\n");
					}
#line 2006 "./build/parser.tab.c"
    break;

  case 68: /* arg_list: expression  */
#line 535 "src/parser.y"
                                                     {
						yyval = yyvsp[0];
						printf("ARG_LIST EXPRESSION\n");
					}
#line 2015 "./build/parser.tab.c"
    break;


#line 2019 "./build/parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 540 "src/parser.y"


void yyerror (char *s){
	printf("\n" ANSI_COLOR_RED "ERRO SINTATICO, LINHA: %d", lineNum);
	printf(ANSI_COLOR_RESET);
	printf(": token inesperado '%s' (código: %d)", yytext, auxError);
	
	switch(auxError){
		case NUM:
			printf(": '%s' não era esperado (NUM)", yytext);
			break; 
		case SOMA:
			printf(": '%s' não era esperado (SOMA)", yytext);
			break;
		case SUB:
			printf(": '%s' não era esperado (SUB)", yytext);
			break;
		case MULT:
			printf(": '%s' não era esperado (MULT)", yytext);
			break;
		case DIV:
			printf(": '%s' não era esperado (DIV)", yytext);
			break;
		case INT:
			printf(": '%s' não era esperado (INT)", yytext);
			break;
		case ID:
			printf(": '%s' não era esperado (ID)", yytext);
			break;
		case VOID:
			printf(": '%s' não era esperado (VOID)", yytext);
			break;
		case WHILE:
			printf(": '%s' não era esperado (WHILE)", yytext);
			break;
		case ELSE:
			printf(": '%s' não era esperado (ELSE)", yytext);
			break;
		case IF:
			printf(": '%s' não era esperado (IF)", yytext);
			break;
		case ABREPARENTESES:
			printf(": '%s' não era esperado (ABREPARENTESES)", yytext);
			break;
		case FECHAPARENTESES:
			printf(": '%s' não era esperado (FECHAPARENTESES)", yytext);
			break;
		case RETURN:
			printf(": '%s' não era esperado (RETURN)", yytext);
			break;
		case COMMA:
			printf(": '%s' não era esperado (COMA)", yytext);
			break;
		case ABRECHAVES:
			printf(": '%s' não era esperado (ABRECHAVES)", yytext);
			break;
		case FECHACHAVES:
			printf(": '%s' não era esperado (FECHACHAVES)", yytext);
			break;
		case SEMICOLON:
			printf(": '%s' não era esperado (SEMICOLON)", yytext);
			break;
		case ATRIB:
			printf(": '%s' não era esperado (ATRIB)", yytext);
			break;
		case ABRECOLCHETES:
			printf(": '%s' não era esperado (ABRECOLCHETES)", yytext);
			break;
		case FECHACOLCHETES:
			printf(": '%s' não era esperado (FECHACOLCHETES)", yytext);
			break;
		case EQ:
			printf(": '%s' não era esperado (EQ)", yytext);
			break;
		case NEQ:
			printf(": '%s' não era esperado (NEQ)", yytext);
			break;
		case LT:
			printf(": '%s' não era esperado (LT)", yytext);
			break;
		case LET:
			printf(": '%s' não era esperado (LET)", yytext);
			break;
		case GT:
			printf(": '%s' não era esperado (GT)", yytext);
			break;
		case GET:
			printf(": '%s' não era esperado (GET)", yytext);
			break;
		case ERRO:
			printf(": '%s' não era esperado (ERRO)", yytext);
			break;
	}
	printf("\n");

    syntax_errors++;
	
	//Desaloca os nos ate o momento
	// Don't free individual nodes - they may share pointers (siblings/children)
	// causing double-free errors. Set nodeCount to 0 to reset tracking.
	nodeCount = 0;
	syntaxTree = NULL;

}

int yylex(void){
    auxError = getToken();
    return auxError;
}

NODEPOINTER parse(void){
    yyparse();
    return syntaxTree;
}

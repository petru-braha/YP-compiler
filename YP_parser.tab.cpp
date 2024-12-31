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
#line 6 "YP_parser.ypp"

#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include "YP_utility.hpp"

extern int yylex();
void yyerror(const char * s);

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern bool method_master_started;
size_t count_error;

function_data* f_data_global;

std::string cls_last_name;
std::string fct_last_name;

std::vector<symbol_table> symbols;
#define LAST_SCOPE symbols.size() - 1

#include "src/dev/error.hpp"

#line 98 "YP_parser.tab.cpp"

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

#include "YP_parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_method_type = 3,                /* method_type  */
  YYSYMBOL_method_print = 4,               /* method_print  */
  YYSYMBOL_R_CLS = 5,                      /* R_CLS  */
  YYSYMBOL_A_PRV = 6,                      /* A_PRV  */
  YYSYMBOL_A_PUB = 7,                      /* A_PUB  */
  YYSYMBOL_A_FLD = 8,                      /* A_FLD  */
  YYSYMBOL_OPERATOR_ASSIGN = 9,            /* OPERATOR_ASSIGN  */
  YYSYMBOL_OPERATOR_RELTIN = 10,           /* OPERATOR_RELTIN  */
  YYSYMBOL_S_NME = 11,                     /* S_NME  */
  YYSYMBOL_R_TYP = 12,                     /* R_TYP  */
  YYSYMBOL_C_INT = 13,                     /* C_INT  */
  YYSYMBOL_C_FLT = 14,                     /* C_FLT  */
  YYSYMBOL_C_CHR = 15,                     /* C_CHR  */
  YYSYMBOL_C_STR = 16,                     /* C_STR  */
  YYSYMBOL_C_BOL = 17,                     /* C_BOL  */
  YYSYMBOL_R_SEQ_IF = 18,                  /* R_SEQ_IF  */
  YYSYMBOL_R_SEQ_FOR = 19,                 /* R_SEQ_FOR  */
  YYSYMBOL_R_SEQ_WHL = 20,                 /* R_SEQ_WHL  */
  YYSYMBOL_21_ = 21,                       /* '{'  */
  YYSYMBOL_22_ = 22,                       /* '}'  */
  YYSYMBOL_23_ = 23,                       /* ';'  */
  YYSYMBOL_24_ = 24,                       /* '('  */
  YYSYMBOL_25_ = 25,                       /* ')'  */
  YYSYMBOL_26_ = 26,                       /* ','  */
  YYSYMBOL_YYACCEPT = 27,                  /* $accept  */
  YYSYMBOL_starting_symbol = 28,           /* starting_symbol  */
  YYSYMBOL_29_1 = 29,                      /* $@1  */
  YYSYMBOL_scope_begin = 30,               /* scope_begin  */
  YYSYMBOL_scope_end = 31,                 /* scope_end  */
  YYSYMBOL_method_master = 32,             /* method_master  */
  YYSYMBOL_cls_decl = 33,                  /* cls_decl  */
  YYSYMBOL_cls_defn = 34,                  /* cls_defn  */
  YYSYMBOL_35_2 = 35,                      /* $@2  */
  YYSYMBOL_arr_fild = 36,                  /* arr_fild  */
  YYSYMBOL_37_3 = 37,                      /* $@3  */
  YYSYMBOL_38_4 = 38,                      /* $@4  */
  YYSYMBOL_39_5 = 39,                      /* $@5  */
  YYSYMBOL_40_6 = 40,                      /* $@6  */
  YYSYMBOL_41_7 = 41,                      /* $@7  */
  YYSYMBOL_42_8 = 42,                      /* $@8  */
  YYSYMBOL_43_9 = 43,                      /* $@9  */
  YYSYMBOL_44_10 = 44,                     /* $@10  */
  YYSYMBOL_var_decl = 45,                  /* var_decl  */
  YYSYMBOL_var_defn = 46,                  /* var_defn  */
  YYSYMBOL_var_call = 47,                  /* var_call  */
  YYSYMBOL_fct_decl = 48,                  /* fct_decl  */
  YYSYMBOL_fct_defn = 49,                  /* fct_defn  */
  YYSYMBOL_50_11 = 50,                     /* $@11  */
  YYSYMBOL_51_12 = 51,                     /* $@12  */
  YYSYMBOL_fct_synp = 52,                  /* fct_synp  */
  YYSYMBOL_arr_parm = 53,                  /* arr_parm  */
  YYSYMBOL_54_13 = 54,                     /* $@13  */
  YYSYMBOL_55_14 = 55,                     /* $@14  */
  YYSYMBOL_56_15 = 56,                     /* $@15  */
  YYSYMBOL_57_16 = 57,                     /* $@16  */
  YYSYMBOL_fct_call = 58,                  /* fct_call  */
  YYSYMBOL_argument = 59,                  /* argument  */
  YYSYMBOL_arr_argm = 60,                  /* arr_argm  */
  YYSYMBOL_obj_decl = 61,                  /* obj_decl  */
  YYSYMBOL_obj_defn = 62,                  /* obj_defn  */
  YYSYMBOL_63_17 = 63,                     /* $@17  */
  YYSYMBOL_obj_vals = 64,                  /* obj_vals  */
  YYSYMBOL_fld_call = 65,                  /* fld_call  */
  YYSYMBOL_cst_call = 66,                  /* cst_call  */
  YYSYMBOL_global_declaration = 67,        /* global_declaration  */
  YYSYMBOL_statement_list = 68,            /* statement_list  */
  YYSYMBOL_statement_parse = 69,           /* statement_parse  */
  YYSYMBOL_call_parse = 70,                /* call_parse  */
  YYSYMBOL_statement_easy = 71,            /* statement_easy  */
  YYSYMBOL_statement_assg = 72,            /* statement_assg  */
  YYSYMBOL_statement_bool = 73             /* statement_bool  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  27
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  47
/* YYNRULES -- Number of rules.  */
#define YYNRULES  100
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  172

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   275


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
      24,    25,     2,     2,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    23,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    21,     2,    22,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    76,    76,    76,    83,    84,    85,    91,    96,   102,
     102,   115,   115,   138,   193,   216,   234,   216,   238,   259,
     238,   263,   263,   264,   264,   265,   265,   267,   268,   269,
     274,   283,   286,   321,   334,   352,   355,   360,   363,   363,
     375,   375,   397,   398,   399,   399,   405,   411,   411,   421,
     434,   434,   440,   446,   446,   456,   472,   473,   474,   474,
     475,   476,   481,   498,   501,   540,   540,   553,   554,   555,
     557,   564,   565,   566,   567,   568,   572,   573,   574,   575,
     576,   576,   577,   587,   588,   589,   593,   594,   595,   596,
     597,   601,   602,   603,   605,   609,   609,   612,   613,   614,
     618
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
  "\"end of file\"", "error", "\"invalid token\"", "method_type",
  "method_print", "R_CLS", "A_PRV", "A_PUB", "A_FLD", "OPERATOR_ASSIGN",
  "OPERATOR_RELTIN", "S_NME", "R_TYP", "C_INT", "C_FLT", "C_CHR", "C_STR",
  "C_BOL", "R_SEQ_IF", "R_SEQ_FOR", "R_SEQ_WHL", "'{'", "'}'", "';'",
  "'('", "')'", "','", "$accept", "starting_symbol", "$@1", "scope_begin",
  "scope_end", "method_master", "cls_decl", "cls_defn", "$@2", "arr_fild",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "var_decl",
  "var_defn", "var_call", "fct_decl", "fct_defn", "$@11", "$@12",
  "fct_synp", "arr_parm", "$@13", "$@14", "$@15", "$@16", "fct_call",
  "argument", "arr_argm", "obj_decl", "obj_defn", "$@17", "obj_vals",
  "fld_call", "cst_call", "global_declaration", "statement_list",
  "statement_parse", "call_parse", "statement_easy", "statement_assg",
  "statement_bool", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-56)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -125,     7,   159,  -125,     6,    13,    15,  -125,  -125,  -125,
    -125,  -125,  -125,   159,   146,  -125,   159,  -125,   159,  -125,
     159,  -125,   159,  -125,    12,  -125,   -12,    -4,    22,  -125,
      29,    44,    69,  -125,  -125,   146,  -125,  -125,  -125,  -125,
    -125,  -125,   146,    50,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,   159,  -125,  -125,    26,  -125,    39,    51,    53,    54,
     187,  -125,    51,    64,  -125,  -125,    78,    93,    84,   170,
      79,  -125,  -125,  -125,    37,    77,    36,    43,  -125,    80,
      90,  -125,    91,    92,    94,    90,  -125,  -125,    95,    97,
      -6,    98,  -125,  -125,  -125,    87,    89,  -125,  -125,    37,
      37,   111,   113,  -125,  -125,  -125,  -125,   100,   102,   101,
     104,  -125,   146,   177,  -125,  -125,   146,  -125,  -125,  -125,
     194,  -125,  -125,  -125,    46,    63,    37,    37,    37,   105,
       3,   106,     3,  -125,   109,  -125,   114,   110,  -125,  -125,
      51,   201,  -125,    51,  -125,  -125,  -125,     3,  -125,     3,
    -125,  -125,  -125,  -125,    90,   115,   116,    37,    90,  -125,
    -125,   146,  -125,  -125,  -125,   146,  -125,  -125,    37,    37,
    -125,  -125
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    71,    72,    73,
      74,    75,     4,     0,     0,    82,     0,     8,     0,    31,
       0,    37,     0,    63,     0,     3,     0,     0,     0,    80,
       0,     0,    34,     5,    96,     0,    85,    92,    91,    93,
      94,     6,     0,     0,    86,    88,    87,    76,    78,    77,
      79,     0,     9,     7,     0,    62,     0,     0,     0,     0,
       0,    30,     0,     0,    89,    90,     0,     0,     0,     0,
       0,    83,    95,    81,     0,     0,    53,    50,    43,     0,
       0,    36,     0,     0,     0,     0,    35,    70,     0,     0,
      34,     0,   100,    58,    57,    61,     0,    59,    84,     0,
       0,     0,     0,    29,    10,    21,    64,    47,     0,    44,
       0,    42,     0,     0,    32,    33,     0,    98,    99,    97,
       0,    56,    27,    28,    18,    15,     0,     0,     0,     0,
       0,     0,     0,    41,     0,    69,     0,     0,    39,    60,
       0,     0,    11,     0,    22,    24,    26,     0,    54,     0,
      51,    67,    66,    68,     0,     0,     0,     0,     0,    48,
      45,     0,    13,    14,    12,     0,    19,    16,     0,     0,
      20,    17
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -125,  -125,  -125,   -14,   -13,  -125,  -125,  -125,  -125,   -87,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,   -24,  -124,  -125,  -125,  -125,
    -125,  -125,  -125,    21,    40,  -125,  -125,  -125,  -125,    14,
      72,   -32,  -125,    75,  -125,  -125,  -125
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,   103,    15,    16,    17,    74,   104,
     157,   143,   169,   140,   168,   126,   127,   128,    18,    19,
      37,    20,    21,    62,    57,    58,    79,   131,   129,   110,
     108,    38,    95,    96,   105,    23,    59,   136,    39,    40,
      25,    41,    42,    43,    44,    45,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      35,    36,    66,    70,    63,    54,   148,     3,   150,    52,
      71,    53,   122,   123,    76,    77,    24,    26,    69,    55,
      56,    35,    36,   159,    27,   160,    28,    24,    35,    36,
      24,    60,    24,    80,    24,    51,    24,    75,    85,   144,
     145,   146,    22,    99,   100,    61,    56,   107,   101,   102,
      76,    77,    64,    22,   109,    54,    22,    98,    22,    33,
      22,   -55,    22,    82,    78,    24,   112,    65,   -52,    55,
     164,   116,   141,    72,    84,    56,    81,    66,    67,    68,
     133,   170,   171,    97,   138,    29,   142,    86,    47,    87,
      48,    22,    49,    69,    50,    92,    88,    89,    35,    36,
     106,    33,    35,    36,    90,   111,     7,     8,     9,    10,
      11,    12,   113,   120,   121,   114,   154,   115,   117,   158,
     118,   119,   124,    73,   125,   -49,   -46,   137,   130,   166,
     132,   147,   149,   167,    97,   151,   153,   152,   162,   163,
     161,   139,    91,     0,   165,     0,     0,    35,    36,    30,
      31,    35,    36,     0,     0,   156,     0,    32,     0,     7,
       8,     9,    10,    11,     4,     0,     0,    12,    33,    34,
       5,     6,     7,     8,     9,    10,    11,     0,     0,     0,
      12,    93,    13,     7,     8,     9,    10,    11,   134,     0,
       7,     8,     9,    10,    11,    94,     0,     0,    83,   135,
       7,     8,     9,    10,    11,    93,     0,     7,     8,     9,
      10,    11,   155,     0,     7,     8,     9,    10,    11
};

static const yytype_int16 yycheck[] =
{
      14,    14,     8,    35,    28,     9,   130,     0,   132,    21,
      42,    23,    99,   100,    11,    12,     2,    11,    24,    23,
      24,    35,    35,   147,    11,   149,    11,    13,    42,    42,
      16,     9,    18,    57,    20,    23,    22,    11,    62,   126,
     127,   128,     2,     6,     7,    23,    24,    11,    11,    12,
      11,    12,    23,    13,    11,     9,    16,    70,    18,    22,
      20,    25,    22,     9,    25,    51,    80,    23,    25,    23,
     157,    85,     9,    23,    60,    24,    23,     8,     9,    10,
     112,   168,   169,    69,   116,    13,    23,    23,    16,    11,
      18,    51,    20,    24,    22,    11,     3,     4,   112,   112,
      23,    22,   116,   116,    11,    25,    13,    14,    15,    16,
      17,    21,    21,    26,    25,    23,   140,    23,    23,   143,
      23,    23,    11,    51,    11,    25,    25,   113,    26,   161,
      26,    26,    26,   165,   120,    26,    26,    23,    23,    23,
     154,   120,    67,    -1,   158,    -1,    -1,   161,   161,     3,
       4,   165,   165,    -1,    -1,   141,    -1,    11,    -1,    13,
      14,    15,    16,    17,     5,    -1,    -1,    21,    22,    23,
      11,    12,    13,    14,    15,    16,    17,    -1,    -1,    -1,
      21,    11,    23,    13,    14,    15,    16,    17,    11,    -1,
      13,    14,    15,    16,    17,    25,    -1,    -1,    11,    22,
      13,    14,    15,    16,    17,    11,    -1,    13,    14,    15,
      16,    17,    11,    -1,    13,    14,    15,    16,    17
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    28,    29,     0,     5,    11,    12,    13,    14,    15,
      16,    17,    21,    23,    30,    32,    33,    34,    45,    46,
      48,    49,    61,    62,    66,    67,    11,    11,    11,    67,
       3,     4,    11,    22,    23,    30,    31,    47,    58,    65,
      66,    68,    69,    70,    71,    72,    73,    67,    67,    67,
      67,    23,    21,    23,     9,    23,    24,    51,    52,    63,
       9,    23,    50,    52,    23,    23,     8,     9,    10,    24,
      68,    68,    23,    67,    35,    11,    11,    12,    25,    53,
      52,    23,     9,    11,    66,    52,    23,    11,     3,     4,
      11,    70,    11,    11,    25,    59,    60,    66,    31,     6,
       7,    11,    12,    31,    36,    61,    23,    11,    57,    11,
      56,    25,    30,    21,    23,    23,    30,    23,    23,    23,
      26,    25,    36,    36,    11,    11,    42,    43,    44,    55,
      26,    54,    26,    68,    11,    22,    64,    66,    68,    60,
      40,     9,    23,    38,    36,    36,    36,    26,    53,    26,
      53,    26,    23,    26,    52,    11,    66,    37,    52,    53,
      53,    30,    23,    23,    36,    30,    68,    68,    41,    39,
      36,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    27,    29,    28,    30,    31,    32,    33,    33,    35,
      34,    37,    36,    36,    36,    38,    39,    36,    40,    41,
      36,    42,    36,    43,    36,    44,    36,    36,    36,    36,
      45,    45,    46,    46,    47,    48,    48,    48,    50,    49,
      51,    49,    52,    52,    54,    53,    53,    55,    53,    53,
      56,    53,    53,    57,    53,    53,    58,    58,    59,    59,
      60,    60,    61,    61,    62,    63,    62,    64,    64,    64,
      65,    66,    66,    66,    66,    66,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    68,    69,    69,    69,    69,
      69,    70,    70,    70,    70,    71,    71,    72,    72,    72,
      73
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     2,     3,     1,     0,
       5,     0,     5,     5,     5,     0,     0,     8,     0,     0,
       8,     0,     3,     0,     3,     0,     3,     2,     2,     1,
       3,     1,     5,     5,     1,     4,     4,     1,     0,     6,
       0,     6,     3,     2,     0,     5,     2,     0,     5,     2,
       0,     4,     1,     0,     4,     1,     4,     3,     1,     1,
       3,     1,     3,     1,     5,     0,     7,     2,     2,     1,
       3,     1,     1,     1,     1,     1,     2,     2,     2,     2,
       2,     3,     1,     2,     3,     1,     1,     1,     1,     2,
       2,     1,     1,     1,     1,     2,     1,     4,     4,     4,
       3
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
  case 2: /* $@1: %empty  */
#line 76 "YP_parser.ypp"
                  { symbols.emplace_back(); }
#line 1288 "YP_parser.tab.cpp"
    break;

  case 3: /* starting_symbol: $@1 global_declaration  */
#line 76 "YP_parser.ypp"
                                                                 {
                      if(0 == count_error)
                        printf("the program was compiled correctly.\n");
                      else
                        printf("the program has %d errors.\n", count_error);
                      }
#line 1299 "YP_parser.tab.cpp"
    break;

  case 4: /* scope_begin: '{'  */
#line 83 "YP_parser.ypp"
                  { symbols.emplace_back(); }
#line 1305 "YP_parser.tab.cpp"
    break;

  case 5: /* scope_end: '}'  */
#line 84 "YP_parser.ypp"
                  { symbols.pop_back(); }
#line 1311 "YP_parser.tab.cpp"
    break;

  case 7: /* cls_decl: R_CLS S_NME ';'  */
#line 91 "YP_parser.ypp"
                          {
            if(LAST_SCOPE)
              yyerror("classes can only be declared globally");
              free((yyvsp[-1].token_name));
          }
#line 1321 "YP_parser.tab.cpp"
    break;

  case 8: /* cls_decl: cls_defn  */
#line 96 "YP_parser.ypp"
                   {
            if(LAST_SCOPE)
              yyerror("classes can only be declared globally");
          }
#line 1330 "YP_parser.tab.cpp"
    break;

  case 9: /* $@2: %empty  */
#line 102 "YP_parser.ypp"
                          { // scope_begin => emplaces back
            if(type_exists((yyvsp[-1].token_name)))
              yyerror("type already defined");
            else
            {
              cls_last_name = (yyvsp[-1].token_name);
              type_insert(cls_last_name);
            }}
#line 1343 "YP_parser.tab.cpp"
    break;

  case 10: /* cls_defn: R_CLS S_NME '{' $@2 arr_fild  */
#line 109 "YP_parser.ypp"
                        {
            cls_last_name.clear();
            free((yyvsp[-3].token_name));
          }
#line 1352 "YP_parser.tab.cpp"
    break;

  case 11: /* $@3: %empty  */
#line 115 "YP_parser.ypp"
                          { /* variable */
            bool is_error = false, error_flag = false;

            error_flag |= is_error =
              type_table[cls_last_name].exists((yyvsp[-1].token_name));
            if(is_error)
              yyerror("identifier already defined");
            
            error_flag |= is_error = 
              is_primitive((yyvsp[-1].token_name)) || type_exists((yyvsp[-1].token_name));
            if(is_error)
              yyerror("identifier treated as a type");
            
            // success
            if(false == error_flag)
            {
              variable_data v_data((yyvsp[-2].token_name));
              type_table[cls_last_name].variable_insert((yyvsp[-1].token_name), v_data);
            }
            
            free((yyvsp[-2].token_name)); free((yyvsp[-1].token_name));
          }
#line 1379 "YP_parser.tab.cpp"
    break;

  case 13: /* arr_fild: R_TYP S_NME OPERATOR_ASSIGN S_NME ';'  */
#line 138 "YP_parser.ypp"
                                                { /* variable */
            bool is_error = false, error_flag = false;

            error_flag |= is_error =
              type_table[cls_last_name].exists((yyvsp[-3].token_name));
            if(is_error)
              yyerror("identifier already defined");
            
            error_flag |= is_error = 
              is_primitive((yyvsp[-3].token_name)) || type_exists((yyvsp[-3].token_name));
            if(is_error)
              yyerror("first identifier treated as a type");
            
            error_flag |= is_error =
              is_primitive((yyvsp[-1].token_name)) || type_exists((yyvsp[-1].token_name));
            if(is_error)
              yyerror("second identifier treated as a type");
            
            // search for the argument
            const variable_data *arg_data =
              type_table[cls_last_name].variable_exists((yyvsp[-1].token_name));
            for(size_t i = LAST_SCOPE; arg_data; i--)
            {
              arg_data = symbols[i].variable_exists((yyvsp[-1].token_name));
              if(0 == i) break;
            }
              
            error_flag |= is_error =
              nullptr == arg_data;
            if(is_error)
              yyerror("argument not found");

            // it is possible that 0 == strcmp($2, $4)
            // only if their scopes differ
            error_flag |= is_error =
              nullptr == arg_data &&
              std::string((yyvsp[-3].token_name)) == std::string((yyvsp[-1].token_name));
            if(is_error)
              yyerror("assignation failed: argument not defined");

            error_flag |= is_error =
              std::string((yyvsp[-4].token_name)) != arg_data->get_data_type();
            if(is_error)
              yyerror("incorrect argument type");
            
            // success
            if(false == error_flag)
            {
              variable_data v_data((yyvsp[-4].token_name), arg_data->get_value());
              type_table[cls_last_name].variable_insert((yyvsp[-3].token_name), v_data);
            }
            
            free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); free((yyvsp[-1].token_name));
          }
#line 1438 "YP_parser.tab.cpp"
    break;

  case 14: /* arr_fild: R_TYP S_NME OPERATOR_ASSIGN cst_call ';'  */
#line 193 "YP_parser.ypp"
                                                   { /* variable */
            bool is_error = false, error_flag = false;

            error_flag |= is_error =
              type_table[cls_last_name].exists((yyvsp[-3].token_name));
            if(is_error)
              yyerror("identifier already defined");
            
            error_flag |= is_error =
              is_primitive((yyvsp[-3].token_name)) || type_exists((yyvsp[-3].token_name));
            if(is_error)
              yyerror("identifier treated as a type");

            // success
            if(false == error_flag && is_type_compatible((yyvsp[-4].token_name), (yyvsp[-1].token_name)))
            {
                variable_data v_data((yyvsp[-4].token_name), (yyvsp[-1].token_name));
                type_table[cls_last_name].variable_insert((yyvsp[-3].token_name), v_data);
            }

            free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); free((yyvsp[-1].token_name));
          }
#line 1465 "YP_parser.tab.cpp"
    break;

  case 15: /* $@4: %empty  */
#line 216 "YP_parser.ypp"
                      { /*? function */
            bool is_error = false, error_flag = false;

            error_flag |= is_error =
              is_already_defined((yyvsp[0].token_name));
            
            error_flag |= is_error =
              type_table[cls_last_name].exists((yyvsp[0].token_name));
            if(is_error)
              yyerror("identifier already defined");

            // success
            if(false == error_flag)
            {
              fct_last_name = std::string((yyvsp[0].token_name));
              function_data f_data((yyvsp[-1].token_name));
              f_data_global = &f_data;
              type_table[cls_last_name].function_insert((yyvsp[0].token_name), f_data);
            }}
#line 1489 "YP_parser.tab.cpp"
    break;

  case 16: /* $@5: %empty  */
#line 234 "YP_parser.ypp"
                                                   {
              free((yyvsp[-5].token_name)); free((yyvsp[-4].token_name));
          }
#line 1497 "YP_parser.tab.cpp"
    break;

  case 18: /* $@6: %empty  */
#line 238 "YP_parser.ypp"
                      { /*? function */
            bool is_error = false, error_flag = false;

            error_flag |= is_error = 
              nullptr == type_exists((yyvsp[-1].token_name));
            if(is_error)
              yyerror("undefined type");
            
            error_flag |= is_already_defined((yyvsp[0].token_name));
            error_flag |= is_error =
              type_table[cls_last_name].exists((yyvsp[0].token_name));
            if(is_error)
              yyerror("identifier already defined");

            // success
            if(false == error_flag)
            {
              fct_last_name = std::string((yyvsp[0].token_name));
              function_data f_data((yyvsp[-1].token_name));
              f_data_global = &f_data;
              type_table[cls_last_name].function_insert((yyvsp[0].token_name), f_data);
            }}
#line 1524 "YP_parser.tab.cpp"
    break;

  case 19: /* $@7: %empty  */
#line 259 "YP_parser.ypp"
                                                   {
              free((yyvsp[-5].token_name)); free((yyvsp[-4].token_name)); 
          }
#line 1532 "YP_parser.tab.cpp"
    break;

  case 21: /* $@8: %empty  */
#line 263 "YP_parser.ypp"
                   { /*type_table[cls_last_name].object_insert(last_object.c_str());*/ }
#line 1538 "YP_parser.tab.cpp"
    break;

  case 23: /* $@9: %empty  */
#line 264 "YP_parser.ypp"
                   { /*type_table[cls_last_name].object_insert(last_object.c_str());*/ }
#line 1544 "YP_parser.tab.cpp"
    break;

  case 25: /* $@10: %empty  */
#line 265 "YP_parser.ypp"
                   { /*type_table[cls_last_name].object_insert(last_object.c_str());*/ }
#line 1550 "YP_parser.tab.cpp"
    break;

  case 30: /* var_decl: R_TYP S_NME ';'  */
#line 274 "YP_parser.ypp"
                          {
            if(false == is_already_defined((yyvsp[-1].token_name)))
            {
              variable_data v_data((yyvsp[-2].token_name));
              symbols[LAST_SCOPE].variable_insert((yyvsp[-1].token_name), v_data);
            }

            free((yyvsp[-2].token_name)); free((yyvsp[-1].token_name)); 
          }
#line 1564 "YP_parser.tab.cpp"
    break;

  case 32: /* var_defn: R_TYP S_NME OPERATOR_ASSIGN S_NME ';'  */
#line 286 "YP_parser.ypp"
                                                {
            bool is_error = false, error_flag = false;
            error_flag |= is_already_defined((yyvsp[-3].token_name));
            
            // search for argument
            const variable_data *argument_defined = nullptr;
            for(size_t i = LAST_SCOPE; ; i--)
            {
              argument_defined = symbols[i].variable_exists((yyvsp[-1].token_name));

              if(argument_defined)
              {
                // type compatibility
                if(std::string((yyvsp[-4].token_name)) == argument_defined->get_data_type())
                  break;
                
                error_flag = true;
                yyerror("incorrect argument type");
              }
              
              if(0 == i) break;
            }

            error_flag |= is_error =
              nullptr == argument_defined;
            if(is_error)
              yyerror("argument not found");

            // success
            if(false == error_flag)
              symbols[LAST_SCOPE].variable_insert((yyvsp[-3].token_name), *argument_defined);
              
            free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); free((yyvsp[-1].token_name));
          }
#line 1603 "YP_parser.tab.cpp"
    break;

  case 33: /* var_defn: R_TYP S_NME OPERATOR_ASSIGN cst_call ';'  */
#line 321 "YP_parser.ypp"
                                                   {
            // both functions provide error messages
            // no need of yyerror statements
            if(false == is_already_defined((yyvsp[-3].token_name)) &&
            true == is_type_compatible((yyvsp[-4].token_name), (yyvsp[-1].token_name)))
            {
              variable_data v_data((yyvsp[-4].token_name), (yyvsp[-1].token_name));
              symbols[LAST_SCOPE].variable_insert((yyvsp[-3].token_name), v_data);
            }
            
            free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); free((yyvsp[-1].token_name));
          }
#line 1620 "YP_parser.tab.cpp"
    break;

  case 34: /* var_call: S_NME  */
#line 334 "YP_parser.ypp"
                {
            if(type_exists((yyvsp[0].token_name)))
              yyerror("type treated as a variable");
            const variable_data *argument_defined = nullptr;
            for(size_t i = LAST_SCOPE; ; i--)
            {
              argument_defined = symbols[i].variable_exists((yyvsp[0].token_name));
              if(argument_defined) break;
              if(0 == i) break;
            }
                
            if(nullptr == argument_defined)
              yyerror("identifier not found");
            free((yyvsp[0].token_name));
          }
#line 1640 "YP_parser.tab.cpp"
    break;

  case 35: /* fct_decl: R_TYP S_NME fct_synp ';'  */
#line 352 "YP_parser.ypp"
                                   {
            free((yyvsp[-3].token_name)); free((yyvsp[-2].token_name));
          }
#line 1648 "YP_parser.tab.cpp"
    break;

  case 36: /* fct_decl: S_NME S_NME fct_synp ';'  */
#line 355 "YP_parser.ypp"
                                   {
            if(nullptr == type_exists((yyvsp[-3].token_name)))
              yyerror("undefined type");
            free((yyvsp[-3].token_name)); free((yyvsp[-2].token_name));
          }
#line 1658 "YP_parser.tab.cpp"
    break;

  case 38: /* $@11: %empty  */
#line 363 "YP_parser.ypp"
                      {
            if(false == is_already_defined((yyvsp[0].token_name)))
            {
              fct_last_name = (yyvsp[0].token_name);
              function_data f_data((yyvsp[-1].token_name));
              f_data_global = &f_data;
              symbols[LAST_SCOPE].function_insert((yyvsp[0].token_name), f_data);
            }}
#line 1671 "YP_parser.tab.cpp"
    break;

  case 39: /* fct_defn: R_TYP S_NME $@11 fct_synp scope_begin statement_list  */
#line 370 "YP_parser.ypp"
                                                   {
            f_data_global = nullptr;
            fct_last_name.clear();
            free((yyvsp[-5].token_name)); free((yyvsp[-4].token_name));
          }
#line 1681 "YP_parser.tab.cpp"
    break;

  case 40: /* $@12: %empty  */
#line 375 "YP_parser.ypp"
                      {
            bool error_flag = 
              nullptr == type_exists((yyvsp[-1].token_name));
            if(error_flag)
              yyerror("undefined type");
            
            error_flag |= is_already_defined((yyvsp[0].token_name));
            
            if(false == error_flag)
            {
              fct_last_name = (yyvsp[0].token_name);
              function_data f_data((yyvsp[-1].token_name));
              f_data_global = &f_data;
              symbols[LAST_SCOPE].function_insert((yyvsp[0].token_name), f_data);
            }}
#line 1701 "YP_parser.tab.cpp"
    break;

  case 41: /* fct_defn: S_NME S_NME $@12 fct_synp scope_begin statement_list  */
#line 389 "YP_parser.ypp"
                                                   {
            f_data_global = nullptr;
            fct_last_name.clear();
            free((yyvsp[-5].token_name)); free((yyvsp[-4].token_name));
          }
#line 1711 "YP_parser.tab.cpp"
    break;

  case 44: /* $@13: %empty  */
#line 399 "YP_parser.ypp"
                      {
            variable_data v_data((yyvsp[-1].token_name));
            f_data_global->
              parameter_insert((yyvsp[0].token_name), &v_data);
            }
#line 1721 "YP_parser.tab.cpp"
    break;

  case 45: /* arr_parm: R_TYP S_NME $@13 ',' arr_parm  */
#line 403 "YP_parser.ypp"
                          { free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); 
          }
#line 1728 "YP_parser.tab.cpp"
    break;

  case 46: /* arr_parm: R_TYP S_NME  */
#line 405 "YP_parser.ypp"
                      {
            variable_data v_data((yyvsp[-1].token_name));
            f_data_global->
              parameter_insert((yyvsp[0].token_name), &v_data);
            free((yyvsp[-1].token_name)); free((yyvsp[0].token_name));
          }
#line 1739 "YP_parser.tab.cpp"
    break;

  case 47: /* $@14: %empty  */
#line 411 "YP_parser.ypp"
                      {
            if(nullptr == type_exists((yyvsp[-1].token_name)))
              yyerror("undefined type");
            else
            {
              object_data o_data((yyvsp[-1].token_name));
              f_data_global->
                parameter_insert((yyvsp[0].token_name), &o_data);
            }}
#line 1753 "YP_parser.tab.cpp"
    break;

  case 48: /* arr_parm: S_NME S_NME $@14 ',' arr_parm  */
#line 419 "YP_parser.ypp"
                           { free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name));
          }
#line 1760 "YP_parser.tab.cpp"
    break;

  case 49: /* arr_parm: S_NME S_NME  */
#line 421 "YP_parser.ypp"
                      {
            if(nullptr == type_exists((yyvsp[-1].token_name)))
              yyerror("undefined type");
            else
            {
              object_data o_data((yyvsp[-1].token_name));
              f_data_global->
                parameter_insert((yyvsp[0].token_name), &o_data);
            }
            
            free((yyvsp[-1].token_name)); free((yyvsp[0].token_name));
          }
#line 1777 "YP_parser.tab.cpp"
    break;

  case 50: /* $@15: %empty  */
#line 434 "YP_parser.ypp"
                {
            variable_data v_data((yyvsp[0].token_name));
            f_data_global->
              parameter_insert(&v_data);
            }
#line 1787 "YP_parser.tab.cpp"
    break;

  case 51: /* arr_parm: R_TYP $@15 ',' arr_parm  */
#line 438 "YP_parser.ypp"
                           { free((yyvsp[-3].token_name));
          }
#line 1794 "YP_parser.tab.cpp"
    break;

  case 52: /* arr_parm: R_TYP  */
#line 440 "YP_parser.ypp"
                {
            variable_data v_data((yyvsp[0].token_name));
            f_data_global->
              parameter_insert(&v_data);
            free((yyvsp[0].token_name));
          }
#line 1805 "YP_parser.tab.cpp"
    break;

  case 53: /* $@16: %empty  */
#line 446 "YP_parser.ypp"
                {
            if(nullptr == type_exists((yyvsp[0].token_name)))
              yyerror("undefined type");
            else
            {
              object_data o_data((yyvsp[0].token_name));
              f_data_global->
                parameter_insert(&o_data);
            }}
#line 1819 "YP_parser.tab.cpp"
    break;

  case 54: /* arr_parm: S_NME $@16 ',' arr_parm  */
#line 454 "YP_parser.ypp"
                            { free((yyvsp[-3].token_name));
          }
#line 1826 "YP_parser.tab.cpp"
    break;

  case 55: /* arr_parm: S_NME  */
#line 456 "YP_parser.ypp"
                {
            if(nullptr == type_exists((yyvsp[0].token_name)))
              yyerror("undefined type");
            else
            {
              object_data o_data((yyvsp[0].token_name));
              f_data_global->
                parameter_insert(&o_data);
            }
            
            free((yyvsp[0].token_name));
          }
#line 1843 "YP_parser.tab.cpp"
    break;

  case 56: /* fct_call: S_NME '(' arr_argm ')'  */
#line 472 "YP_parser.ypp"
                                 { /* provide return capacity */ free((yyvsp[-3].token_name)); }
#line 1849 "YP_parser.tab.cpp"
    break;

  case 57: /* fct_call: S_NME '(' ')'  */
#line 473 "YP_parser.ypp"
                        { /* provide return capacity */ free((yyvsp[-2].token_name)); }
#line 1855 "YP_parser.tab.cpp"
    break;

  case 62: /* obj_decl: S_NME S_NME ';'  */
#line 481 "YP_parser.ypp"
                          {
            bool error_flag =
              nullptr == type_exists((yyvsp[-2].token_name));
            if(error_flag)
              yyerror("undefined type");
            
            error_flag |= is_already_defined((yyvsp[-1].token_name));

            // success
            if(false == error_flag)
            {
              object_data o_data((yyvsp[-2].token_name));
              symbols[LAST_SCOPE].object_insert((yyvsp[-1].token_name), o_data);
            }

            free((yyvsp[-2].token_name)); free((yyvsp[-1].token_name));
          }
#line 1877 "YP_parser.tab.cpp"
    break;

  case 64: /* obj_defn: S_NME S_NME OPERATOR_ASSIGN S_NME ';'  */
#line 501 "YP_parser.ypp"
                                                {
            bool error_flag = 
              nullptr == type_exists((yyvsp[-4].token_name));
            if(error_flag)
              yyerror("undefined type");

            error_flag |= is_already_defined((yyvsp[-3].token_name));
            
            // search for the argument
            const object_data *argument_defined = nullptr;
            for(size_t i = LAST_SCOPE; ; i--)
            {
              argument_defined = symbols[i].object_exists((yyvsp[-1].token_name));

              if(argument_defined)
              {
                // type compatibility
                if(std::string((yyvsp[-4].token_name)) == argument_defined->get_data_type())
                  break;
                
                error_flag = true;
                yyerror("incorrect argument type");
              }
              
              if(0 == i) break;
            }

            if(nullptr == argument_defined)
            {
              error_flag = true;
              yyerror("argument not found");
            }

            // success
            if(false == error_flag)
              symbols[LAST_SCOPE].object_insert((yyvsp[-3].token_name), *argument_defined);
              
            free((yyvsp[-4].token_name)); free((yyvsp[-3].token_name)); free((yyvsp[-1].token_name));
          }
#line 1921 "YP_parser.tab.cpp"
    break;

  case 65: /* $@17: %empty  */
#line 540 "YP_parser.ypp"
                      { /*TODO: HARDEST THINGGGGGG */
            if(nullptr == type_exists((yyvsp[-1].token_name)))
              yyerror("undefined type");
            else
            {
              object_data o_data((yyvsp[-1].token_name));
              symbols[LAST_SCOPE].object_insert((yyvsp[0].token_name), o_data);
            }

            }
#line 1936 "YP_parser.tab.cpp"
    break;

  case 66: /* obj_defn: S_NME S_NME $@17 OPERATOR_ASSIGN '{' obj_vals ';'  */
#line 549 "YP_parser.ypp"
                                               {
            free((yyvsp[-6].token_name)); free((yyvsp[-5].token_name));
          }
#line 1944 "YP_parser.tab.cpp"
    break;

  case 70: /* fld_call: S_NME A_FLD S_NME  */
#line 557 "YP_parser.ypp"
                            { /* search type, search field */ }
#line 1950 "YP_parser.tab.cpp"
    break;

  case 71: /* cst_call: C_INT  */
#line 564 "YP_parser.ypp"
                { free((yyvsp[0].token_name)); }
#line 1956 "YP_parser.tab.cpp"
    break;

  case 72: /* cst_call: C_FLT  */
#line 565 "YP_parser.ypp"
                { free((yyvsp[0].token_name)); }
#line 1962 "YP_parser.tab.cpp"
    break;

  case 73: /* cst_call: C_CHR  */
#line 566 "YP_parser.ypp"
                { free((yyvsp[0].token_name)); }
#line 1968 "YP_parser.tab.cpp"
    break;

  case 74: /* cst_call: C_STR  */
#line 567 "YP_parser.ypp"
                { free((yyvsp[0].token_name)); }
#line 1974 "YP_parser.tab.cpp"
    break;

  case 75: /* cst_call: C_BOL  */
#line 568 "YP_parser.ypp"
                { free((yyvsp[0].token_name)); }
#line 1980 "YP_parser.tab.cpp"
    break;

  case 90: /* statement_parse: method_print ';'  */
#line 597 "YP_parser.ypp"
                                   { std::string s = (yyvsp[-1].token_name) + 6; s[s.size() - 1] = '\0'; printf("%s", s.c_str()); }
#line 1986 "YP_parser.tab.cpp"
    break;


#line 1990 "YP_parser.tab.cpp"

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

#line 631 "YP_parser.ypp"


//------------------------------------------------
//------------------------------------------------
// C++ functions:

void yyerror(const char * s){
    count_error++;
    printf("error - line %d: %s.\n", yylineno, s);
}

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        yyerror("wrong number of arguments");
        return EXIT_FAILURE;
    }

    FILE* ptr = fopen(argv[1],"r");
    if(nullptr == ptr)
    {
        yyerror("invalid file");
        return EXIT_FAILURE;
    }

    yyin = ptr;
    yyparse();
    return EXIT_SUCCESS;
}

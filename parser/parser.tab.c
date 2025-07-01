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
#line 1 "parser.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <vector>
#include <variant>
#include <optional>
#include "../include/ast.h"

// 声明全局根变量
std::unique_ptr<CompUnit> root;

int yylex();
void yyerror(const char *s);
extern char* yytext;
extern int line_number;
extern int col_number;

// 类型转换辅助函数
template<typename T>
std::unique_ptr<T> make_unique_from_ptr(T* ptr) {
    return std::unique_ptr<T>(ptr);
}

#line 97 "parser.tab.c"

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
  YYSYMBOL_INT_CONST = 3,                  /* INT_CONST  */
  YYSYMBOL_FLOAT_CONST = 4,                /* FLOAT_CONST  */
  YYSYMBOL_IDENT = 5,                      /* IDENT  */
  YYSYMBOL_STR_CONST = 6,                  /* STR_CONST  */
  YYSYMBOL_ERROR = 7,                      /* ERROR  */
  YYSYMBOL_PLUS = 8,                       /* PLUS  */
  YYSYMBOL_MINUS = 9,                      /* MINUS  */
  YYSYMBOL_MUL = 10,                       /* MUL  */
  YYSYMBOL_DIV = 11,                       /* DIV  */
  YYSYMBOL_MOD = 12,                       /* MOD  */
  YYSYMBOL_ASSIGN = 13,                    /* ASSIGN  */
  YYSYMBOL_NOT = 14,                       /* NOT  */
  YYSYMBOL_LT = 15,                        /* LT  */
  YYSYMBOL_GT = 16,                        /* GT  */
  YYSYMBOL_LEQ = 17,                       /* LEQ  */
  YYSYMBOL_GEQ = 18,                       /* GEQ  */
  YYSYMBOL_EQ = 19,                        /* EQ  */
  YYSYMBOL_NE = 20,                        /* NE  */
  YYSYMBOL_AND = 21,                       /* AND  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_LPAREN = 23,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 24,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 25,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 26,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 27,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 28,                    /* RBRACE  */
  YYSYMBOL_COMMA = 29,                     /* COMMA  */
  YYSYMBOL_SEMI = 30,                      /* SEMI  */
  YYSYMBOL_CONST = 31,                     /* CONST  */
  YYSYMBOL_IF = 32,                        /* IF  */
  YYSYMBOL_ELSE = 33,                      /* ELSE  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_VOID = 35,                      /* VOID  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_FLOAT = 37,                     /* FLOAT  */
  YYSYMBOL_RETURN = 38,                    /* RETURN  */
  YYSYMBOL_BREAK = 39,                     /* BREAK  */
  YYSYMBOL_CONTINUE = 40,                  /* CONTINUE  */
  YYSYMBOL_UMINUS = 41,                    /* UMINUS  */
  YYSYMBOL_UPLUS = 42,                     /* UPLUS  */
  YYSYMBOL_UNOT = 43,                      /* UNOT  */
  YYSYMBOL_LOWER_THAN_ELSE = 44,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_CompUnit = 46,                  /* CompUnit  */
  YYSYMBOL_CompItemList = 47,              /* CompItemList  */
  YYSYMBOL_Decl = 48,                      /* Decl  */
  YYSYMBOL_ConstDecl = 49,                 /* ConstDecl  */
  YYSYMBOL_ConstDefList = 50,              /* ConstDefList  */
  YYSYMBOL_ConstDef = 51,                  /* ConstDef  */
  YYSYMBOL_VarDecl = 52,                   /* VarDecl  */
  YYSYMBOL_VarDefList = 53,                /* VarDefList  */
  YYSYMBOL_VarDef = 54,                    /* VarDef  */
  YYSYMBOL_ArrayDims = 55,                 /* ArrayDims  */
  YYSYMBOL_FuncDef = 56,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 57,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 58,                /* FuncFParam  */
  YYSYMBOL_Block = 59,                     /* Block  */
  YYSYMBOL_BlockItemList = 60,             /* BlockItemList  */
  YYSYMBOL_Stmt = 61,                      /* Stmt  */
  YYSYMBOL_AssignStmt = 62,                /* AssignStmt  */
  YYSYMBOL_ExpStmt = 63,                   /* ExpStmt  */
  YYSYMBOL_IfStmt = 64,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 65,                 /* WhileStmt  */
  YYSYMBOL_BreakStmt = 66,                 /* BreakStmt  */
  YYSYMBOL_ContinueStmt = 67,              /* ContinueStmt  */
  YYSYMBOL_ReturnStmt = 68,                /* ReturnStmt  */
  YYSYMBOL_Exp = 69,                       /* Exp  */
  YYSYMBOL_Cond = 70,                      /* Cond  */
  YYSYMBOL_LOrExp = 71,                    /* LOrExp  */
  YYSYMBOL_LAndExp = 72,                   /* LAndExp  */
  YYSYMBOL_EqExp = 73,                     /* EqExp  */
  YYSYMBOL_RelExp = 74,                    /* RelExp  */
  YYSYMBOL_AddExp = 75,                    /* AddExp  */
  YYSYMBOL_MulExp = 76,                    /* MulExp  */
  YYSYMBOL_UnaryExp = 77,                  /* UnaryExp  */
  YYSYMBOL_FunctionCall = 78,              /* FunctionCall  */
  YYSYMBOL_FuncRParams = 79,               /* FuncRParams  */
  YYSYMBOL_PrimaryExp = 80,                /* PrimaryExp  */
  YYSYMBOL_LVal = 81,                      /* LVal  */
  YYSYMBOL_ArrayIndices = 82,              /* ArrayIndices  */
  YYSYMBOL_Number = 83,                    /* Number  */
  YYSYMBOL_ConstExp = 84,                  /* ConstExp  */
  YYSYMBOL_InitVal = 85,                   /* InitVal  */
  YYSYMBOL_InitValList = 86,               /* InitValList  */
  YYSYMBOL_ConstInitVal = 87,              /* ConstInitVal  */
  YYSYMBOL_ConstInitValList = 88,          /* ConstInitValList  */
  YYSYMBOL_BType = 89                      /* BType  */
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
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   286

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  191

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   299


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   136,   136,   145,   151,   157,   161,   169,   170,   175,
     186,   190,   198,   204,   214,   225,   229,   237,   243,   249,
     255,   264,   268,   276,   282,   292,   298,   311,   315,   323,
     328,   333,   342,   345,   353,   359,   365,   371,   381,   382,
     383,   384,   385,   386,   387,   388,   393,   400,   404,   412,
     417,   426,   433,   440,   447,   451,   459,   464,   469,   470,
     478,   479,   487,   488,   492,   500,   501,   505,   509,   513,
     521,   522,   526,   534,   535,   539,   543,   551,   552,   553,
     556,   559,   566,   571,   580,   584,   592,   593,   594,   599,
     604,   612,   616,   624,   627,   634,   639,   642,   646,   657,
     661,   669,   672,   676,   687,   691,   699,   700
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
  "\"end of file\"", "error", "\"invalid token\"", "INT_CONST",
  "FLOAT_CONST", "IDENT", "STR_CONST", "ERROR", "PLUS", "MINUS", "MUL",
  "DIV", "MOD", "ASSIGN", "NOT", "LT", "GT", "LEQ", "GEQ", "EQ", "NE",
  "AND", "OR", "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "LBRACE",
  "RBRACE", "COMMA", "SEMI", "CONST", "IF", "ELSE", "WHILE", "VOID", "INT",
  "FLOAT", "RETURN", "BREAK", "CONTINUE", "UMINUS", "UPLUS", "UNOT",
  "LOWER_THAN_ELSE", "$accept", "CompUnit", "CompItemList", "Decl",
  "ConstDecl", "ConstDefList", "ConstDef", "VarDecl", "VarDefList",
  "VarDef", "ArrayDims", "FuncDef", "FuncFParams", "FuncFParam", "Block",
  "BlockItemList", "Stmt", "AssignStmt", "ExpStmt", "IfStmt", "WhileStmt",
  "BreakStmt", "ContinueStmt", "ReturnStmt", "Exp", "Cond", "LOrExp",
  "LAndExp", "EqExp", "RelExp", "AddExp", "MulExp", "UnaryExp",
  "FunctionCall", "FuncRParams", "PrimaryExp", "LVal", "ArrayIndices",
  "Number", "ConstExp", "InitVal", "InitValList", "ConstInitVal",
  "ConstInitValList", "BType", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-100)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     101,    37,    25,  -100,  -100,    19,   101,  -100,  -100,  -100,
    -100,    33,    40,    26,  -100,  -100,  -100,     8,    55,  -100,
      14,    59,  -100,   -11,   252,     5,   160,    31,    86,  -100,
     259,    42,    40,  -100,    67,    -1,  -100,   102,  -100,  -100,
      -3,   160,   160,   160,   160,   224,  -100,    93,   187,  -100,
    -100,  -100,  -100,  -100,  -100,    67,    22,    93,    71,   252,
     160,    46,  -100,   231,  -100,  -100,   259,  -100,   148,  -100,
      67,    37,    85,    72,   160,    90,  -100,  -100,  -100,   107,
    -100,  -100,    92,   160,   160,   160,   160,   160,  -100,    67,
    -100,  -100,    91,  -100,  -100,   112,  -100,  -100,  -100,   105,
     147,    49,   142,   151,  -100,  -100,   186,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,  -100,   162,   164,    86,  -100,  -100,
     167,  -100,  -100,    58,   170,   160,  -100,  -100,   252,   187,
     187,  -100,  -100,  -100,  -100,  -100,  -100,   259,   160,   160,
    -100,   171,  -100,  -100,  -100,  -100,  -100,  -100,   160,   177,
    -100,   160,  -100,   178,  -100,  -100,   149,   181,   184,   104,
     143,    93,   182,  -100,   180,   183,  -100,  -100,    95,   160,
     160,   160,   160,   160,   160,   160,   160,    95,  -100,   174,
     184,   104,   143,   143,    93,    93,    93,    93,  -100,    95,
    -100
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,   106,   107,     0,     2,     3,     7,     8,
       4,     0,     0,     0,     1,     5,     6,    17,     0,    15,
       0,     0,    10,     0,     0,     0,     0,    18,     0,    14,
       0,     0,     0,     9,     0,     0,    27,     0,    93,    94,
      89,     0,     0,     0,     0,     0,    96,    56,    70,    73,
      78,    77,    87,    88,    19,     0,     0,    95,     0,     0,
       0,    17,    16,     0,   101,    12,     0,    11,     0,    23,
       0,     0,    29,     0,     0,    90,    79,    80,    81,     0,
      97,    99,     0,     0,     0,     0,     0,     0,    25,     0,
      21,    20,     0,   102,   104,     0,    13,    32,    47,     0,
       0,     0,     0,     0,    34,    40,     0,    35,    38,    39,
      41,    42,    43,    44,    45,     0,    87,     0,    24,    28,
       0,    82,    84,     0,     0,     0,    86,    98,     0,    71,
      72,    74,    75,    76,    26,    22,   103,     0,     0,     0,
      54,     0,    52,    53,    33,    36,    37,    48,     0,    30,
      83,     0,    91,     0,   100,   105,     0,    57,    58,    60,
      62,    65,     0,    55,     0,    31,    85,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    46,    49,
      59,    61,    63,    64,    66,    67,    68,    69,    51,     0,
      50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -100,  -100,  -100,     0,  -100,  -100,   179,  -100,  -100,   191,
     -19,   206,   190,   150,   -23,  -100,   -99,  -100,  -100,  -100,
    -100,  -100,  -100,  -100,    -9,    98,  -100,    61,    73,   -17,
     -26,    83,   -25,  -100,  -100,  -100,   -63,  -100,  -100,   -12,
     -35,  -100,   -54,  -100,     2
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,     8,    21,    22,     9,    18,    19,
      27,    10,    35,    36,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   156,   157,   158,   159,   160,
      47,    48,    49,    50,   123,    51,    52,    75,    53,    64,
      54,    82,    65,    95,    37
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      57,    31,    11,    12,    57,   116,    15,   146,    11,    94,
      81,    69,    96,    34,    58,    46,    76,    77,    78,    14,
      73,    24,    74,    70,    91,     3,     4,    30,    71,    55,
      13,    25,    88,    26,    57,    79,    46,    57,    17,    26,
      57,     3,     4,   116,    59,    20,    89,   118,    92,    23,
      46,    71,    38,    39,    40,    66,    60,    41,    42,    24,
     131,   132,   133,    43,   122,   124,   134,    60,   104,   179,
     117,    26,    44,     3,     4,    38,    39,    40,   188,   140,
      41,    42,   150,   155,    28,    29,    43,   151,    32,    33,
     190,    61,   141,   154,    68,    44,   121,    90,    38,    39,
      40,    83,    84,    41,    42,   116,   145,    72,   117,    43,
     120,    57,   161,   161,   116,   125,   153,   135,    44,    46,
     127,   128,    68,   171,   172,    98,   116,    99,   138,   100,
     165,   126,     1,   101,   102,   103,     2,     3,     4,   164,
     136,   137,   166,   161,   161,   161,   161,   184,   185,   186,
     187,    38,    39,    40,   182,   183,    41,    42,   173,   174,
     175,   176,    43,    38,    39,    40,   129,   130,    41,    42,
     139,    44,   142,   168,    43,    68,    97,   148,    98,     1,
      99,   143,   100,    44,     3,     4,   101,   102,   103,    38,
      39,    40,   147,   149,    41,    42,   152,    85,    86,    87,
      43,   163,    26,   169,   167,   170,   177,   189,    60,    44,
     178,    67,    16,    68,   144,    56,    98,     1,    99,    62,
     100,   119,     3,     4,   101,   102,   103,    38,    39,    40,
     180,     0,    41,    42,    38,    39,    40,   162,    43,    41,
      42,     0,     0,   181,     0,    43,     0,    44,     0,     0,
       0,    45,    80,     0,    44,    38,    39,    40,    63,    93,
      41,    42,    38,    39,    40,     0,    43,    41,    42,     0,
       0,     0,     0,    43,     0,    44,     0,     0,     0,    45,
       0,     0,    44,     0,     0,     0,    63
};

static const yytype_int16 yycheck[] =
{
      26,    20,     0,     1,    30,    68,     6,   106,     6,    63,
      45,    34,    66,    24,    26,    24,    41,    42,    43,     0,
      23,    13,    25,    24,    59,    36,    37,    13,    29,    24,
       5,    23,    55,    25,    60,    44,    45,    63,     5,    25,
      66,    36,    37,   106,    13,     5,    24,    70,    60,    23,
      59,    29,     3,     4,     5,    13,    25,     8,     9,    13,
      85,    86,    87,    14,    73,    74,    89,    25,    68,   168,
      68,    25,    23,    36,    37,     3,     4,     5,   177,    30,
       8,     9,    24,   137,    29,    30,    14,    29,    29,    30,
     189,     5,   101,   128,    27,    23,    24,    26,     3,     4,
       5,     8,     9,     8,     9,   168,   106,     5,   106,    14,
      25,   137,   138,   139,   177,    25,   125,    26,    23,   128,
      28,    29,    27,    19,    20,    30,   189,    32,    23,    34,
     149,    24,    31,    38,    39,    40,    35,    36,    37,   148,
      28,    29,   151,   169,   170,   171,   172,   173,   174,   175,
     176,     3,     4,     5,   171,   172,     8,     9,    15,    16,
      17,    18,    14,     3,     4,     5,    83,    84,     8,     9,
      23,    23,    30,    24,    14,    27,    28,    13,    30,    31,
      32,    30,    34,    23,    36,    37,    38,    39,    40,     3,
       4,     5,    30,    26,     8,     9,    26,    10,    11,    12,
      14,    30,    25,    22,    26,    21,    24,    33,    25,    23,
      30,    32,     6,    27,    28,    25,    30,    31,    32,    28,
      34,    71,    36,    37,    38,    39,    40,     3,     4,     5,
     169,    -1,     8,     9,     3,     4,     5,   139,    14,     8,
       9,    -1,    -1,   170,    -1,    14,    -1,    23,    -1,    -1,
      -1,    27,    28,    -1,    23,     3,     4,     5,    27,    28,
       8,     9,     3,     4,     5,    -1,    14,     8,     9,    -1,
      -1,    -1,    -1,    14,    -1,    23,    -1,    -1,    -1,    27,
      -1,    -1,    23,    -1,    -1,    -1,    27
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    35,    36,    37,    46,    47,    48,    49,    52,
      56,    89,    89,     5,     0,    48,    56,     5,    53,    54,
       5,    50,    51,    23,    13,    23,    25,    55,    29,    30,
      13,    55,    29,    30,    24,    57,    58,    89,     3,     4,
       5,     8,     9,    14,    23,    27,    69,    75,    76,    77,
      78,    80,    81,    83,    85,    24,    57,    75,    84,    13,
      25,     5,    54,    27,    84,    87,    13,    51,    27,    59,
      24,    29,     5,    23,    25,    82,    77,    77,    77,    69,
      28,    85,    86,     8,     9,    10,    11,    12,    59,    24,
      26,    85,    84,    28,    87,    88,    87,    28,    30,    32,
      34,    38,    39,    40,    48,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,    69,    81,    89,    59,    58,
      25,    24,    69,    79,    69,    25,    24,    28,    29,    76,
      76,    77,    77,    77,    59,    26,    28,    29,    23,    23,
      30,    69,    30,    30,    28,    48,    61,    30,    13,    26,
      24,    29,    26,    69,    85,    87,    70,    71,    72,    73,
      74,    75,    70,    30,    69,    55,    69,    26,    24,    22,
      21,    19,    20,    15,    16,    17,    18,    24,    30,    61,
      72,    73,    74,    74,    75,    75,    75,    75,    61,    33,
      61
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    47,    48,    48,    49,
      50,    50,    51,    51,    52,    53,    53,    54,    54,    54,
      54,    55,    55,    56,    56,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    60,    60,    60,    60,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    63,    63,    64,
      64,    65,    66,    67,    68,    68,    69,    70,    71,    71,
      72,    72,    73,    73,    73,    74,    74,    74,    74,    74,
      75,    75,    75,    76,    76,    76,    76,    77,    77,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    85,    85,    85,    86,
      86,    87,    87,    87,    88,    88,    89,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     2,     2,     1,     1,     4,
       1,     3,     3,     4,     3,     1,     3,     1,     2,     3,
       4,     3,     4,     5,     6,     5,     6,     1,     3,     2,
       4,     5,     2,     3,     1,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     2,     5,
       7,     5,     2,     2,     2,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     3,     3,     3,     1,     1,     2,
       2,     2,     3,     4,     1,     3,     3,     1,     1,     1,
       2,     3,     4,     1,     1,     1,     1,     2,     3,     1,
       3,     1,     2,     3,     1,     3,     1,     1
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
  case 2: /* CompUnit: CompItemList  */
#line 136 "parser.y"
                 {
        (yyval.comp_unit) = new CompUnit({line_number});
        (yyval.comp_unit)->items = std::move(*(yyvsp[0].comp_item_list));
        delete (yyvsp[0].comp_item_list);
        root = make_unique_from_ptr((yyval.comp_unit));
    }
#line 1332 "parser.tab.c"
    break;

  case 3: /* CompItemList: Decl  */
#line 145 "parser.y"
         {
        (yyval.comp_item_list) = new std::vector<std::variant<std::unique_ptr<Decl>, std::unique_ptr<FuncDef>>>();
        std::variant<std::unique_ptr<Decl>, std::unique_ptr<FuncDef>> item;
        item = make_unique_from_ptr((yyvsp[0].decl));
        (yyval.comp_item_list)->push_back(std::move(item));
    }
#line 1343 "parser.tab.c"
    break;

  case 4: /* CompItemList: FuncDef  */
#line 151 "parser.y"
              {
        (yyval.comp_item_list) = new std::vector<std::variant<std::unique_ptr<Decl>, std::unique_ptr<FuncDef>>>();
        std::variant<std::unique_ptr<Decl>, std::unique_ptr<FuncDef>> item;
        item = make_unique_from_ptr((yyvsp[0].func_def));
        (yyval.comp_item_list)->push_back(std::move(item));
    }
#line 1354 "parser.tab.c"
    break;

  case 5: /* CompItemList: CompItemList Decl  */
#line 157 "parser.y"
                        {
        (yyvsp[-1].comp_item_list)->emplace_back(make_unique_from_ptr((yyvsp[0].decl)));
        (yyval.comp_item_list) = (yyvsp[-1].comp_item_list);
    }
#line 1363 "parser.tab.c"
    break;

  case 6: /* CompItemList: CompItemList FuncDef  */
#line 161 "parser.y"
                           {
        (yyvsp[-1].comp_item_list)->emplace_back(make_unique_from_ptr((yyvsp[0].func_def)));
        (yyval.comp_item_list) = (yyvsp[-1].comp_item_list);
    }
#line 1372 "parser.tab.c"
    break;

  case 7: /* Decl: ConstDecl  */
#line 169 "parser.y"
              { (yyval.decl) = (yyvsp[0].const_decl); }
#line 1378 "parser.tab.c"
    break;

  case 8: /* Decl: VarDecl  */
#line 170 "parser.y"
              { (yyval.decl) = (yyvsp[0].var_decl); }
#line 1384 "parser.tab.c"
    break;

  case 9: /* ConstDecl: CONST BType ConstDefList SEMI  */
#line 175 "parser.y"
                                  {
        std::vector<std::unique_ptr<ConstDef>> defs;
        for (auto& def : *(yyvsp[-1].const_def_list)) {
            defs.push_back(std::move(def));
        }
        delete (yyvsp[-1].const_def_list);
        (yyval.const_decl) = new ConstDecl((yyvsp[-2].base_type), std::move(defs), {line_number});
    }
#line 1397 "parser.tab.c"
    break;

  case 10: /* ConstDefList: ConstDef  */
#line 186 "parser.y"
             {
        (yyval.const_def_list) = new std::vector<std::unique_ptr<ConstDef>>();
        (yyval.const_def_list)->push_back(make_unique_from_ptr((yyvsp[0].const_def)));
    }
#line 1406 "parser.tab.c"
    break;

  case 11: /* ConstDefList: ConstDefList COMMA ConstDef  */
#line 190 "parser.y"
                                  {
        (yyvsp[-2].const_def_list)->push_back(make_unique_from_ptr((yyvsp[0].const_def)));
        (yyval.const_def_list) = (yyvsp[-2].const_def_list);
    }
#line 1415 "parser.tab.c"
    break;

  case 12: /* ConstDef: IDENT ASSIGN ConstInitVal  */
#line 198 "parser.y"
                              {
        std::vector<std::unique_ptr<Exp>> dims;
        (yyval.const_def) = new ConstDef(std::string((yyvsp[-2].str_val)), std::move(dims), 
                         make_unique_from_ptr((yyvsp[0].const_init_val)), {line_number});
        free((yyvsp[-2].str_val));
    }
#line 1426 "parser.tab.c"
    break;

  case 13: /* ConstDef: IDENT ArrayDims ASSIGN ConstInitVal  */
#line 204 "parser.y"
                                          {
        (yyval.const_def) = new ConstDef(std::string((yyvsp[-3].str_val)), std::move(*(yyvsp[-2].exp_list)), 
                         make_unique_from_ptr((yyvsp[0].const_init_val)), {line_number});
        free((yyvsp[-3].str_val));
        delete (yyvsp[-2].exp_list);
    }
#line 1437 "parser.tab.c"
    break;

  case 14: /* VarDecl: BType VarDefList SEMI  */
#line 214 "parser.y"
                          {
        std::vector<std::unique_ptr<VarDef>> defs;
        for (auto& def : *(yyvsp[-1].var_def_list)) {
            defs.push_back(std::move(def));
        }
        delete (yyvsp[-1].var_def_list);
        (yyval.var_decl) = new VarDecl((yyvsp[-2].base_type), std::move(defs), {line_number});
    }
#line 1450 "parser.tab.c"
    break;

  case 15: /* VarDefList: VarDef  */
#line 225 "parser.y"
           {
        (yyval.var_def_list) = new std::vector<std::unique_ptr<VarDef>>();
        (yyval.var_def_list)->push_back(make_unique_from_ptr((yyvsp[0].var_def)));
    }
#line 1459 "parser.tab.c"
    break;

  case 16: /* VarDefList: VarDefList COMMA VarDef  */
#line 229 "parser.y"
                              {
        (yyvsp[-2].var_def_list)->push_back(make_unique_from_ptr((yyvsp[0].var_def)));
        (yyval.var_def_list) = (yyvsp[-2].var_def_list);
    }
#line 1468 "parser.tab.c"
    break;

  case 17: /* VarDef: IDENT  */
#line 237 "parser.y"
          {
        std::vector<std::unique_ptr<Exp>> dims;
        std::optional<std::unique_ptr<InitVal>> init;
        (yyval.var_def) = new VarDef(std::string((yyvsp[0].str_val)), std::move(dims), std::move(init), {line_number});
        free((yyvsp[0].str_val));
    }
#line 1479 "parser.tab.c"
    break;

  case 18: /* VarDef: IDENT ArrayDims  */
#line 243 "parser.y"
                      {
        std::optional<std::unique_ptr<InitVal>> init;
        (yyval.var_def) = new VarDef(std::string((yyvsp[-1].str_val)), std::move(*(yyvsp[0].exp_list)), std::move(init), {line_number});
        free((yyvsp[-1].str_val));
        delete (yyvsp[0].exp_list);
    }
#line 1490 "parser.tab.c"
    break;

  case 19: /* VarDef: IDENT ASSIGN InitVal  */
#line 249 "parser.y"
                           {
        std::vector<std::unique_ptr<Exp>> dims;
        std::optional<std::unique_ptr<InitVal>> init = make_unique_from_ptr((yyvsp[0].init_val));
        (yyval.var_def) = new VarDef(std::string((yyvsp[-2].str_val)), std::move(dims), std::move(init), {line_number});
        free((yyvsp[-2].str_val));
    }
#line 1501 "parser.tab.c"
    break;

  case 20: /* VarDef: IDENT ArrayDims ASSIGN InitVal  */
#line 255 "parser.y"
                                     {
        std::optional<std::unique_ptr<InitVal>> init = make_unique_from_ptr((yyvsp[0].init_val));
        (yyval.var_def) = new VarDef(std::string((yyvsp[-3].str_val)), std::move(*(yyvsp[-2].exp_list)), std::move(init), {line_number});
        free((yyvsp[-3].str_val));
        delete (yyvsp[-2].exp_list);
    }
#line 1512 "parser.tab.c"
    break;

  case 21: /* ArrayDims: LBRACKET ConstExp RBRACKET  */
#line 264 "parser.y"
                               {
        (yyval.exp_list) = new std::vector<std::unique_ptr<Exp>>();
        (yyval.exp_list)->push_back(make_unique_from_ptr((yyvsp[-1].exp)));
    }
#line 1521 "parser.tab.c"
    break;

  case 22: /* ArrayDims: ArrayDims LBRACKET ConstExp RBRACKET  */
#line 268 "parser.y"
                                           {
        (yyvsp[-3].exp_list)->push_back(make_unique_from_ptr((yyvsp[-1].exp)));
        (yyval.exp_list) = (yyvsp[-3].exp_list);
    }
#line 1530 "parser.tab.c"
    break;

  case 23: /* FuncDef: VOID IDENT LPAREN RPAREN Block  */
#line 276 "parser.y"
                                   {
        std::vector<std::unique_ptr<FuncFParam>> params;
        (yyval.func_def) = new FuncDef(BaseType::VOID, std::string((yyvsp[-3].str_val)), std::move(params), 
                        make_unique_from_ptr((yyvsp[0].block)), {line_number});
        free((yyvsp[-3].str_val));
    }
#line 1541 "parser.tab.c"
    break;

  case 24: /* FuncDef: VOID IDENT LPAREN FuncFParams RPAREN Block  */
#line 282 "parser.y"
                                                 {
        std::vector<std::unique_ptr<FuncFParam>> params;
        for (auto& param : *(yyvsp[-2].param_list)) {
            params.push_back(std::move(param));
        }
        delete (yyvsp[-2].param_list);
        (yyval.func_def) = new FuncDef(BaseType::VOID, std::string((yyvsp[-4].str_val)), std::move(params), 
                        make_unique_from_ptr((yyvsp[0].block)), {line_number});
        free((yyvsp[-4].str_val));
    }
#line 1556 "parser.tab.c"
    break;

  case 25: /* FuncDef: BType IDENT LPAREN RPAREN Block  */
#line 292 "parser.y"
                                      {
        std::vector<std::unique_ptr<FuncFParam>> params;
        (yyval.func_def) = new FuncDef((yyvsp[-4].base_type), std::string((yyvsp[-3].str_val)), std::move(params), 
                        make_unique_from_ptr((yyvsp[0].block)), {line_number});
        free((yyvsp[-3].str_val));
    }
#line 1567 "parser.tab.c"
    break;

  case 26: /* FuncDef: BType IDENT LPAREN FuncFParams RPAREN Block  */
#line 298 "parser.y"
                                                  {
        std::vector<std::unique_ptr<FuncFParam>> params;
        for (auto& param : *(yyvsp[-2].param_list)) {
            params.push_back(std::move(param));
        }
        delete (yyvsp[-2].param_list);
        (yyval.func_def) = new FuncDef((yyvsp[-5].base_type), std::string((yyvsp[-4].str_val)), std::move(params), 
                        make_unique_from_ptr((yyvsp[0].block)), {line_number});
        free((yyvsp[-4].str_val));
    }
#line 1582 "parser.tab.c"
    break;

  case 27: /* FuncFParams: FuncFParam  */
#line 311 "parser.y"
               {
        (yyval.param_list) = new std::vector<std::unique_ptr<FuncFParam>>();
        (yyval.param_list)->push_back(make_unique_from_ptr((yyvsp[0].func_param)));
    }
#line 1591 "parser.tab.c"
    break;

  case 28: /* FuncFParams: FuncFParams COMMA FuncFParam  */
#line 315 "parser.y"
                                   {
        (yyvsp[-2].param_list)->push_back(make_unique_from_ptr((yyvsp[0].func_param)));
        (yyval.param_list) = (yyvsp[-2].param_list);
    }
#line 1600 "parser.tab.c"
    break;

  case 29: /* FuncFParam: BType IDENT  */
#line 323 "parser.y"
                {
        std::vector<std::unique_ptr<Exp>> dims;
        (yyval.func_param) = new FuncFParam((yyvsp[-1].base_type), std::string((yyvsp[0].str_val)), false, std::move(dims), {line_number});
        free((yyvsp[0].str_val));
    }
#line 1610 "parser.tab.c"
    break;

  case 30: /* FuncFParam: BType IDENT LBRACKET RBRACKET  */
#line 328 "parser.y"
                                    {
        std::vector<std::unique_ptr<Exp>> dims;
        (yyval.func_param) = new FuncFParam((yyvsp[-3].base_type), std::string((yyvsp[-2].str_val)), true, std::move(dims), {line_number});
        free((yyvsp[-2].str_val));
    }
#line 1620 "parser.tab.c"
    break;

  case 31: /* FuncFParam: BType IDENT LBRACKET RBRACKET ArrayDims  */
#line 333 "parser.y"
                                              {
        (yyval.func_param) = new FuncFParam((yyvsp[-4].base_type), std::string((yyvsp[-3].str_val)), true, std::move(*(yyvsp[0].exp_list)), {line_number});
        free((yyvsp[-3].str_val));
        delete (yyvsp[0].exp_list);
    }
#line 1630 "parser.tab.c"
    break;

  case 32: /* Block: LBRACE RBRACE  */
#line 342 "parser.y"
                  {
        (yyval.block) = new Block({line_number});
    }
#line 1638 "parser.tab.c"
    break;

  case 33: /* Block: LBRACE BlockItemList RBRACE  */
#line 345 "parser.y"
                                  {
        (yyval.block) = new Block({line_number});
        (yyval.block)->items = std::move(*(yyvsp[-1].block_item_list));
        delete (yyvsp[-1].block_item_list);
    }
#line 1648 "parser.tab.c"
    break;

  case 34: /* BlockItemList: Decl  */
#line 353 "parser.y"
         {
        (yyval.block_item_list) = new std::vector<std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>>>();
        std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>> item;
        item = make_unique_from_ptr((yyvsp[0].decl));
        (yyval.block_item_list)->push_back(std::move(item));
    }
#line 1659 "parser.tab.c"
    break;

  case 35: /* BlockItemList: Stmt  */
#line 359 "parser.y"
           {
        (yyval.block_item_list) = new std::vector<std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>>>();
        std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>> item;
        item = make_unique_from_ptr((yyvsp[0].stmt));
        (yyval.block_item_list)->push_back(std::move(item));
    }
#line 1670 "parser.tab.c"
    break;

  case 36: /* BlockItemList: BlockItemList Decl  */
#line 365 "parser.y"
                         {
        std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>> item;
        item = make_unique_from_ptr((yyvsp[0].decl));
        (yyvsp[-1].block_item_list)->push_back(std::move(item));
        (yyval.block_item_list) = (yyvsp[-1].block_item_list);
    }
#line 1681 "parser.tab.c"
    break;

  case 37: /* BlockItemList: BlockItemList Stmt  */
#line 371 "parser.y"
                         {
        std::variant<std::unique_ptr<Stmt>, std::unique_ptr<Decl>> item;
        item = make_unique_from_ptr((yyvsp[0].stmt));
        (yyvsp[-1].block_item_list)->push_back(std::move(item));
        (yyval.block_item_list) = (yyvsp[-1].block_item_list);
    }
#line 1692 "parser.tab.c"
    break;

  case 38: /* Stmt: AssignStmt  */
#line 381 "parser.y"
               { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1698 "parser.tab.c"
    break;

  case 39: /* Stmt: ExpStmt  */
#line 382 "parser.y"
              { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1704 "parser.tab.c"
    break;

  case 40: /* Stmt: Block  */
#line 383 "parser.y"
            { (yyval.stmt) = (yyvsp[0].block); }
#line 1710 "parser.tab.c"
    break;

  case 41: /* Stmt: IfStmt  */
#line 384 "parser.y"
             { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1716 "parser.tab.c"
    break;

  case 42: /* Stmt: WhileStmt  */
#line 385 "parser.y"
                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1722 "parser.tab.c"
    break;

  case 43: /* Stmt: BreakStmt  */
#line 386 "parser.y"
                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1728 "parser.tab.c"
    break;

  case 44: /* Stmt: ContinueStmt  */
#line 387 "parser.y"
                   { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1734 "parser.tab.c"
    break;

  case 45: /* Stmt: ReturnStmt  */
#line 388 "parser.y"
                 { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1740 "parser.tab.c"
    break;

  case 46: /* AssignStmt: LVal ASSIGN Exp SEMI  */
#line 393 "parser.y"
                         {
        (yyval.stmt) = new AssignStmt(make_unique_from_ptr((yyvsp[-3].lval)), make_unique_from_ptr((yyvsp[-1].exp)), {line_number});
    }
#line 1748 "parser.tab.c"
    break;

  case 47: /* ExpStmt: SEMI  */
#line 400 "parser.y"
         {
        std::optional<std::unique_ptr<Exp>> expr;
        (yyval.stmt) = new ExpStmt(std::move(expr), {line_number});
    }
#line 1757 "parser.tab.c"
    break;

  case 48: /* ExpStmt: Exp SEMI  */
#line 404 "parser.y"
               {
        std::optional<std::unique_ptr<Exp>> expr = make_unique_from_ptr((yyvsp[-1].exp));
        (yyval.stmt) = new ExpStmt(std::move(expr), {line_number});
    }
#line 1766 "parser.tab.c"
    break;

  case 49: /* IfStmt: IF LPAREN Cond RPAREN Stmt  */
#line 412 "parser.y"
                                                     {
        std::optional<std::unique_ptr<Stmt>> else_stmt;
        (yyval.stmt) = new IfStmt(make_unique_from_ptr((yyvsp[-2].exp)), make_unique_from_ptr((yyvsp[0].stmt)), 
                       std::move(else_stmt), {line_number});
    }
#line 1776 "parser.tab.c"
    break;

  case 50: /* IfStmt: IF LPAREN Cond RPAREN Stmt ELSE Stmt  */
#line 417 "parser.y"
                                           {
        std::optional<std::unique_ptr<Stmt>> else_stmt = make_unique_from_ptr((yyvsp[0].stmt));
        (yyval.stmt) = new IfStmt(make_unique_from_ptr((yyvsp[-4].exp)), make_unique_from_ptr((yyvsp[-2].stmt)), 
                       std::move(else_stmt), {line_number});
    }
#line 1786 "parser.tab.c"
    break;

  case 51: /* WhileStmt: WHILE LPAREN Cond RPAREN Stmt  */
#line 426 "parser.y"
                                  {
        (yyval.stmt) = new WhileStmt(make_unique_from_ptr((yyvsp[-2].exp)), make_unique_from_ptr((yyvsp[0].stmt)), {line_number});
    }
#line 1794 "parser.tab.c"
    break;

  case 52: /* BreakStmt: BREAK SEMI  */
#line 433 "parser.y"
               {
        (yyval.stmt) = new BreakStmt({line_number});
    }
#line 1802 "parser.tab.c"
    break;

  case 53: /* ContinueStmt: CONTINUE SEMI  */
#line 440 "parser.y"
                  {
        (yyval.stmt) = new ContinueStmt({line_number});
    }
#line 1810 "parser.tab.c"
    break;

  case 54: /* ReturnStmt: RETURN SEMI  */
#line 447 "parser.y"
                {
        std::optional<std::unique_ptr<Exp>> expr;
        (yyval.stmt) = new ReturnStmt(std::move(expr), {line_number});
    }
#line 1819 "parser.tab.c"
    break;

  case 55: /* ReturnStmt: RETURN Exp SEMI  */
#line 451 "parser.y"
                      {
        std::optional<std::unique_ptr<Exp>> expr = make_unique_from_ptr((yyvsp[-1].exp));
        (yyval.stmt) = new ReturnStmt(std::move(expr), {line_number});
    }
#line 1828 "parser.tab.c"
    break;

  case 56: /* Exp: AddExp  */
#line 459 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 1834 "parser.tab.c"
    break;

  case 57: /* Cond: LOrExp  */
#line 464 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 1840 "parser.tab.c"
    break;

  case 58: /* LOrExp: LAndExp  */
#line 469 "parser.y"
            { (yyval.exp) = (yyvsp[0].exp); }
#line 1846 "parser.tab.c"
    break;

  case 59: /* LOrExp: LOrExp OR LAndExp  */
#line 470 "parser.y"
                        {
        (yyval.exp) = new BinaryExp(BinaryOp::OR, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1855 "parser.tab.c"
    break;

  case 60: /* LAndExp: EqExp  */
#line 478 "parser.y"
          { (yyval.exp) = (yyvsp[0].exp); }
#line 1861 "parser.tab.c"
    break;

  case 61: /* LAndExp: LAndExp AND EqExp  */
#line 479 "parser.y"
                        {
        (yyval.exp) = new BinaryExp(BinaryOp::AND, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1870 "parser.tab.c"
    break;

  case 62: /* EqExp: RelExp  */
#line 487 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 1876 "parser.tab.c"
    break;

  case 63: /* EqExp: EqExp EQ RelExp  */
#line 488 "parser.y"
                      {
        (yyval.exp) = new BinaryExp(BinaryOp::EQ, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1885 "parser.tab.c"
    break;

  case 64: /* EqExp: EqExp NE RelExp  */
#line 492 "parser.y"
                      {
        (yyval.exp) = new BinaryExp(BinaryOp::NEQ, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1894 "parser.tab.c"
    break;

  case 65: /* RelExp: AddExp  */
#line 500 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 1900 "parser.tab.c"
    break;

  case 66: /* RelExp: RelExp LT AddExp  */
#line 501 "parser.y"
                       {
        (yyval.exp) = new BinaryExp(BinaryOp::LT, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1909 "parser.tab.c"
    break;

  case 67: /* RelExp: RelExp GT AddExp  */
#line 505 "parser.y"
                       {
        (yyval.exp) = new BinaryExp(BinaryOp::GT, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1918 "parser.tab.c"
    break;

  case 68: /* RelExp: RelExp LEQ AddExp  */
#line 509 "parser.y"
                        {
        (yyval.exp) = new BinaryExp(BinaryOp::LTE, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1927 "parser.tab.c"
    break;

  case 69: /* RelExp: RelExp GEQ AddExp  */
#line 513 "parser.y"
                        {
        (yyval.exp) = new BinaryExp(BinaryOp::GTE, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1936 "parser.tab.c"
    break;

  case 70: /* AddExp: MulExp  */
#line 521 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 1942 "parser.tab.c"
    break;

  case 71: /* AddExp: AddExp PLUS MulExp  */
#line 522 "parser.y"
                         {
        (yyval.exp) = new BinaryExp(BinaryOp::ADD, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1951 "parser.tab.c"
    break;

  case 72: /* AddExp: AddExp MINUS MulExp  */
#line 526 "parser.y"
                          {
        (yyval.exp) = new BinaryExp(BinaryOp::SUB, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1960 "parser.tab.c"
    break;

  case 73: /* MulExp: UnaryExp  */
#line 534 "parser.y"
             { (yyval.exp) = (yyvsp[0].exp); }
#line 1966 "parser.tab.c"
    break;

  case 74: /* MulExp: MulExp MUL UnaryExp  */
#line 535 "parser.y"
                          {
        (yyval.exp) = new BinaryExp(BinaryOp::MUL, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1975 "parser.tab.c"
    break;

  case 75: /* MulExp: MulExp DIV UnaryExp  */
#line 539 "parser.y"
                          {
        (yyval.exp) = new BinaryExp(BinaryOp::DIV, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1984 "parser.tab.c"
    break;

  case 76: /* MulExp: MulExp MOD UnaryExp  */
#line 543 "parser.y"
                          {
        (yyval.exp) = new BinaryExp(BinaryOp::MOD, make_unique_from_ptr((yyvsp[-2].exp)), 
                          make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 1993 "parser.tab.c"
    break;

  case 77: /* UnaryExp: PrimaryExp  */
#line 551 "parser.y"
               { (yyval.exp) = (yyvsp[0].exp); }
#line 1999 "parser.tab.c"
    break;

  case 78: /* UnaryExp: FunctionCall  */
#line 552 "parser.y"
                   { (yyval.exp) = (yyvsp[0].exp); }
#line 2005 "parser.tab.c"
    break;

  case 79: /* UnaryExp: PLUS UnaryExp  */
#line 553 "parser.y"
                                {
        (yyval.exp) = new UnaryExp(UnaryOp::PLUS, make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 2013 "parser.tab.c"
    break;

  case 80: /* UnaryExp: MINUS UnaryExp  */
#line 556 "parser.y"
                                  {
        (yyval.exp) = new UnaryExp(UnaryOp::MINUS, make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 2021 "parser.tab.c"
    break;

  case 81: /* UnaryExp: NOT UnaryExp  */
#line 559 "parser.y"
                              {
        (yyval.exp) = new UnaryExp(UnaryOp::NOT, make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 2029 "parser.tab.c"
    break;

  case 82: /* FunctionCall: IDENT LPAREN RPAREN  */
#line 566 "parser.y"
                        {
        std::vector<std::unique_ptr<Exp>> args;
        (yyval.exp) = new FunctionCall(std::string((yyvsp[-2].str_val)), std::move(args), {line_number});
        free((yyvsp[-2].str_val));
    }
#line 2039 "parser.tab.c"
    break;

  case 83: /* FunctionCall: IDENT LPAREN FuncRParams RPAREN  */
#line 571 "parser.y"
                                      {
        (yyval.exp) = new FunctionCall(std::string((yyvsp[-3].str_val)), std::move(*(yyvsp[-1].exp_list)), {line_number});
        free((yyvsp[-3].str_val));
        delete (yyvsp[-1].exp_list);
    }
#line 2049 "parser.tab.c"
    break;

  case 84: /* FuncRParams: Exp  */
#line 580 "parser.y"
        {
        (yyval.exp_list) = new std::vector<std::unique_ptr<Exp>>();
        (yyval.exp_list)->push_back(make_unique_from_ptr((yyvsp[0].exp)));
    }
#line 2058 "parser.tab.c"
    break;

  case 85: /* FuncRParams: FuncRParams COMMA Exp  */
#line 584 "parser.y"
                            {
        (yyvsp[-2].exp_list)->push_back(make_unique_from_ptr((yyvsp[0].exp)));
        (yyval.exp_list) = (yyvsp[-2].exp_list);
    }
#line 2067 "parser.tab.c"
    break;

  case 86: /* PrimaryExp: LPAREN Exp RPAREN  */
#line 592 "parser.y"
                      { (yyval.exp) = (yyvsp[-1].exp); }
#line 2073 "parser.tab.c"
    break;

  case 87: /* PrimaryExp: LVal  */
#line 593 "parser.y"
           { (yyval.exp) = (yyvsp[0].lval); }
#line 2079 "parser.tab.c"
    break;

  case 88: /* PrimaryExp: Number  */
#line 594 "parser.y"
             { (yyval.exp) = (yyvsp[0].exp); }
#line 2085 "parser.tab.c"
    break;

  case 89: /* LVal: IDENT  */
#line 599 "parser.y"
          {
        std::vector<std::unique_ptr<Exp>> indices;
        (yyval.lval) = new LVal(std::string((yyvsp[0].str_val)), std::move(indices), {line_number});
        free((yyvsp[0].str_val));
    }
#line 2095 "parser.tab.c"
    break;

  case 90: /* LVal: IDENT ArrayIndices  */
#line 604 "parser.y"
                         {
        (yyval.lval) = new LVal(std::string((yyvsp[-1].str_val)), std::move(*(yyvsp[0].exp_list)), {line_number});
        free((yyvsp[-1].str_val));
        delete (yyvsp[0].exp_list);
    }
#line 2105 "parser.tab.c"
    break;

  case 91: /* ArrayIndices: LBRACKET Exp RBRACKET  */
#line 612 "parser.y"
                          {
        (yyval.exp_list) = new std::vector<std::unique_ptr<Exp>>();
        (yyval.exp_list)->push_back(make_unique_from_ptr((yyvsp[-1].exp)));
    }
#line 2114 "parser.tab.c"
    break;

  case 92: /* ArrayIndices: ArrayIndices LBRACKET Exp RBRACKET  */
#line 616 "parser.y"
                                         {
        (yyvsp[-3].exp_list)->push_back(make_unique_from_ptr((yyvsp[-1].exp)));
        (yyval.exp_list) = (yyvsp[-3].exp_list);
    }
#line 2123 "parser.tab.c"
    break;

  case 93: /* Number: INT_CONST  */
#line 624 "parser.y"
              {
        (yyval.exp) = new Number((yyvsp[0].int_val), {line_number});
    }
#line 2131 "parser.tab.c"
    break;

  case 94: /* Number: FLOAT_CONST  */
#line 627 "parser.y"
                  {
        (yyval.exp) = new Number((yyvsp[0].float_val), {line_number});
    }
#line 2139 "parser.tab.c"
    break;

  case 95: /* ConstExp: AddExp  */
#line 634 "parser.y"
           { (yyval.exp) = (yyvsp[0].exp); }
#line 2145 "parser.tab.c"
    break;

  case 96: /* InitVal: Exp  */
#line 639 "parser.y"
        {
        (yyval.init_val) = new InitVal(make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 2153 "parser.tab.c"
    break;

  case 97: /* InitVal: LBRACE RBRACE  */
#line 642 "parser.y"
                    {
        std::vector<std::unique_ptr<InitVal>> inits;
        (yyval.init_val) = new InitVal(std::move(inits), {line_number});
    }
#line 2162 "parser.tab.c"
    break;

  case 98: /* InitVal: LBRACE InitValList RBRACE  */
#line 646 "parser.y"
                                {
        std::vector<std::unique_ptr<InitVal>> inits;
        for (auto& init : *(yyvsp[-1].init_list)) {
            inits.push_back(std::move(init));
        }
        delete (yyvsp[-1].init_list);
        (yyval.init_val) = new InitVal(std::move(inits), {line_number});
    }
#line 2175 "parser.tab.c"
    break;

  case 99: /* InitValList: InitVal  */
#line 657 "parser.y"
            {
        (yyval.init_list) = new std::vector<std::unique_ptr<InitVal>>();
        (yyval.init_list)->push_back(make_unique_from_ptr((yyvsp[0].init_val)));
    }
#line 2184 "parser.tab.c"
    break;

  case 100: /* InitValList: InitValList COMMA InitVal  */
#line 661 "parser.y"
                                {
        (yyvsp[-2].init_list)->push_back(make_unique_from_ptr((yyvsp[0].init_val)));
        (yyval.init_list) = (yyvsp[-2].init_list);
    }
#line 2193 "parser.tab.c"
    break;

  case 101: /* ConstInitVal: ConstExp  */
#line 669 "parser.y"
             {
        (yyval.const_init_val) = new ConstInitVal(make_unique_from_ptr((yyvsp[0].exp)), {line_number});
    }
#line 2201 "parser.tab.c"
    break;

  case 102: /* ConstInitVal: LBRACE RBRACE  */
#line 672 "parser.y"
                    {
        std::vector<std::unique_ptr<ConstInitVal>> inits;
        (yyval.const_init_val) = new ConstInitVal(std::move(inits), {line_number});
    }
#line 2210 "parser.tab.c"
    break;

  case 103: /* ConstInitVal: LBRACE ConstInitValList RBRACE  */
#line 676 "parser.y"
                                     {
        std::vector<std::unique_ptr<ConstInitVal>> inits;
        for (auto& init : *(yyvsp[-1].const_init_list)) {
            inits.push_back(std::move(init));
        }
        delete (yyvsp[-1].const_init_list);
        (yyval.const_init_val) = new ConstInitVal(std::move(inits), {line_number});
    }
#line 2223 "parser.tab.c"
    break;

  case 104: /* ConstInitValList: ConstInitVal  */
#line 687 "parser.y"
                 {
        (yyval.const_init_list) = new std::vector<std::unique_ptr<ConstInitVal>>();
        (yyval.const_init_list)->push_back(make_unique_from_ptr((yyvsp[0].const_init_val)));
    }
#line 2232 "parser.tab.c"
    break;

  case 105: /* ConstInitValList: ConstInitValList COMMA ConstInitVal  */
#line 691 "parser.y"
                                          {
        (yyvsp[-2].const_init_list)->push_back(make_unique_from_ptr((yyvsp[0].const_init_val)));
        (yyval.const_init_list) = (yyvsp[-2].const_init_list);
    }
#line 2241 "parser.tab.c"
    break;

  case 106: /* BType: INT  */
#line 699 "parser.y"
        { (yyval.base_type) = BaseType::INT; }
#line 2247 "parser.tab.c"
    break;

  case 107: /* BType: FLOAT  */
#line 700 "parser.y"
            { (yyval.base_type) = BaseType::FLOAT; }
#line 2253 "parser.tab.c"
    break;


#line 2257 "parser.tab.c"

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

#line 703 "parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Parse error at line %d: %s\n", line_number, s);
}

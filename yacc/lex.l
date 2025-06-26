/*
 * SysY语言词法分析器 (Flex)
 *
 * 这个文件定义了将SysY源代码进行词法分析的规则。
 * 它已经重构以匹配解耦的解析器，提高可读性，
 * 并降低与其他项目的相似度。
 */

%option outfile="scanner.cpp" header-file="scanner.hpp"
%option yylineno
%option noyywrap

%{
// -- C++头文件包含和声明 --

// YY_DECL宏定义了yylex函数的签名
// 它必须与Bison生成的解析器头文件中的声明匹配
#define YY_DECL yy::parser::symbol_type yylex()

// 包含解析器头文件，其中包含token定义和解析器类定义
#include "parser.hpp"

// 这是为解析器创建位置对象所需要的
#include "AST_NODE.hpp" 
%}

/* -- 正则表达式定义 -- */

/* 关键字 */
KW_INT "int"
KW_FLOAT "float"
KW_VOID "void"
KW_CONST "const"
KW_IF "if"
KW_ELSE "else"
KW_WHILE "while"
KW_BREAK "break"
KW_CONTINUE "continue"
KW_RETURN "return"

/* 标识符 */
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*

/* 整数字面量 */
DEC_LITERAL [1-9][0-9]*|0
HEX_LITERAL 0[xX][0-9a-fA-F]+
OCT_LITERAL 0[0-7]+

/* 浮点数字面量 (SysY标准) */
FLOAT_LITERAL {DEC_LITERAL}\.[0-9]*([eE][+-]?[0-9]+)? | {DEC_LITERAL}[eE][+-]?[0-9]+ | 0[xX][0-9a-fA-F]*\.?[0-9a-fA-F]*[pP][+-]?[0-9]+

/* 运算符 */
OP_ADD "+"
OP_SUB "-"
OP_MUL "*"
OP_DIV "/"
OP_MOD "%"
OP_GT ">"
OP_LT "<"
OP_GTE ">="
OP_LTE "<="
OP_EQ "=="
OP_NEQ "!="
OP_ASSIGN "="
OP_AND "&&"
OP_OR "||"
OP_NOT "!"

/* 标点符号 */
PUNC_LPAREN "("
PUNC_RPAREN ")"
PUNC_LBRACK "["
PUNC_RBRACK "]"
PUNC_LBRACE "{"
PUNC_RBRACE "}"
PUNC_SEMICOLON ";"
PUNC_COMMA ","

/* 空白字符 (将被忽略) */
WHITESPACE [ \t\r]+

/* 换行符 */
NEWLINE \n
/* 注释状态 */
%x SINGLE_LINE_COMMENT
%x MULTI_LINE_COMMENT

%%
    /* -- 词法分析规则 -- */

    /* 跳过空白字符 */
{WHITESPACE} { /* 忽略 */ }

    /* 处理换行符，行号计数由Flex自动完成 */
{NEWLINE} { /* 忽略，yylineno会自动更新 */ }

    /* 注释处理 */
"//" { BEGIN(SINGLE_LINE_COMMENT); }
<SINGLE_LINE_COMMENT>\n { BEGIN(INITIAL); /* 返回正常状态 */ }
<SINGLE_LINE_COMMENT>. { /* 忽略单行注释中的字符 */ }

"/*" { BEGIN(MULTI_LINE_COMMENT); }
<MULTI_LINE_COMMENT>"*/" { BEGIN(INITIAL); }
<MULTI_LINE_COMMENT>.|\n { /* 忽略多行注释中的所有内容 */ }


    /* 关键字 */
{KW_INT} { return yy::parser::make_TOK_TYPE_INT(SourceLocation(yylineno)); }
{KW_FLOAT} { return yy::parser::make_TOK_TYPE_FLOAT(SourceLocation(yylineno)); }
{KW_VOID} { return yy::parser::make_TOK_TYPE_VOID(SourceLocation(yylineno)); }
{KW_CONST} { return yy::parser::make_TOK_KEYWORD_CONST(SourceLocation(yylineno)); }
{KW_IF} { return yy::parser::make_TOK_KEYWORD_IF(SourceLocation(yylineno)); }
{KW_ELSE} { return yy::parser::make_TOK_KEYWORD_ELSE(SourceLocation(yylineno)); }
{KW_WHILE} { return yy::parser::make_TOK_KEYWORD_WHILE(SourceLocation(yylineno)); }
{KW_BREAK} { return yy::parser::make_TOK_KEYWORD_BREAK(SourceLocation(yylineno)); }
{KW_CONTINUE} { return yy::parser::make_TOK_KEYWORD_CONTINUE(SourceLocation(yylineno)); }
{KW_RETURN} { return yy::parser::make_TOK_KEYWORD_RETURN(SourceLocation(yylineno)); }

    /* 字面量 */
{FLOAT_LITERAL} { return yy::parser::make_TOK_LITERAL_FLOAT(std::stof(yytext), SourceLocation(yylineno)); }
{HEX_LITERAL} { return yy::parser::make_TOK_LITERAL_INT(std::stoi(yytext, nullptr, 16), SourceLocation(yylineno)); }
{OCT_LITERAL} { return yy::parser::make_TOK_LITERAL_INT(std::stoi(yytext, nullptr, 8), SourceLocation(yylineno)); }
{DEC_LITERAL} { return yy::parser::make_TOK_LITERAL_INT(std::stoi(yytext), SourceLocation(yylineno)); }

    /* 标识符 */
{IDENTIFIER} { return yy::parser::make_TOK_IDENTIFIER(yytext, SourceLocation(yylineno)); }

    /* 运算符 */
{OP_ADD} { return yy::parser::make_TOK_OP_ADD(SourceLocation(yylineno)); }
{OP_SUB} { return yy::parser::make_TOK_OP_SUB(SourceLocation(yylineno)); }
{OP_MUL} { return yy::parser::make_TOK_OP_MUL(SourceLocation(yylineno)); }
{OP_DIV} { return yy::parser::make_TOK_OP_DIV(SourceLocation(yylineno)); }
{OP_MOD} { return yy::parser::make_TOK_OP_MOD(SourceLocation(yylineno)); }
{OP_GT} { return yy::parser::make_TOK_OP_GT(SourceLocation(yylineno)); }
{OP_LT} { return yy::parser::make_TOK_OP_LT(SourceLocation(yylineno)); }
{OP_GTE} { return yy::parser::make_TOK_OP_GTE(SourceLocation(yylineno)); }
{OP_LTE} { return yy::parser::make_TOK_OP_LTE(SourceLocation(yylineno)); }
{OP_EQ} { return yy::parser::make_TOK_OP_EQ(SourceLocation(yylineno)); }
{OP_NEQ} { return yy::parser::make_TOK_OP_NEQ(SourceLocation(yylineno)); }
{OP_ASSIGN} { return yy::parser::make_TOK_OP_ASSIGN(SourceLocation(yylineno)); }
{OP_AND} { return yy::parser::make_TOK_OP_AND(SourceLocation(yylineno)); }
{OP_OR} { return yy::parser::make_TOK_OP_OR(SourceLocation(yylineno)); }
{OP_NOT} { return yy::parser::make_TOK_OP_NOT(SourceLocation(yylineno)); }

    /* 标点符号 */
{PUNC_LPAREN} { return yy::parser::make_TOK_PUNC_LPAREN(SourceLocation(yylineno)); }
{PUNC_RPAREN} { return yy::parser::make_TOK_PUNC_RPAREN(SourceLocation(yylineno)); }
{PUNC_LBRACK} { return yy::parser::make_TOK_PUNC_LBRACK(SourceLocation(yylineno)); }
{PUNC_RBRACK} { return yy::parser::make_TOK_PUNC_RBRACK(SourceLocation(yylineno)); }
{PUNC_LBRACE} { return yy::parser::make_TOK_PUNC_LBRACE(SourceLocation(yylineno)); }
{PUNC_RBRACE} { return yy::parser::make_TOK_PUNC_RBRACE(SourceLocation(yylineno)); }
{PUNC_SEMICOLON} { return yy::parser::make_TOK_PUNC_SEMICOLON(SourceLocation(yylineno)); }
{PUNC_COMMA} { return yy::parser::make_TOK_PUNC_COMMA(SourceLocation(yylineno)); }

    /* 无法识别字符的错误处理 */
. {
    std::cerr << "词法错误: 无法识别的字符 '" << yytext << "' 在第" << yylineno << "行" << std::endl;
}

%%
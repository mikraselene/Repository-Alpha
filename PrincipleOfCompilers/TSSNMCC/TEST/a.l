%{
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;


#define RT(xx)  pos += yyleng; return xx;

#define TOKENS                                      \
    TOKEN(0, Token::ERR, ERROR, "error")            \
    TOKEN(1, Token::KEYWORD, FLOAT, "float")        \
    TOKEN(2, Token::KEYWORD, DOUBLE, "double")      \
    TOKEN(3, Token::KEYWORD, CHAR, "char")          \
    TOKEN(4, Token::KEYWORD, SHORT, "short")        \
    TOKEN(5, Token::KEYWORD, INT, "int")            \
    TOKEN(6, Token::KEYWORD, UNSIGNED, "unsigned")  \
    TOKEN(7, Token::UNKNOWN, POINTER, "pointer")    \
    TOKEN(8, Token::KEYWORD, VOID, "void")          \
    TOKEN(9, Token::KEYWORD, STRUCT, "struct")      \
    TOKEN(10, Token::KEYWORD, UNION, "union")       \
    TOKEN(11, Token::UNKNOWN, FUNCTION, "function") \
    TOKEN(12, Token::UNKNOWN, ARRAY, "array")       \
    TOKEN(13, Token::KEYWORD, ENUM, "enum")         \
    TOKEN(14, Token::KEYWORD, LONG, "long")         \
    TOKEN(15, Token::KEYWORD, CONST, "const")       \
    TOKEN(16, Token::KEYWORD, VOLATILE, "volatile") \
    TOKEN(32, Token::IDENTIFIER, ID, "id")          \
    TOKEN(33, Token::OPERATOR, EXCL, "!")           \
    TOKEN(34, Token::NUMBER, FLTCON, "float con")   \
    TOKEN(35, Token::NUMBER, INTCON, "int con")     \
    TOKEN(36, Token::TEXT, STRCON, "string con")    \
    TOKEN(37, Token::OPERATOR, MOD, "%")            \
    TOKEN(38, Token::OPERATOR, AND, "&")            \
    TOKEN(39, Token::OPERATOR, INCR, "++")          \
    TOKEN(40, Token::SEPARATOR, LPAR, "(")          \
    TOKEN(41, Token::SEPARATOR, RPAR, ")")          \
    TOKEN(42, Token::OPERATOR, ASTERISK, "*")       \
    TOKEN(43, Token::OPERATOR, PLUS, "+")           \
    TOKEN(44, Token::OPERATOR, COMMA, ",")          \
    TOKEN(45, Token::OPERATOR, MINUS, "-")          \
    TOKEN(46, Token::OPERATOR, DOT, ".")            \
    TOKEN(47, Token::OPERATOR, SLASH, "/")          \
    TOKEN(48, Token::OPERATOR, DECR, "--")          \
    TOKEN(49, Token::OPERATOR, DEREF, "->")         \
    TOKEN(50, Token::OPERATOR, ANDAND, "&&")        \
    TOKEN(51, Token::OPERATOR, OROR, "||")          \
    TOKEN(52, Token::OPERATOR, LEQL, "<=")          \
    TOKEN(53, Token::OPERATOR, EQL, "==")           \
    TOKEN(54, Token::OPERATOR, NEQ, "!=")           \
    TOKEN(55, Token::OPERATOR, GEQL, ">=")          \
    TOKEN(56, Token::OPERATOR, RSHIFT, ">>")        \
    TOKEN(57, Token::OPERATOR, LSHIFT, "<<")        \
    TOKEN(58, Token::OPERATOR, COLON, ":")          \
    TOKEN(59, Token::SEPARATOR, SEMICOL, ";")       \
    TOKEN(60, Token::OPERATOR, LESS, "<")           \
    TOKEN(61, Token::OPERATOR, ASSIGN, "=")         \
    TOKEN(62, Token::OPERATOR, GREATER, ">")        \
    TOKEN(63, Token::OPERATOR, QUESTION, "?")       \
    TOKEN(65, Token::KEYWORD, SIZEOF, "sizeof")     \
    TOKEN(67, Token::KEYWORD, AUTO, "auto")         \
    TOKEN(68, Token::KEYWORD, BREAK, "break")       \
    TOKEN(69, Token::KEYWORD, CASE, "case")         \
    TOKEN(70, Token::KEYWORD, CONTINUE, "continue") \
    TOKEN(71, Token::KEYWORD, DEFAULT, "default")   \
    TOKEN(72, Token::KEYWORD, DO, "do")             \
    TOKEN(73, Token::KEYWORD, ELSE, "else")         \
    TOKEN(74, Token::KEYWORD, EXTERN, "extern")     \
    TOKEN(75, Token::KEYWORD, FOR, "for")           \
    TOKEN(76, Token::KEYWORD, GOTO, "goto")         \
    TOKEN(77, Token::KEYWORD, IF, "if")             \
    TOKEN(78, Token::KEYWORD, REGISTER, "register") \
    TOKEN(79, Token::KEYWORD, RETURN, "return")     \
    TOKEN(80, Token::KEYWORD, SIGNED, "signed")     \
    TOKEN(81, Token::KEYWORD, STATIC, "static")     \
    TOKEN(82, Token::KEYWORD, SWITCH, "switch")     \
    TOKEN(83, Token::KEYWORD, TYPEDEF, "typedef")   \
    TOKEN(84, Token::KEYWORD, WHILE, "while")       \
    TOKEN(91, Token::SEPARATOR, LBRKT, "[")         \
    TOKEN(93, Token::SEPARATOR, RBRKT, "]")         \
    TOKEN(94, Token::OPERATOR, CARET, "^")          \
    TOKEN(123, Token::SEPARATOR, LBRACE, "{")       \
    TOKEN(124, Token::OPERATOR, BAR, "|")           \
    TOKEN(125, Token::SEPARATOR, RBRACE, "}")       \
    TOKEN(126, Token::OPERATOR, TLIDE, "~")         \
    TOKEN(127, Token::END, EOI, "$")


#define TOKEN(num, type, name, str) name = num,
enum
{
    TOKENS
};



void RRR(int token)
{

}

int pos = 1;


%}


%option noyywrap

%x comment
id [a-zA-Z][a-zA-Z1-9_]*

%%

[ \t\r]+        { continue; }

\n              { pos = 1; yylineno++; continue; }

0|[1-9][0-9]+   { RT(INTCON); }
0x[0-9a-fA-F]+  { RT(INTCON); }
0[0-7]+         { RT(INTCON); }

auto            { RT(AUTO); }
break           { RT(BREAK); }
case            { RT(CASE); }
char            { RT(CHAR); }
const           { RT(CONST); }
continue        { RT(CONTINUE); }
default         { RT(DEFAULT); }
double          { RT(DOUBLE); }
do              { RT(DO); }
else            { RT(ELSE); }
enum            { RT(ENUM); }
extern          { RT(EXTERN); }
float           { RT(FLOAT); }
for             { RT(FOR); }
goto            { RT(GOTO); }
if              { RT(IF); }
int             { RT(INT); }
long            { RT(LONG); }
register        { RT(REGISTER); }
return          { RT(RETURN); }
short           { RT(SHORT); }
signed          { RT(SIGNED); }
sizeof          { RT(SIZEOF); }
static          { RT(STATIC); }
struct          { RT(STRUCT); }
switch          { RT(SWITCH); }
typedef         { RT(TYPEDEF); }
union           { RT(UNION); }
unsigned        { RT(UNSIGNED); }
void            { RT(VOID); }
volatile        { RT(VOLATILE); }
while           { RT(WHILE); }

\".*\"          { RT(STRCON); }

\'\\?.\'        { RT(INTCON); }

\/\/[^\n]*      { continue; }

\/\*            { BEGIN comment; } 
<comment>.      { continue; }
<comment>\n     { yylineno++; continue; }
<comment>\*\/   { BEGIN INITIAL; }

{id}            { RT(ID); }

"+"             { RT(PLUS); }
"++"            { RT(INCR); }
"->"            { RT(DEREF); }
"-"             { RT(MINUS); }
"--"            { RT(DECR); }
"<"             { RT(LESS); }
"<="            { RT(LEQL); }
"<<"            { RT(LSHIFT); }
">"             { RT(GREATER); }
">="            { RT(GEQL); }
">>"            { RT(RSHIFT); }
"="             { RT(ASSIGN); }
"=="            { RT(EQL); }
"|"             { RT(BAR); }
"||"            { RT(OROR); }
"&"             { RT(AND); }
"&&"            { RT(ANDAND); }
"!"             { RT(EXCL); }
"!="            { RT(NEQ); }
"."             { RT(DOT); }
"*"             { RT(ASTERISK); }
","             { RT(COMMA); }
"/"             { RT(SLASH); }
":"             { RT(COLON); }
";"             { RT(SEMICOL); }
"?"             { RT(QUESTION); }
"^"             { RT(CARET); }
"~"             { RT(TLIDE); }
"%"             { RT(MOD); }

"("             { RT(LPAR); }
")"             { RT(RPAR); }
"["             { RT(LBRKT); }
"]"             { RT(RBRKT); }
"{"             { RT(LBRACE); }
"}"             { RT(RBRACE); }

.               { RT(ERROR); }


%%

int main()
{
    uint tok = 0;
   while(1)
 {   tok = yylex();
    cout<<tok<<"\n";}
}
#ifndef C_H
#define C_H

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include <assert.h>

#define FLAG_DISABLE_COLORS false
#define FLAG_DCOLOR false

#pragma region // tokens

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

#pragma endregion

#define TOKEN(num, type, name, str) name = num,
enum
{
    TOKENS
};

#pragma region // colors

#if FLAG_DISABLE_COLORS
#define RESET
#define BOLD
#define FAINT
#define ITALIC
#define UNDERLINE
#define BLINK
#define BLINKFAST
#define NEGATIVE
#define CONCEAL
#define STRIKE
#define BLACK
#define RED
#define GREEN
#define YELLOW
#define BLUE
#define MAGENTA
#define CYAN
#define WHITE

#else
#define RESET "\e[0m"
#define BOLD "\e[1m"
#define FAINT "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define BLINKFAST "\e[6m"
#define NEGATIVE "\e[7m"
#define CONCEAL "\e[8m"
#define STRIKE "\e[9m"

#if FLAG_DCOLOR
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

#else
#define BLACK "\e[90m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define YELLOW "\e[93m"
#define BLUE "\e[94m"
#define MAGENTA "\e[95m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"

#endif
#endif

#define PRINT(xx) printf(xx RESET)

#pragma endregion

#define FATAL true

#define uint unsigned int
#define uchar unsigned char
#define ull unsigned long long
#define ll long long
#define ld long double

#define MALLOC(type, size) (type *)malloc(sizeof(type *) * size)

uchar *pos;
uint ln_no = 1;
uint col_no = 1;
uint error_cnt = 0;
uint warning_cnt = 0;

void Error(const char *err_message)
{
    error_cnt++;
    printf("%d:%d: ", ln_no, col_no);
    PRINT(RED UNDERLINE "error: ");
    printf("%s\n", err_message);
    uchar *ecp = pos;
    uint len = 1;
    // XXX: cp++;...cp--; here could be optimized?
    while (*(pos + 1) != '\n')
    {
        pos++;
    }
    while (*(pos - 1) != '\n')
    {
        pos--;
        len++;
    }
    ecp = MALLOC(uchar, len);
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        *(ecp + i) = *(pos + i);
    }
    printf("%s\n", ecp);
    for (i = 0; i < col_no; i++)
    {
        printf(" ");
    }
    PRINT(GREEN "^\n");
    pos += len;
}

void Error(const char *err_message, bool fatal)
{
    Error(err_message);
    if (fatal == true)
    {
        PRINT(MAGENTA ITALIC "*Exeunt Instructions and Data*\n");
        exit(EXIT_FAILURE);
    }
}

void Warning(const char *war_message)
{
    warning_cnt++;
    printf("%d:%d: ", ln_no + 1, col_no + 1);
    PRINT(YELLOW UNDERLINE "warning: ");
    printf("%s\n", war_message);
    uchar *ecp = pos;
    uint len = 1;
    while (*(pos + 1) != '\n')
    {
        pos++;
    }
    while (*(pos - 1) != '\n')
    {
        pos--;
        len++;
    }
    ecp = MALLOC(uchar, len);
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        *(ecp + i) = *(pos + i);
    }
    printf("%s\n", ecp);
    for (i = 0; i < col_no; i++)
    {
        printf(" ");
    }
    PRINT(GREEN "^\n");
    pos += len;
}

#endif

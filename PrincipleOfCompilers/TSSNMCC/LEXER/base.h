#ifndef _BASE_H_
#define _BASE_H_

#pragma region // BASE

#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#pragma region // define: tokens

enum
{
    T_ERROR = 0,
    T_IDENTIFIER,
    T_KEYWORD,
    T_CONSTANT,
    T_STRLITERAL,
    T_OPERATOR,
    T_SEPARATOR,
    T_UNKNOWN,
    T_EOI,
};

#define TOKENS                                 \
    TOKEN(0, T_ERROR, ERROR, "error")          \
    TOKEN(1, T_KEYWORD, FLOAT, "float")        \
    TOKEN(2, T_KEYWORD, DOUBLE, "double")      \
    TOKEN(3, T_KEYWORD, CHAR, "char")          \
    TOKEN(4, T_KEYWORD, SHORT, "short")        \
    TOKEN(5, T_KEYWORD, INT, "int")            \
    TOKEN(6, T_KEYWORD, UNSIGNED, "unsigned")  \
    TOKEN(7, T_UNKNOWN, POINTER, "pointer")    \
    TOKEN(8, T_KEYWORD, VOID, "void")          \
    TOKEN(9, T_KEYWORD, STRUCT, "struct")      \
    TOKEN(10, T_KEYWORD, UNION, "union")       \
    TOKEN(11, T_UNKNOWN, FUNCTION, "function") \
    TOKEN(12, T_UNKNOWN, ARRAY, "array")       \
    TOKEN(13, T_KEYWORD, ENUM, "enum")         \
    TOKEN(14, T_KEYWORD, LONG, "long")         \
    TOKEN(15, T_KEYWORD, CONST, "const")       \
    TOKEN(16, T_KEYWORD, VOLATILE, "volatile") \
    TOKEN(32, T_IDENTIFIER, ID, "id")          \
    TOKEN(33, T_OPERATOR, EXCL, "!")           \
    TOKEN(34, T_CONSTANT, FLTCON, "fltcon")    \
    TOKEN(35, T_CONSTANT, INTCON, "intcon")    \
    TOKEN(36, T_STRLITERAL, STRCON, "strcon")  \
    TOKEN(37, T_OPERATOR, MOD, "%")            \
    TOKEN(38, T_OPERATOR, AND, "&")            \
    TOKEN(39, T_OPERATOR, INCR, "++")          \
    TOKEN(40, T_SEPARATOR, LPAR, "(")          \
    TOKEN(41, T_SEPARATOR, RPAR, ")")          \
    TOKEN(42, T_OPERATOR, ASTERISK, "*")       \
    TOKEN(43, T_OPERATOR, PLUS, "+")           \
    TOKEN(44, T_OPERATOR, COMMA, ",")          \
    TOKEN(45, T_OPERATOR, MINUS, "-")          \
    TOKEN(46, T_OPERATOR, DOT, ".")            \
    TOKEN(47, T_OPERATOR, SLASH, "/")          \
    TOKEN(48, T_OPERATOR, DECR, "--")          \
    TOKEN(49, T_OPERATOR, DEREF, "->")         \
    TOKEN(50, T_OPERATOR, ANDAND, "&&")        \
    TOKEN(51, T_OPERATOR, OROR, "||")          \
    TOKEN(52, T_OPERATOR, LEQL, "<=")          \
    TOKEN(53, T_OPERATOR, EQL, "==")           \
    TOKEN(54, T_OPERATOR, NEQ, "!=")           \
    TOKEN(55, T_OPERATOR, GEQL, ">=")          \
    TOKEN(56, T_OPERATOR, RSHIFT, ">>")        \
    TOKEN(57, T_OPERATOR, LSHIFT, "<<")        \
    TOKEN(58, T_OPERATOR, COLON, ":")          \
    TOKEN(59, T_SEPARATOR, SEMICOL, ";")       \
    TOKEN(60, T_OPERATOR, LESS, "<")           \
    TOKEN(61, T_OPERATOR, ASSIGN, "=")         \
    TOKEN(62, T_OPERATOR, GREATER, ">")        \
    TOKEN(63, T_OPERATOR, QUESTION, "?")       \
    TOKEN(65, T_KEYWORD, SIZEOF, "sizeof")     \
    TOKEN(67, T_KEYWORD, AUTO, "auto")         \
    TOKEN(68, T_KEYWORD, BREAK, "break")       \
    TOKEN(69, T_KEYWORD, CASE, "case")         \
    TOKEN(70, T_KEYWORD, CONTINUE, "continue") \
    TOKEN(71, T_KEYWORD, DEFAULT, "default")   \
    TOKEN(72, T_KEYWORD, DO, "do")             \
    TOKEN(73, T_KEYWORD, ELSE, "else")         \
    TOKEN(74, T_KEYWORD, EXTERN, "extern")     \
    TOKEN(75, T_KEYWORD, FOR, "for")           \
    TOKEN(76, T_KEYWORD, GOTO, "goto")         \
    TOKEN(77, T_KEYWORD, IF, "if")             \
    TOKEN(78, T_KEYWORD, REGISTER, "register") \
    TOKEN(79, T_KEYWORD, RETURN, "return")     \
    TOKEN(80, T_KEYWORD, SIGNED, "signed")     \
    TOKEN(81, T_KEYWORD, STATIC, "static")     \
    TOKEN(82, T_KEYWORD, SWITCH, "switch")     \
    TOKEN(83, T_KEYWORD, TYPEDEF, "typedef")   \
    TOKEN(84, T_KEYWORD, WHILE, "while")       \
    TOKEN(91, T_SEPARATOR, LBRKT, "[")         \
    TOKEN(93, T_SEPARATOR, RBRKT, "]")         \
    TOKEN(94, T_OPERATOR, CARET, "^")          \
    TOKEN(123, T_SEPARATOR, LBRACE, "{")       \
    TOKEN(124, T_OPERATOR, BAR, "|")           \
    TOKEN(125, T_SEPARATOR, RBRACE, "}")       \
    TOKEN(126, T_OPERATOR, TLIDE, "~")         \
    TOKEN(127, T_EOI, EOI, "$")

#pragma endregion

#pragma region // define: colors

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

#pragma region // define: etc

#define FLAG_DISABLE_COLORS false
#define FLAG_DCOLOR false

#define FATAL true

#define uint unsigned int
#define uchar unsigned char
#define ull unsigned long long
#define ll long long
#define ld long double

#define MALLOC(type, size) (type *)malloc(sizeof(type *) * size)

#pragma endregion

uchar *buf;
uchar *pos;
uchar *first_pos;
uint ln_no = 1;
uint col_no = 1;

#pragma region // error and warning

uint error_cnt = 0;
uint warning_cnt = 0;

void Exit(bool exit_code)
{
    PRINT(MAGENTA ITALIC "*Exeunt Instructions and Data*\n");
    printf(FAINT "exit code: %d\n" RESET, exit_code);
    exit(exit_code);
}

void ErrorMessage(const char *err_message)
{
    PRINT(RED UNDERLINE "error: ");
    printf("%s", err_message);
}

void WarningMessage(const char *war_message, ...)
{
    PRINT(YELLOW UNDERLINE "warning: ");
    printf("%s", war_message);
}

void Error(const char *err_message)
{
    error_cnt++;
    printf("%d:%d: ", ln_no, col_no);
    ErrorMessage(err_message);
    uchar *anomaly = pos;
    uint len = 1;
    // XXX: pos++;...pos--; could this be optimized?
    while (*(pos + 1) != '\n')
    {
        pos++;
    }
    while (*(pos - 1) != '\n')
    {
        pos--;
        len++;
    }
    anomaly = MALLOC(uchar, len);
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        *(anomaly + i) = *(pos + i);
    }
    printf("%s\n", anomaly);
    for (i = 0; i < col_no; i++)
    {
        printf(" ");
    }
    PRINT(GREEN "^\n");
    pos += len;
}

void FatalError(const char *err_message)
{
    Error(err_message);
    Exit(EXIT_FAILURE);
}

void Warning(const char *war_message)
{
    warning_cnt++;
    printf("%d:%d: ", ln_no + 1, col_no + 1);
    WarningMessage(war_message);
    uchar *anomaly = pos;
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
    anomaly = MALLOC(uchar, len);
    unsigned int i;
    for (i = 0; i < len; i++)
    {
        *(anomaly + i) = *(pos + i);
    }
    printf("%s\n", anomaly);
    for (i = 0; i < col_no; i++)
    {
        printf(" ");
    }
    PRINT(GREEN "^\n");
    pos += len;
}

void Exeunt()
{
    if (error_cnt == 0 && warning_cnt == 0)
    {
        PRINT(GREEN "Let there be light!\n");
        printf("Build succeeded with 0 errors, 0 warnings.\n");
        Exit(EXIT_SUCCESS);
    }
    else if (error_cnt == 0 && warning_cnt != 0)
    {
        PRINT(YELLOW "A bad peace is even worse than war.\n");
        printf("Build succeeded with ");
        printf(error_cnt == 1 ? "%d error, " : "%d errors, ", error_cnt);
        printf(warning_cnt == 1 ? "%d warning.\n" : "%d warnings.\n", warning_cnt);
        Exit(EXIT_SUCCESS);
    }
    else
    {
        PRINT(RED "To err is human.\n");
        printf("Build failed with ");
        printf(error_cnt == 1 ? "%d error, " : "%d errors, ", error_cnt);
        printf(warning_cnt == 1 ? "%d warning.\n" : "%d warnings.\n", warning_cnt);
        Exit(EXIT_FAILURE);
    }
}

#pragma endregion

#pragma endregion

#endif

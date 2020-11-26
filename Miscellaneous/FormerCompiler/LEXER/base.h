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

#define TOKENS                                   \
    TOKEN(0, T_ERROR, ERROR, "error")            \
    TOKEN(1, T_KEYWORD, AND, "and")              \
    TOKEN(2, T_KEYWORD, ARRAY, "array")          \
    TOKEN(3, T_KEYWORD, BEGIN, "begin")          \
    TOKEN(4, T_KEYWORD, BOOL, "bool")            \
    TOKEN(5, T_KEYWORD, CALL, "call")            \
    TOKEN(6, T_KEYWORD, CASE, "case")            \
    TOKEN(7, T_KEYWORD, CHAR, "char")            \
    TOKEN(8, T_KEYWORD, CONSTANT, "constant")    \
    TOKEN(9, T_KEYWORD, DIM, "dim")              \
    TOKEN(10, T_KEYWORD, DO, "do")               \
    TOKEN(11, T_KEYWORD, ELSE, "else")           \
    TOKEN(12, T_KEYWORD, END, "end")             \
    TOKEN(13, T_CONSTANT, FALSE, "false")        \
    TOKEN(14, T_KEYWORD, FOR, "for")             \
    TOKEN(15, T_KEYWORD, IF, "if")               \
    TOKEN(16, T_KEYWORD, INPUT, "input")         \
    TOKEN(17, T_KEYWORD, INTEGER, "integer")     \
    TOKEN(18, T_KEYWORD, NOT, "not")             \
    TOKEN(19, T_KEYWORD, OF, "of")               \
    TOKEN(20, T_KEYWORD, OR, "or")               \
    TOKEN(21, T_KEYWORD, OUTPUT, "output")       \
    TOKEN(22, T_KEYWORD, PROCEDURE, "procedure") \
    TOKEN(23, T_KEYWORD, PROGRAM, "program")     \
    TOKEN(24, T_KEYWORD, READ, "read")           \
    TOKEN(25, T_KEYWORD, REAL, "real")           \
    TOKEN(26, T_KEYWORD, REPEAT, "repeat")       \
    TOKEN(27, T_KEYWORD, SET, "set")             \
    TOKEN(28, T_KEYWORD, STOP, "stop")           \
    TOKEN(29, T_KEYWORD, THEN, "then")           \
    TOKEN(30, T_KEYWORD, TO, "to")               \
    TOKEN(31, T_CONSTANT, TRUE, "true")          \
    TOKEN(32, T_KEYWORD, UNTIL, "until")         \
    TOKEN(33, T_KEYWORD, VAR, "var")             \
    TOKEN(34, T_KEYWORD, WHILE, "while")         \
    TOKEN(35, T_KEYWORD, WRITE, "write")         \
    TOKEN(36, T_IDENTIFIER, ID, "identifier")    \
    TOKEN(37, T_CONSTANT, INTCON, "intcon")      \
    TOKEN(38, T_STRLITERAL, CHARCON, "charcon")  \
    TOKEN(39, T_SEPARATOR, LPAR, "(")            \
    TOKEN(40, T_SEPARATOR, RPAR, ")")            \
    TOKEN(41, T_OPERATOR, ASTERISK, "*")         \
    TOKEN(42, T_OPERATOR, ASTSLASH, "*/")        \
    TOKEN(43, T_OPERATOR, PLUS, "+")             \
    TOKEN(44, T_OPERATOR, COMMA, ",")            \
    TOKEN(45, T_OPERATOR, MINUS, "-")            \
    TOKEN(46, T_OPERATOR, DOT, ".")              \
    TOKEN(47, T_OPERATOR, DOTDOT, "..")          \
    TOKEN(48, T_OPERATOR, SLASH, "/")            \
    TOKEN(49, T_OPERATOR, SLASHAST, "/*")        \
    TOKEN(50, T_OPERATOR, COLON, ":")            \
    TOKEN(51, T_OPERATOR, ASSIGN, ":=")          \
    TOKEN(52, T_OPERATOR, SEMICOL, ";")          \
    TOKEN(53, T_OPERATOR, LESS, "<")             \
    TOKEN(54, T_OPERATOR, LEQL, "<=")            \
    TOKEN(55, T_OPERATOR, NEQL, "<>")            \
    TOKEN(56, T_OPERATOR, EQUAL, "=")            \
    TOKEN(57, T_OPERATOR, GREATER, ">")          \
    TOKEN(58, T_OPERATOR, GEQL, ">=")            \
    TOKEN(59, T_SEPARATOR, LBRKT, "[")           \
    TOKEN(60, T_SEPARATOR, RBRKT, "]")           \
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

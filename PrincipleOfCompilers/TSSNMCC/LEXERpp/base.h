#ifndef BASE_H
#define BASE_H

#pragma region // BASE

#include <limits.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <vector>
using std::vector;

#define FLAG_DISABLE_COLORS 0
#define FLAG_DCOLOR 0
#define FATAL 1
#define DO_NOT_PRINT 0

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

/// TOKEN(num, type, name, prec, str)
#define TOKENS                                      \
    TOKEN(0, T_ERROR, ERROR, 0, "error")            \
    TOKEN(1, T_KEYWORD, FLOAT, 0, "float")          \
    TOKEN(2, T_KEYWORD, DOUBLE, 0, "double")        \
    TOKEN(3, T_KEYWORD, CHAR, 0, "char")            \
    TOKEN(4, T_KEYWORD, SHORT, 0, "short")          \
    TOKEN(5, T_KEYWORD, INT, 0, "int")              \
    TOKEN(6, T_KEYWORD, UNSIGNED, 0, "unsigned")    \
    TOKEN(7, T_UNKNOWN, POINTER, 0, "pointer")      \
    TOKEN(8, T_KEYWORD, VOID, 0, "void")            \
    TOKEN(9, T_KEYWORD, STRUCT, 0, "struct")        \
    TOKEN(10, T_KEYWORD, UNION, 0, "union")         \
    TOKEN(11, T_UNKNOWN, FUNCTION, 0, "function")   \
    TOKEN(12, T_UNKNOWN, ARRAY, 0, "array")         \
    TOKEN(13, T_KEYWORD, ENUM, 0, "enum")           \
    TOKEN(14, T_KEYWORD, LONG, 0, "long")           \
    TOKEN(15, T_KEYWORD, CONST, 0, "const")         \
    TOKEN(16, T_KEYWORD, VOLATILE, 0, "volatile")   \
    TOKEN(32, T_IDENTIFIER, ID, 0, "id")            \
    TOKEN(33, T_OPERATOR, EXCL, 0, "!")             \
    TOKEN(34, T_CONSTANT, FLTCON, 0, "fltcon")      \
    TOKEN(35, T_CONSTANT, INTCON, 0, "intcon")      \
    TOKEN(36, T_STRLITERAL, STRCON, 0, "strcon")    \
    TOKEN(37, T_OPERATOR, MOD, 13, "%")             \
    TOKEN(38, T_OPERATOR, AND, 8, "&")              \
    TOKEN(39, T_OPERATOR, INCR, 14, "++")           \
    TOKEN(40, T_SEPARATOR, LPAR, 0, "(")            \
    TOKEN(41, T_SEPARATOR, RPAR, 0, ")")            \
    TOKEN(42, T_OPERATOR, ASTERISK, 13, "*")        \
    TOKEN(43, T_OPERATOR, PLUS, 12, "+")            \
    TOKEN(44, T_OPERATOR, COMMA, 1, ",")            \
    TOKEN(45, T_OPERATOR, MINUS, 12, "-")           \
    TOKEN(46, T_OPERATOR, DOT, 0, ".")              \
    TOKEN(47, T_OPERATOR, SLASH, 13, "/")           \
    TOKEN(48, T_OPERATOR, DECR, 14, "--")           \
    TOKEN(49, T_OPERATOR, DEREF, 0, "->")           \
    TOKEN(50, T_OPERATOR, ANDAND, 5, "&&")          \
    TOKEN(51, T_OPERATOR, OROR, 4, "||")            \
    TOKEN(52, T_OPERATOR, LEQL, 10, "<=")           \
    TOKEN(53, T_OPERATOR, EQL, 9, "==")             \
    TOKEN(54, T_OPERATOR, NEQ, 9, "!=")             \
    TOKEN(55, T_OPERATOR, GEQL, 10, ">=")           \
    TOKEN(56, T_OPERATOR, RSHIFT, 11, ">>")         \
    TOKEN(57, T_OPERATOR, LSHIFT, 11, "<<")         \
    TOKEN(58, T_OPERATOR, COLON, 13, ":") /*TODO:*/ \
    TOKEN(59, T_SEPARATOR, SEMICOL, 0, ";")         \
    TOKEN(60, T_OPERATOR, LESS, 10, "<")            \
    TOKEN(61, T_OPERATOR, ASSIGN, 2, "=")           \
    TOKEN(62, T_OPERATOR, GREATER, 10, ">")         \
    TOKEN(63, T_OPERATOR, QUESTION, 13, "?")        \
    TOKEN(65, T_KEYWORD, SIZEOF, 14, "sizeof")      \
    TOKEN(67, T_KEYWORD, AUTO, 0, "auto")           \
    TOKEN(68, T_KEYWORD, BREAK, 0, "break")         \
    TOKEN(69, T_KEYWORD, CASE, 0, "case")           \
    TOKEN(70, T_KEYWORD, CONTINUE, 0, "continue")   \
    TOKEN(71, T_KEYWORD, DEFAULT, 0, "default")     \
    TOKEN(72, T_KEYWORD, DO, 0, "do")               \
    TOKEN(73, T_KEYWORD, ELSE, 0, "else")           \
    TOKEN(74, T_KEYWORD, EXTERN, 0, "extern")       \
    TOKEN(75, T_KEYWORD, FOR, 0, "for")             \
    TOKEN(76, T_KEYWORD, GOTO, 0, "goto")           \
    TOKEN(77, T_KEYWORD, IF, 0, "if")               \
    TOKEN(78, T_KEYWORD, REGISTER, 0, "register")   \
    TOKEN(79, T_KEYWORD, RETURN, 0, "return")       \
    TOKEN(80, T_KEYWORD, SIGNED, 0, "signed")       \
    TOKEN(81, T_KEYWORD, STATIC, 0, "static")       \
    TOKEN(82, T_KEYWORD, SWITCH, 0, "switch")       \
    TOKEN(83, T_KEYWORD, TYPEDEF, 0, "typedef")     \
    TOKEN(84, T_KEYWORD, WHILE, 0, "while")         \
    TOKEN(91, T_SEPARATOR, LBRKT, 0, "[")           \
    TOKEN(93, T_SEPARATOR, RBRKT, 0, "]")           \
    TOKEN(94, T_OPERATOR, CARET, 7, "^")            \
    TOKEN(123, T_SEPARATOR, LBRACE, 0, "{")         \
    TOKEN(124, T_OPERATOR, BAR, 6, "|")             \
    TOKEN(125, T_SEPARATOR, RBRACE, 0, "}")         \
    TOKEN(126, T_OPERATOR, TLIDE, 14, "~")          \
    TOKEN(127, T_EOI, EOI, 0, "$")

#define TOKEN(num, type, name, prec, str) name = num,
enum
{
    TOKENS
};
#undef TOKEN

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

#pragma region // dsefine: cases

#define CASE_ID \
    case 'h':   \
    case 'j':   \
    case 'k':   \
    case 'm':   \
    case 'n':   \
    case 'o':   \
    case 'p':   \
    case 'q':   \
    case 'x':   \
    case 'y':   \
    case 'z':   \
    case 'A':   \
    case 'B':   \
    case 'C':   \
    case 'D':   \
    case 'E':   \
    case 'F':   \
    case 'G':   \
    case 'H':   \
    case 'I':   \
    case 'J':   \
    case 'K':   \
    case 'L':   \
    case 'M':   \
    case 'N':   \
    case 'O':   \
    case 'P':   \
    case 'Q':   \
    case 'R':   \
    case 'S':   \
    case 'T':   \
    case 'U':   \
    case 'V':   \
    case 'W':   \
    case 'X':   \
    case 'Y':   \
    case 'Z':   \
    case '_'

#define CASE_DIGIT \
    case '0':      \
    case '1':      \
    case '2':      \
    case '3':      \
    case '4':      \
    case '5':      \
    case '6':      \
    case '7':      \
    case '8':      \
    case '9'

#define CASE_OTHER \
    case ';':      \
    case ',':      \
    case '.':      \
    case ':':      \
    case '*':      \
    case '~':      \
    case '%':      \
    case '^':      \
    case '?':      \
    case '[':      \
    case ']':      \
    case '{':      \
    case '}':      \
    case '(':      \
    case ')'

#define CASE_NEXTLINE \
    case '\n':        \
    case '\v':        \
    case '\r':        \
    case '\f'

#pragma endregion

#pragma region // define: etc

#define uint unsigned int
#define uchar unsigned char
#define ull unsigned long long
#define ll long long
#define ld long double

clock_t clock_start_ = clock();
clock_t clock_end_ = clock();
#define TICK clock_start_ = clock()
#define TOCK clock_end_ = clock()
#define TIME_COST (double)(clock_end_ - clock_start_) / CLOCKS_PER_SEC

#pragma endregion

union Information
{
    union
    {
        ll i;     // int constant
        ull u;    // unsigned constant
        ld f;     // float constant
        uchar *s; // string constant
    } val;        // constant value
    uchar *name;  // name of the identifier
} current_info;

struct Coordinate
{
    uint ln;
    uint col;
};

struct Token
{
    uint id;
    Information info;
    Coordinate coordinate;
};

class Program
{
public:
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
    void Error(const char *err_message, uchar *pos, Coordinate c)
    {
        error_cnt++;
        printf("%d:%d: ", c.ln, c.col);
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
        anomaly = new uchar[len];
        unsigned int i;
        for (i = 0; i < len; i++)
        {
            *(anomaly + i) = *(pos + i);
        }
        printf("%s\n", anomaly);
        for (i = 0; i < c.col; i++)
        {
            printf(" ");
        }
        PRINT(GREEN "^\n");
        pos += len;
    }
    void FatalError(const char *err_message, uchar *pos, Coordinate c)
    {
        Error(err_message, pos, c);
        Exit(EXIT_FAILURE);
    }
    void Warning(const char *war_message, uchar *pos, Coordinate c)
    {
        warning_cnt++;
        printf("%d:%d: ", c.ln + 1, c.col + 1);
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
        anomaly = new uchar[len];
        unsigned int i;
        for (i = 0; i < len; i++)
        {
            *(anomaly + i) = *(pos + i);
        }
        printf("%s\n", anomaly);
        for (i = 0; i < c.col; i++)
        {
            printf(" ");
        }
        PRINT(GREEN "^\n");
        pos += len;
    }

    uint GetErrorCount() { return error_cnt; }
    uint GetWarningCount() { return warning_cnt; }

    void Exit(bool exit_code)
    {
        PRINT(MAGENTA ITALIC "*Exeunt Instructions and Data*\n");
        printf(FAINT "exit code: %d\n" RESET, exit_code);
        exit(exit_code);
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

private:
    uint error_cnt = 0;
    uint warning_cnt = 0;
} prog;

#pragma endregion

#endif
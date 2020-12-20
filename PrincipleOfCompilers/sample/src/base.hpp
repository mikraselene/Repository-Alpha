#ifndef BASE_HPP
#define BASE_HPP

#pragma region // BASE

#include <climits>
#include <cstdarg>
#include <cstdbool>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::function;
using std::pair;
using std::setw;
using std::stoi;
using std::string;
using std::to_string;
using std::vector;

#define FLAG_DISABLE_COLORS 1
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

/// SINGLETON(num, name, str)
#define SINGLETONS                \
    SINGLETON(0, TOK, "")         \
    SINGLETON(1, ASGN, ":=")      \
    SINGLETON(2, PROG, "program") \
    SINGLETON(3, SYS, "sys")      \
    SINGLETON(4, JNZ, "jnz")      \
    SINGLETON(5, JROP, "jrop")    \
    SINGLETON(6, JUMP, "jump")    \
    SINGLETON(7, NEG, "neg")      \
    SINGLETON(8, TARG, "true")    \
    SINGLETON(9, FARG, "false")   \
    SINGLETON(10, SINGID, "")     \
    SINGLETON(11, TRES, "T")      \
    SINGLETON(12, FRES, "F")      \
    SINGLETON(13, NONE, "-")      \
    SINGLETON(14, INTC, "-")

/// TOKEN(num, type, name, str)
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

#define TOKEN(num, type, name, str) name = num,
enum
{
    TOKENS
};
#undef TOKEN

#define SINGLETON(num, name, str) str,
string singleton_str[] = {SINGLETONS};
#undef SINGLETON

#define SINGLETON(num, name, str) name = num,
enum
{
    SINGLETONS
};
#undef SINGLETON

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

#pragma region // define: cases

#define CASE_ID \
    case 'g':   \
    case 'h':   \
    case 'l':   \
    case 'j':   \
    case 'k':   \
    case 'm':   \
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

#define CASE_NEXTLINE \
    case '\n':        \
    case '\v':        \
    case '\r':        \
    case '\f'

#pragma endregion

#pragma region // define: etc

clock_t clock_start_ = clock();
clock_t clock_end_ = clock();
#define TICK clock_start_ = clock()
#define TOCK clock_end_ = clock()
#define ull unsigned long long
#define ll long long
#define ld long double
#define ALL(x) x.begin(), x.end()
#define TIME_COST (double)(clock_end_ - clock_start_) / CLOCKS_PER_SEC
#define CURRENT_TOKEN_ID tokens[current_token_index]->id
#define NEXT_QUADRUPLE quadruple_list[elem.result.poc]
#define TOK(x) pair<int, string>(TOK, x)
#define SINGID(x) pair<int, int>(SINGID, x)
#define JROP(x) pair<int, string>(JROP, "j" + x)
#define INTC(x) pair<int, int>(INTC, x)
#define CURRENT_POS tokens[current_token_index - 1]->pos
#define CURRENT_COORD tokens[current_token_index - 1]->coordinate

#pragma endregion

char *initial;
char *conclusion;

struct Information
{
    union U
    {
        ll i;    // int constant
        ull u;   // unsigned constant
        ld f;    // float constant
        char *s; // string constant
    } val;       // constant value
    char *name;  // name of the identifier
} current_info;

const char *token_str[128] = {0};
uint token_type[128] = {0};
uint token_name[128] = {0};

struct Coordinate
{
    uint ln;
    uint col;
};

struct Token
{
    char *pos;
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
        printf("%s\n", err_message);
    }
    void WarningMessage(const char *war_message, ...)
    {
        PRINT(YELLOW UNDERLINE "warning: ");
        printf("%s\n", war_message);
    }
    void Error(const char *err_message, char *pos, Coordinate c)
    {
        error_cnt++;
        printf("%d:%d: ", c.ln, c.col);
        ErrorMessage(err_message);
        uint len = 1;
        int k = 0;
        // XXX: pos++;...pos--; could this be optimized?
        while (*pos != '\n' && *(pos + 1) != '\n' && pos + 1 != conclusion)
        {
            pos++;
            k++;
        }
        while (*pos != '\n' && *(pos - 1) != '\n' && pos != initial)
        {
            pos--;
            //k++;
            len++;
            if (len > 128)
            {
                break;
            }
        }
        for (int i = 0; i < len; i++)
        {
            printf("%c", *(pos + i));
        }
        printf("\n");
        for (int i = 0; i < c.col - 1; i++)
        {
            printf(" ");
        }
        PRINT(GREEN "^\n");
        pos += len;
    }
    void FatalError(const char *err_message, char *pos, Coordinate c)
    {
        Error(err_message, pos, c);
        Exit(EXIT_FAILURE);
    }
    void Warning(const char *war_message, char *pos, Coordinate c)
    {
        warning_cnt++;
        printf("%d:%d: ", c.ln + 1, c.col + 1);
        WarningMessage(war_message);
        char *anomaly = pos;
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
        anomaly = new char[len];
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
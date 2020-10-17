#include "base.h"

#pragma region // LEX

typedef union
{
    union
    {
        ll i;     // int constant
        ull u;    // unsigned constant
        ld d;     // double constant
        uchar *s; // string constant
    } val;        // constant value
    uchar *name;  // name of the identifier
} Infomation;
Infomation current_info;

typedef struct
{
    uint id;         // The ID of the token, which is defined below.
    Infomation info; // The detail information of the token.
} Token;

#pragma region // CASES

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

#pragma region // DEFINES

#define TOKEN(num, type, name, str) name = num,
enum
{
    TOKENS
};

// XXX: This could be optimized. !memcmp() -> (*rcp == '*' && *(rcp + 1) == '*' && ...)
#define MATCH_STR(str, x, STR)                                                           \
    if (!memcmp(current_pos, str, x) && (!(map[*(current_pos + x)] & (DIGIT | LETTER)))) \
    {                                                                                    \
        pos = current_pos + x;                                                           \
        return STR;                                                                      \
    }

#define MATCH_CHAR(ch, STR) \
    if (*current_pos == ch) \
    {                       \
        pos++;              \
        return STR;         \
    }

#pragma endregion

enum
{
    BLANK = 1,   // 000001
    NEWLINE = 2, // 000010
    LETTER = 4,  // 000100
    DIGIT = 8,   // 001000
    HEX = 16,    // 010000
    OTHER = 32,  // 100000
};

static uint map[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,                                                          //
    BLANK, NEWLINE, BLANK, BLANK,                                                       // HT LF VT FF
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,                            //
    BLANK,                                                                              // (space)
    OTHER, OTHER, OTHER,                                                                // ! " #
    0,                                                                                  //
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,        // % & , ( ) * + , - . /
    DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT, DIGIT,               // 0~9
    OTHER, OTHER, OTHER, OTHER, OTHER, OTHER,                                           // : ; < = > ?
    0,                                                                                  //
    LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, // A~F
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,     // G~Z
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,     // G~Z
    OTHER, OTHER, OTHER, OTHER,                                                         // [ (backslash) ] ^
    LETTER,                                                                             // _
    0,                                                                                  //
    LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, LETTER | HEX, // a~f
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,     // g~z
    LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,     // g~z
    OTHER, OTHER, OTHER, OTHER,                                                         // { | } ~
    0,                                                                                  //
};

uint GetTokenID()
{
    while (true)
    {
        uchar *current_pos = pos;
        while (map[*current_pos] & BLANK)
        {
            current_pos++;
        }
        col_no = current_pos - first_pos;
        pos = current_pos + 1;
        switch (*current_pos++)
        {
        CASE_ID: // #identifier#
        id:
        {
            uchar *start_pos = current_pos - 1;
            while (map[*current_pos] & (DIGIT | LETTER))
            {
                current_pos++;
            }
            uint i;
            uint len = current_pos - start_pos;
            current_info.name = MALLOC(uchar, len);
            for (i = 0; i < len; i++)
            {
                current_info.name[i] = start_pos[i];
            }
            current_info.name[len] = '\0';
            pos = current_pos;
            return ID;
        }
        CASE_OTHER: // #other#
        {
            return *(current_pos - 1);
        }
        CASE_NEXTLINE: // #nextline#
        {
            ln_no++;
            first_pos = pos;
            continue;
        }
        CASE_DIGIT: // #digit#
        {
            ull n = 0;
            uchar *last_pos = current_pos - 1;
            if (*last_pos == '0' && (*current_pos == 'x' || *current_pos == 'X')) // hexadecimal
            {
                uint last_digit = 0;
                bool invalid_hex = false;
                bool overflow = false;
                while (*++current_pos)
                {
                    if (map[*current_pos] & DIGIT)
                    {
                        last_digit = *current_pos - '0';
                    }
                    else if (map[*current_pos] & LETTER)
                    {
                        if (*current_pos >= 'a' && *current_pos <= 'f')
                        {
                            last_digit = *current_pos - 'a' + 10;
                        }
                        else if (*current_pos >= 'A' && *current_pos <= 'F')
                        {
                            last_digit = *current_pos - 'A' + 10;
                        }
                        else
                        {
                            invalid_hex = true;
                        }
                    }
                    else
                    {
                        break;
                    }
                    if (n & ~(~0UL >> 4))
                    {
                        overflow = true;
                    }
                    else
                    {
                        n = (n << 4) + last_digit;
                    }
                }
                if (current_pos - last_pos <= 2)
                {
                    Error("invalid hexadecimal constant");
                    return ERROR;
                }
                pos = current_pos;
                current_info.val.i = n;
                if (invalid_hex)
                {
                    Error("invalid hexadecimal constant");
                    return ERROR;
                }
            }
            else if (*last_pos == '0') // octal
            {
                bool invalid_oct = false;
                bool overflow = false;
                for (; map[*current_pos] & DIGIT; current_pos++)
                {
                    if (*current_pos == '8' || *current_pos == '9')
                    {
                        invalid_oct = true;
                    }
                    if (n & ~(~0UL >> 3))
                    {
                        overflow = true;
                    }
                    else
                    {
                        n = (n << 3) + (*current_pos - '0');
                    }
                }
                pos = current_pos;
                current_info.val.i = n;
                if (invalid_oct)
                {
                    Error("invalid octal constant");
                }
            }
            else // decimal
            {
                bool overflow = false;
                for (n = *last_pos - '0'; map[*current_pos] & DIGIT;)
                {
                    uint d = *current_pos++ - '0';
                    if (n > (ULONG_MAX - d) / 10)
                    {
                        overflow = true;
                    }
                    else
                    {
                        n = 10 * n + d;
                    }
                }
                if (*current_pos == '.')
                {
                    uchar *start_pos = current_pos;
                    do
                    {
                        current_pos++;
                    } while (map[*current_pos] & DIGIT);
                    uint len = current_pos - start_pos;
                    uchar *x = MALLOC(uchar, len);
                    uint i;
                    for (i = 0; i < len; i++)
                    {
                        *(x + i) = *(start_pos + i);
                    }
                    x[len] = '\0';
                    pos = current_pos;
                    current_info.val.d = n + strtod((char *)x, NULL);
                    return FLTCON;
                }
                pos = current_pos;
                current_info.val.i = n;
            }
            return INTCON;
        }
        case '.': // .
        {
            if ((map[*current_pos] & DIGIT) == 0)
            {
                return '.';
            }
        }
        case '\'': // '
        {
            uchar *start_pos = current_pos - 1;
            do
            {
                current_pos++;
            } while ((*(current_pos - 2) != '\\' && *(current_pos - 1) == '\\') || *current_pos != '\'');
            uint i;
            uint len = current_pos - start_pos + 1;
            current_info.val.s = MALLOC(uchar, len);
            for (i = 0; i < len; i++)
            {
                current_info.val.s[i] = start_pos[i];
            }
            pos = current_pos + 1;
            return STRCON;
        }
        case '"': // "
        {
            uchar *start_pos = current_pos - 1;
            bool flag = false;
            do
            {
                flag = false;
                if (*current_pos == '\\' && *(current_pos + 1) != '\\')
                {
                    flag = true;
                }
                current_pos++;
            } while (flag == true || *current_pos != '"');
            uint i;
            uint len = current_pos - start_pos + 1;
            current_info.val.s = MALLOC(uchar, len);
            for (i = 0; i < len; i++)
            {
                current_info.val.s[i] = start_pos[i];
            }
            pos = current_pos + 1;
            return STRCON;
        }
        case '/': // /**/ // /
        {
            if (*current_pos == '*')
            {
                uchar *c;
                current_pos++;
                while (*current_pos != '/' || *c != '*')
                {
                    c = current_pos++;
                    if (map[*current_pos] & NEWLINE)
                    {
                        ln_no++;
                    }
                }
                current_pos++;
                pos = current_pos;
                continue;
            }
            else if (*current_pos == '/')
            {
                while (*current_pos != '\n')
                {
                    current_pos++;
                }
                pos = current_pos;
                continue;
            }
            return '/';
        }
        case '+': // ++ +
        {
            MATCH_CHAR('+', INCR)
            return '+';
        }
        case '-': // -> -- -
        {
            MATCH_CHAR('>', DEREF)
            MATCH_CHAR('-', DECR)
            return '-';
        }
        case '<': // <= << <
        {
            MATCH_CHAR('=', LEQL)
            MATCH_CHAR('<', LSHIFT)
            return '<';
        }
        case '>': // >= >> >
        {
            MATCH_CHAR('=', GEQL)
            MATCH_CHAR('>', RSHIFT)
            return '>';
        }
        case '=': // == =
        {
            MATCH_CHAR('=', EQL)
            return '=';
        }
        case '|': // || |
        {
            MATCH_CHAR('|', OROR)
            return '|';
        }
        case '&': // && &
        {
            MATCH_CHAR('&', ANDAND)
            return '&';
        }
        case '!': // != !
        {
            MATCH_CHAR('=', NEQ)
            return '!';
        }
        case 'a': // auto
        {
            MATCH_STR("uto", 3, AUTO)
            goto id;
        }
        case 'b': // break
        {
            MATCH_STR("reak", 4, BREAK)
            goto id;
        }
        case 'c': // case char const continue
        {
            MATCH_STR("ase", 3, CASE)
            MATCH_STR("har", 3, CHAR)
            MATCH_STR("onst", 4, CONST)
            MATCH_STR("ontinue", 7, CONTINUE)
            goto id;
        }
        case 'd': // default double do
        {
            MATCH_STR("efault", 6, DEFAULT)
            MATCH_STR("ouble", 5, DOUBLE)
            MATCH_STR("o", 1, DO)
            goto id;
        }
        case 'e': // else enum extern
        {
            MATCH_STR("lse", 3, ELSE)
            MATCH_STR("num", 3, ENUM)
            MATCH_STR("xtern", 5, EXTERN)
            goto id;
        }
        case 'f': // float for
        {
            MATCH_STR("loat", 4, FLOAT)
            MATCH_STR("or", 2, FOR)
            goto id;
        }
        case 'g': // goto
        {
            MATCH_STR("oto", 3, GOTO)
            goto id;
        }
        case 'i': // if uint
        {
            MATCH_STR("f", 1, IF)
            MATCH_STR("nt", 2, INT)
            goto id;
        }
        case 'l': // long
        {
            MATCH_STR("ong", 3, LONG)
            goto id;
        }
        case 'r': // register return
        {
            MATCH_STR("egister", 7, REGISTER)
            MATCH_STR("eturn", 5, RETURN)
            goto id;
        }
        case 's': // short signed sizeof static struct switch
        {
            MATCH_STR("hort", 4, SHORT)
            MATCH_STR("igned", 5, SIGNED)
            MATCH_STR("izeof", 5, SIZEOF)
            MATCH_STR("tatic", 5, STATIC)
            MATCH_STR("truct", 5, STRUCT)
            MATCH_STR("witch", 5, SWITCH)
            goto id;
        }
        case 't': // typedef
        {
            MATCH_STR("ypedef", 6, TYPEDEF)
            goto id;
        }
        case 'u': // union unsigned
        {
            MATCH_STR("nion", 4, UNION)
            MATCH_STR("nsigned", 7, UNSIGNED)
            goto id;
        }
        case 'v': // void volatile
        {
            MATCH_STR("oid", 3, VOID)
            MATCH_STR("olatile", 7, VOLATILE)
            goto id;
        }
        case 'w': // while
        {
            MATCH_STR("hile", 4, WHILE)
            goto id;
        }
        case '\0': //
        {
            return EOI;
        }
        default: //
        {
            if ((map[*(pos - 1)] & BLANK) == 0)
            {
                Error("illegal character");
            }
        }
        }
    }
    return ERROR;
}

Token GetToken()
{
    Token next;
    next.id = GetTokenID();
    next.info = current_info;
    return next;
}

#undef TOKEN

#pragma endregion

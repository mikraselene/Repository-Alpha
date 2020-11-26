#ifndef _LEX_H_
#define _LEX_H_

#include "base.h"

typedef union
{
    union
    {
        ll i;     // int constant
        ull u;    // unsigned constant
        ld f;     // float constant
        uchar *s; // string constant
    } val;        // constant value
    uchar *name;  // name of the identifier
} Information;
Information current_info;

typedef struct
{
    uint id;
    Information info;
    struct
    {
        uint ln;
        uint col;
    } coordinate;
} Token;

#pragma region // CASES

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

#pragma region // DEFINES

#define TOKEN(num, type, name, str) name = num,
enum
{
    TOKENS
};

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
        col_no = current_pos - first_pos + 1;
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
            uint len = current_pos - start_pos;
            current_info.name = MALLOC(uchar, len);
            for (uint i = 0; i < len; i++)
            {
                current_info.name[i] = start_pos[i];
            }
            current_info.name[len] = '\0';
            pos = current_pos;
            return ID;
        }
        case '+':
        {
            return PLUS;
        }
        case '-':
        {
            return MINUS;
        }
        case '=':
        {
            return EQUAL;
        }
        case ';':
        {
            return SEMICOL;
        }
        case ',':
        {
            return COMMA;
        }
        case '*':
        {
            return ASTERISK;
        }
        case '[':
        {
            return LBRKT;
        }
        case ']':
        {
            return RBRKT;
        }
        case '(':
        {
            return LPAR;
        }
        case ')':
        {
            return RPAR;
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
            uchar *start_pos = current_pos - 1;
            if (*start_pos == '0' && (*current_pos == 'x' || *current_pos == 'X')) // hexadecimal
            {
                uint last_digit = 0;
                bool invalid_hex = false;
                bool overflow = false;
                while (true)
                {
                    current_pos++;
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
                            break;
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
                if (current_pos - start_pos <= 2)
                {
                    invalid_hex = true;
                }
                pos = current_pos;
                current_info.val.i = n;
                if (invalid_hex)
                {
                    current_info.val.i = 0;
                    Error("invalid hexadecimal constant\n");
                    return ERROR;
                }
            }
            else if (*start_pos == '0') // octal
            {
                bool invalid_oct = false;
                bool overflow = false;
                while (map[*current_pos] & DIGIT)
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
                    current_pos++;
                }
                pos = current_pos;
                current_info.val.i = n;
                if (invalid_oct)
                {
                    current_info.val.i = 0;
                    Error("invalid octal constant\n");
                    return ERROR;
                }
            }
            else // decimal
            {
                bool overflow = false;
                for (n = *start_pos - '0'; map[*current_pos] & DIGIT;)
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
                /*
                if (*current_pos == '.')
                {
                    uchar *start_pos = current_pos;
                    do
                    {
                        current_pos++;
                    } while (map[*current_pos] & DIGIT);
                    uint len = current_pos - start_pos;
                    uchar *x = MALLOC(uchar, len);
                    for (uint i = 0; i < len; i++)
                    {
                        x[i] = start_pos[i];
                    }
                    x[len] = '\0';
                    pos = current_pos;
                    current_info.val.f = n + strtod((char *)x, NULL);
                    return FLTCON;
                }
                */
                pos = current_pos;
                current_info.val.i = n;
            }
            return INTCON;
        }
        case '.': // .. .
        {
            MATCH_CHAR('.', DOTDOT)
            return DOT;
        }
        case '\'': // '
        {
            uchar *start_pos = current_pos;
            bool escape_sequence = false;
            do
            {
                escape_sequence = false;
                if (*current_pos == '\\' && *(current_pos + 1) != '\\')
                {
                    escape_sequence = true;
                }
                current_pos++;
            } while (escape_sequence == true || *current_pos != '\'');
            uint i;
            uint len = current_pos - start_pos;
            current_info.val.s = MALLOC(uchar, len);
            for (i = 0; i < len; i++)
            {
                current_info.val.s[i] = start_pos[i];
            }
            current_info.val.s[len] = '\0';
            pos = current_pos + 1;
            return CHARCON;
        }
        case '/': // /**/ // /
        {
            if (*(current_pos) == '*')
            {
                while (*current_pos != '*' || *(current_pos + 1) != '/')
                {
                    current_pos++;
                    if (map[*current_pos] & NEWLINE)
                    {
                        ln_no++;
                    }
                }
                pos = current_pos + 2;
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
            return SLASH;
        }
        case '<': // <= <> <
        {
            MATCH_CHAR('>', NEQL)
            MATCH_CHAR('=', LEQL)
            return LESS;
        }
        case '>': // >= >
        {
            MATCH_CHAR('=', GEQL)
            return GREATER;
        }
        case ':': // := :
        {
            MATCH_CHAR('=', ASSIGN)
            return COLON;
        }
        case 'a': // and array
        {
            MATCH_STR("nd", 2, AND)
            MATCH_STR("rray", 4, ARRAY)
            goto id;
        }
        case 'b': // begin bool
        {
            MATCH_STR("egin", 4, BEGIN)
            MATCH_STR("ool", 3, BOOL)
            goto id;
        }
        case 'c': // call case char constant
        {
            MATCH_STR("all", 3, CALL)
            MATCH_STR("ase", 3, CASE)
            MATCH_STR("har", 3, CHAR)
            MATCH_STR("onstant", 7, CONSTANT)
            goto id;
        }
        case 'd': // dim do
        {
            MATCH_STR("im", 2, DIM)
            MATCH_STR("o", 1, DO)
            goto id;
        }
        case 'e': // else end
        {
            MATCH_STR("lse", 3, ELSE)
            MATCH_STR("nd", 2, END)
            goto id;
        }
        case 'f': // false for
        {
            MATCH_STR("alse", 4, FALSE)
            MATCH_STR("or", 2, FOR)
            goto id;
        }
        case 'i': // if input integer
        {
            MATCH_STR("f", 1, IF)
            MATCH_STR("nput", 4, INPUT)
            MATCH_STR("nteger", 6, INTEGER)
            goto id;
        }
        case 'n': // not
        {
            MATCH_STR("ot", 2, NOT)
            goto id;
        }
        case 'o': // of or output
        {
            MATCH_STR("f", 1, OF)
            MATCH_STR("r", 1, OR)
            MATCH_STR("utput", 5, OUTPUT)
            goto id;
        }
        case 'p': // procedure program
        {
            MATCH_STR("rocedure", 8, PROCEDURE)
            MATCH_STR("rogram", 6, PROGRAM)
            goto id;
        }
        case 'r': // read real repeat
        {
            MATCH_STR("ead", 3, READ)
            MATCH_STR("eal", 3, REAL)
            MATCH_STR("epeat", 5, REPEAT)
            goto id;
        }
        case 's': // set stop
        {
            MATCH_STR("et", 2, SET)
            MATCH_STR("top", 3, STOP)
            goto id;
        }
        case 't': // then to true
        {
            MATCH_STR("hen", 3, THEN)
            MATCH_STR("o", 1, TO)
            MATCH_STR("rue", 3, TRUE)
            goto id;
        }
        case 'u': // until
        {
            MATCH_STR("ntil", 4, UNTIL)
            goto id;
        }
        case 'v': // var
        {
            MATCH_STR("ar", 2, VAR)
            goto id;
        }
        case 'w': // while write
        {
            MATCH_STR("hile", 4, WHILE)
            MATCH_STR("rite", 4, WRITE)
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
                Error("illegal character\n");
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
    next.coordinate.ln = ln_no;
    next.coordinate.col = col_no;
    return next;
}

#undef TOKEN
#endif

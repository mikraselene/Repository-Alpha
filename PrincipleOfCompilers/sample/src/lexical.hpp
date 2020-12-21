#ifndef LEXICAL_HPP
#define LEXICAL_HPP

#include "base.hpp"

class Tokenizer
{
    enum
    {
        BLANK = 1,   // 000001
        NEWLINE = 2, // 000010
        LETTER = 4,  // 000100
        DIGIT = 8,   // 001000
        HEX = 16,    // 010000
        OTHER = 32,  // 100000
    };
    const uint map[128] = {
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

    char *buf;
    uint len;
    char *pos;
    char *first_pos;
    Coordinate coord;
    vector<Token *> token_vec;
    int cnt[3] = {1, 1, 1};

public:
    Tokenizer(const char *filename)
    {
#define TOKEN(num, type, name, str) \
    token_str[num] = str;           \
    token_type[num] = type;         \
    token_name[num] = name;
        TOKENS
#undef TOKEN
        FILE *fp = fopen(filename, "r");
        if (fp == NULL)
        {
            prog.ErrorMessage("no such file or directory: ");
            printf("%s\n", filename);
            prog.Exit(EXIT_FAILURE);
        }
        fseek(fp, 0, SEEK_END);
        len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        buf = new char[len];
        initial = buf;
        conclusion = buf + len - 1;
        Initialize();
        fread(pos, len, 1, fp);
        fclose(fp);
    }

    int TokenizeTest()
    {
        int cnt = 0;
        Token *token;
        do
        {
            token = GetToken();
            cnt++;
        } while (token->id != EOI);
        Initialize();
        return cnt;
    }
    vector<Token *> Token2Vec()
    {
        Token *token;
        int cnt = 0;
        do
        {
            token = GetToken();
            token_vec.push_back(token);
        } while (token->id != EOI);
        Initialize();
        return token_vec;
    }
    void Token2File(const char *filename)
    {
        std::function<void(FILE *, Token *, int)> print_token = [&](FILE *file, Token *token, int n) {
            char *s = new char[19];
            fprintf(file, "│ %5d ", n);
            switch (token_type[token->id])
            {
            case T_IDENTIFIER:
            {
                strcpy(s, (const char *)token->info.name);
                s[18] = '\0';
                s[17] = s[16] = s[15] = '.';
                fprintf(file, "│ %18s │ %18s │ %18s ", "identifier", token_str[token->id], s);
                break;
            }
            case T_KEYWORD:
            {
                fprintf(file, "│ %18s │ %18s │ %18s ", "keyword", token_str[token->id], token_str[token->id]);
                break;
            }
            case T_CONSTANT:
            {
                if (token_name[token->id] == INTCON)
                {
                    fprintf(file, "│ %18s │ %18s │ %18lld ", "constant", token_str[token->id], token->info.val.i);
                }
                break;
            }
            case T_STRLITERAL:
            {
                strcpy(s, token->info.val.s);
                s[18] = '\0';
                s[17] = s[16] = s[15] = '.';
                fprintf(file, "│ %18s │ %18s │ %18s ", "string literal", token_str[token->id], s);
                break;
            }
            case T_OPERATOR:
            {
                fprintf(file, "│ %18s │ %18s │ %18s ", "operator", token_str[token->id], token_str[token->id]);
                break;
            }
            case T_SEPARATOR:
            {
                fprintf(file, "│ %18s │ %18s │ %18s ", "separator", token_str[token->id], token_str[token->id]);
                break;
            }
            case T_EOI:
            {
                fprintf(file, "│ %18s │ %18s │ %18s ", "conclusion", token_str[token->id], "$");
                break;
            }
            case T_ERROR:
            {
                fprintf(file, "│ %18s │ %18s │ %18s ", "error", token_str[token->id], "error");
                break;
            }
            default:
            {
                int unknown_token = 1;
                prog.Error("unknown token\n", pos, coord);
                break;
            }
            }
            char coordinate[18];
            sprintf(coordinate, "%d:%d", token->coordinate.ln, token->coordinate.col);
            fprintf(file, "│ %18s │\n", coordinate);
            delete[] s;
        };
        FILE *token_file = fopen(filename, "w");
        fprintf(token_file, "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
                            "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
                            "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n");
        uint cnt = 0;
        Token *token;
        do
        {
            token = GetToken();
            print_token(token_file, token, cnt++);
        } while (token->id != EOI);
        fprintf(token_file, "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n");
        fclose(token_file);
        Initialize();
    }
    void PrintAsTheyWish(string info)
    {
        cout << info << endl;
        vector<Token *> v = Token2Vec();
        uint cnt = 1;
        for (Token *i : v)
        {
            cout << "(" << i->id << ", ";
            switch (token_type[i->id])
            {
            case T_CONSTANT:
            {
                if (token_name[i->id] == INTCON)
                {
                    cout << i->info.val.i;
                }
                else if (token_name[i->id] == CHARCON)
                {
                    cout << i->info.val.s;
                }
                break;
            }
            case T_IDENTIFIER:
            {
                cout << i->info.name;
                break;
            }
            default:
            {
                cout << "-";
            }
            }
            cout << ")  ";
            if (cnt % 5 == 0)
            {
                cout << endl;
            }
            cnt++;
        }
        cout << endl;
    }

    void Destruct()
    {
        delete[] buf;
        for (Token *i : token_vec)
        {
            delete i;
        }
    }
    ~Tokenizer()
    {
        delete[] buf;
        for (Token *i : token_vec)
        {
            delete i;
        }
    }

private:
    void Initialize()
    {
        pos = buf;
        first_pos = pos;
        coord = {1, 1};
    }
    Token *GetToken()
    {
        std::function<uint()> get_token_id = [&]() -> uint {
#define MATCH_CHAR(ch, STR) \
    if (*current_pos == ch) \
    {                       \
        pos++;              \
        return STR;         \
    }
#define MATCH_STR(str, STR)                                        \
    if (!memcmp(current_pos, str, strlen(str)) &&                  \
        (!(map[*(current_pos + strlen(str))] & (DIGIT | LETTER)))) \
    {                                                              \
        pos = current_pos + strlen(str);                           \
        return STR;                                                \
    }
            while (true)
            {
                char *current_pos = pos;
                while (map[*current_pos] & BLANK)
                {
                    current_pos++;
                }
                coord.col = current_pos - first_pos + 1;
                pos = current_pos + 1;
                switch (*current_pos++)
                {
                CASE_ID: // #identifier#
                id:
                {
                    char *start_pos = current_pos - 1;
                    while (map[*current_pos] & (DIGIT | LETTER))
                    {
                        current_pos++;
                    }
                    uint len = current_pos - start_pos;
                    current_info.name = new char[len];
                    for (uint i = 0; i < len; i++)
                    {
                        current_info.name[i] = start_pos[i];
                    }
                    current_info.name[len] = '\0';
                    pos = current_pos;
                    return ID;
                }
                CASE_NEXTLINE: // #nextline#
                {
                    coord.ln++;
                    first_pos = pos;
                    continue;
                }
                CASE_DIGIT: // #digit#
                {
                    ull n = 0;
                    char *start_pos = current_pos - 1;
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
                            prog.Error("invalid hexadecimal constant\n", pos, coord);
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
                            prog.Error("invalid octal constant\n", pos, coord);
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
                        pos = current_pos;
                        current_info.val.i = n;
                    }
                    return INTCON;
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
                case '.': // .. .
                {
                    MATCH_CHAR('.', DOTDOT)
                    return DOT;
                }
                case '\'': // '
                {
                    char *start_pos = current_pos;
                    bool escape_sequence = false;
                    do
                    {
                        escape_sequence = false;
                        if (*current_pos == '\n')
                        {
                            coord.col += uint(current_pos - start_pos);
                            prog.Error("unterminated string\n", pos, coord);
                            pos = current_pos;
                            return ERROR;
                        }
                        if (*current_pos == '\\' && *(current_pos + 1) != '\\')
                        {
                            escape_sequence = true;
                        }
                        current_pos++;
                    } while (escape_sequence == true || *current_pos != '\'');
                    uint i;
                    uint len = current_pos - start_pos;
                    current_info.val.s = new char[len];
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
                    if (*(current_pos + 1) == '*')
                    {
                        while (*current_pos != '*' || *(current_pos + 1) != '/')
                        {
                            current_pos++;
                            if (map[*current_pos] & NEWLINE)
                            {
                                coord.col += current_pos - pos;
                                prog.Error("unterminated /* comment\n", pos, coord);
                                pos = current_pos;
                                return ERROR;
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
                    MATCH_CHAR('=', LEQL)
                    MATCH_CHAR('>', NEQL)
                    return LESS;
                }
                case '>': // >= >
                {
                    MATCH_CHAR('=', GEQL)
                    return GREATER;
                }
                case ':': // := :
                {
                    MATCH_CHAR('=', ASSIGN);
                    return COLON;
                }
                case 'a': // and array
                {
                    MATCH_STR("nd", AND)
                    MATCH_STR("rray", ARRAY)
                    goto id;
                }
                case 'b': // begin bool
                {
                    MATCH_STR("egin", BEGIN)
                    MATCH_STR("ool", BOOL)
                    goto id;
                }
                case 'c': // call case char constant
                {
                    MATCH_STR("all", CALL)
                    MATCH_STR("ase", CASE)
                    MATCH_STR("har", CHAR)
                    MATCH_STR("onstant", CONSTANT)
                    goto id;
                }
                case 'd': // dim do
                {
                    MATCH_STR("im", DIM)
                    MATCH_STR("o", DO)
                    goto id;
                }
                case 'e': // else end
                {
                    MATCH_STR("lse", ELSE)
                    MATCH_STR("nd", END)
                    goto id;
                }
                case 'f': // false for
                {
                    MATCH_STR("alse", FALSE)
                    MATCH_STR("or", FOR)
                    goto id;
                }
                case 'i': // if input integer
                {
                    MATCH_STR("f", IF)
                    MATCH_STR("nput", INPUT)
                    MATCH_STR("nteger", INTEGER)
                    goto id;
                }
                case 'n': // not
                {
                    MATCH_STR("ot", NOT)
                    goto id;
                }
                case 'o': // of or output
                {
                    MATCH_STR("f", OF)
                    MATCH_STR("r", OR)
                    MATCH_STR("utput", OUTPUT)
                    goto id;
                }
                case 'p': // procedure program
                {
                    MATCH_STR("rocedure", PROCEDURE)
                    MATCH_STR("rogram", PROGRAM)
                    goto id;
                }
                case 'r': // read real repeat
                {
                    MATCH_STR("ead", READ)
                    MATCH_STR("eal", REAL)
                    MATCH_STR("epeat", REPEAT)
                    goto id;
                }
                case 's': // set stop
                {
                    MATCH_STR("et", SET)
                    MATCH_STR("top", STOP)
                    goto id;
                }
                case 't': // then to true
                {
                    MATCH_STR("hen", THEN)
                    MATCH_STR("o", TO)
                    MATCH_STR("rue", TRUE)
                    goto id;
                }
                case 'u': // until
                {
                    MATCH_STR("ntil", UNTIL)
                    goto id;
                }
                case 'v': // var
                {
                    MATCH_STR("ar", VAR)
                    goto id;
                }
                case 'w': // while write
                {
                    MATCH_STR("hile", WHILE)
                    MATCH_STR("rite", WRITE)
                    goto id;
                }
                case '\0': //
                {
                    return EOI;
                }
                default: //
                {
                    cout << (*(pos - 2) == '\0');
                    if (*(pos - 1) == '\n')
                    {
                        continue;
                    }
                    if (pos - 1 == conclusion)
                    {
                        cout << "hello";
                        return EOI;
                    }
                    if ((map[*(pos - 1)] & BLANK) == 0)
                    {
                        cout << "xhello";
                        exit(1);
                        pos--;
                        coord.col--;
                        prog.Error("illegal character", pos, coord);
                        pos = current_pos;
                    }
                    continue;
                }
                }
            }
            return ERROR;
#undef MATCH_STR
        };
        Token *next = new Token;
        next->id = get_token_id();
        next->pos = pos - 1;
        next->info = current_info;
        next->coordinate = coord;
        return next;
    }
};

#endif

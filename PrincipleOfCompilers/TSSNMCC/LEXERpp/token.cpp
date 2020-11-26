#include "base.h"

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
    const char *token_str[128] = {0};
    uint token_type[128] = {0};
    uint token_name[128] = {0};
    uchar *buf;
    uint len;
    uchar *pos;
    uchar *first_pos;
    Coordinate coord;
    vector<Token *> token_vec;

public:
    Tokenizer(const char *filename)
    {
#define TOKEN(num, type, name, prec, str) \
    token_str[num] = str;                 \
    token_type[num] = type;               \
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
        buf = new uchar[len];
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

    void Token2File(const char *token_file_name)
    {
        FILE *token_file = fopen(token_file_name, "w");
        fprintf(token_file, "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
                            "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
                            "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n");
        uint cnt = 0;
        Token *token;
        do
        {
            token = GetToken();
            PrintToken(token_file, token, cnt++);
        } while (token->id != EOI);
        fprintf(token_file, "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n");
        fclose(token_file);
        Initialize();
    }

    ~Tokenizer()
    {
        delete[] buf;
        //for (Token *i : token_vec)
        {
            //delete i;
        }
    }

private:
    void Initialize()
    {
        pos = buf;
        first_pos = pos;
        coord = {1, 1};
    }

    void PrintToken(FILE *file, Token *token, int n)
    {
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
            if (token_name[token->id] == FLTCON)
            {
                fprintf(file, "│ %18s │ %18s │ %18Lf ", "constant", token_str[token->id], token->info.val.f);
            }
            break;
        }
        case T_STRLITERAL:
        {
            strcpy(s, (const char *)token->info.val.s);
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
    }

    Token *GetToken()
    {
        Token *next = new Token;
        next->id = GetTokenID();
        next->info = current_info;
        next->coordinate = coord;
        return next;
    }

    uint GetTokenID()
    {
#define MATCH_STR(str, STR)                                                                                  \
    if (!memcmp(current_pos, str, strlen(str)) && (!(map[*(current_pos + strlen(str))] & (DIGIT | LETTER)))) \
    {                                                                                                        \
        pos = current_pos + strlen(str);                                                                     \
        return STR;                                                                                          \
    }
        while (true)
        {
            uchar *current_pos = pos;
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
                uchar *start_pos = current_pos - 1;
                while (map[*current_pos] & (DIGIT | LETTER))
                {
                    current_pos++;
                }
                uint len = current_pos - start_pos;
                current_info.name = new uchar[len];
                for (uint i = 0; i < len; i++)
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
                coord.ln++;
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
                    if (*current_pos == '.')
                    {
                        uchar *start_pos = current_pos;
                        do
                        {
                            current_pos++;
                        } while (map[*current_pos] & DIGIT);
                        uint len = current_pos - start_pos;
                        uchar *x = new uchar[len];
                        for (uint i = 0; i < len; i++)
                        {
                            x[i] = start_pos[i];
                        }
                        x[len] = '\0';
                        pos = current_pos;
                        current_info.val.f = n + strtod((char *)x, NULL);
                        return FLTCON;
                    }
                    pos = current_pos;
                    current_info.val.i = n;
                }
                return INTCON;
            }
            case '\'': // '
            {
                if (*current_pos == '\\' && *(current_pos + 2) == '\'')
                {
                    uchar *next_pos = current_pos + 1;
                    switch (*next_pos)
                    {
                    case 'a':
                        current_info.val.i = '\a';
                        break;
                    case 'b':
                        current_info.val.i = '\b';
                        break;
                    case 'f':
                        current_info.val.i = '\f';
                        break;
                    case 'n':
                        current_info.val.i = '\n';
                        break;
                    case 'r':
                        current_info.val.i = '\r';
                        break;
                    case 't':
                        current_info.val.i = '\t';
                        break;
                    case 'v':
                        current_info.val.i = '\v';
                        break;
                    case '\\':
                        current_info.val.i = '\\';
                        break;
                    case '\'':
                        current_info.val.i = '\'';
                        break;
                    CASE_DIGIT:
                        current_info.val.i = *next_pos - '0';
                        break;
                    default:
                        prog.Warning("unknown escape sequence\n", pos, coord);
                        current_info.val.i = *next_pos;
                        break;
                    }
                    pos = current_pos + 3;
                }
                else if (*(current_pos + 1) == '\'')
                {
                    current_info.val.i = *current_pos;
                    pos = current_pos + 2;
                }
                else
                {
                    current_info.val.i = 0;
                    prog.Error("unrecognized character\n", pos, coord);
                    return ERROR;
                }
                return INTCON;
            }
            case '"': // "
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
                } while (escape_sequence == true || *current_pos != '"');
                uint i;
                uint len = current_pos - start_pos - 1;
                current_info.val.s = new uchar[len];
                for (i = 0; i < len; i++)
                {
                    current_info.val.s[i] = start_pos[i];
                }
                current_info.val.s[len] = '\0';
                pos = current_pos + 1;
                return STRCON;
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
                            coord.ln++;
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
                return '/';
            }
            case '+': // ++ +
            {
                MATCH_STR("+", INCR)
                return '+';
            }
            case '-': // -> -- -
            {
                MATCH_STR(">", DEREF)
                MATCH_STR("-", DECR)
                return '-';
            }
            case '<': // <= << <
            {
                MATCH_STR("=", LEQL)
                MATCH_STR("<", LSHIFT)
                return '<';
            }
            case '>': // >= >> >
            {
                MATCH_STR("=", GEQL)
                MATCH_STR(">", RSHIFT)
                return '>';
            }
            case '=': // == =
            {
                MATCH_STR("=", EQL)
                return '=';
            }
            case '|': // || |
            {
                MATCH_STR("|", OROR)
                return '|';
            }
            case '&': // && &
            {
                MATCH_STR("&", ANDAND)
                return '&';
            }
            case '!': // != !
            {
                MATCH_STR("=", NEQ)
                return '!';
            }
            case 'a': // auto
            {
                MATCH_STR("uto", AUTO)
                goto id;
            }
            case 'b': // break
            {
                MATCH_STR("reak", BREAK)
                goto id;
            }
            case 'c': // case char const continue
            {
                MATCH_STR("ase", CASE)
                MATCH_STR("har", CHAR)
                MATCH_STR("onst", CONST)
                MATCH_STR("ontinue", CONTINUE)
                goto id;
            }
            case 'd': // default double do
            {
                MATCH_STR("efault", DEFAULT)
                MATCH_STR("ouble", DOUBLE)
                MATCH_STR("o", DO)
                goto id;
            }
            case 'e': // else enum extern
            {
                MATCH_STR("lse", ELSE)
                MATCH_STR("num", ENUM)
                MATCH_STR("xtern", EXTERN)
                goto id;
            }
            case 'f': // float for
            {
                MATCH_STR("loat", FLOAT)
                MATCH_STR("or", FOR)
                goto id;
            }
            case 'g': // goto
            {
                MATCH_STR("oto", GOTO)
                goto id;
            }
            case 'i': // if int
            {
                MATCH_STR("f", IF)
                MATCH_STR("nt", INT)
                goto id;
            }
            case 'l': // long
            {
                MATCH_STR("ong", LONG)
                goto id;
            }
            case 'r': // register return
            {
                MATCH_STR("egister", REGISTER)
                MATCH_STR("eturn", RETURN)
                goto id;
            }
            case 's': // short signed sizeof static struct switch
            {
                MATCH_STR("hort", SHORT)
                MATCH_STR("igned", SIGNED)
                MATCH_STR("izeof", SIZEOF)
                MATCH_STR("tatic", STATIC)
                MATCH_STR("truct", STRUCT)
                MATCH_STR("witch", SWITCH)
                goto id;
            }
            case 't': // typedef
            {
                MATCH_STR("ypedef", TYPEDEF)
                goto id;
            }
            case 'u': // union unsigned
            {
                MATCH_STR("nion", UNION)
                MATCH_STR("nsigned", UNSIGNED)
                goto id;
            }
            case 'v': // void volatile
            {
                MATCH_STR("oid", VOID)
                MATCH_STR("olatile", VOLATILE)
                goto id;
            }
            case 'w': // while
            {
                MATCH_STR("hile", WHILE)
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
                    prog.Error("illegal character\n", pos, coord);
                }
            }
            }
        }
        return ERROR;
#undef MATCH_STR
    }
};

#define FLAG_TEST 1

int main()
{
    Tokenizer sample("0.sample");
#if FLAG_TEST
    TICK;
    int n = 1;
    for (int i = 0; i < n; i++)
    {
        sample.TokenizeTest(); // 30000 tokens, n = 1000, 0.62 sec.
    }
    TOCK;
    printf("TEST: %f s\n", TIME_COST);
#else
    TICK;
    vector<Token *> vec = sample.Token2Vec();
    sample.Token2File("0.tokens");
    TOCK;
    printf("LEX: %f s\n", TIME_COST);
#endif
    prog.Exeunt();
}
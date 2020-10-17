#include <iostream>
#include <fstream>
#include <iomanip>

#include "lex.c"

std::string token_str[128];
uint token_type[128];
uint token_name[128];

void PrintToken(std::ofstream &out, Token token, int n)
{
#define OUT(xx, yy)                              \
    out << std::setw(18) << xx;                  \
    out << " │ ";                                \
    out << std::setw(18) << token_str[token.id]; \
    out << " │ ";                                \
    out << std::setw(18) << yy;                  \
    out << " │ ";

    out << "│ ";
    out << std::setw(5) << n;
    out << " │ ";
    switch (token_type[token.id])
    {
    case T_IDENTIFIER:
    {
        uchar *s = token.info.name;
        s[18] = '\0';
        s[17] = s[16] = s[15] = '.';
        OUT("identifier", s)
        break;
    }
    case T_KEYWORD:
    {
        OUT("keyword", token_str[token.id])
        break;
    }
    case T_SEPARATOR:
    {
        OUT("separator", token_str[token.id])
        break;
    }
    case T_OPERATOR:
    {
        OUT("operator", token_str[token.id])
        break;
    }
    case T_NUMBER:
    {
        if (token_name[token.id] == INTCON)
        {
            OUT("number", token.info.val.i);
        }
        if (token_name[token.id] == FLTCON)
        {
            OUT("number", token.info.val.d);
        }
        break;
    }
    case T_TEXT:
    {
        uchar *s = token.info.val.s;
        s[18] = '\0';
        s[17] = '"';
        s[16] = s[15] = s[14] = '.';
        OUT("text", s);
        break;
    }
    case T_EOI:
    {
        OUT("conclusion", "$");
        break;
    }
    case T_ERROR:
    {
        OUT("error", "error");
        break;
    }
    default:
    {
        int unknown_token = 1;
        Error("unknown token");
        break;
    }
    }
    std::string pos = "" + std::to_string(ln_no) + ":" + std::to_string(col_no) + "";
    out << std::setw(18) << pos;
    out << " │" << std::endl;
#undef OUT
}

uint ReadFile(const char *name)
{
    FILE *fp = fopen(name, "r");
    fseek(fp, 0, SEEK_END);
    uint len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = MALLOC(uchar, len);
    pos = buf;
    fread(pos, len, 1, fp);
    fclose(fp);
    return len;
}

int main()
{
#define TOKEN(num, type, name, str) \
    token_str[num] = str;           \
    token_type[num] = type;         \
    token_name[num] = name;
    TOKENS
#undef TOKEN

    uint length = ReadFile("0.sample");
    first_pos = pos;
    std::ofstream token_stream("1.tokens");
    token_stream << "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
                 << "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
                 << "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n";
    uint cnt = 0;
    Token token;
    do
    {
        token = GetToken();
        PrintToken(token_stream, token, cnt++);
    } while (token.id != EOI);
    token_stream << "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n";
    token_stream.close();
    delete[] buf;
    Exeunt();
}

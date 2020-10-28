#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>

#include "lex.c"
#include "read.c"

using namespace std;

string w[128];
int t[128];
int x[128];

class Token
{
public:
    enum
    {
        ERR = 0,
        IDENTIFIER,
        KEYWORD,
        SEPARATOR,
        OPERATOR,
        NUMBER,
        TEXT,
        COMMENT,
        UNKNOWN,
        END,
    };
    Token(uint n, uint toknum)
    {
        this->n = n;
        this->toknum = toknum;
        this->word = w[toknum];
        this->type = t[toknum];
        this->name = x[toknum];
        this->position = {ln_no, col_no};
    }
    friend ostream &operator<<(ostream &out, Token t)
    {
#define OUT(xx, yy)            \
    out << setw(18) << xx;     \
    out << " │ ";              \
    out << setw(18) << t.word; \
    out << " │ ";              \
    out << setw(18) << yy;     \
    out << " │ ";

        out << "│ ";
        out << setw(5) << t.n;
        out << " │ ";

        switch (t.type)
        {
        case IDENTIFIER:
        {
            uchar *s = token;
            s[18] = '\0';
            s[17] = s[16] = s[15] = '.';
            OUT("identifier", s)
            break;
        }
        case KEYWORD:
        {
            OUT("keyword", t.word)
            break;
        }
        case SEPARATOR:
        {
            OUT("separator", t.word)
            break;
        }
        case OPERATOR:
        {
            OUT("operator", t.word)
            break;
        }
        case NUMBER:
        {
            if (t.name == INTCON)
            {
                OUT("number", val.vtype.i);
            }
            if (t.name == FLTCON)
            {
                OUT("number", val.vtype.d);
            }
            break;
        }
        case TEXT:
        {
            uchar *s = val.vtype.s;
            s[18] = '\0';
            s[17] = '"';
            s[16] = s[15] = s[14] = '.';
            OUT("text", s);
            break;
        }
        case END:
        {
            OUT("conclusion", "$");
            break;
        }
        case ERROR:
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
        string pos = "" + to_string(t.position.line) + ":" + to_string(t.position.column) + "";
        out << setw(18) << pos;
        out << " │" << endl;
        return out;
#undef OUT
    }

private:
    uint n;
    uint toknum;
    string word;
    struct Tuple
    {
        uint x;
        uint y;
    } tuple;
    int type;
    int name;
    struct Position
    {
        uint line;
        uint column;
    } position;
};

void Exeunt()
{
    if (error_cnt == 0 && warning_cnt == 0)
    {
        PRINT(GREEN "Let there be light!\n");
        printf("Build succeeded with 0 errors, 0 warnings.\n");
    }
    else if (error_cnt == 0 && warning_cnt != 0)
    {
        PRINT(YELLOW "A bad peace is even worse than war.\n");
        printf("Build succeeded with ");
        printf(error_cnt == 1 ? "%d error, " : "%d errors, ", error_cnt);
        printf(warning_cnt == 1 ? "%d warning.\n" : "%d warnings.\n", warning_cnt);
    }
    else
    {
        PRINT(RED "To err is human.\n");
        printf("Build failed with ");
        printf(error_cnt == 1 ? "%d error, " : "%d errors, ", error_cnt);
        printf(warning_cnt == 1 ? "%d warning.\n" : "%d warnings.\n", warning_cnt);
        PRINT(MAGENTA ITALIC "*Exeunt Instructions and Data*\n");
        exit(EXIT_FAILURE);
    }
}

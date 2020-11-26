#include "lex.h"

#define DO_NOT_PRINT true

const char *token_str[128] = {0};
uint token_type[128] = {0};
uint token_name[128] = {0};

void PrintToken(FILE *file, Token token, int n)
{
    fprintf(file, "│ %5d ", n);
    switch (token_type[token.id])
    {
    case T_IDENTIFIER:
    {
        uchar *s = token.info.name;
        s[18] = '\0';
        s[17] = s[16] = s[15] = '.';
        fprintf(file, "│ %18s │ %18s │ %18s ", "identifier", token_str[token.id], s);
        break;
    }
    case T_KEYWORD:
    {
        fprintf(file, "│ %18s │ %18s │ %18s ", "keyword", token_str[token.id], token_str[token.id]);
        break;
    }
    case T_CONSTANT:
    {
        if (token_name[token.id] == INTCON)
        {
            fprintf(file, "│ %18s │ %18s │ %18lld ", "constant", token_str[token.id], token.info.val.i);
        }
        if (token_name[token.id] == FLTCON)
        {
            fprintf(file, "│ %18s │ %18s │ %18Lf ", "constant", token_str[token.id], token.info.val.f);
        }
        break;
    }
    case T_STRLITERAL:
    {
        uchar *s = token.info.val.s;
        s[18] = '\0';
        s[17] = s[16] = s[15] = '.';
        fprintf(file, "│ %18s │ %18s │ %18s ", "string literal", token_str[token.id], s);
        break;
    }
    case T_OPERATOR:
    {
        fprintf(file, "│ %18s │ %18s │ %18s ", "operator", token_str[token.id], token_str[token.id]);
        break;
    }
    case T_SEPARATOR:
    {
        fprintf(file, "│ %18s │ %18s │ %18s ", "separator", token_str[token.id], token_str[token.id]);
        break;
    }
    case T_EOI:
    {
        fprintf(file, "│ %18s │ %18s │ %18s ", "conclusion", token_str[token.id], "$");
        break;
    }
    case T_ERROR:
    {
        fprintf(file, "│ %18s │ %18s │ %18s ", "error", token_str[token.id], "error");
        break;
    }
    default:
    {
        int unknown_token = 1;
        Error("unknown token\n");
        break;
    }
    }
    char coordinate[18];
    sprintf(coordinate, "%d:%d", token.coordinate.ln, token.coordinate.col);
    fprintf(file, "│ %18s │\n", coordinate);
}

uint ReadFile(const char *name)
{
    FILE *fp = fopen(name, "r");
    if (fp == NULL)
    {
        ErrorMessage("no such file or directory: ");
        printf("%s\n", name);
        Exit(EXIT_FAILURE);
    }
    fseek(fp, 0, SEEK_END);
    uint len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = new uchar[len];
    pos = buf;
    fread(pos, len, 1, fp);
    fclose(fp);
    return len;
}

void LexerWrite(const char *token_file_name)
{
#define TOKEN(num, type, name, prec, str) \
    token_str[num] = str;                 \
    token_type[num] = type;               \
    token_name[num] = name;
    TOKENS
#undef TOKEN

    first_pos = pos;
#if DO_NOT_PRINT == false
    FILE *token_file = fopen(token_file_name, "w");
    fprintf(token_file, "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
                        "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
                        "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n");
#endif
    uint cnt = 0;
    Token token;
    do
    {
        token = GetToken();
#if DO_NOT_PRINT == false
        PrintToken(token_file, token, cnt++);
#endif
    } while (token.id != EOI);
#if DO_NOT_PRINT == false
    fprintf(token_file, "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n");
    fclose(token_file);
#endif
}

int main()
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 100; i++)
    {
        ReadFile("../c.c.sample");
        LexerWrite("0.tokens");
        delete[] buf;
    }
    end = clock();
    printf("LEX: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    Exeunt();
}

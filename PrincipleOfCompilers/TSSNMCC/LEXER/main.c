#include "lex.h"

const char *token_str[128];
uint token_type[128];
uint token_name[128];

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
        s[17] = '"';
        s[16] = s[15] = s[14] = '.';
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

#undef OUT
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
    buf = MALLOC(uchar, len);
    pos = buf;
    fread(pos, len, 1, fp);
    fclose(fp);
    return len;
}

void LexerWrite(const char *token_file_name)
{
#define TOKEN(num, type, name, str) \
    token_str[num] = str;           \
    token_type[num] = type;         \
    token_name[num] = name;
    TOKENS
#undef TOKEN
    first_pos = pos;
    FILE *token_file = fopen(token_file_name, "w");
    fprintf(token_file, "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
                        "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
                        "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n");
    uint cnt = 0;
    Token token;
    do
    {
        token = GetToken();
        PrintToken(token_file, token, cnt++);
    } while (token.id != EOI);
    fprintf(token_file, "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n");
    fclose(token_file);
}

int main()
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 1; i++)
    {
        ReadFile("../c.c.sample");
        LexerWrite("0.tokens");
        free(buf);
    }
    end = clock();
    printf("LEX: %f s\n", (double)(end - start) / CLOCKS_PER_SEC);
    Exeunt();
}

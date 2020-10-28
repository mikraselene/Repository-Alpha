#include "main.hpp"

int main()
{
#define TOKEN(num, type, name, str) \
    w[num] = str;                   \
    t[num] = type;                  \
    x[num] = name;
    TOKENS
#undef TOKEN
    clock_t start, end;
    start = clock();
    for (int i = 0; i < 100; i++)
    {
        uint length = ReadFile("0.sample");
        first = cp;
        ofstream file("0.tokens");
        file << "╒═══════╤════════════════════╤════════════════════╤════════════════════╤════════════════════╕\n"
             << "│    NO │               TYPE │              TOKEN │              VALUE │           POSITION │\n"
             << "╞═══════╪════════════════════╪════════════════════╪════════════════════╪════════════════════╡\n";
        uint cnt = 0;
        uint tok = 0;
        do
        {
            tok = GetToken();
            file << Token(cnt++, tok);
        } while (tok != EOI);
        file << "└───────┴────────────────────┴────────────────────┴────────────────────┴────────────────────┘\n";
        file.close();
        delete[] buf;
    }
    end = clock();
    printf("%f s\n", ((double)(end - start) / CLOCKS_PER_SEC));
    Exeunt();
}

#include "sematic.hpp"

#define INFO "201930343162 Qyu Yiwei"

void TimeCostTest(const char *filename)
{
    Tokenizer sample(filename);
    TICK;
    int n = 1000;
    for (int i = 0; i < n; i++)
    {
        sample.TokenizeTest(); // Time(30000000 tokens) = 0.62 sec. (2.3 GHz Intel Core i9, -O2)
    }
    TOCK;
    printf("TEST: %f s\n", TIME_COST);
}

#define TEST_TOKENIZER(filename) Tokenizer(filename).PrintAsTheyWish(INFO)
#define TEST_PARSER(filename) Parser(Tokenizer(filename).Token2Vec()).PrintAsTheyWish(INFO)

int main()
{
    // Use TEST_TOKENIZER(filename) or TEST_PARSER(filename) to test me.
    // Do not test more than one case a time.
    TICK;
    TEST_PARSER("test/4.test");
    TOCK;
    printf("Time Cost: %lf s\n", TIME_COST);
    prog.Exeunt();
}

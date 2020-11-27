#include "sematic.hpp"

#define INFO "201930343162 Qyu Yiwei"

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

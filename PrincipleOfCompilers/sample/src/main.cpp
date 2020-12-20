#include "sematic.hpp"

#define INFO "Principle of Compilers SCUT 201930343162 Qyu Yiwei"

#define TEST_TOKENIZER(filename) Tokenizer("../test/" filename).PrintAsTheyWish(INFO)
#define TEST_PARSER(filename) Parser(Tokenizer("../test/" filename).Token2Vec()).PrintAsTheyWish(INFO)

int main()
{
    // Use TEST_TOKENIZER(filename) or TEST_PARSER(filename) to test me.
    // Do not test more than one case a time.
    // TICK;
    TEST_PARSER("fast_pow.test");
    // TOCK;
    // printf("Time Cost: %lf s\n", TIME_COST);
    // prog.Exeunt();
}
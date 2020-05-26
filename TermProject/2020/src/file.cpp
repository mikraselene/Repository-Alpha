#include "../inc/file.h"

using std::cerr;
using std::cout;
using std::ifstream;
using std::vector;

void File::LoadFromFile()
{
    std::ifstream in("f.txt");
    if (!in.is_open())
    {
        cout << "Error opening file";
        exit(1);
    }
    while (!in.eof())
    {
        extern vector<Bill *> pBill;
        int year = 0;
        int month = 0;
        int day = 0;
        double amount = 0;
        in >> year >> month >> day >> amount;
        Year Y(year);
        Month M(month);
        Day D(day);
        Date date(Y, M, D);
        Bill *p = new Bill(1, amount, date, "info");
        pBill.push_back(p);
    }
}
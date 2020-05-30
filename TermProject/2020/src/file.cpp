#include "../inc/file.h"

using std::cerr;
using std::cout;
using std::ifstream;
using std::vector;

void File::LoadFromFile()
{
#if 0
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
        if (amount == 0)
        {
            //TODO:
        }
        else
        {
            Bill *p = new Bill(abs(amount) / amount, abs(amount), date, "info");
            p->Add();
        }
    }
#endif

#if 1
    extern vector<Bill *> pBill;
    extern vector<Transaction *> pTransaction;
    extern vector<DepositAndLoan *> pDepoAndLoan;
    std::ifstream inFile("binary.dat", std::ios::binary);
    int size[3];

    inFile.read((char *)size, 3 * sizeof(int));
    for (int i = 0; i < size[0]; i++)
    {
        BILL_DATA data;
        inFile.read((char *)&data, sizeof(BILL_DATA));
        Bill *p = new Bill(data.type, data.amount, data.date, data.info);
        p->Add();
    }
    for (int i = 0; i < size[1]; i++)
    {
        TRANSACTION_DATA data;
        inFile.read((char *)&data, sizeof(TRANSACTION_DATA));
        Transaction *p = new Transaction;
        p->SetData(data);
        pTransaction.push_back(p);
    }
    for (int i = 0; i < size[2]; i++)
    {
        DEPOSIT_AND_LOAN_DATA data;
        inFile.read((char *)&data, sizeof(DEPOSIT_AND_LOAN_DATA));
        DepositAndLoan *p = new DepositAndLoan;
        p->SetData(data);
        pDepoAndLoan.push_back(p);
    }
    inFile.close();
#endif
}

void File::SaveToFile()
{
    extern vector<Bill *> pBill;
    extern vector<Transaction *> pTransaction;
    extern vector<DepositAndLoan *> pDepoAndLoan;
    std::ofstream outFile("binary.dat", std::ios::out | std::ios::binary);
    int size[3];
    size[0] = pBill.size();
    size[1] = pTransaction.size();
    size[2] = pDepoAndLoan.size();
    outFile.write((char *)size, 3 * sizeof(int));
    for (int i = 0; i < size[0]; i++)
    {
        BILL_DATA data = pBill[i]->GetData();
        outFile.write((char *)&data, sizeof(BILL_DATA));
    }
    for (int i = 0; i < size[1]; i++)
    {
        TRANSACTION_DATA data = pTransaction[i]->GetData();
        outFile.write((char *)&data, sizeof(TRANSACTION_DATA));
    }
    for (int i = 0; i < size[2]; i++)
    {
        DEPOSIT_AND_LOAN_DATA data = pDepoAndLoan[i]->GetData();
        outFile.write((char *)&data, sizeof(DEPOSIT_AND_LOAN_DATA));
    }
    outFile.close();
}

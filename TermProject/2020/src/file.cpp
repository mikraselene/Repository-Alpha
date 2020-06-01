#include "../inc/file.h"

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
            
        }
        else
        {
            Bill *p = new Bill(abs(amount) / amount, abs(amount), date, "info");
            p->Add();
        }
    }
#endif

#if 1
    extern std::vector<std::shared_ptr<Bill>> pBill;
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    std::ifstream inFile("binary.dat", std::ios::binary);
    int size[3];

    inFile.read((char *)size, 3 * sizeof(int));
    for (int i = 0; i < size[BILL]; i++)
    {
        Bill::DATA data;
        inFile.read((char *)&data, sizeof(Bill::DATA));
        std::shared_ptr<Bill>
            p = std::make_shared<Bill>(data.type, data.amount, data.date, data.info);
        p->Add();
    }
    for (int i = 0; i < size[TRANSACTION]; i++)
    {
        Transaction::DATA data;
        inFile.read((char *)&data, sizeof(Transaction::DATA));
        std::shared_ptr<Transaction> p = std::make_shared<Transaction>();
        p->SetData(data);
        pTransaction.push_back(p);
    }
    for (int i = 0; i < size[DEPOSIT_AND_LOAN]; i++)
    {
        DepositAndLoan::DATA data;
        inFile.read((char *)&data, sizeof(DepositAndLoan::DATA));
        std::shared_ptr<DepositAndLoan> p = std::make_shared<DepositAndLoan>();
        p->SetData(data);
        pDepoAndLoan.push_back(p);
    }
    inFile.close();
#endif
}

void File::SaveToFile()
{
    extern std::vector<std::shared_ptr<Bill>> pBill;
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    std::ofstream outFile("binary.dat", std::ios::out | std::ios::binary);
    int size[3];
    size[0] = pBill.size();
    size[1] = pTransaction.size();
    size[2] = pDepoAndLoan.size();
    outFile.write((char *)size, 3 * sizeof(int));
    for (int i = 0; i < size[0]; i++)
    {
        Bill::DATA data = pBill[i]->GetData();
        outFile.write((char *)&data, sizeof(Bill::DATA));
    }
    for (int i = 0; i < size[1]; i++)
    {
        Transaction::DATA data = pTransaction[i]->GetData();
        outFile.write((char *)&data, sizeof(Transaction::DATA));
    }
    for (int i = 0; i < size[2]; i++)
    {
        DepositAndLoan::DATA data = pDepoAndLoan[i]->GetData();
        outFile.write((char *)&data, sizeof(DepositAndLoan::DATA));
    }
    outFile.close();
}

#include "../inc/file.h"

/*---------------------------------------------------------------------------
函数: void LoadFromFile()

目的:
    从二进制文件 save.dat 中读取储存的信息. 
---------------------------------------------------------------------------*/
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
    std::ifstream inFile("save.dat", std::ios::binary);
    if (!inFile.is_open())
    {
        std::cerr << NError::CANNOT_OPEN_FILE << ". " << std::endl;
        std::ofstream outFile("save.dat", std::ios::out | std::ios::binary);
    }
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

/*---------------------------------------------------------------------------
函数: void SaveToFile()

目的:
    将改动保存到二进制文件 save.dat 中. 
---------------------------------------------------------------------------*/
void File::SaveToFile()
{
    extern std::vector<std::shared_ptr<Bill>> pBill;
    extern std::vector<std::shared_ptr<Transaction>> pTransaction;
    extern std::vector<std::shared_ptr<DepositAndLoan>> pDepoAndLoan;
    std::ofstream outFile("save.dat", std::ios::out | std::ios::binary);
    int size[3];
    size[BILL] = pBill.size();
    size[TRANSACTION] = pTransaction.size();
    size[DEPOSIT_AND_LOAN] = pDepoAndLoan.size();
    outFile.write((char *)size, 3 * sizeof(int));
    for (int i = 0; i < size[BILL]; i++)
    {
        Bill::DATA data = pBill[i]->GetData();
        outFile.write((char *)&data, sizeof(Bill::DATA));
    }
    for (int i = 0; i < size[TRANSACTION]; i++)
    {
        Transaction::DATA data = pTransaction[i]->GetData();
        outFile.write((char *)&data, sizeof(Transaction::DATA));
    }
    for (int i = 0; i < size[DEPOSIT_AND_LOAN]; i++)
    {
        DepositAndLoan::DATA data = pDepoAndLoan[i]->GetData();
        outFile.write((char *)&data, sizeof(DepositAndLoan::DATA));
    }
    outFile.close();
}

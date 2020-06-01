#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <memory>

#include "date.h"
#include "input.h"
#include "text.h"
#include "period.h"
#include "category.h"
#include "menu.h"
#include "bill.h"

class Asset
{
public:
    enum
    {
        INCOME = 1,
        EXPENSE = -1,
    };
    enum
    {
        DEPOSIT = 1,
        LOAN = -1,
    };

protected:
    void
    SetId(const int &);
    double SetAmount() const;
    Date SetDate() const;
    Category SetCategory() const;
    Period SetPeriod() const;
    int SetCode() const;
    void ShowCategory() const;
    void PrintInstruction() const;
    int id;
};

class Transaction : public Asset,
                    public std::enable_shared_from_this<Transaction>
{
    friend class File;
    friend class Refresh;
    friend class TransactionMenu;

public:
    struct DATA
    {
        int type;
        double amount;
        Category category;
        Date date;
        Date tempDate;
        Period period;
    };

private:
    void InputSingleTransaction(const int &);
    void InputSingleCode();
    void InputRegularTransaction(const int &);
    void InputRegularCode();

    void SingleSubmenu();
    void InputSingleSubmenuCode();
    void RegularSubmenu() const;
    void InputRegularSubmenuCode() const;

    void Edit();
    void Delete() const;
    void Print() const;

    void SetData(const DATA &);
    DATA GetData() const;

    template <typename T1, typename T2, typename T3>
    void PrintOneBody(const T1 &,
                      const T2 &,
                      const T3 &) const;

    template <typename T1, typename T2, typename T3>
    void PrintInputSingleBody(const std::string &,
                              const T1 &,
                              const T2 &,
                              const T3 &) const;

    template <typename T1, typename T2, typename T3, typename T4>
    void PrintInputRegularBody(const std::string &,
                               const T1 &,
                               const T2 &,
                               const T3 &,
                               const T4 &) const;

    Period GetPeriod() const;
    Date GetTempDate() const;
    void AddToBill(const std::shared_ptr<Date> &) const;
    void ResetDate();

    int type;
    double amount;
    Category category;
    Date tempDate;
    Date date;
    Period period;
};

class DepositAndLoan : public Asset,
                       public std::enable_shared_from_this<DepositAndLoan>
{
    friend class File;
    friend class Refresh;
    friend class DepositAndLoanMenu;

public:
    struct DATA
    {
        bool isCompound;
        int type;
        double principle;
        double tempPrinciple;
        double rate;
        double totalInterest;
        Date date;
        Date tempDate;
        Period period;
        std::string info;
    };

private:
    void InputDepositAndLoan(const int &);
    void InputCode();

    void Submenu() const;
    void InputSubmenuCode() const;

    void Print() const;

    void SetData(const DATA &);
    DATA GetData() const;

    template <typename T1, typename T2, typename T3,
              typename T4, typename T5, typename T6>
    void PrintInputBody(const T1 &,
                        const T2 &,
                        const T3 &,
                        const T4 &,
                        const T5 &,
                        const T6 &) const;

    Period GetPeriod() const;
    Date GetTempDate() const;
    void AddToBill(const std::shared_ptr<Date> &);
    void CheckCompound();
    void ResetDate();

    double GetTotalInterest() const;
    void PrintTotalInterest() const;

    double SetRate() const;
    bool SetType() const;
    std::string SetInfo() const;

    int type;
    bool isCompound;
    double principle;
    double tempPrinciple;
    double rate;
    double totalInterest;
    Date date;
    Date tempDate;
    Period period;
    std::string info;
};

#endif

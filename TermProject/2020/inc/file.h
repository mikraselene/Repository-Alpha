#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <cmath>
#include <iostream>

#include "date.h"
#include "bill.h"
#include "asset.h"

class File
{
public:
    void LoadFromFile();
    void SaveToFile();
    void Export();

private:
    enum
    {
        BILL = 0,
        TRANSACTION = 1,
        DEPOSIT_AND_LOAN = 2,
    };
};

#endif

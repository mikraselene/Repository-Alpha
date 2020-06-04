#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <cmath>
#include <iostream>

#include "date.h"
#include "bill.h"
#include "asset.h"

/*---------------------------------------------------------------------------
类名: File

描述:
    实现文件读写操作.
---------------------------------------------------------------------------*/
class File
{
public:
    enum
    {
        BILL = 0,
        TRANSACTION = 1,
        DEPOSIT_AND_LOAN = 2,
    };

    void LoadFromFile();
    void SaveToFile();
};

#endif

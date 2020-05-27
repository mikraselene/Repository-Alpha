#ifndef FILE_H
#define FILE_H

#include <fstream>
#include <cmath>
#include <iostream>

#include "date.h"
#include "bill.h"

class File
{
public:
    void LoadFromFile();
    void SaveToFile();
    void Export();
};

#endif

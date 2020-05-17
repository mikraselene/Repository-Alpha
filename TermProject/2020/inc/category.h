#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <list>

#include "text.h"

void AddDefault();
class Category
{
public:
    Category(std::string c);
    void Add();
    void Del();
    std::string GetCategory();

private:
    std::string category;
};

#endif

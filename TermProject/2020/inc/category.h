#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <list>

#include "text.h"

void AddDefault();
class Category
{
public:
    Category();
    Category(std::string c);
    void Add();
    void Del();
    std::string GetCategory();
    friend std::ostream &operator<<(std::ostream &, Category);

private:
    std::string category;
};

#endif

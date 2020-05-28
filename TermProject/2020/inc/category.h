#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <vector>

#include "text.h"

void AddDefault();
class Category
{
public:
    Category();
    Category(std::string c);
    void Add();
    void Del();
    operator std::string();
    friend std::ostream &operator<<(std::ostream &, Category);

private:
    std::string category;
};

#endif

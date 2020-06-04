#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <memory>
#include <vector>

#include "text.h"

void AddDefault();

/*---------------------------------------------------------------------------
类名: Category 

描述:
    自定义 Category 数据类型.
---------------------------------------------------------------------------*/
class Category : public std::enable_shared_from_this<Category>
{
public:
    Category();
    Category(const std::string &);
    void Add();
    void Del();
    operator std::string() const;
    friend std::ostream &operator<<(std::ostream &, const Category &);

private:
    std::string category;
};

#endif

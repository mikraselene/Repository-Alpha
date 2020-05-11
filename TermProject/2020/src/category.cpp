#include <iostream>
#include <list>
#include "../inc/category.h"
using namespace std;

list<Category *> pCategory;

Category::Category(string c)
{
    category = c;
}
void Category::Add()
{
    for (auto it : pCategory)
    {
        if (it->GetCategory() == this->GetCategory())
        {
            return;
        }
    }
    pCategory.push_back(this);
}
void Category::Del()
{
    for (auto it = pCategory.begin(); it != pCategory.end();)
    {
        if (*it == this)
        {
            pCategory.erase(it++);
            break;
        }
    }
}
string Category::GetCategory()
{
    return category;
}

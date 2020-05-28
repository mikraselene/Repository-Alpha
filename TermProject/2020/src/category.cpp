#include "../inc/category.h"

using namespace std;

vector<Category *> pCategory;

void AddDefault()
{
    using namespace NCategory;
    string defaultCategory[7] =
        {ROUTINE, FOOD, CLOTHING, EDUCATION, ENTERTAINMENT, INTERNET, MISCELLANEOUS};
    for (int i = 0; i < 7; i++)
    {
        Category *temp = new Category(defaultCategory[i]);
        temp->Add();
    }
}

Category::Category(string c)
{
    category = c;
}

Category::Category()
{
    category = "";
}
void Category::Add()
{
    for (auto it : pCategory)
    {
        if (string(*it) == category)
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

Category::operator string()
{
    return category;
}
ostream &operator<<(ostream &out, Category A)
{
    cout << A.category;
    return out;
}

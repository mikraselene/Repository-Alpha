#include "../inc/category.h"

std::vector<Category *> pCategory;

/*---------------------------------------------------------------------------
函数: void AddDefault()

目的:
    把默认类别添加到 pCategory 中.

调用: 
    Add();
---------------------------------------------------------------------------*/
void AddDefault()
{
    std::string defaultCategory[7] = {NCategory::ROUTINE,
                                      NCategory::FOOD,
                                      NCategory::CLOTHING,
                                      NCategory::EDUCATION,
                                      NCategory::ENTERTAINMENT,
                                      NCategory::INTERNET,
                                      NCategory::MISCELLANEOUS};
    for (int i = 0; i < 7; i++)
    {
        Category *temp = new Category(defaultCategory[i]);
        temp->Add();
    }
}

Category::Category()
{
    category = NCategory::ROUTINE;
}

Category::Category(const std::string &category)
{
    this->category = category;
}

/*---------------------------------------------------------------------------
函数: void Add()

目的:
    判断给定的类别是否在 pCategory 中, 如果不在, 则将其添加到 pCategory.
---------------------------------------------------------------------------*/
void Category::Add()
{
    for (auto it : pCategory)
    {
        if (std::string(*it) == category)
        {
            return;
        }
    }
    pCategory.push_back(this);
}

/*---------------------------------------------------------------------------
函数: void Del()

目的:
    从 pCategory 中删除给定的类别.
---------------------------------------------------------------------------*/
void Category::Del()
{
    for (auto it = pCategory.begin(); it != pCategory.end();)
    {
        if (*it == this)
        {
            pCategory.erase(it++);
            break;
        }
        else
        {
            it++;
        }
    }
}

Category::operator std::string() const
{
    return category;
}

std::ostream &operator<<(std::ostream &out, const Category &A)
{
    std::cout << A.category;
    return out;
}

#include <iostream>
#include <list>
#include <string>
using namespace std;
class Category;
list<Category *> pCategory;
class Category
{
public:
    Category(string c)
    {
        category = c;
    }
    void Add()
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
    void Del()
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
    string GetCategory()
    {
        return category;
    }

private:
    string category;
};

int main()
{
    for (int i = 0; i < 5; i++)
    {
        string a;
        cin >> a;
        Category *s = new Category(a);
        s->Add();
    }
    for (auto it : pCategory)
    {
        cout << it->GetCategory() << endl;
    }
}

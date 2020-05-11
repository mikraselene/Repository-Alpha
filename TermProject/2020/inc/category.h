#include <iostream>
using namespace std;

class Category
{
public:
    Category(string c);
    void Add();
    void Del();
    string GetCategory();

private:
    string category;
};
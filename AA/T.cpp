#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>

struct trie_node
{
    int count = 0;
    std::string val;
    std::map<const char, std::shared_ptr<trie_node>> children = {};
};

class trie
{
    using pointer = std::shared_ptr<trie_node>;

public:
    trie()
    {
        root = std::make_shared<trie_node>();
    }
    void insert(std::string word)
    {
        auto current_node = root;
        for (auto i : word)
        {
            auto node = current_node->children[i];
            if (node == nullptr)
            {
                node = std::make_shared<trie_node>();
                current_node->children[i] = node;
            }
            current_node = node;
        }
        current_node->count++;
        current_node->val = word;
    }
    auto search(std::string word) -> pointer
    {
        auto current_node = root;
        for (auto i : word)
        {
            auto node = current_node->children[i];
            if (node == nullptr)
            {
                return 0;
            }
            current_node = node;
        }
        return current_node;
    }
    auto count(std::string word) -> int
    {
        return search(word)->count;
    }
    void remove(std::string word)
    {
    }

private:
    std::shared_ptr<trie_node> root;
};

int main()
{
    std::vector<std::string> keywords =
        {"auto", "break", "case", "char",
         "const", "continue", "default", "do",
         "double", "else", "enum", "extern",
         "float", "for", "goto", "if",
         "int", "long", "register", "return",
         "short", "signed", "sizeof", "static",
         "struct", "switch", "typedef", "union",
         "unsigned", "void", "volatile", "while"};
    trie w;
    for (auto word : keywords)
    {
        w.insert(word);
    }
    std::string word;
    while (std::cin >> word)
    {
        std::cout << w.search(word) << std::endl;
    }
}

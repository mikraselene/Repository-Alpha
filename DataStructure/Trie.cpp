#include <string>
#include <vector>
#include <map>
#include <iostream>

class Trie
{
public:
    Trie(std::vector<std::string> word_list)
    {
        root = new TrieNode;
        for (auto word : word_list)
        {
            Add(word);
        }
    }
    void Add(std::string word)
    {
        TrieNode *current_node = root;
        for (auto i : word)
        {
            TrieNode *node = current_node->children[i];
            if (!node)
            {
                node = new TrieNode();
                current_node->children[i] = node;
            }
            current_node = node;
        }
        current_node->is_leaf = true;
    }
    bool Find(std::string word)
    {
        TrieNode *current_node = root;
        for (auto i : word)
        {
            TrieNode *node = current_node->children[i];
            if (!node)
            {
                return false;
            }
            current_node = node;
        }
        return current_node->is_leaf;
    }

private:
    struct TrieNode
    {
        std::string val;
        std::map<const char, TrieNode *> children = {};
        bool is_leaf = false;
    };
    TrieNode *root;
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
    Trie word_list(keywords);
    std::string word;
    while (std::cin >> word)
    {
        std::cout << (word_list.Find(word) ? "true" : "false") << std::endl;
    }
}

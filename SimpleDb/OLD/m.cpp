#include <iostream>
#include "bptree.hpp"
using namespace std;

struct Key
{
    bool operator<(const Key &that) const
    {
        return strcmp(this->key, that.key) < 0;
    }
    bool operator<=(const Key &that) const
    {
        return strcmp(this->key, that.key) <= 0;
    }
    bool operator==(const Key &that) const
    {
        return strcmp(this->key, that.key) == 0;
    }

    char key[64];
    int64_t page_id;
    std::ostream &operator<<(std::ostream &out)
    {
        out << key;
        return out;
    }
};

struct Record
{
    char key[64];
    uint32_t pos;
    uint32_t len;
};

constexpr uint64_t PAGE_SIZE = 1024 * 1024;
constexpr uint64_t BTREE_ORDER = 3;

int main()
{
    std::shared_ptr<Pager> pm =
        std::make_shared<Pager>("new.index", true);
    bptree<Key, BTREE_ORDER> bt(pm);
    Pager record_manager("new.bin", true);
    int64_t page_id;
    vector<string> str{
        "Let me not to the marriage of true minds",
        "Admit impediments. Love is not love",
        "Which alters when it alteration finds,",
        "Or bends with the remover to remove:",
        "O, no! it is an ever-fix`ed mark,",
        "That looks on tempests and is never shaken;",
        "It is the star to every wand'ring bark,",
        "Whose worth's unknown, although his heighth be taken.",
        "Love's not Time's fool, though rosy lips and cheeks",
        "Within his bending sickle's compass come;",
        "Love alters not with his brief hours and weeks,",
        "But bears it out even to the edge of doom:",
        "If this be error and upon me proved,",
        "I never writ, nor no man ever loved.",
        "In faith I do not love thee with mine eyes,",
        "For they in thee a thousand errors note;",
        "But `tis my heart that loves what they despise,",
        "Who in despite of view is pleased to dote.",
        "Nor are mine ears with thy tongue`s tune delighted;",
        "Nor tender feeling to base touches prone,",
        "Nor taste, nor smell, desire to be invited",
        "To any sensual feast with thee alone.",
        "But my five wits, nor my five senses can",
        "Dissuade one foolish heart from serving thee,",
        "Who leaves unswayed the likeness of a man,",
        "Thy proud heart`s slave and vassal wretch to be.",
        "Only my plague thus far I count my gain,",
        "That she that makes me sin awards me pain.",
    };
    vector<Record> v{};
    for (auto s : str)
    {
        Record r;
        r.pos = 0;
        snprintf(r.key, sizeof(r.key), "%s", s.c_str());
        v.push_back(r);
    }
    page_id = 1;
    for (auto i : v)
    {
        record_manager.save(page_id, &i);
        char that[64];
        Key k;
        snprintf(k.key, sizeof(k.key), "%s", i.key);
        k.page_id = page_id;
        bt.insert(k);
        page_id++;
    }

    printf("FIND `Who':\n");
    auto iter = bt.find_geq(Key{"Who", -1});

    Record s;
    record_manager.recover((*iter).page_id, &s);
    //std::cout << "KEY = " << s.key << '\n';

    for (int i = 0;; i++)
    {
        if (string((*iter).key).find(string("Who")) == 0)
        {
            std::cout << "KEY = " << (*iter).key << "\n";
            iter++;
            continue;
        }
        break;
    }
    printf("\n");
    //auto x = bt.find(Key{"f", -1});

    bt.print_tree();
}

//
// Created by jaoks on 5/17/20.
//
/*
#include <gtest/gtest.h>
#include "../src/btree.hpp"

clock_t clock_start_ = clock();
clock_t clock_end_ = clock();
#define TICK clock_start_ = clock()
#define TOCK clock_end_ = clock()
#define TIME_COST (double)(clock_end_ - clock_start_) / CLOCKS_PER_SEC


struct Key
{
    int64_t key;
    int64_t page_id;
    bool operator<(const Key &p) const { return this->key < p.key; }
    bool operator<=(const Key &p) const { return this->key <= p.key; }
    bool operator==(const Key &p) const { return this->key == p.key; }
};

struct TestStruct
{
    int64_t key;
    int64_t data;
};

std::ostream &
operator<<(std::ostream &out, Key &p)
{
    out << p.key;
    return out;
}

constexpr int64_t PAGE_SIZE = 1024;

struct BTreeTest : public ::testing::Test
{
};
*/
//
// Created by jaoks on 5/17/20.
//

#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <cstring>
#include "../src/bptree.hpp"

using std::string;
using std::vector;

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
};

constexpr uint64_t PAGE_SIZE = 1024 * 1024;
constexpr uint64_t BTREE_ORDER = 3;
// (PAGE_SIZE - (6 * sizeof(int64_t) + sizeof(Key))) /
// (sizeof(Key) + sizeof(int64_t));

struct BTreeTest : public ::testing::Test
{
};

TEST_F(BTreeTest, TestC)
{
    std::shared_ptr<Pager> pm =
        std::make_shared<Pager>("x.index", true);
    bptree<Key, BTREE_ORDER> bt(pm);
    Pager record_manager("students.bin", true);
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
    auto iter = bt.find_min_geq_than(Key{"Who", -1});

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

    /*
    for (; it_a != it_b; ++it_a)
    {
        auto pair = *it_a;
        Record s;
        record_manager.recover(pair.page_id, &s);
        std::cout << "KEY = " << s.key << '\n';
    }
    */
}

/*
TEST_F(BTreeTest, PrintTest)
{
    std::shared_ptr<Pager> pager =
        std::make_shared<Pager>("test1.index", true);
    btree<Key, 3> bt(pager);
    Pager record_manager("test1.bin", true);
    int64_t page_id;
    for (int i = 0; i < 10; i++)
    {
        TestStruct p{i, i / 2};
        page_id = i;
        record_manager.save(page_id, &p);
        bt.insert(Key{p.key, page_id});
    }
    bt.print_tree();
}

TEST_F(BTreeTest, OneMillionTest)
{
    std::shared_ptr<Pager> pager =
        std::make_shared<Pager>("test2.index", true);
    btree<Key, 60> bt(pager);
    Pager record_manager("test2.bin", true);
    int64_t page_id;

    TICK;
    for (int i = 0; i < 1; i++)
    {
        TestStruct p{i, i / 2};
        page_id = i;
        record_manager.save(page_id, &p);
        bt.insert(Key{p.key, page_id});
    }
    TOCK;
    printf("TIME COST (INSERT): %lf s\n\n", TIME_COST);
    TICK;
    auto iter = bt.find(Key{1, -1});
    TestStruct s;
    record_manager.recover((*iter).page_id, &s);
    printf("%lld\n", s.data);
    TOCK;
    printf("TIME COST (FIND): %lf s\n\n", TIME_COST);
    
    auto end = bt.find(Key{500420, -1});
    for (; iter != end; ++iter)
    {
        auto pair = *iter;
        TestStruct s;
        record_manager.recover(pair.page_id, &s);
        //std::cout << "ID " << s.key << '\n';
    }
    
}
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include "bptree.hpp"

using std::accumulate;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::stringstream;
using std::vector;

#define RESET "\e[0m"
#define BOLD "\e[1m"
#define FAINT "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define BLINKFAST "\e[6m"
#define NEGATIVE "\e[7m"
#define CONCEAL "\e[8m"
#define STRIKE "\e[9m"

#if 0
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define MAGENTA "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"
#else
#define BLACK "\e[90m"
#define RED "\e[91m"
#define GREEN "\e[92m"
#define YELLOW "\e[93m"
#define BLUE "\e[94m"
#define MAGENTA "\e[95m"
#define CYAN "\e[96m"
#define WHITE "\e[97m"
#endif

struct Key
{
    bool operator<(const Key &t) const { return strcmp(key, t.key) < 0; }
    bool operator<=(const Key &t) const { return strcmp(key, t.key) <= 0; }
    bool operator==(const Key &t) const { return strcmp(key, t.key) == 0; }

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

class Database
{
public:
    auto find(string value) -> int
    {
        Key k;
        snprintf(k.key, sizeof(k.key), "%s", value.c_str());
        k.page_id = -1;
        auto iter = bt->find_min_geq_than(k);
        Record s;
        record_manager->recover((*iter).page_id, &s);
        auto cnt = 0;
        for (cnt = 0;; cnt++)
        {
            if (string((*iter).key).find(value) == 0)
            {
                string str((*iter).key);
                cout << "[" << cnt + 1 << "] ";
                cout << BOLD GREEN << str.substr(0, value.size()) << RESET;
                cout << str.substr(value.size(), str.size() - value.size());
                cout << "\n";
                iter++;
                continue;
            }
            break;
        }
        return cnt;
    }
    void insert(Record r)
    {
        cout << r.key << endl;
        record_manager->save(page_id, &r);
        char that[64];
        Key k;
        snprintf(k.key, sizeof(k.key), "%s", r.key);
        k.page_id = page_id;
        bt->insert(k);
        page_id++;
    }
    void db_open(string name)
    {
        auto index = name + ".index";
        auto bin = name + ".bin";
        pm = std::make_shared<Pager>(index, true);
        bt = new bptree<Key, 3>(pm);
        record_manager = new Pager(bin, true);
    }
    int page_id = 1;
    shared_ptr<Pager> pm;
    Pager *record_manager;
    bptree<Key, 3> *bt;
};
Database db;

class CommandLine
{
    enum class MetaCommandResult
    {
        SUCCESS,
        UNRECOGNIZED_COMMAND,
    };
    enum class Statement
    {
        INSERT,
        SELECT,
        OPEN,
        EXIT,
        FIND,
        READ,
        UNKNOWN,
    };
    map<string, Statement> stmt{
        {"insert", Statement::INSERT},
        {"select", Statement::SELECT},
        {"open", Statement::OPEN},
        {"exit", Statement::EXIT},
        {"read", Statement::READ},
        {"find", Statement::FIND},
    };

public:
    CommandLine(string cmd, vector<string> a) : command(cmd), args(a)
    {
    }
    void execute()
    {
        execute_command(command_statement());
    }
    auto command_statement() -> Statement
    {
        return stmt.find(command) != stmt.end()
                   ? stmt[command]
                   : Statement::UNKNOWN;
    }
    void execute_command(Statement s)
    {
        switch (s)
        {
        case Statement::INSERT: // insert
        {                       // value...
            bool success = execute_insert();
            break;
        }
        case Statement::READ:
        {
            bool success = execute_read();
            break;
        }
        case Statement::SELECT: // select
        {
            bool success = execute_select();
            break;
        }
        case Statement::FIND: // find
        {
            bool success = execute_find();
            break;
        }
        case Statement::EXIT: // exit
        {
            cout << "So long..." << endl;
            exit(EXIT_SUCCESS);
        }
        case Statement::OPEN: // open
        {
            if (args.size() != 1)
            {
                cerr << "Too "
                     << (args.size() > 1 ? "many" : "few")
                     << " arguments." << endl;
                cerr << "Format: open `name`" << endl;
                break;
            }
            auto name = args[0];
            bool success = execute_open(name);
            cout << GREEN << "Database '" << name << "' is open."
                 << RESET << endl;
            break;
        }
        default:
        { /* code */
            break;
        }
        }
    }

private:
    bool execute_read()
    {
        return 1;
    }
    bool execute_open(string name)
    {
        db.db_open(name);
        return true;
    }
    bool execute_insert()
    {
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
        for (auto i : v)
        {
            db.insert(i);
        }
        return true;
    }
    bool execute_select()
    {
        cout << "SELECT OK" << endl;
        return true;
    }
    bool execute_find()
    {
        cout << "    ? > ";
        string str;
        getline(cin, str);
        if (str == "")
        {
            return false;
        }
        int r = db.find(str);
        cout << r << " record" << (r == 1 ? "" : "s") << " found." << endl;
        return true;
    }
    string command;
    vector<string> args;
};

void print_msg()
{
    printf("tssndb version 1.1.0\n");
    printf("i.e. too simple sometimes naive database\n");
}
void print_prompt()
{
    cout << "MDB >>> ";
}

int main()
{
    print_msg();
    while (true)
    {
        print_prompt();
        string str, command, argument;
        getline(cin, str);
        stringstream in(str);
        vector<string> args;
        in >> command;
        while (in >> argument)
        {
            args.push_back(argument);
        }
        CommandLine cmdln(command, args);
        cmdln.execute();
    }
}

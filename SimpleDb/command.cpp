#include <fmt/core.h>
#include <fmt/ostream.h>
#include <fmt/color.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>

#include "bptree.hpp"
#include "util.hpp"

#if defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
constexpr char MKDIR[] = "md";
constexpr char CLEAR[] = "cls";
#else
constexpr char MKDIR[] = "mkdir";
constexpr char CLEAR[] = "clear";
#endif

struct Key
{
    Key() {}
    explicit Key(int64_t id) : id(id) {}

    bool operator<(const Key &t) const { return strcmp(key, t.key) < 0; }
    bool operator<=(const Key &t) const { return strcmp(key, t.key) <= 0; }
    bool operator==(const Key &t) const { return strcmp(key, t.key) == 0; }
    std::ostream &operator<<(std::ostream &out)
    {
        out << key;
        return out;
    }

    char key[64];
    int64_t id = -1;
};

struct Record
{
    Record() {}
    Record(uint32_t pos, uint32_t len) : pos(pos), len(len) {}

    uint32_t pos = 0;
    uint32_t len = 0;
};

class Database
{
    friend class CommandLine;

protected:
    void find(std::string value)
    {
        if (!is_open())
        {
            throw database_not_open();
        }
        Key k(-1);
        snprintf(k.key, sizeof(k.key), "%s", value.c_str());
        auto iter = bt->find_geq(k);
        auto cnt = 0;
        std::vector<std::pair<Record, std::string>> results;
        while (true)
        {
            if (std::string(iter->key).find(value) == 0)
            {
                cnt++;
                std::string str(iter->key);
                auto num = fmt::format("[{}] ", cnt);
                auto found = str.substr(0, value.size());
                str = str.substr(value.size(), str.size() - value.size());
                fmt::print(fg(fmt::terminal_color::bright_blue), "{:>5}", num);
                fmt::print(fg(fmt::terminal_color::bright_green), found);
                fmt::print("{}\n", str);
                Record s;
                record_manager->recover(iter->id, &s);
                results.push_back({s, iter->key});
                iter++;
                continue;
            }
            break;
        }
        fmt::print("{} record(s) found.\n", cnt);
    }

    void insert(Record r, std::string key)
    {
        if (!is_open())
        {
            throw database_not_open();
        }
        record_manager->save(id, &r);
        char that[64];
        Key k(id);
        snprintf(k.key, sizeof(k.key), "%s", key.c_str());
        bt->insert(k);
        id++;
    }

    void select()
    {
        if (!is_open())
        {
            throw database_not_open();
        }
        bt->print();
    }

    void db_open(std::string name, bool new_file)
    {
        this->name = name;
        is_open = true;
        if (new_file)
        {
            system(fmt::format("{} database/{}", MKDIR, name).c_str());
        }
        auto idx = fmt::format("database/{0}/{0}_idx.bin", name);
        auto rec = fmt::format("database/{0}/{0}_rec.bin", name);
        page_manager = std::make_shared<Pager>(idx, new_file);
        record_manager = std::make_shared<Pager>(rec, new_file);
        bt = new BPTree<Key, 3>(page_manager);
        Record s;
        id = record_manager->get_id(&s);
    }

    void db_close()
    {
        is_open = false;
        name = "24601";
    }

    Property<bool> is_open{false};
    Property<std::string> name{"24601"};

private:
    int id = 0;
    std::shared_ptr<Pager> page_manager;
    std::shared_ptr<Pager> record_manager;
    BPTree<Key, 3> *bt;
};
Database db;

class CommandLine
{
    enum class Statement
    {
        INSERT,
        SELECT,
        OPEN,
        EXIT,
        FIND,
        READ,
        CREATE,
        WHOAMI,
        UNKNOWN,
    };
    enum class State
    {
        FAILURE,
        SUCCESS,
    };
    std::map<std::string, Statement> statement_map{
        {"insert", Statement::INSERT},
        {"select", Statement::SELECT},
        {"open", Statement::OPEN},
        {"exit", Statement::EXIT},
        {"read", Statement::READ},
        {"find", Statement::FIND},
        {"whoami", Statement::WHOAMI},
    };
    std::map<Statement, std::function<void(void)>> execute_map = {
        {Statement::CREATE, [&]() { execute_create(); }},
        {Statement::OPEN, [&]() { execute_open(); }},
        {Statement::READ, [&]() { execute_read(); }},
        {Statement::INSERT, [&]() { execute_insert(); }},
        {Statement::SELECT, [&]() { execute_select(); }},
        {Statement::FIND, [&]() { execute_find(); }},
        {Statement::WHOAMI, [&]() { execute_whoami(); }},
        {Statement::EXIT, [&]() { execute_exit(); }},
        {Statement::UNKNOWN, [&]() { execute_unknown(); }},
    };

public:
    CommandLine(std::string cmd, std::vector<std::string> a)
        : command(cmd), args(a) {}

    void execute()
    {
        execute_map[statement_map.find(command) != statement_map.end()
                        ? statement_map[command]
                        : Statement::UNKNOWN]();
    }

private:
    void execute_create()
    {
        try
        {
            if (args.size() != 1)
            {
                throw invalid_arguments_num(1, args.size());
                return;
            }
            auto name = args[0];
            db.db_open(name, true);
            fmt::print(fg(fmt::terminal_color::bright_green),
                       "Database {} is created.\n", name);
        }
        catch (invalid_arguments_num &e)
        {
            fmt::print(fg(fmt::terminal_color::bright_red), "{}", e.what());
            fmt::print("Expected {} argument(s), but got {}.\n",
                       e.expected_num, e.got_num);
            fmt::print(fg(fmt::terminal_color::bright_cyan), "Format: ");
            fmt::print("create [name]\n");
            return;
        }
    }

    void execute_read()
    {
    }

    void execute_open()
    {
        try
        {
            if (args.size() != 1)
            {
                throw invalid_arguments_num(1, args.size());
                return;
            }
            if (db.is_open())
            {
                fmt::print("Open a new database? (y/n) ");
                std::string str;
                getline(std::cin, str);
                if (str == "y")
                {
                    fmt::print(fg(fmt::terminal_color::bright_magenta),
                               "Database {} is closed.\n", db.name());
                    db.db_close();
                }
                else
                {
                    return;
                }
            }
            auto name = args[0];
            db.db_open(name, false);
            fmt::print(fg(fmt::terminal_color::bright_green),
                       "Database {} is open.\n", name);
        }
        catch (invalid_arguments_num &e)
        {
            fmt::print(fg(fmt::terminal_color::bright_red), "{}", e.what());
            fmt::print("Expected {} argument(s), but got {}.\n",
                       e.expected_num, e.got_num);
            fmt::print(fg(fmt::terminal_color::bright_cyan), "Format: ");
            fmt::print("open [name]\n");
            return;
        }
        catch (file_not_exist &e)
        {
            auto fn = e.file_name;
            fmt::print(fg(fmt::terminal_color::bright_cyan), "{}\n", e.what());
            fmt::print("Create it now? (y/n) ");
            std::string str;
            getline(std::cin, str);
            if (str == "y")
            {
                db.db_open(args[0], true);
                fmt::print(fg(fmt::terminal_color::bright_green),
                           "Database {} is created.\n", args[0]);
            }
            return;
        }
        catch (file_opening_error &e)
        {
            fmt::print(fg(fmt::terminal_color::bright_red),
                       "File corrupted.\n");
            fmt::print("Remove it now? (y/n) ");
            std::string str;
            getline(std::cin, str);
            if (str == "y")
            {
                auto fn = e.file_name;
                auto name = fn.substr(0, fn.find("."));
                auto res1 = remove(fmt::format("{}_rec.bin", name).c_str());
                auto res2 = remove(fmt::format("{}_idx.bin", name).c_str());
                (res1 == EOF || res2 == EOF)
                    ? fmt::print("This message should not be shown...\n")
                    : fmt::print(fg(fmt::terminal_color::bright_green),
                                 "File removed.\n");
            }
            return;
        }
    }

    void execute_insert()
    {
        clk.tick();
        int64_t id;
        std::vector<std::string> str{
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
        std::vector<std::pair<Record, std::string>> v{};
        int i = 0;
        for (auto s : str)
        {
            Record r(i, i * 2);
            i++;
            v.push_back({r, s});
        }
        for (auto i : v)
        {
            db.insert(i.first, i.second);
        }
        clk.tock();
        fmt::print("INSERT OK");
        clk.print_time_cost();
        fmt::print("\n");
    }

    void execute_select()
    {
        try
        {
            db.select();
            fmt::print("SELECT OK");
            fmt::print("\n");
        }
        catch (database_not_open &e)
        {
            fmt::print(fg(fmt::terminal_color::bright_red), "{}\n", e.what());
            fmt::print("Please open a database first.\n");
        }
    }

    void execute_find()
    {
        print_prompt2();
        std::string str;
        getline(std::cin, str);
        if (str == "")
        {
            //
        }
        db.find(str);
        fmt::print("FIND OK");
        fmt::print("\n");
    }

    void execute_whoami()
    {
        fmt::print("Who am I? ");
        fmt::print(fg(fmt::terminal_color::bright_blue),
                   "Database {}!\n", db.name());
    }

    void execute_exit()
    {
        db.db_close();
        fmt::print("So long...\n");
        exit(EXIT_SUCCESS);
    }

    void execute_unknown()
    {
        fmt::print(fg(fmt::terminal_color::bright_red),
                   "Command not found: ");
        fmt::print("{}\n", command);
    }

    std::string command;
    std::vector<std::string> args;
};

int main()
{
    print_msg();
    while (true)
    {
        print_prompt();
        std::string str, command, argument;
        getline(std::cin, str);
        std::stringstream in(str);
        std::vector<std::string> args;
        in >> command;
        while (in >> argument)
        {
            args.push_back(argument);
        }
        CommandLine cmdln(command, args);
        cmdln.execute();
    }
}

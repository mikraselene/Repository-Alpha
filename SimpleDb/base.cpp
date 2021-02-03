#include <iostream>
#include <sstream>
#include <vector>

#include "database.hpp"

using std::cin;
using std::cout;
using std::string;
using std::stringstream;
using std::vector;

enum class MetaCommandResult
{
    SUCCESS,
    UNRECOGNIZED_COMMAND,
};
enum class PrepareResult
{
    SUCCESS,
    UNRECOGNIZED_STATEMENT,
};
enum class Statement
{
    UNKNOWN,
    INSERT,
    SELECT,
} stmt;

using std::endl;
class CC
{
public:
    void print()
    {
        for (auto i : current_database_name_)
        {
            cout << i << endl;
        }
    }
    void add_database(string name)
    {
        current_database_name_.push_back(name);
    }

private:
    vector<string> current_database_name_;
};

class command_line
{
public:
    command_line() : command_(""), args_() {}
    command_line(string cmd, vector<string> args)
        : command_(cmd), args_(args) {}
    void execute()
    {
        if (*command_.begin() == '.')
        {
            do_meta_command();
        }
        else
        {
            prepare_statement();
            execute(stmt);
        }
    }
    auto do_meta_command() -> MetaCommandResult // TODO:
    {
        if (command_ == ".exit")
        {
            db.dbclose();
            exit(EXIT_SUCCESS);
        }
        else if (command_ == ".open")
        {
            string dbname = args_[0];
            db.dbopen(dbname.c_str());
            return MetaCommandResult::SUCCESS;
        }
        else if (command_ == ".close")
        {
            db.dbclose();
            return MetaCommandResult::SUCCESS;
        }
        else
        {
            return MetaCommandResult::UNRECOGNIZED_COMMAND;
        }
    }
    auto prepare_statement() -> PrepareResult
    {
        if (command_ == "insert")
        {
            stmt = Statement::INSERT;
            return PrepareResult::SUCCESS;
        }
        if (command_ == "select")
        {
            stmt = Statement::SELECT;
            return PrepareResult::SUCCESS;
        }
        return PrepareResult::UNRECOGNIZED_STATEMENT;
    }
    void execute(Statement s)
    {
        switch (s)
        {
        case Statement::INSERT:
        {
            string key;
            int p1, p2;
            cout << "INSERT(" << db.dbname() << "): \n";
            cin >> key >> p1 >> p2; // TODO:
            getchar();
            db.table()->insert(Row(key, p1, p2));
            break;
        }
        case Statement::SELECT:
        {
            cout << "SELECT(" << db.dbname() << "): \n";
            db.table()->select();
            break;
        }
        default:
        {
            cout << "WHAT??\n";
            break;
        }
        }
    }

private:
    string command_;
    vector<string> args_;
};

void print_msg()
{
    printf("tssndb version 1.0.0\n");
    printf("i.e. too simple sometimes naive database\n");
}
void print_prompt()
{
    cout << "TSSN > ";
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
        command_line cmdln(command, args);
        cmdln.execute();
    }
}

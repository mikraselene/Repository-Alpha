#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

enum class meta_command_result
{
    SUCCESS,
    UNRECOGNIZED_COMMAND,
};
enum class prepare_result
{
    SUCCESS,
    UNRECOGNIZED_STATEMENT,
};
enum class statement
{
    UNKNOWN,
    INSERT,
    SELECT,
} stmt;

/*
readxml {filename}
save
search byauthor {author}
search byauthor like {author}
search byauthor regex {regex author}
search bytitle {title}
search bytitle like {title}
search bytitle regex {regex title}
co_author {author}
keyword list
keyword {year}
.exit
.help
.clear
*/

class command_line
{
public:
    command_line() : command_(""), args_() {}
    command_line(string cmd, vector<string> args) : command_(cmd), args_(args) {}
    void execute()
    {
        if (*command_.begin() == '.')
        {
            do_meta_command();
        }
        else
        {
            prepare_statement();
            execute_statement(stmt);
        }
    }
    auto do_meta_command() -> meta_command_result // TODO:
    {
        if (command_ == ".exit")
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            return meta_command_result::UNRECOGNIZED_COMMAND;
        }
    }
    auto prepare_statement() -> prepare_result
    {
        if (command_ == "insert")
        {
            stmt = statement::INSERT;
            return prepare_result::SUCCESS;
        }
        if (command_ == "select")
        {
            stmt = statement::SELECT;
            return prepare_result::SUCCESS;
        }
        return prepare_result::UNRECOGNIZED_STATEMENT;
    }
    void execute_statement(statement s)
    {
        switch (s)
        {
        case statement::INSERT:
        {
            // TODO: DO INSERT
            cout << "INSERT\n";
            break;
        }
        case statement::SELECT:
        {
            // TODO: DO SELECT
            cout << "SELECT\n";
            break;
        }
        default:
        {
            cout << "?\n";
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
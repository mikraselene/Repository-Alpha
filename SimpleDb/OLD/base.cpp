#include <iostream>
#include <sstream>
#include <vector>

#include "database.hpp"
//#include "read_xml_file.hpp"

using std::cin;
using std::cout;
using std::endl;
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
    INSERT,
    SELECT,
    UNKNOWN,
} stmt;

// TODO: 注释没写好.
class CommandLine
{
public:
    CommandLine() : command_(""), args_() {}
    CommandLine(string cmd, vector<string> args)
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
        if (command_ == ".test")
        {
            db.dbopen("test.db");
            //read_xmlfile("vs.xml");
            return MetaCommandResult::SUCCESS;
        }
        if (command_ == ".exit") // format: .exit
        {
            db.dbclose();
            exit(EXIT_SUCCESS);
        }
        else if (command_ == ".open") // format: .open [sample_dbname].db
        {
            string dbname = args_[0];
            db.dbopen(dbname.c_str());
            return MetaCommandResult::SUCCESS;
        }
        else if (command_ == ".read") // format: .read [sample_xmlname].xml
        {
            assert(db.is_open());
            string xmlname = args_[0];
            //read_xmlfile(xmlname.c_str());
            return MetaCommandResult::SUCCESS;
        }
        else
        {
            cout << "UNKNOWN" << endl;
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
        case Statement::INSERT: // insert manually
        {
            string key;
            int p1, p2;
            cout << "INSERT(" << db.dbname() << "): \n";
            cin >> key >> p1 >> p2; // TODO:
            getchar();
            db.table()->insert(key, Row(p1, p2));
            break;
        }
        case Statement::SELECT: // print all the data
        {
            cout << "SELECT(" << db.dbname() << "): \n";
            db.table()->select();
            break;
        }
        default:
        {
            cout << "UNKNOWN" << endl;
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
    cout << "DB > ";
}

/* 使用例:

tssndb version 1.0.0
i.e. too simple sometimes naive database
DB > .open sample.db
    (x1 如果不存在给定的文件, 会新建一个.)
DB > select
SELECT(sample.db): 
    (x2 现在还没有数据, 所以什么都不显示.)
DB > insert
INSERT(sample.db): 
sample_key 114 514
    (x3 我插入了一条数据, 其实用不上手动插入的.)
DB > select
SELECT(sample.db): 
sample_key                                                     , 114, 514
    (x4 现在有一条数据, key 的长度强制设置为 64.)
DB > .read small.xml
    (x5 读取给定的 xml 文件, 对文件格式有要求, 所以现在先用格式正确的文件, 之后再优化.)
DB > select
SELECT(sample.db): 
sample_key                                                     , 114, 514
Spectre Attacks: Exploiting Speculative Execution.             , 6, 570
Meltdown                                                       , 571, 1095
Computer Science Curricula 2013                                , 1096, 1344

...

Machine Translation Demonstration                              , 14533, 14851
Implementation Aspects of a Natural Language Understanding Sy.., 14852, 15202
    (x6 读取出来的数据加在刚才的数据后. 似乎还支持 Unicode 字符方面还存在一些问题?)
DB > .exit
    (x7 关闭就是保存, 下次开启可以直接读 db 文件, 不用再读 xml 文件了.)

*/
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

#ifndef SIMPLEDB_CODE_READ_XML_FILE_HPP_
#define SIMPLEDB_CODE_READ_XML_FILE_HPP_

#include <libxml/SAX2.h>

#include <map>
#include <utility>
#include <string>
#include <vector>

#include "database.hpp"

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

using xstr = const xmlChar *;
using position = pair<uint32_t, uint32_t>;

position pos = {6, 0};

enum class ParserState
{
    AUTHOR,
    TITLE,
    OTHER,
};
// 一个状态机, 用于表明当前需要插入数据的归属 (是属于 author 或是属于 title).
ParserState state = ParserState::OTHER;

// 这个是根据状态机的状态来决定选用哪个 vector.
// 要插入其他数据的化得添加代码.
// 例如, 想要添加日期就在 ParserState 里加 DATE 状态, 再在下面加一行:
// vector<string> &time_key_list = key_list[ParserState::TIME];
map<ParserState, vector<string>> key_list;
vector<string> &title_key_list = key_list[ParserState::TITLE];
vector<string> &author_key_list = key_list[ParserState::AUTHOR];

// 表明当前在 DOM 树中的层数.
int layer_count;

struct file_opening_error : public std::exception
{
    const char *what() const throw() { return "file opening error"; }
};
struct file_reading_error : public std::exception
{
    const char *what() const throw() { return "file reading error"; }
};
struct xml_parsing_error : public std::exception
{
    const char *what() const throw() { return "xml parsing error"; }
};

// 插入是在这三个函数里. key 存在 key_list 内, 其他部分可以不用考虑.
// 如果要用图或者其他数据结构来存 key-value 之类的数据, 就在这里添加代码.
// 这里设计得好像还不够好, 以后有需求再改.

// 这里是读取 <text>...</text> 然后看 text 是作者还是标题.
// 如果要存其他的 (比如日期) 就在 ParserState 里面添加状态,
// 然后添加一个 vector<string>, 再在这里修改代码, 可能用 switch 比较方便.
static void on_start_element(void *ctx, xstr name, xstr *attrs)
{
    layer_count++;
    state = strcmp((const char *)name, "author") == 0
                ? ParserState::AUTHOR
                : strcmp((const char *)name, "title") == 0
                      ? ParserState::TITLE
                      : ParserState::OTHER;
}

// 这里是读到最后, 把数据插入到数据库的表中.
// 如果想插入其他数据, 直接添加代码就可以.
static void on_end_element(void *ctx, xstr name)
{
    layer_count--;
    if (layer_count == 1)
    {
        pos.second = xmlSAX2GetColumnNumber(ctx) - 2;
        for (auto it : author_key_list)
        {
            // author_map.insert({it, pos});
            // db.table()->insert(Row(it, pos.first, pos.second));
        }
        for (auto it : title_key_list)
        {
            // title_map.insert({it, pos});
            db.table()->insert(Row(it, pos.first, pos.second));
        }
        pos.first = pos.second + 1;
        author_key_list.clear();
        title_key_list.clear();
    }
}

// 这里是读取正文, 根据 ParserState 的状态来决定往哪个 vector 里插入数据.
static void on_characters(void *ctx, xstr ch, int len)
{
    auto push_back_helper = [](string k) {
        // 这里保证插入的 key 最大长度为 KEY_LENGTH, 现在设置为 64.
        if (k.size() > database::KEY_LENGTH)
        {
            k = k.substr(0, database::KEY_LENGTH - 3) + "...";
        }
        k.resize(database::KEY_LENGTH, ' ');
        assert(k.size() == database::KEY_LENGTH);
        key_list[state].push_back(k);
    };
    string key((const char *)ch, len);
    if (state != ParserState::OTHER)
    {
        // 避免标题过长, 检查数据后发现用 "-" 和 ";" 来分割标题是合理的.
        while (key.find(" - ") != key.npos || key.find("; ") != key.npos)
        {
            bool flag = key.find(" - ") < key.find("; ");
            auto p = key.find(flag ? " - " : "; ");
            auto temp = key.substr(0, p);
            push_back_helper(temp);
            key.erase(0, p + (flag ? 3 : 2));
        }
        push_back_helper(key);
        state = ParserState::OTHER;
    }
}

// 利用 libxml 读取 xml 文件.
void read_xmlfile(const char *file_name)
{
    assert(db.is_open());
    FILE *file = fopen(file_name, "r");
    layer_count = 0;
    char chars[1024];
    try
    {
        if (file == nullptr)
        {
            throw file_opening_error();
        }
        auto res = fread(chars, 1, 4, file);
        if (res <= 0)
        {
            throw file_reading_error();
        }
        auto sax_hander = [&] {
            xmlSAXHandler sax_hander;
            memset(&sax_hander, 0, sizeof(xmlSAXHandler));
            sax_hander.initialized = XML_SAX2_MAGIC;
            sax_hander.startElement = on_start_element;
            sax_hander.endElement = on_end_element;
            sax_hander.characters = on_characters;
            return sax_hander;
        }();
        auto ctxt =
            xmlCreatePushParserCtxt(&sax_hander, nullptr, chars, res, nullptr);
        while ((res = fread(chars, 1, sizeof(chars), file)) > 0)
        {
            if (xmlParseChunk(ctxt, chars, res, 0))
            {
                xmlParserError(ctxt, "xmlParseChunk");
                throw xml_parsing_error();
            }
        }
        xmlParseChunk(ctxt, chars, 0, 1);
        xmlFreeParserCtxt(ctxt);
        xmlCleanupParser();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    fclose(file);
}

#endif // SIMPLEDB_CODE_READ_XML_FILE_HPP_

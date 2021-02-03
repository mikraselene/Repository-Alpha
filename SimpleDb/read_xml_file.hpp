#ifndef SIMPLEDB_READ_XML_FILE_HPP_
#define SIMPLEDB_READ_XML_FILE_HPP_

#include <libxml/SAX2.h>

#include <map>
#include <utility>
#include <string>
#include <vector>

#include "util.hpp"

#define MATCH(y, x) strcmp((const char *)y, x) == 0
#define KEY_MAX_SIZE 64

using std::map;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

using xstr = const xmlChar *;
using position = pair<uint32_t, uint32_t>;

multimap<string, position> title_map;
multimap<string, position> author_map;
position pos = {6, 0};
enum class parser_state
{
    AUTHOR,
    TITLE,
    OTHER,
};
parser_state state = parser_state::OTHER;
map<parser_state, vector<string>> key_list;
vector<string> &title_key_list = key_list[parser_state::TITLE];
vector<string> &author_key_list = key_list[parser_state::AUTHOR];
int layer_count;

int max_key_size = 0;

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

static void on_start_element(void *ctx, xstr name, xstr *attrs)
{
    layer_count++;
    state = MATCH(name, "author") ? parser_state::AUTHOR
                                  : MATCH(name, "title") ? parser_state::TITLE
                                                         : parser_state::OTHER;
}
static void on_end_element(void *ctx, xstr name)
{
    layer_count--;
    if (layer_count == 1)
    {
        pos.second = xmlSAX2GetColumnNumber(ctx) - 2;
        for (auto it : author_key_list)
        {
            author_map.insert({it, pos});
        }
        for (auto it : title_key_list)
        {
            title_map.insert({it, pos});
        }
        pos.first = pos.second + 1;
        author_key_list.clear();
        title_key_list.clear();
        author_map.clear();
        title_map.clear();
    }
}
uint32_t cnt = 0;
static void on_characters(void *ctx, xstr ch, int len)
{
    auto push_back_helper = [](string k) {
        if (k.size() > KEY_MAX_SIZE)
        {
            k = k.substr(0, KEY_MAX_SIZE - 3) + "...";
        }
        k.resize(KEY_MAX_SIZE, ' ');
        if (k.size() != 64)
        {
            exit(1);
        }
        key_list[state].push_back(k);
        cnt++;
    };
    string key((const char *)ch, len);
    if (state != parser_state::OTHER)
    {
        while (key.find(" - ") != key.npos || key.find("; ") != key.npos)
        {
            bool flag = key.find(" - ") < key.find("; ");
            auto p = key.find(flag ? " - " : "; ");
            auto temp = key.substr(0, p);
            push_back_helper(temp);
            key.erase(0, p + (flag ? 3 : 2));
        }
        push_back_helper(key);
        state = parser_state::OTHER;
    }
}

void read_xmlfile(const char *file_name)
{
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

#endif // SIMPLEDB_READ_XML_FILE_HPP_

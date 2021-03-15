#include "read_xml_file.hpp"
using std::cout;
using std::endl;

int main()
{
    TICK;
    read_xmlfile("ndblp.xml");
    cout << "0";
    for (int i = 0; i < 64 - 3; i++)
    {
        cout << " ";
    }
    cout << "63";
    cout << "    64    71" << endl;
    for (int i = 0; i < 64; i++)
    {
        cout << "-";
    }
    cout << "    --------" << endl;
    for (auto i : title_map)
    {
        cout << i.first
             << "    ["
             << i.second.first
             << ", "
             << i.second.second
             << "]" << endl;
    }
    cout << cnt << endl;
    TOCK;
    PRINT_TIME_COST;
}

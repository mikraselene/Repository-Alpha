#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

#define OUT(xx) copy(xx.begin(), xx.end(), ostream_iterator<string>(cout, " "))

/*
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
*/

/*
    void GetFollow()
    {
        for (auto it : productions)
        {
            string left = it.first;
            set<string> right = it.second;
            for (auto ii : right)
            {
                string temp = ii;
                for (int i = 0; i < temp.size(); i++)
                {
                    if (vt.find(temp.substr(i, 1)) != vt.end())
                    {
                        continue;
                    }
                    else if (i + 1 < temp.size() && temp[i + 1] == '\'')
                    {
                        if (vt.find(temp.substr(i + 2, 1)) != vt.end())
                        {
                            follow_set[temp.substr(i, 2)].insert(temp.substr(i + 2, 1));
                            i++;
                        }
                        else
                        {
                            string x = temp.substr(i + 2, (i + 3 < temp.size() && temp[i + 3] == '\'') ? 2 : 1);
                            set<string> ff = first_set[x];
                            for (auto nn : ff)
                            {
                                if (nn != "#")
                                {
                                    follow_set[temp.substr(i, 2)].insert(nn);
                                }
                            }
                        }
                    }
                    else
                    {
                    }
                }
            }
        }
        // TODO:
    }
*/

class Grammar
{
public:
    Grammar(vector<string> productions_in_string)
    {
        set<string> temp_productions;
        for (auto p : productions_in_string)
        {
            temp_productions.insert(p);
            follow_set[p.substr(0, 1)].insert("$");
        }
        for (auto p : temp_productions)
        {
            for (auto x : p)
            {
                int position = p.find("->");
                string left = p.substr(0, position);
                string right = p.substr(position + 2);
                set<string> temp_set;
                string next_production = "";
                for (auto j : right)
                {
                    j == '|' ? temp_set.insert(next_production), next_production = ""
                             : next_production += j;
                }
                temp_set.insert(next_production);
                productions.insert({left, temp_set});
            }
            for (int i = 0; i < p.size(); i++)
            {
                if (p[i] == '-' || p[i] == '>' || p[i] == '|')
                {
                    continue;
                }
                p[i] >= 'A' && p[i] <= 'Z'
                    ? p[i + 1] == '\''
                          ? vn.insert(p.substr(i++, 2))
                          : vn.insert(p.substr(i, 1))
                    : vt.insert(p.substr(i, 1));
            }
        }
        OUT(vn);
        cout << endl;
        OUT(vt);
        cout << endl;
    }
    void GetFirst()
    {
        function<set<string>(string)> get_first = [&](string s) -> set<string> {
            if (productions.count(s))
            {
                set<string> temp = productions[s];
                for (auto str : temp)
                {
                    cout << str << endl;
                    if (str == "#")
                    {
                        first_set[s].insert("#");
                    }
                    else
                    {
                        int has_epsilon_in_all = true;
                        for (int i = 0; i < str.size(); i++)
                        {
                            bool has_epsilon = false;
                            auto func = [&](set<string> temp_set) {
                                for (auto i : temp_set)
                                {
                                    if (i == "#")
                                    {
                                        has_epsilon = true;
                                    }
                                    else
                                    {
                                        first_set[s].insert(i);
                                    }
                                }
                            };
                            if (str[i + 1] == '\'')
                            {
                                func(get_first(str.substr(i++, 2)));
                            }
                            else if (vn.find(str.substr(i, 1)) != vn.end())
                            {
                                func(get_first(str.substr(i, 1)));
                            }
                            else
                            {
                                first_set[s].insert(str.substr(i, 1));
                            }
                            if (has_epsilon == false)
                            {
                                has_epsilon_in_all = false;
                                break;
                            }
                        }
                        if (has_epsilon_in_all == true)
                        {
                            first_set[s].insert("#");
                        }
                    }
                }
            }
            return first_set[s];
        };
        for (auto prod : productions)
        {
            get_first(prod.first);
        }
        for (auto it : first_set)
        {
            cout << "FIRST(" << it.first << "): ";
            OUT(it.second);
            cout << endl;
        }
    }

private:
    map<string, set<string>> productions;
    set<string> vt;
    set<string> vn;
    map<string, set<string>> first_set;
    map<string, set<string>> follow_set;
};

int main()
{
    vector<string> prod = {
        "E->TE'",
        "E'->+TE'|#",
        "T->FT'",
        "T'->*FT'|#",
        "F->(E)|i",
    };
    Grammar g(prod);
    g.GetFirst();
}

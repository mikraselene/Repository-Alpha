#include <iostream>
#include <map>
#include <set>
#include <list>
#include <vector>
using namespace std;

#define OUT(xx) copy(xx.begin(), xx.end(), ostream_iterator<int>(cout, " "))

#define RULE(l, ...)    \
    {                   \
        l,              \
        {               \
            __VA_ARGS__ \
        }               \
    }

#define TO(...)     \
    {               \
        __VA_ARGS__ \
    }

/*
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
*/

enum
{
    E,
    T,
    Ex,
    Tx,
    PLUS,
    F,
    STAR,
    L,
    R,
    id,
    epsilon,
};
/*
E->TE'
E'->+TE'|#
T->FT'
T'->*FT'|#
F->(E)|i
*/
vector<string> name = {"E", "T", "E'", "T'", "+", "F", "*", "(", ")", "id", "#"};

/*
*/
class Grammar
{
public:
    Grammar()
    {
        vt = {STAR, PLUS, id, L, R, epsilon};
        vn = {E, T, Ex, Tx, F};
        productions = {
            RULE(E,
                 TO(T, Ex)),
            RULE(Ex,
                 TO(PLUS, T, Ex),
                 TO(epsilon)),
            RULE(T,
                 TO(F, Tx)),
            RULE(Tx,
                 TO(STAR, F, Tx),
                 TO(epsilon)),
            RULE(F,
                 TO(L, E, R),
                 TO(id)),
        };
    }
    void GetFirst()
    {
        function<set<int>(int)> get_first = [&](int s) -> set<int> {
            if (productions.count(s))
            {
                set<list<int>> production_set = productions[s];
                for (auto production : production_set)
                {
                    if (*production.begin() == epsilon)
                    {
                        first_set[s].insert(epsilon);
                    }
                    else
                    {
                        int has_epsilon_in_all = true;
                        for (auto i : production)
                        {
                            bool has_epsilon = false;
                            if (vn.find(i) != vn.end())
                            {
                                for (auto j : get_first(i))
                                {
                                    if (j == epsilon)
                                    {
                                        has_epsilon = true;
                                    }
                                    else
                                    {
                                        first_set[s].insert(j);
                                    }
                                }
                            }
                            else
                            {
                                first_set[s].insert(i);
                            }
                            if (has_epsilon == false)
                            {
                                has_epsilon_in_all = false;
                                break;
                            }
                        }
                        if (has_epsilon_in_all == true)
                        {
                            first_set[s].insert(epsilon);
                        }
                    }
                }
            }
            return first_set[s];
        };
        for (auto p : productions)
        {
            get_first(p.first);
        }
        for (auto f : first_set)
        {
            cout << "FIRST(" << name[f.first] << "): ";
            for (auto i : f.second)
            {
                cout << name[i] << " ";
            }
            cout << endl;
        }
    }
    void GetFollow()
    {
    }

private:
    map<int, set<list<int>>> productions;
    set<int> vt;
    set<int> vn;
    map<int, set<int>> first_set;
    map<int, set<int>> follow_set;
};

int main()
{
    Grammar x;
    x.GetFirst();
}
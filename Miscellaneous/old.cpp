#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "lexical.hpp"

using namespace std;
#define il inline
#define fi first
#define se second
#define nas 61
#define inv 62

enum VarType
{
    VT_INT,
    VT_STRING,
    VT_BOOL,
};
map<string, int> variable_list;

class Singleton
{
    friend class Parser;
    friend class Quadruple;

public:
    Singleton()
    {
        this->content = "";
        this->type = -1;
        this->index_in_list = -1;
    }
    Singleton(string content)
    {
        this->content = content;
        this->type = -1;
        this->index_in_list = -1;
    }
    Singleton(const char *content)
    {
        this->content = content;
        this->type = -1;
        this->index_in_list = -1;
    }
    Singleton(string content, int type)
    {
        this->content = content;
        this->type = type;
        this->index_in_list = type == ID ? variable_list.size() : -1;
    }
    Singleton(Token *token)
    {
        this->content = (const char *)token->info.name;
        this->type = token->id;
        this->index_in_list = token->id == ID ? variable_list.size() : -1;
    }
    void SetContent(string s) { content = s; }
    void SetContent(int s) { content = to_string(s); }

protected:
    Token *token;
    string content;
    int other;
    int type;
    int index_in_list;
    VarType var_type;
};

class Quadruple // = Three-Address Code
{
    friend class Parser;

public:
    Quadruple(Singleton op, Singleton arg1, Singleton arg2, Singleton result)
    {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->result = result;
    }
    void Print()
    {
        cout << "(" << op.content << ", " << arg1.content << ", " << arg2.content << ", " << result.content << ")" << endl;
    }

protected:
    Singleton op;
    Singleton arg1;
    Singleton arg2;
    Singleton result;
};

class compiler
{
    typedef pair<int, int> pii;
    struct pp
    {
        pii val, pos;
        pp(pii a, pii b)
        {
            val = a, pos = b;
        }
    };
    map<string, int> ht;
    map<string, int> idx;
    vector<pp> vec;
    int tot;
    il void init()
    {
        ht.clear(), idx.clear(), vec.clear(), tot = 0;
        string s[35] = {
            "and", "array", "begin", "bool", "call", "case", "char", "constant", "dim", "do",
            "else", "end", "false", "for", "if", "input", "integer", "not", "of", "or",
            "output", "procedure", "program", "read", "real", "repeat", "set", "stop", "then", "to",
            "true", "until", "var", "while", "write"};
        string t[22] = {
            "(", ")", "*", "*/", "+", ",", "-", ".", "..", "/", "/*", ":", ":=",
            ";", "<", "<=", "<>", "=", ">", ">=", "[", "]"};
        for (int i = 0; i < 35; i++)
            ht[s[i]] = i + 1;
        for (int i = 0; i < 22; i++)
            ht[t[i]] = i + 39;
    }
    il bool ischar(char c)
    {
        return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
    }
    il bool isnum(char c)
    {
        return c >= '0' && c <= '9';
    }
    il int judge(string a)
    {
        if (ht.find(a) != ht.end())
            return ht[a];
        int sz = a.size();
        if (a[0] == '\'')
        {
            for (int i = 1; i < sz - 1; i++)
                if (a[i] == '\'')
                    return 62;
            if (a[sz - 1] != '\'')
                return 61;
            else
            {
                if (!idx[a])
                {
                    idx[a] = ++tot;
                    name[tot] = a;
                }
                return 38;
            }
        }
        if (isnum(a[0]))
        {
            for (int i = 0; i < sz; i++)
                if (!isnum(a[i]))
                    return 62;
            if (!idx[a])
            {
                idx[a] = ++tot;
                name[tot] = a;
            }
            return 37;
        }
        if (ischar(a[0]))
        {
            for (int i = 0; i < sz; i++)
                if (!isnum(a[i]) && !ischar(a[i]))
                    return 62;
            if (!idx[a])
            {
                idx[a] = ++tot;
                name[tot] = a;
            }
            return 36;
        }
        return 62;
    }
    il void show_title()
    {
        cout << "This program is made by Amori\n";
        cout << "Class: 2017 Computer Science 1\n";
        cout << "Sno: 201730615155\n";
    }
    il void judge_helper(string tp, int line, int pos)
    {
        int id = judge(tp);
        int iid = 0;
        if (id >= 36 && id <= 38)
            iid = idx[tp];
        vec.push_back(pp(pii(id, iid), pii(line, pos)));
    }
    il vector<pii> out(bool ret)
    {
        cout << "\nAnalysis:\n\n";
        vector<pii> error1;
        vector<pii> error2;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].val.fi == nas)
                error2.push_back(vec[i].pos);
            if (vec[i].val.fi == inv)
                error1.push_back(vec[i].pos);
        }
        int st = 0;
        int mark = -1;
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i].val.fi == 49 && st == 0)
                st = 1;
            if (vec[i].val.fi == 42)
            {
                if (st == 1)
                    st = 0;
                else
                {
                    mark = i;
                    break;
                }
            }
        }
        bool flag = true;
        if (!error1.empty())
        {
            flag = false;
            cout << "Error1 occurs (invalid input) at: \n";
            for (int i = 0; i < error1.size(); i++)
                cout << "Line " << error1[i].fi << ' ' << "Word " << error1[i].se << endl;
        }
        if (!error2.empty())
        {
            flag = false;
            cout << "Error2 occurs (expected a ' ) at: \n";
            for (int i = 0; i < error2.size(); i++)
                cout << "Line " << error2[i].fi << ' ' << "Word " << error2[i].se << endl;
        }
        if (mark != -1)
        {
            flag = false;
            cout << "Error3 occurs (Start with '*/') at:\n";
            cout << "Line " << vec[mark].pos.fi << ' ' << "Word " << vec[mark].pos.se << endl;
        }
        if (st == 1)
        {
            flag = false;
            cout << "Error3 occurs (expected a '*/' at end)\n";
        }
        if (flag)
        {
            if (ret)
            {
                int cnt = 0;
                st = 0;
                for (int i = 0; i < vec.size(); i++)
                {
                    if (vec[i].val.fi == 49)
                        st = 1;
                    if (vec[i].val.fi == 42)
                    {
                        st = 0;
                        continue;
                    }
                    if (st)
                        continue;
                    cnt++;
                    cout << '(' << vec[i].val.fi << ',';
                    if (vec[i].val.se == 0)
                        cout << "-) ";
                    else
                        cout << vec[i].val.se << ") ";
                    if (cnt % 5 == 0)
                        cout << endl;
                }
                cout << endl;
            }
            vector<pii> rett;
            int cnt = 0;
            st = 0;
            for (int i = 0; i < vec.size(); i++)
            {
                if (vec[i].val.fi == 49)
                    st = 1;
                if (vec[i].val.fi == 42)
                {
                    st = 0;
                    continue;
                }
                if (st)
                    continue;
                pii temp(vec[i].val.fi, -1);
                if (vec[i].val.se == 0)
                    ;
                else
                    temp.se = vec[i].val.se;
                rett.push_back(temp);
            }
            return rett;
        }
        return error1;
    }

public:
    map<int, string> name;
    char filename[105];
    vector<pii> run(bool f)
    {
        init();
        show_title();
        string s;
        cout << "Please input the number of test case:(1/2/3/4)\n";
        int x;
        cin >> x;
        strcpy(filename, "test#.txt");
        filename[4] = x + '0';
        freopen(filename, "r", stdin);
        bool flag = 0;
        int line = 0;
        while (getline(cin, s))
        {
            line++;
            if (flag)
            {
                flag = false;
                continue;
            }
            int sz = s.size();
            string tp;
            int pos = 0;
            for (int i = 0; i < sz; i++)
            {
                if (s[i] != ' ')
                {
                    string x;
                    int num = 0;
                    x.push_back(s[i]);
                    if (ht.find(x) != ht.end())
                        num = ht[x];
                    if (num >= 39)
                    {
                        if (!tp.empty())
                            judge_helper(tp, line, ++pos), tp.clear();
                        if (i != sz - 1)
                        {
                            i++;
                            if (num == 41 && s[i] == '/')
                                vec.push_back(pp(pii(42, 0), pii(line, ++pos)));
                            else if (num == 46 && s[i] == '.')
                                vec.push_back(pp(pii(47, 0), pii(line, ++pos)));
                            else if (num == 48 && s[i] == '*')
                                vec.push_back(pp(pii(49, 0), pii(line, ++pos)));
                            else if (num == 50 && s[i] == '=')
                                vec.push_back(pp(pii(51, 0), pii(line, ++pos)));
                            else if (num == 53 && s[i] == '=')
                                vec.push_back(pp(pii(54, 0), pii(line, ++pos)));
                            else if (num == 53 && s[i] == '>')
                                vec.push_back(pp(pii(55, 0), pii(line, ++pos)));
                            else if (num == 57 && s[i] == '=')
                                vec.push_back(pp(pii(58, 0), pii(line, ++pos)));
                            else
                            {
                                i--;
                                vec.push_back(pp(pii(num, 0), pii(line, ++pos)));
                            }
                        }
                        else
                            vec.push_back(pp(pii(num, 0), pii(line, ++pos)));
                    }
                    else
                        tp.push_back(s[i]);
                }
                else if (!tp.empty())
                    judge_helper(tp, line, ++pos), tp.clear();
            }
            if (!tp.empty())
                judge_helper(tp, line, ++pos), tp.clear();
        }
        return out(f);
    }
};

#define error exit(-1)
typedef pair<int, int> pii;
#define NONE "-"

class Parser
{
    int temp_variable_index = 1;
    string GenerateTempVar()
    {
        return "T" + to_string(temp_variable_index++);
    }

public:
    string to_string(int num)
    {
        string ret;
        while (num)
        {
            ret.push_back(num % 10 + '0');
            num /= 10;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    string deal(string A)
    {
        string tp;
        for (int i = 0; i < A.size(); i++)
        {
            tp.push_back(A[i]);
            if (A[i] == '+' || A[i] == '-' || A[i] == '*' || A[i] == '/')
            {
                string x = GenerateTempVar();
                string y = deal(A.substr(i + 1));
                string op;
                op.push_back(A[i]);
                AddQuadruple(op, A.substr(0, i), y, x);
                return x;
            }
        }
        return tp;
    }
    compiler A;
    vector<pii> tokens;
    vector<Quadruple> quadruple_list;
    int current_token_index;
    void out()
    {
        string token_str[128];
#define TOKEN(num, type, name, str) \
    token_str[num] = str;
        TOKENS
#undef TOKEN
        for (auto elem : tokens)
        {
            cout << token_str[elem.fi] << ", " << elem.se << endl;
        }
        for (int i = 0; i < quadruple_list.size(); i++)
            quadruple_list[i].Print();
    }
    void solve()
    {
        tokens = A.run(0);
        current_token_index = 0;
        Program();
        AddQuadruple("sys", NONE, NONE, NONE);
        cout << '\n';
        out();
    }
    void Expect(int num)
    {
        if (tokens[current_token_index].fi == num)
            current_token_index++;
        else
            error;
    }
    void AddQuadruple(string a, string b, string c, string d)
    {
        quadruple_list.push_back(Quadruple(a, b, c, d));
    }
    void Program()
    {
        Expect(PROGRAM);
        Expect(ID);
        Expect(SEMICOL);
        AddQuadruple("Program", A.name[tokens[current_token_index - 2].se], NONE, NONE);
        if (tokens[current_token_index].fi == VAR)
        {
            Expect(VAR);
            VariantDeclaration();
        }
        if (tokens[current_token_index].fi == BEGIN)
        {
            Expect(BEGIN);
            MultiplicativeExpression();
            Expect(END);
        }
        else
            error;
    }

    void VariantDeclaration()
    {
        if (tokens[current_token_index].fi == ID)
            IdentifierList();
        else
            error;
        Expect(COLON);
        if (tokens[current_token_index].fi == BOOL || tokens[current_token_index].fi == CHAR || tokens[current_token_index].fi == INTEGER)
            current_token_index++;
        else
            error;
        Expect(SEMICOL);
        if (tokens[current_token_index].fi == ID)
        {
            VariantDeclaration();
        }
    }
    void IdentifierList()
    {
        Expect(ID);
        if (tokens[current_token_index].fi == COMMA)
        {
            Expect(COMMA);
            IdentifierList();
        }
    }

    void MultiplicativeExpression()
    {
        Expression();
        if (tokens[current_token_index].fi == 52)
        {
            current_token_index++;
            MultiplicativeExpression();
        }
    }
    void Expression()
    {
        if (tokens[current_token_index].fi == ID)
        {
            Expect(ID);
            Expect(ASSIGN);
            string var = A.name[tokens[current_token_index - 2].se];
            string ret = parseSSA();
            AddQuadruple(":=", ret, NONE, var);
        }
        else if (tokens[current_token_index].fi == IF)
        {
            int tcur = quadruple_list.size();
            Expect(IF);
            BooleanExpression();
            Expect(THEN);
            int Ttrue = quadruple_list.size();
            Expression();
            int Ffalse = quadruple_list.size();
            if (tokens[current_token_index].fi == ELSE)
            {
                AddQuadruple("j", NONE, NONE, NONE);
                Ffalse++;
                int temp = quadruple_list.size() - 1;
                Expect(ELSE);
                Expression();
                quadruple_list[temp].result.content = to_string(quadruple_list.size());
            }
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.content == "T")
                    quadruple_list[i].result.content = to_string(Ttrue);
                if (quadruple_list[i].result.content == "F")
                    quadruple_list[i].result.content = to_string(Ffalse);
            }
        }
        else if (tokens[current_token_index].fi == WHILE)
        {
            Expect(WHILE);
            int tcur = quadruple_list.size();
            BooleanExpression();
            Expect(DO);
            int Ttrue = quadruple_list.size();
            Expression();
            AddQuadruple("j", NONE, NONE, to_string(tcur));
            int Ffalse = quadruple_list.size();
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.content == "T")
                    quadruple_list[i].result.content = to_string(Ttrue);
                if (quadruple_list[i].result.content == "F")
                    quadruple_list[i].result.content = to_string(Ffalse);
            }
        }
        else if (tokens[current_token_index].fi == REPEAT)
        {
            int Ttrue = quadruple_list.size();
            Expect(REPEAT);
            Expression();
            int tcur = quadruple_list.size();
            Expect(UNTIL);
            BooleanExpression();
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.content == "F")
                    quadruple_list[i].result.content = to_string(Ttrue);
                if (quadruple_list[i].result.content == "T")
                    quadruple_list[i].result.content = to_string((int)quadruple_list.size());
            }
        }
        else if (tokens[current_token_index].fi == BEGIN)
        {
            Expect(BEGIN);
            MultiplicativeExpression();
            Expect(END);
        }
        else
            error;
    }

    string parseSSA()
    {
        string tp1 = parseSSB();
        string tp2 = AdditionAndSubtraction();
        string x = deal(tp1 + tp2);
        return x;
    }
    string parseSSB()
    {
        string tp1 = parseSSC();
        string tp2 = MultiplyAndDivide();
        string x = deal(tp1 + tp2);
        return x;
    }
    string parseSSC()
    {
        if (tokens[current_token_index].fi == MINUS)
        {
            ++current_token_index;
            string tp = parseSSC();
            string result = GenerateTempVar();
            AddQuadruple(NONE, "minus", tp, result);
            return result;
        }
        else
        {
            if (tokens[current_token_index].fi == ID)
                current_token_index++;
            else if (tokens[current_token_index].fi == INTCON)
                current_token_index++;
            else if (tokens[current_token_index].fi == LPAR)
            {
                current_token_index++;
                string x = parseSSA();
                Expect(RPAR);
                return x;
            }
            cout << A.name[tokens[current_token_index - 1].se];
            return A.name[tokens[current_token_index - 1].se];
        }
    }

    string MultiplyAndDivide()
    {
        if (tokens[current_token_index].fi == ASTERISK)
        {
            current_token_index++;
            string tp1 = parseSSC();
            string tp2 = MultiplyAndDivide();
            return "*" + tp1 + tp2;
        }
        else if (tokens[current_token_index].fi == SLASH)
        {
            current_token_index++;
            string tp1 = parseSSC();
            string tp2 = MultiplyAndDivide();
            return "/" + tp1 + tp2;
        }
        else
            return "";
    }
    string AdditionAndSubtraction()
    {
        if (tokens[current_token_index].fi == PLUS)
        {
            current_token_index++;
            string tp1 = parseSSB();
            string tp2 = AdditionAndSubtraction();
            return "+" + tp1 + tp2;
        }
        else if (tokens[current_token_index].fi == MINUS)
        {
            current_token_index++;
            string tp1 = parseSSB();
            string tp2 = AdditionAndSubtraction();
            return "-" + tp1 + tp2;
        }
        else
            return "";
    }

    void BooleanExpression()
    {
        BooleanConstant();
        LogicalAndExpression();
        LogicalOrExpression();
    }
    void LogicalOrExpression()
    {
        if (tokens[current_token_index].fi == OR)
        {
            current_token_index++;
            quadruple_list[quadruple_list.size() - 1].result = to_string(quadruple_list.size());
            BooleanConstant();
            LogicalAndExpression();
            LogicalOrExpression();
        }
    }
    void LogicalAndExpression()
    {
        if (tokens[current_token_index].fi == AND)
        {
            current_token_index++;
            quadruple_list[quadruple_list.size() - 2].result = to_string(quadruple_list.size());
            BooleanConstant();
            LogicalAndExpression();
        }
    }
    void BooleanConstant()
    {
        if (tokens[current_token_index].fi == NOT)
        {
            current_token_index++;
            BooleanConstant();
        }
        else
        {
            if (tokens[current_token_index].fi == FALSE)
            {
                current_token_index++;
                AddQuadruple("jnz", "FALSE", NONE, "T");
                AddQuadruple("j", NONE, NONE, "F");
            }
            else if (tokens[current_token_index].fi == TRUE)
            {
                current_token_index++;
                AddQuadruple("jnz", "TRUE", NONE, "T");
                AddQuadruple("j", NONE, NONE, "F");
            }
            else if (tokens[current_token_index].fi == LPAR)
            {
                Expect(LPAR);
                BooleanExpression();
                Expect(RPAR);
            }
            else
            {
                string tp1 = parseSSA();
                if (tokens[current_token_index].fi >= LESS && tokens[current_token_index].fi <= GEQL)
                {
                    int tp = quadruple_list.size();
                    string op;
                    if (tokens[current_token_index].fi == LESS)
                        op = "<";
                    if (tokens[current_token_index].fi == LEQL)
                        op = "<=";
                    if (tokens[current_token_index].fi == NEQL)
                        op = "<>";
                    if (tokens[current_token_index].fi == EQUAL)
                        op = "=";
                    if (tokens[current_token_index].fi == GREATER)
                        op = ">";
                    if (tokens[current_token_index].fi == GEQL)
                        op = ">=";
                    ++current_token_index;
                    AddQuadruple("j" + op, tp1, NONE, "T");
                    AddQuadruple("j", NONE, NONE, "F");
                    string tp2 = parseSSA();
                    quadruple_list[tp].arg2 = tp2;
                    return;
                }
                AddQuadruple("jnz", tp1, NONE, "T");
                AddQuadruple("jnz", NONE, NONE, "F");
            }
        }
    }
};
int main()
{
    Parser A;
    A.solve();
}

void Error(string error_message, Coordinate coord, char *pos)
{
    cout << "错的不是你，是这个sekai"
         << "不要以为我可以输出错误信息，希腊奶，我也不知道为什么错"
         << "这段鬼画符是真的编译不下去，让我们为它默哀114(ℏG/c^5)^0.5"
         << "电脑没油了，先exit(1)了，886";
    exit(1);
}

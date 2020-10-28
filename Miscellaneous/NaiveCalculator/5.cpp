#include <iostream>
#include <vector>
#include <map>
#include <cmath>
using namespace std;

const char NUMBER = 'n';
const char UNKNOWN = 'u';
const char VARIABLE = 'v';
const char DECLARATION = 'd';
const char FUNCTION = 'f';
const char END_FLAG = ';';
enum
{
    DIVIDE_BY_ZERO,
    ILLEGAL_STATEMENT,
    RIGHT_PARNETHESES_EXPECTED,
    PRIMARY_EXPECTED,
};

void Error(int flag)
{
    switch (flag)
    {
    case DIVIDE_BY_ZERO:
        throw runtime_error("Divide by zero.");
    case ILLEGAL_STATEMENT:
        throw runtime_error("Illegal statement.");
    case RIGHT_PARNETHESES_EXPECTED:
        throw runtime_error("Right parnetheses expected.");
    case PRIMARY_EXPECTED:
        throw runtime_error("Primary expected.");
    default:
        break;
    }
}

class Token
{
public:
    Token()
    {
        this->type = UNKNOWN;
        this->value = 0;
        this->name = "";
    }
    Token(char type)
    {
        this->type = type;
        this->value = 0;
        this->name = "";
    }
    Token(double value)
    {
        this->type = NUMBER;
        this->value = value;
        this->name = "";
    }
    Token(string name)
    {
        this->type = VARIABLE;
        this->value = 0;
        this->name = name;
    }
    char GetType() { return type; }
    double GetValue() { return value; }
    string GetName() { return name; }
    friend ostream &operator<<(ostream &out, Token t)
    {
        switch (t.type)
        {
        case NUMBER:
            cout << "<" << t.value << ">" << endl;
            break;
        case VARIABLE:
            cout << "<\"" << t.name << "\">" << endl;
            break;
        default:
            cout << "<" << t.type << ">" << endl;
            break;
        }
        return out;
    }

private:
    char type;
    double value;
    string name;
};

class TokenIn
{
public:
    TokenIn()
    {
        buffer_is_full = 0;
    }
    Token GetToken()
    {
        if (buffer_is_full)
        {
            buffer_is_full = 0;
            return buffer;
        }
        char ch;
        cin >> ch;
        if (find(opt_set.begin(), opt_set.end(), ch) != opt_set.end())
        {
            return Token(ch);
        }
        else if (find(num_set.begin(), num_set.end(), ch) != num_set.end())
        {
            cin.unget();
            double val;
            cin >> val;
            return Token(val);
        }
        else
        {
            if (isalpha(ch))
            {
                string s;
                s += ch;
                while (cin.get(ch) && isalnum(ch))
                {
                    s += ch;
                }
                cin.unget();
                if (s == "var")
                {
                    return Token(DECLARATION);
                }
                if (s == "plus")
                {
                    return Token(FUNCTION);
                }
                return Token(s);
            }
            //Error(ILLEGAL_STATEMENT);
        }
        return Token(UNKNOWN);
    }
    void PutBack(Token t)
    {
        buffer = t;
        buffer_is_full = 1;
    }

private:
    static const vector<const char> opt_set;
    static const vector<const char> num_set;
    bool buffer_is_full;
    Token buffer;
} ts;
const vector<const char> TokenIn::opt_set =
    {'+', '-', '*', '/', '%', '(', ')', ';'};
const vector<const char> TokenIn::num_set =
    {'.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

class Calculate
{
public:
    Calculate()
    {
        while (1)
        {
            try
            {
                cout << ">> ";
                Token t = ts.GetToken();
                while (t.GetType() == END_FLAG)
                {
                    t = ts.GetToken();
                }
                ts.PutBack(t);
                cout << Statement() << endl;
            }
            catch (exception &e)
            {
                cerr << e.what() << endl;
            }
        }
    }

private:
    double Primary()
    {
        Token t = ts.GetToken();
        switch (t.GetType())
        {
        case '(':
        {
            double d = Expression();
            t = ts.GetToken();
            if (t.GetType() != ')')
            {
                Error(RIGHT_PARNETHESES_EXPECTED);
            }
            return d;
        }
        case NUMBER:
            return t.GetValue();
        case VARIABLE:
            return variables[t.GetName()];
        case '-':
            return -Primary();
        case '+':
            return +Primary();
        default:
            Error(PRIMARY_EXPECTED);
            return -1;
        }
    }
    double Term()
    {
        double left = Primary();
        Token t = ts.GetToken();
        while (1)
        {
            switch (t.GetType())
            {
            case '*':
                left *= Primary();
                t = ts.GetToken();
                break;
            case '/':
            {
                double p = Primary();
                if (p == 0)
                {
                    Error(DIVIDE_BY_ZERO);
                }
                left /= p;
                t = ts.GetToken();
                break;
            }
            case '%':
            {
                double p = Primary();
                if (p == 0)
                {
                    Error(DIVIDE_BY_ZERO);
                }
                left = fmod(left, p);
                t = ts.GetToken();
                break;
            }
            default:
                ts.PutBack(t);
                return left;
            }
        }
    }
    double Expression()
    {
        double left = Term();
        Token t = ts.GetToken();
        while (1)
        {
            switch (t.GetType())
            {
            case '+':
                left += Term();
                t = ts.GetToken();
                break;
            case '-':
                left -= Term();
                t = ts.GetToken();
                break;
            default:
                ts.PutBack(t);
                return left;
            }
        }
    }
    double Declaration()
    {
        Token t = ts.GetToken();
        string name = t.GetName();
        if (name == "")
        {
            //Error(ILLEGAL_STATEMENT);
        }
        Token equal = ts.GetToken();
        if (equal.GetType() != '=')
        {
            //Error(ILLEGAL_STATEMENT);
        }
        double var = Expression();
        variables.insert(pair<string, double>(name, var));
        //TODO:
        return var;
    }
    double Statement()
    {
        Token t = ts.GetToken();
        switch (t.GetType())
        {
        case DECLARATION:
            return Declaration();
        default:
            ts.PutBack(t);
            return Expression();
        }
    }
    map<string, double> variables;
};

int main()
{
    try
    {
        Calculate();
        return 0;
    }
    catch (exception &e)
    {
        cerr << e.what() << endl;
        return -1;
    }
    catch (...)
    {
        return -2;
    }
}

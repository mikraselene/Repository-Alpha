
#include <iostream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <functional>

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
#include <iostream>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <stack>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

typedef enum
{
    AND = 1,
    ARRAY = 2,
    BEGIN = 3,
    BOOL = 4,
    CALL = 5,
    CASE = 6,
    CHAR = 7,
    CONSTANT = 8,
    DIM = 9,
    DO = 10,
    ELSE = 11,
    END = 12,
    FALSE = 13,
    FOR = 14,
    IF = 15,
    INPUT = 16,
    INTEGER = 17,
    NOT = 18,
    OF = 19,
    OR = 20,
    OUTPUT = 21,
    PROCEDURE = 22,
    PROGRAM = 23,
    READ = 24,
    REAL = 25,
    REPEAT = 26,
    SET = 27,
    STOP = 28,
    THEN = 29,
    TO = 30,
    TRUE = 31,
    UNTIL = 32,
    VAR = 33,
    WHILE = 34,
    WRITE = 35,
    ID = 36,
    NUM = 37,
    LPAREN = 39,
    RPAREN = 40,
    TIMES = 41,
    PLUS = 43,
    MINUS = 45,
    OVER = 48,
    EQ = 50,
    ASSIGN = 51,
    SEMI = 52,
    LT = 53
} TokenType;
typedef enum
{
    T_INTEGER,
    T_BOOL,
    T_CHAR
} VarType;
template <class T>
struct greater : binary_function<T, T, bool>
{
    bool operator()(const T &x, const T &y) const
    {
        return x > y;
    }
};
void SplitString(const string &s, vector<string> &v, const string &c);
void SplitString(const string &s, vector<string> &v, const string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
}

class State
{
public:
    vector<int> true_chain;
    vector<int> false_chain;
    int codebegin;
    bool accept;
    State() { accept = true; }
    void true_pushback(int a) { true_chain.push_back(a); }
    void false_pushback(int a) { false_chain.push_back(a); }
    void addTrueChain(State &st)
    {
        true_chain.insert(true_chain.end(), st.true_chain.begin(), st.true_chain.end());
    }
    void addFalseChain(State &st)
    {
        false_chain.insert(false_chain.end(), st.false_chain.begin(), st.false_chain.end());
    }
    void swapChain()
    {
        vector<int> temp = true_chain;
        true_chain = false_chain;
        false_chain = temp;
    }
};

class Unit
{
public:
    string err_msg;
    int lineNum;
    int linePos;
    int constant_id;
    Unit() : content(""), type(-1) {}
    Unit(string in_content, int in_type, int in_constant_id = 0) : content(in_content), type(in_type), constant_id(in_constant_id) {}
    void setInfo(int lineNum, int linePos, string err_msg)
    {
        this->lineNum = lineNum;
        this->linePos = linePos;
        this->err_msg = err_msg;
    }
    void printInfo()
    {
        string temp;
        if (type >= 36 && type <= 38)
        {
            temp = "(" + to_string(type) + "," + to_string(constant_id) + ")";
        }
        else
        {
            temp = "(" + to_string(type) + "," + "-" + ")";
        }
        cout << setw(10) << temp;
    }
    string getErrInfo()
    {
        return "At line " + to_string(lineNum) + " pos " + to_string(linePos) + " : " + err_msg + "\n";
    }
    int getType()
    {
        return type;
    }
    void setType(int type)
    {
        this->type = type;
    }
    string getContent()
    {
        return content;
    }
    void setVarType(VarType v)
    {
        var_type = v;
    }
    VarType getVarType()
    {
        return var_type;
    }
    void setContent(string s)
    {
        content = s;
    }

private:
    string content;
    VarType var_type;
    int type;
};

typedef enum
{
    START,
    INASSIGN,
    INNUM,
    INID,
    INQUOTE,
    INSLASH,
    INCOMMENT,
    RIGHTCOMMENT,
    INGT,
    INLT,
    INDOT,
    DONE
} StateType;

class grammarParser
{
public:
    map<string, int> keywords = map<string, int>({{"and", 1}, {"array", 2}, {"begin", 3}, {"bool", 4}, {"call", 5}, {"case", 6}, {"char", 7}, {"constant", 8}, {"dim", 9}, {"do", 10}, {"else", 11}, {"end", 12}, {"false", 13}, {"for", 14}, {"if", 15}, {"input", 16}, {"integer", 17}, {"not", 18}, {"of", 19}, {"or", 20}, {"output", 21}, {"procedure", 22}, {"program", 23}, {"read", 24}, {"real", 25}, {"repeat", 26}, {"set", 27}, {"stop", 28}, {"then", 29}, {"to", 30}, {"true", 31}, {"until", 32}, {"var", 33}, {"while", 34}, {"write", 35}, {"(", 39}, {")", 40}, {"*", 41}, {"*/", 42}, {"+", 43}, {",", 44}, {"-", 45}, {".", 46}, {"..", 47}, {"/", 48}, {"/*", 49}, {":", 50}, {":=", 51}, {";", 52}, {"<", 53}, {"<=", 54}, {"<>", 55}, {"=", 56}, {">", 57}, {">=", 58}, {"[", 59}, {"]", 60}});

    map<string, int> constantList;
    vector<string> inputList;
    vector<Unit> unitList;
    vector<Unit> errorList;
    vector<vector<Unit>> tacList;
    vector<Unit> customList;
    vector<Unit> varList;
    stack<Unit> cal_stack;
    int lineNum;
    int linePos;
    int unit_index;
    int addressNum;
    int sys_tempVar;
    Unit *currUnit;

    grammarParser()
    {
        this->inputList = vector<string>();
        this->unitList = vector<Unit>();
        this->constantList = map<string, int>();
        this->errorList = vector<Unit>();
        sys_tempVar = 1;
    }

    void walkhere(string input)
    {
        cout << "walk here " << input << endl;
    }
    void error(string err_msg)
    {
        cout << err_msg << " at line " << currUnit->lineNum << " position " << currUnit->linePos << endl;
        exit(0);
    }
    void printKeywords()
    {
        for (auto i : keywords)
        {
            cout << i.first << " " << i.second << endl;
        }
    }
    void inputCode()
    {
        this->rawInput = "";
        this->inputList.resize(0);
        this->unitList.resize(0);
        cout << "Input file name:\n";
        //cin >> this->programName;
        this->programName = "test3.txt";
        std::ifstream fin(this->programName, std::ios::in);
        string temp;
        if (!fin)
        {
            cout << "File not exists!" << endl;
            exit(0);
        }
        while (getline(fin, temp))
        {
            vector<string> tempList = vector<string>();
            this->rawInput.append(temp + "\n");
            this->inputList.push_back(temp + "\n");
        }
    }
    int checkWords()
    {
        lineNum = 0;
        linePos = 0;
        while (getToken() != 0)
            ;
        return this->errorList.size();
    }
    int getToken()
    {
        StateType state = START;
        int currTokenType = 0;
        bool is_comment = false, is_err = false;
        string currToken = "", err_msg = "";
        while (state != DONE)
        {
            bool save_flag = true;
            int currChar = getChar();
            switch (state)
            {
            case START:
            {
                if (isdigit(currChar))
                {
                    state = INNUM;
                }
                else if (isalpha(currChar))
                {
                    state = INID;
                }
                else if (currChar == ':')
                {
                    state = INASSIGN;
                }
                else if (currChar == '\'')
                {
                    save_flag = false;
                    state = INQUOTE;
                }
                else if (currChar == '/')
                {
                    state = INSLASH;
                }
                else if (currChar == '>')
                {
                    state = INGT;
                }
                else if (currChar == '<')
                {
                    state = INLT;
                }
                else if (currChar == '.')
                {
                    state = INDOT;
                }
                else if (currChar == 0)
                {

                    state = DONE;
                    currTokenType = 0;
                    save_flag = false;
                }
                else if ((currChar == ' ') || (currChar == '\t') || (currChar == '\n'))
                {
                    save_flag = false;
                }
                else
                {
                    state = DONE;
                    string temp_key = "";
                    temp_key += (char)currChar;
                    if (this->keywords.find(temp_key) != this->keywords.end())
                    {
                        currTokenType = this->keywords[temp_key];
                    }
                    else
                    {
                        currTokenType = -1;
                        is_err = true;
                        err_msg = "invalid Token";
                    }
                }
                break;
            }
            case INASSIGN:
            {
                state = DONE;
                if (currChar == '=')
                {
                    currTokenType = this->keywords[":="];
                }
                else
                {
                    currTokenType = this->keywords[":"];
                    save_flag = false;
                    backtrackChar();
                }
                break;
            }
            case INGT:
            {
                state = DONE;
                if (currChar == '=')
                {
                    currTokenType = this->keywords[">="];
                }
                else
                {
                    currTokenType = this->keywords[">"];
                    save_flag = false;
                    backtrackChar();
                }
                break;
            }
            case INLT:
            {
                state = DONE;
                if (currChar == '=')
                {
                    currTokenType = this->keywords["<="];
                }
                else if (currChar == '>')
                {
                    currTokenType = this->keywords["<>"];
                }
                else
                {
                    currTokenType = this->keywords["<"];
                    save_flag = false;
                    backtrackChar();
                }
                break;
            }
            case INDOT:
            {
                state = DONE;
                if (currChar == '.')
                {
                    currTokenType = this->keywords[".."];
                }
                else
                {
                    currTokenType = this->keywords["."];
                    save_flag = false;
                    backtrackChar();
                }
                break;
            }
            case INQUOTE:
            {
                if (currChar == '\'')
                {
                    save_flag = false;
                    state = DONE;
                    currTokenType = 38;
                }
                else if (currChar == '\n')
                {
                    state = DONE;
                    currTokenType = -1;
                    is_err = true;
                    err_msg = "Syntax ERROR: Missing '\n";
                }
                break;
            }
            case INSLASH:
            {
                if (currChar == '*')
                {
                    state = INCOMMENT;
                }
                else
                {
                    state = DONE;
                    save_flag = false;
                    backtrackChar();
                    currTokenType = this->keywords["/"];
                }
                break;
            }
            case INCOMMENT:
            {
                if (currChar == '*')
                {
                    state = RIGHTCOMMENT;
                }
                else if (currChar == '\n')
                {
                    is_comment = true;
                    state = DONE;
                    currTokenType = -1;
                    is_err = true;
                    err_msg = "Syntax error: Comment format incorrect, missing */\n";
                }
                break;
            }
            case RIGHTCOMMENT:
            {
                if (currChar == '/')
                {
                    is_comment = true;
                    state = DONE;
                    currTokenType = this->keywords["*/"];
                }
                else if (currChar == '\n')
                {
                    is_comment = true;
                    state = DONE;
                    currTokenType = -1;
                    is_err = true;
                    err_msg = "Syntax error: Comment format incorrect, missing /\n";
                }
                else
                {
                    is_comment = true;
                    state = INCOMMENT;
                }
                break;
            }
            case INNUM:
            {
                if (!isdigit(currChar) && !isalpha(currChar))
                {
                    backtrackChar();
                    save_flag = false;
                    state = DONE;
                    currTokenType = 37;
                }
                else if (!isdigit(currChar) && isalpha(currChar))
                {
                    backtrackChar();
                    save_flag = false;
                    state = DONE;
                    currTokenType = 37;
                    is_err = true;
                    err_msg = "error: wrong constant num";
                }
                break;
            }
            case INID:
            {
                if (!isdigit(currChar) && !isalpha(currChar))
                {
                    backtrackChar();
                    save_flag = false;
                    state = DONE;
                    currTokenType = 36;
                }
                break;
            }
            }
            if (save_flag)
            {
                currToken += currChar;
            }
            if (state == DONE)
            {

                if (currTokenType == 36)
                {
                    if (this->keywords.find(currToken) != this->keywords.end())
                    {
                        currTokenType = this->keywords[currToken];
                    }
                }

                int id = 0;
                Unit unit = Unit(currToken, currTokenType, id);
                unit.setInfo(lineNum + 1, linePos - currToken.length() + 1, err_msg);
                if (currTokenType >= 36 && currTokenType <= 38)
                {
                    if (this->constantList.find(currToken) == this->constantList.end())
                    {
                        id = constantList.size() + 1;
                        unit.constant_id = id;
                        constantList.insert({currToken, id});
                        customList.push_back(unit);
                    }
                    else
                    {
                        unit.constant_id = this->constantList[currToken];
                    }
                }
                if (is_err)
                {
                    this->errorList.push_back(unit);
                }
                else if (!is_comment && !currTokenType == 0)
                {
                    this->unitList.push_back(unit);
                }
            }
        }
        return currTokenType;
    }
    void backtrackChar()
    {
        linePos--;
    }
    int getChar()
    {
        if (linePos >= inputList[lineNum].length())
        {
            lineNum++;
            linePos = 0;
        }
        if (lineNum >= this->inputList.size())
        {

            currChar = 0;
            return currChar;
        }
        currChar = inputList[lineNum][linePos++];
        return currChar;
    }
    void printListType()
    {
        int i = 0;
        for (auto element : this->unitList)
        {
            i++;
            element.printInfo();
            if (i % 5 == 0)
                cout << endl;
        }
        cout << endl;
        for (auto element : this->errorList)
        {
            cout << element.getErrInfo();
        }
    }
    Unit pop_stack()
    {
        Unit ret = cal_stack.top();
        cal_stack.pop();
        return ret;
    }
    int pushTac(Unit u1, Unit u2, Unit u3, Unit u4)
    {
        vector<Unit> tempTac = {u1, u2, u3, u4};
        tacList.push_back(tempTac);
        addressNum++;
        return addressNum - 1;
    }
    VarType getCurrUnitType()
    {
        int idx = constantList[currUnit->getContent()];
        return varList[idx].getVarType();
    }
    Unit generateTempVar()
    {
        string content = "T" + to_string(sys_tempVar++);
        Unit temp = Unit(content, 36, constantList.size());
        constantList.insert({content, constantList.size()});
        return temp;
    }
    int parse()
    {
        unit_index = 0;
        getNextToken();
        sentence();
        return 0;
    }
    int getNextToken()
    {
        if (unit_index < unitList.size())
            currUnit = &unitList[unit_index++];
        return unit_index - 1;
    }
    State sentence()
    {
        State temp;
        switch (currUnit->getType())
        {
        case 23:
        {

            Unit *unit_temp = currUnit;
            getNextToken();
            if (currUnit->getType() != 36)
            {
                error("Error: missing program name");
            }
            pushTac(*unit_temp, *currUnit, *currUnit, *currUnit);
            getNextToken();
            if (currUnit->getType() != keywords[";"])
            {
                error("Error: missing keywords ;");
            }
            getNextToken();
            temp = Declare();
            getNextToken();
            sentence();
            if (currUnit->getType() != 46)
            {
                error("Error: without . ending");
            }
            pushTac(*currUnit, *currUnit, *currUnit, *currUnit);
            break;
        }
        case 36:
        {
            temp = Assign_Exp();
            break;
        }
        case 3:
        {
            temp = multi_sentence();
            break;
        }
        case 34:
        {
            temp = while_Exp();
            break;
        }
        case 15:
        {
            temp = if_Exp();
            break;
        }
        case 26:
        {
            temp = repeat_Exp();
            break;
        }
        default:
        {
            error("Error: unexpected token " + currUnit->getContent());
        }
        }
        return temp;
    }

    State Declare()
    {
        State temp;
        switch (currUnit->getType())
        {
        case 33:
        {
            getNextToken();
            valueDefine();
            if (currUnit->getType() != 52)
            {
                error("Error: missing keywords ;");
            }
            getNextToken();
            while (currUnit->getType() == 36)
            {
                temp = multiDeclare();
                getNextToken();
            }
            unit_index--;
            break;
        }
        default:
            break;
        }
        return temp;
    }
    Unit valueDefine()
    {

        Unit temp = *currUnit;
        if (currUnit->getType() != 36)
        {
            error("Error: missing keywords ;");
        }
        getNextToken();

        temp.setVarType((remainValueDefine()).getVarType());
        constantList[temp.getContent()] = varList.size();
        varList.push_back(temp);
        return temp;
    }
    Unit remainValueDefine()
    {
        Unit temp = *currUnit;
        switch (currUnit->getType())
        {
        case 44:
        {
            getNextToken();
            temp.setVarType((valueDefine()).getVarType());
            break;
        }
        case 50:
        {
            getNextToken();
            temp.setVarType((TypeDefine()).getVarType());
            break;
        }
        default:
        {
            error("Error: syntax error " + currUnit->getContent());
        }
        }
        return temp;
    }
    Unit TypeDefine()
    {
        Unit temp;
        switch (currUnit->getType())
        {
        case 17:
        {
            temp.setVarType(T_INTEGER);
            getNextToken();
            break;
        }
        case 4:
        {
            temp.setVarType(T_BOOL);
            getNextToken();
            break;
        }
        case 7:
        {
            temp.setVarType(T_CHAR);
            getNextToken();
            break;
        }
        default:
        {
            error("Error: syntax error " + currUnit->getContent());
        }
        }
        return temp;
    }
    State multiDeclare()
    {
        State temp;
        switch (currUnit->getType())
        {
        case 36:
        {
            valueDefine();
            if (currUnit->getType() != 52)
            {
                error("Error: without ;");
            }
            break;
        }
        default:
            break;
        }
        return temp;
    }

    State multi_sentence()
    {
        State temp;
        if (currUnit->getType() == 3)
        {
            getNextToken();
            temp = sentenceList();
            if (currUnit->getType() != 12)
            {
                error("Error: syntax error: no end");
            }
            getNextToken();
        }
        return temp;
    }
    State sentenceList()
    {
        State temp = sentence();
        if (currUnit->getType() == 52)
        {
            getNextToken();
            sentenceList();
        }
        return temp;
    }

    State Assign_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        if (!checkDefine())
        {
            error("Error: undefined identifier" + currUnit->getContent());
        }

        if (varList[constantList[currUnit->getContent()]].getVarType() != T_INTEGER)
        {
            error("Error : wrong type ,expected integer variable, current variable is " + currUnit->getContent());
        }
        cal_stack.push(*currUnit);
        getNextToken();
        if (currUnit->getType() != keywords[":="])
        {
            error("Error: missing token :=");
        }
        Unit assign_op = *currUnit;
        temp = Cacl_Exp();

        if (cal_stack.size() >= 2)
        {
            Unit u1 = pop_stack();
            Unit u2 = pop_stack();
            Unit null_unit = Unit("-", 0, 0);
            pushTac(assign_op, u1, null_unit, u2);
        }
        return temp;
    }
    State Cacl_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        temp = Term();
        while (currUnit->getType() == 45 || currUnit->getType() == 43)
        {
            Unit op = *currUnit;
            temp = Term();
            if (cal_stack.size() >= 2)
            {
                Unit u1 = pop_stack();
                Unit u2 = pop_stack();
                Unit temp_var = generateTempVar();
                pushTac(op, u2, u1, temp_var);
                cal_stack.push(temp_var);
            }
        }
        return temp;
    }
    State Term()
    {
        State temp;
        temp.codebegin = addressNum;
        temp = factor();
        getNextToken();
        if (currUnit->getType() == 41 || currUnit->getType() == 48)
        {
            Unit op = *currUnit;
            temp = Term();
            Unit u1 = pop_stack();
            Unit u2 = pop_stack();
            Unit temp_var = generateTempVar();
            pushTac(op, u2, u1, temp_var);

            cal_stack.push(temp_var);
        }
        return temp;
    }
    State factor()
    {
        State temp;
        temp.codebegin = addressNum;
        getNextToken();
        switch (currUnit->getType())
        {
        case 45:
        {
            Unit op = *currUnit;
            factor();
            Unit u1 = pop_stack();
            Unit temp_var = generateTempVar();
            cal_stack.push(temp_var);
            pushTac(op, u1, op, temp_var);
            break;
        }
        case 37:
        {
            cal_stack.push(*currUnit);
            break;
        }
        case 36:
        {
            if (!checkDefine())
            {
                error("Error: undefined identifier" + currUnit->getContent());
            }
            else if (getCurrUnitType() != T_INTEGER)
            {
                error("Error: Wrong Type, expected integer");
            }
            cal_stack.push(*currUnit);
            break;
        }
        case 39:
        {
            Cacl_Exp();
            if (currUnit->getType() != 40)
            {
                error("Error: without )");
            }
            break;
        }
        default:
        {
            error("Error: unexpected token " + currUnit->getContent());
        }
        }
        return temp;
    }
    bool checkDefine()
    {
        bool flag = false;
        for (auto element : varList)
        {
            if (element.getContent() == currUnit->getContent())
            {
                flag = true;
                return flag;
            }
        }
        return flag;
    }

    State while_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        getNextToken();
        temp = bool_Exp();
        if (currUnit->getType() == 10)
        {
            getNextToken();
            sentence();
        }
        else
        {
            error("Error: missing keyword do");
        }
        pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit(to_string(temp.codebegin), 0));
        for (int i = 0; i < temp.false_chain.size() - 1; i++)
        {
            tacList[temp.false_chain[i]][3].setContent(to_string(addressNum));
        }
        int idx = temp.false_chain[temp.false_chain.size() - 1];
        tacList[idx][3].setContent(to_string(addressNum));
        return temp;
    }

    State if_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        getNextToken();
        temp = bool_Exp();
        if (currUnit->getType() == 29)
        {
            getNextToken();
            sentence();
            temp.true_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("0", 0)));
            int idx = temp.false_chain[temp.false_chain.size() - 1];
            tacList[idx][3].setContent(to_string(addressNum));
        }
        else
        {
            error("Error: missing keyword then");
        }
        if (currUnit->getType() == 11)
        {
            getNextToken();
            for (auto i : temp.false_chain)
            {
                tacList[i][3].setContent(to_string(addressNum));
            }
            sentence();
            int idx = temp.true_chain[temp.true_chain.size() - 1];
            tacList[idx][3].setContent(to_string(addressNum));
        }
        return temp;
    }

    State repeat_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        getNextToken();
        sentence();
        if (currUnit->getType() == 32)
        {
            getNextToken();
            State temp_state = bool_Exp();
            int idx = temp_state.false_chain[temp_state.false_chain.size() - 1];
            tacList[idx][3].setContent(to_string(temp.codebegin));
        }
        else
        {
            error("Error: missing keyword then");
        }
        return temp;
    }

    State bool_Exp()
    {
        State temp;
        temp.codebegin = addressNum;
        temp = bool_Term();
        if (currUnit->getType() == 20)
        {
            Unit op = *currUnit;
            getNextToken();
            State temp_state = bool_Exp();
            temp.addTrueChain(temp_state);

            for (int i = 0; i < temp.false_chain.size(); i++)
            {
                tacList[temp.false_chain[i]][3].setContent(to_string(temp_state.codebegin));
            }

            temp.addFalseChain(temp_state);
            if (temp.false_chain.size() >= 1)
            {
                temp.false_chain[0] = temp.false_chain[temp.false_chain.size() - 1];
                temp.false_chain.resize(1);
            }
        }

        for (int i = 0; i < temp.true_chain.size(); i++)
        {
            tacList[temp.true_chain[i]][3].setContent(to_string(addressNum));
        }
        return temp;
    }
    State bool_Term()
    {
        State temp;
        temp.codebegin = addressNum;
        temp = bool_factor();
        if (currUnit->getType() == 1)
        {
            Unit op = *currUnit;
            getNextToken();
            State temp_state = bool_Term();
            temp.addFalseChain(temp_state);
            for (int i = 0; i < temp.true_chain.size(); i++)
            {
                tacList[temp.true_chain[i]][3].setContent(to_string(temp_state.codebegin));
            }

            temp.addTrueChain(temp_state);
            if (temp.true_chain.size() >= 1)
            {
                temp.true_chain[0] = temp.true_chain[temp.true_chain.size() - 1];
                temp.true_chain.resize(1);
            }
        }
        return temp;
    }
    State bool_factor()
    {
        State temp;
        temp.codebegin = addressNum;
        switch (currUnit->getType())
        {
        case 45:
        {
        }
        case 37:
        {
            unit_index--;
            temp = Cacl_Exp();
            Unit u1 = pop_stack();
            int type = currUnit->getType();
            Unit op = *currUnit;

            if (type >= 53 && type <= 58)
            {
                temp = Cacl_Exp();
                Unit u2 = pop_stack();

                temp.true_pushback(pushTac(Unit("j" + op.getContent(), 0), u1, u2, Unit("-", 0)));
                temp.false_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("-", 0)));
            }
            else
            {
                error("Error: incomplete Expression");
            }
            break;
        }
        case 36:
        {
            if (!checkDefine())
            {
                error("Error: undefined identifier " + currUnit->getContent());
            }
            if (getCurrUnitType() == T_INTEGER)
            {
                unit_index--;
                temp = Cacl_Exp();
                Unit u1 = pop_stack();
                int type = currUnit->getType();
                Unit op = *currUnit;
                if (type >= 53 && type <= 58)
                {
                    temp = Cacl_Exp();
                    if (!temp.accept)
                    {
                        return temp;
                    }
                    Unit u2 = pop_stack();

                    temp.true_pushback(pushTac(Unit("j" + op.getContent(), 0), u1, u2, Unit("-", 0)));
                    temp.false_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("-", 0)));
                }
                else
                {
                    error("Error: incomplete Expression");
                }
            }
            else if (getCurrUnitType() == T_BOOL)
            {
                temp.true_pushback(pushTac(Unit("jnz", 0), *currUnit, Unit("-", 0), Unit("-", 0)));
                temp.false_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("-", 0)));
                getNextToken();
                return temp;
            }
            else
            {
                error("Error: unexpected token " + currUnit->getContent());
            }
            break;
        }
        case 18:
        {
            Unit op = *currUnit;
            getNextToken();
            temp = bool_factor();
            temp.swapChain();
            break;
        }
        case 31:
        {
            temp.true_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("-", 0)));
            cal_stack.push(*currUnit);
            getNextToken();
            break;
        }
        case 13:
        {
            temp.false_pushback(pushTac(Unit("jump", 0), Unit("-", 0), Unit("-", 0), Unit("-", 0)));
            cal_stack.push(*currUnit);
            getNextToken();
            break;
        }
        case 39:
        {
            getNextToken();
            bool_Exp();
            if (currUnit->getType() != 40)
            {
                error("Error: without )");
            }
            getNextToken();
            break;
        }
        default:
        {
            error("Error: unexpected token " + currUnit->getContent());
        }
        }
        return temp;
    }
    void compressJump()
    {
        for (auto &element : tacList)
        {
            int idx;
            auto nextJump = element;
            while (nextJump[0].getContent() == "jump")
            {
                stringstream ss;
                ss << nextJump[3].getContent();
                ss >> idx;
                nextJump = tacList[idx];
            }
            if (element[0].getContent() == "jump")
            {
                element[3].setContent(to_string(idx));
            }
        }
    }
    void printTAC()
    {
        compressJump();
        int i = 0;
        for (auto element : tacList)
        {
            string lineNum = "(" + to_string(i) + ")";
            if (element[0].getType() == 23)
            {
                cout << setw(5) << lineNum << "(" << element[0].getContent() << ","
                     << element[1].getContent() << ",-,-)" << endl;
            }
            else if (element[0].getType() == 46)
            {
                cout << setw(5) << lineNum << "(sys,-,-,-)" << endl;
            }
            else
            {
                cout << setw(5) << lineNum << "(" << element[0].getContent() << "," << element[1].getContent() << ","
                     << element[2].getContent() << "," << element[3].getContent() << ")" << endl;
            }
            i++;
        }
    }

private:
    string rawInput;
    string programName;
    char currChar;
};

int main()
{
    grammarParser parser = grammarParser();
    parser.inputCode();
    parser.checkWords();
    parser.printListType();
    parser.parse();
    parser.printTAC();
    return 0;
}

#ifndef SEMATIC_HPP
#define SEMATIC_HPP
#include "lexical.hpp"

enum SingletonType
{
    TOKEN,  // token
    ASGN,   // op: assign
    PROG,   // op: start
    SYS,    // op: end
    JNZ,    // op: jnz
    JROP,   // op: jrop
    JUMP,   // op: jump
    SINGID, // result: singleton id
    TRES,   // result: true
    FRES,   // result: false
    NONE,   // -
};

class Singleton
{
public:
    Singleton(SingletonType type)
    {
    }

private:
    string content;
    SingletonType type;
    int info;
};

class Quadruple // = Three-Address Code
{
    friend class Parser;

public:
    Quadruple(string op, string arg1, string arg2, string result)
    {
        this->op = op;
        this->arg1 = arg1;
        this->arg2 = arg2;
        this->result = result;
    }
    void Print()
    {
        int w = 8;
        cout << "("
             << setw(w) << op << ","
             << setw(w) << arg1 << ","
             << setw(w) << arg2 << ","
             << setw(w) << result << ")" << endl;
    }

protected:
    string op;
    string arg1;
    string arg2;
    string result;
};

#define error exit(-1)

#define CURRENT_TOKEN_ID tokens[current_token_index]->id

class Parser
{
    int current_token_index = 0;
    int temp_variable_index = 0;
    vector<Token *> tokens;
    vector<Quadruple> quadruple_list;
    string GenerateTempVar()
    {
        return "T" + to_string(++temp_variable_index);
    }
    void AddQuadruple(string op, string arg1, string arg2, string result)
    {
        quadruple_list.push_back(Quadruple(op, arg1, arg2, result));
    }
    void Expect(int num)
    {
        if (CURRENT_TOKEN_ID == num)
        {
            current_token_index++;
        }
        else
        {
            error;
        }
    }

public:
    Parser(vector<Token *> tokens)
    {
        this->tokens = tokens;
        Program();
        AddQuadruple("sys", "-", "-", "-");
    }
    void PrintAsTheyWish(string info)
    {
        cout << info << endl;
        cout << "     (      OP,    ARG1,    ARG2,  RESULT)\n";
        for (int i = 0; i < quadruple_list.size(); i++)
        {
            cout << setw(3) << i << ". ";
            quadruple_list[i].Print();
        }
    }

private:
    void Program()
    {
        Expect(PROGRAM);
        Expect(ID);
        Expect(SEMICOL);
        AddQuadruple("Program", tokens[current_token_index - 2]->info.name, "-", "-");
        if (CURRENT_TOKEN_ID == VAR)
        {
            Expect(VAR);
            VariantDeclaration();
        }
        if (CURRENT_TOKEN_ID == BEGIN)
        {
            Expect(BEGIN);
            MultiplicativeExpression();
            Expect(END);
        }
        else
        {
            error;
        }
    }

    void VariantDeclaration()
    {
        if (CURRENT_TOKEN_ID == ID)
        {
            IdentifierList();
        }
        else
        {
            error;
        }
        Expect(COLON);
        if (CURRENT_TOKEN_ID == BOOL || CURRENT_TOKEN_ID == CHAR || CURRENT_TOKEN_ID == INTEGER)
        {
            current_token_index++;
        }
        else
        {
            error;
        }
        Expect(SEMICOL);
        if (CURRENT_TOKEN_ID == ID)
        {
            VariantDeclaration();
        }
    }
    void IdentifierList()
    {
        Expect(ID);
        if (CURRENT_TOKEN_ID == COMMA)
        {
            Expect(COMMA);
            IdentifierList();
        }
    }
    void MultiplicativeExpression()
    {
        Expression();
        if (CURRENT_TOKEN_ID == SEMICOL)
        {
            current_token_index++;
            MultiplicativeExpression();
        }
    }
    void Expression()
    {
        if (CURRENT_TOKEN_ID == ID)
        {
            Expect(ID);
            Expect(ASSIGN);
            string result = tokens[current_token_index - 2]->info.name;
            string arg1 = parseSSA();
            AddQuadruple(":=", arg1, "-", result);
        }
        else if (CURRENT_TOKEN_ID == IF)
        {
            int tcur = quadruple_list.size();
            Expect(IF);
            BooleanExpression();
            Expect(THEN);
            int Ttrue = quadruple_list.size();
            Expression();
            int Ffalse = quadruple_list.size();
            if (CURRENT_TOKEN_ID == ELSE)
            {
                AddQuadruple("j", "-", "-", "-");
                Ffalse++;
                int temp = quadruple_list.size() - 1;
                Expect(ELSE);
                Expression();
                quadruple_list[temp].result = to_string(quadruple_list.size());
            }
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result == "T")
                    quadruple_list[i].result = to_string(Ttrue);
                if (quadruple_list[i].result == "F")
                    quadruple_list[i].result = to_string(Ffalse);
            }
        }
        else if (CURRENT_TOKEN_ID == WHILE)
        {
            Expect(WHILE);
            int tcur = quadruple_list.size();
            BooleanExpression();
            Expect(DO);
            int Ttrue = quadruple_list.size();
            Expression();
            AddQuadruple("j", "-", "-", to_string(tcur));
            int Ffalse = quadruple_list.size();
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result == "T")
                {
                    quadruple_list[i].result = to_string(Ttrue);
                }
                if (quadruple_list[i].result == "F")
                {
                    quadruple_list[i].result = to_string(Ffalse);
                }
            }
        }
        else if (CURRENT_TOKEN_ID == REPEAT)
        {
            int Ttrue = quadruple_list.size();
            Expect(REPEAT);
            Expression();
            int tcur = quadruple_list.size();
            Expect(UNTIL);
            BooleanExpression();
            for (int i = tcur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result == "F")
                {
                    quadruple_list[i].result = to_string(Ttrue);
                }
                if (quadruple_list[i].result == "T")
                {
                    quadruple_list[i].result = to_string(quadruple_list.size());
                }
            }
        }
        else if (CURRENT_TOKEN_ID == BEGIN)
        {
            Expect(BEGIN);
            MultiplicativeExpression();
            Expect(END);
        }
        else
        {
            error;
        }
    }

    string deal(string str)
    {
        string tp;
        for (int i = 0; i < str.size(); i++)
        {
            tp.push_back(str[i]);
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                string result = GenerateTempVar();
                string arg2 = deal(str.substr(i + 1));
                string op;
                op.push_back(str[i]);
                AddQuadruple(op, str.substr(0, i), arg2, result);
                return result;
            }
        }
        return tp;
    }
    string parseSSA()
    {
        string tp1 = parseSSB();
        string tp2 = AdditionAndSubtraction();
        return deal(tp1 + tp2);
    }
    string parseSSB()
    {
        string tp1 = parseSSC();
        string tp2 = MultiplyAndDivide();
        return deal(tp1 + tp2);
    }
    string parseSSC()
    {
        if (CURRENT_TOKEN_ID == MINUS)
        {
            current_token_index++;
            string arg2 = parseSSC();
            string result = GenerateTempVar();
            AddQuadruple("-", "minus", arg2, result);
            return result;
        }
        else
        {
            if (CURRENT_TOKEN_ID == ID)
            {
                current_token_index++;
            }
            else if (CURRENT_TOKEN_ID == INTCON)
            {
                return to_string(tokens[current_token_index++]->info.val.i);
            }
            else if (CURRENT_TOKEN_ID == LPAR)
            {
                current_token_index++;
                string x = parseSSA();
                Expect(RPAR);
                return x;
            }
            return tokens[current_token_index - 1]->info.name;
        }
    }
    string MultiplyAndDivide()
    {
        if (CURRENT_TOKEN_ID == ASTERISK || CURRENT_TOKEN_ID == SLASH)
        {
            string op = token_str[CURRENT_TOKEN_ID];
            current_token_index++;
            string tp1 = parseSSC();
            string tp2 = MultiplyAndDivide();
            return op + tp1 + tp2;
        }
        else
        {
            return "";
        }
    }
    string AdditionAndSubtraction()
    {
        if (CURRENT_TOKEN_ID == PLUS || CURRENT_TOKEN_ID == MINUS)
        {
            string op = token_str[CURRENT_TOKEN_ID];
            current_token_index++;
            string tp1 = parseSSB();
            string tp2 = AdditionAndSubtraction();
            return op + tp1 + tp2;
        }
        else
        {
            return "";
        }
    }

    void BooleanExpression()
    {
        BooleanConstant();
        LogicalAndExpression();
        LogicalOrExpression();
    }
    void LogicalOrExpression()
    {
        if (CURRENT_TOKEN_ID == OR)
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
        if (CURRENT_TOKEN_ID == AND)
        {
            current_token_index++;
            quadruple_list[quadruple_list.size() - 2].result = to_string(quadruple_list.size());
            BooleanConstant();
            LogicalAndExpression();
        }
    }
    void BooleanConstant()
    {
        if (CURRENT_TOKEN_ID == NOT)
        {
            current_token_index++;
            BooleanConstant();
        }
        else
        {
            if (CURRENT_TOKEN_ID == FALSE)
            {
                current_token_index++;
                AddQuadruple("jnz", "FALSE", "-", "T");
                AddQuadruple("j", "-", "-", "F");
            }
            else if (CURRENT_TOKEN_ID == TRUE)
            {
                current_token_index++;
                AddQuadruple("jnz", "TRUE", "-", "T");
                AddQuadruple("j", "-", "-", "F");
            }
            else if (CURRENT_TOKEN_ID == LPAR)
            {
                Expect(LPAR);
                BooleanExpression();
                Expect(RPAR);
            }
            else
            {
                string tp1 = parseSSA();
                if (CURRENT_TOKEN_ID >= LESS && CURRENT_TOKEN_ID <= GEQL)
                {
                    int tp = quadruple_list.size();
                    string op = token_str[CURRENT_TOKEN_ID];
                    current_token_index++;
                    AddQuadruple("j" + op, tp1, "-", "T");
                    AddQuadruple("j", "-", "-", "F");
                    string tp2 = parseSSA();
                    quadruple_list[tp].arg2 = tp2;
                    return;
                }
                AddQuadruple("jnz", tp1, "-", "T");
                AddQuadruple("jnz", "-", "-", "F");
            }
        }
    }
};

#endif

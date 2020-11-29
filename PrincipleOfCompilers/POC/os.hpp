#ifndef SEMATIC_HPP
#define SEMATIC_HPP
#include "lexical.hpp"

class Singleton
{
    friend class Parser;
    friend class Quadruple;

public:
    Singleton()
    {
        this->content = "";
        this->type = -1;
    }
    Singleton(string content)
    {
        this->content = content;
        this->type = -1;
    }
    Singleton(const char *content)
    {
        this->content = content;
        this->type = -1;
    }
    Singleton(string content, int type)
    {
        this->content = content;
        this->type = type;
    }
    Singleton(Token *token)
    {
        this->content = (const char *)token->info.name;
        this->type = token->id;
    }
    void SetContent(string s) { content = s; }
    void SetContent(int s) { content = to_string(s); }

protected:
    Token *token;
    string content;
    int other;
    int type;
    int index_in_list;
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
        cout << "("
             << op.content << ", "
             << arg1.content << ", "
             << arg2.content << ", "
             << result.content << ")" << endl;
    }

protected:
    Singleton op;
    Singleton arg1;
    Singleton arg2;
    Singleton result;
};

#define error exit(-1)
#define NONE "-"
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

public:
    Parser(vector<Token *> tokens)
    {
        this->tokens = tokens;
        Program();
        AddQuadruple("sys", NONE, NONE, NONE);
    }
    void PrintAsTheyWish(string info)
    {
        cout << info << endl;
        for (int i = 0; i < quadruple_list.size(); i++)
        {
            cout << "(" << i << ")\t";
            quadruple_list[i].Print();
        }
    }

private:
    void Expect(int num)
    {
        if (CURRENT_TOKEN_ID == num)
            current_token_index++;
        else
            error;
    }
    string deal(string str)
    {
        string tp;
        for (int i = 0; i < str.size(); i++)
        {
            tp.push_back(str[i]);
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                string x = GenerateTempVar();
                string y = deal(str.substr(i + 1));
                string op;
                op.push_back(str[i]);
                AddQuadruple(op, str.substr(0, i), y, x);
                return x;
            }
        }
        return tp;
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
        AddQuadruple("Program", (char *)tokens[current_token_index - 2]->info.name, NONE, NONE);
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
            error;
    }

    void VariantDeclaration()
    {
        if (CURRENT_TOKEN_ID == ID)
            DeclarationSpecifiers();
        else
            error;
        Expect(COLON);
        if (CURRENT_TOKEN_ID == BOOL || CURRENT_TOKEN_ID == CHAR || CURRENT_TOKEN_ID == INTEGER)
            current_token_index++;
        else
            error;
        Expect(SEMICOL);
        if (CURRENT_TOKEN_ID == ID)
        {
            VariantDeclaration();
        }
    }
    void DeclarationSpecifiers()
    {
        Expect(ID);
        if (CURRENT_TOKEN_ID == COMMA)
        {
            Expect(COMMA);
            DeclarationSpecifiers();
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
            string var = (char *)tokens[current_token_index - 2]->info.name;
            string ret = parseSSA();
            AddQuadruple(":=", ret, NONE, var);
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
        else if (CURRENT_TOKEN_ID == WHILE)
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
                if (quadruple_list[i].result.content == "F")
                    quadruple_list[i].result.content = to_string(Ttrue);
                if (quadruple_list[i].result.content == "T")
                    quadruple_list[i].result.content = to_string((int)quadruple_list.size());
            }
        }
        else if (CURRENT_TOKEN_ID == BEGIN)
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
        if (CURRENT_TOKEN_ID == MINUS)
        {
            ++current_token_index;
            string tp = parseSSC();
            string result = GenerateTempVar();
            AddQuadruple(NONE, "minus", tp, result);
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
                current_token_index++;
                return to_string(tokens[current_token_index - 1]->info.val.i);
            }
            else if (CURRENT_TOKEN_ID == LPAR)
            {
                current_token_index++;
                string x = parseSSA();
                Expect(RPAR);
                return x;
            }
            return (char *)tokens[current_token_index - 1]->info.name;
        }
    }
    string MultiplyAndDivide()
    {
        if (CURRENT_TOKEN_ID == ASTERISK)
        {
            current_token_index++;
            string tp1 = parseSSC();
            string tp2 = MultiplyAndDivide();
            return "*" + tp1 + tp2;
        }
        else if (CURRENT_TOKEN_ID == SLASH)
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
        if (CURRENT_TOKEN_ID == PLUS)
        {
            current_token_index++;
            string tp1 = parseSSB();
            string tp2 = AdditionAndSubtraction();
            return "+" + tp1 + tp2;
        }
        else if (CURRENT_TOKEN_ID == MINUS)
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
                AddQuadruple("jnz", "FALSE", NONE, "T");
                AddQuadruple("j", NONE, NONE, "F");
            }
            else if (CURRENT_TOKEN_ID == TRUE)
            {
                current_token_index++;
                AddQuadruple("jnz", "TRUE", NONE, "T");
                AddQuadruple("j", NONE, NONE, "F");
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
                    string op;
                    if (CURRENT_TOKEN_ID == LESS)
                        op = "<";
                    if (CURRENT_TOKEN_ID == LEQL)
                        op = "<=";
                    if (CURRENT_TOKEN_ID == NEQL)
                        op = "<>";
                    if (CURRENT_TOKEN_ID == EQUAL)
                        op = "=";
                    if (CURRENT_TOKEN_ID == GREATER)
                        op = ">";
                    if (CURRENT_TOKEN_ID == GEQL)
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

#endif

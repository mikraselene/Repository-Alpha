#ifndef SEMATIC_HPP
#define SEMATIC_HPP
#include "lexical.hpp"

using std::function;
using std::pair;
using std::stoi;

#define TOK(x) pair<int, string>(TOK, x)
#define SINGID(x) pair<int, int>(SINGID, x)
#define JROP(x) pair<int, string>(JROP, "j" + x)
#define INTC(x) pair<int, int>(INTC, x)

struct Singleton
{
    Singleton() : info(NONE), content("-"), poc(-1) {}
    Singleton(int t) : info(t), content(singleton_str[t]), poc(-1) {}
    Singleton(pair<int, string> p) : info(p.first), content(p.second), poc(-1) {}
    Singleton(pair<int, int> p) : info(p.first), content(to_string(p.second)), poc(p.second) {}
    int info;
    string content;
    int poc;
};

struct Quadruple
{
    Quadruple(Singleton op, Singleton arg1, Singleton arg2, Singleton result)
        : op(op), arg1(arg1), arg2(arg2), result(result) {}
    Singleton op;
    Singleton arg1;
    Singleton arg2;
    Singleton result;
};

#define Error(message)                               \
    prog.Error(message, CURRENT_POS, CURRENT_COORD); \
    prog.Exeunt();

#define CURRENT_POS tokens[current_token_index - 1]->pos
#define CURRENT_COORD tokens[current_token_index - 1]->coordinate

class Parser
{
    int current_token_index = 0;
    int temp_variable_index = 0;
    vector<Token *> tokens;
    vector<Quadruple> quadruple_list;

public:
    Parser(vector<Token *> tokens) : tokens(tokens)
    {
        Program();
        function<Quadruple(Quadruple)> f = [&](Quadruple elem) -> Quadruple {
            return NEXT_QUADRUPLE.op.info == JUMP ? f(NEXT_QUADRUPLE) : elem;
        };
        for (Quadruple &elem : quadruple_list)
        {
            if (elem.op.info == JUMP)
            {
                elem = f(elem);
            }
        }
        AddQuadruple(SYS, NONE, NONE, NONE);
    }
    void PrintAsTheyWish(string info)
    {
        int w = 10;
        cout << info << endl;
        cout << "     (        OP,      ARG1,      ARG2,    RESULT)" << endl;
        for (int i = 0; i < quadruple_list.size(); i++)
        {
            cout << setw(3) << i << ". ";
            Quadruple q = quadruple_list[i];
            cout << "("
                 << setw(w) << q.op.content << ","
                 << setw(w) << q.arg1.content << ","
                 << setw(w) << q.arg2.content << ","
                 << setw(w) << q.result.content << ")" << endl;
        }
    }

private:
    void Program()
    {
        Expect(PROGRAM, "expected 'program'");
        Expect(ID, "expected an identifier");
        Expect(SEMICOL, "expected ';'");
        string name = tokens[current_token_index - 2]->info.name;
        AddQuadruple(PROG, TOK(name), NONE, NONE);
        if (CURRENT_TOKEN_ID == VAR)
        {
            Expect(VAR, "expected 'var'");
            VariableDeclaration();
        }
        if (CURRENT_TOKEN_ID == BEGIN)
        {
            Expect(BEGIN, "expected 'begin'");
            IdentifierList();
            Expect(END, "expected 'end'");
        }
        else
        {
            Error("expected 'var' or 'begin'");
        }
    }

    void VariableDeclaration()
    {
        if (CURRENT_TOKEN_ID == ID)
        {
            DeclarationSpecifiers();
        }
        else
        {
            Error("expected an identifier");
        }
        Expect(COLON, "expected ':'");
        if (CURRENT_TOKEN_ID == BOOL || CURRENT_TOKEN_ID == CHAR || CURRENT_TOKEN_ID == INTEGER)
        {
            current_token_index++;
        }
        else
        {
            Error("unknown type name"); // FIXME:
        }
        Expect(SEMICOL, "expected ';'");
        if (CURRENT_TOKEN_ID == ID)
        {
            VariableDeclaration();
        }
    }
    void DeclarationSpecifiers()
    {
        Expect(ID, "expected an identifier");
        if (CURRENT_TOKEN_ID == COMMA)
        {
            Expect(COMMA, "expected ','");
            DeclarationSpecifiers();
        }
    }
    void IdentifierList()
    {
        Statement();
        if (CURRENT_TOKEN_ID == SEMICOL)
        {
            current_token_index++;
            IdentifierList();
        }
    }

    void Statement()
    {
        switch (CURRENT_TOKEN_ID)
        {
        case ID: // assignment_statement
        {
            Expect(ID, "expected an identifier");
            Expect(ASSIGN, "expected ':='");
            string result = tokens[current_token_index - 2]->info.name;
            Singleton arg1 = MultiplicativeExpression();
            AddQuadruple(ASGN, arg1, NONE, TOK(result));
            break;
        }
        case IF: // selection statement
        {
            int cur = quadruple_list.size();
            Expect(IF, "expected 'if'");
            BooleanExpression();
            Expect(THEN, "expected 'then'");
            int t = quadruple_list.size();
            Statement();
            int f = quadruple_list.size();
            if (CURRENT_TOKEN_ID == ELSE)
            {
                AddQuadruple(JUMP, NONE, NONE, NONE);
                f++;
                int temp = quadruple_list.size() - 1;
                Expect(ELSE, "expected 'else'");
                Statement();
                quadruple_list[temp].result = SINGID(quadruple_list.size());
            }
            for (int i = cur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.info == TRES)
                {
                    quadruple_list[i].result = SINGID(t);
                }
                if (quadruple_list[i].result.info == FRES)
                {
                    quadruple_list[i].result = SINGID(f);
                }
            }
            break;
        }
        case WHILE: // iteration statement
        {
            Expect(WHILE, "expected 'while'");
            int cur = quadruple_list.size();
            BooleanExpression();
            Expect(DO, "expected 'do'");
            int t = quadruple_list.size();
            Statement();
            AddQuadruple(JUMP, NONE, NONE, SINGID(cur));
            int f = quadruple_list.size();
            for (int i = cur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.info == TRES)
                {
                    quadruple_list[i].result = SINGID(t);
                }
                if (quadruple_list[i].result.info == FRES)
                {
                    quadruple_list[i].result = SINGID(f);
                }
            }
            break;
        }
        case REPEAT: // iteration statement
        {
            int t = quadruple_list.size();
            Expect(REPEAT, "expected 'repeat'");
            Statement();
            int cur = quadruple_list.size();
            Expect(UNTIL, "expected 'until'");
            BooleanExpression();
            for (int i = cur; i < quadruple_list.size(); i++)
            {
                if (quadruple_list[i].result.info == FRES)
                {
                    quadruple_list[i].result = SINGID(t);
                }
                if (quadruple_list[i].result.info == TRES)
                {
                    quadruple_list[i].result = SINGID(quadruple_list.size());
                }
            }
            break;
        }
        case BEGIN: // compound statement
        {
            Expect(BEGIN, "expected 'begin'");
            IdentifierList();
            Expect(END, "expected 'end'");
            break;
        }
        default:
        {
            Error("Invaild.\n");
        }
        }
    }

    Singleton ArithmeticExpression(string str)
    {
        string t;
        for (int i = 0; i < str.size(); i++)
        {
            t.push_back(str[i]);
            if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
            {
                Singleton result = GenerateTempVar();
                Singleton arg2 = ArithmeticExpression(str.substr(i + 1));
                string opc;
                opc.push_back(str[i]);
                Singleton op = TOK(opc);
                AddQuadruple(op, TOK(str.substr(0, i)), arg2, result);
                return result;
            }
        }
        return TOK(t);
    }
    Singleton MultiplicativeExpression()
    {
        string t1 = UnaryExpression().content;
        string t2 = AdditionAndSubtraction().content;
        return ArithmeticExpression(t1 + t2);
    }
    Singleton UnaryExpression()
    {
        string t1 = PrimaryExpression().content;
        string t2 = MultiplyAndDivide().content;
        return ArithmeticExpression(t1 + t2);
    }
    Singleton PrimaryExpression()
    {
        if (CURRENT_TOKEN_ID == MINUS)
        {
            current_token_index++;
            Singleton arg2 = PrimaryExpression();
            Singleton result = GenerateTempVar();
            AddQuadruple(NONE, NEG, arg2, result);
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
                return INTC(tokens[current_token_index++]->info.val.i);
            }
            else if (CURRENT_TOKEN_ID == LPAR)
            {
                current_token_index++;
                Singleton s = MultiplicativeExpression();
                Expect(RPAR, "expected ')'");
                return s;
            }
            return TOK(tokens[current_token_index - 1]->info.name);
        }
    }
    Singleton MultiplyAndDivide()
    {
        if (CURRENT_TOKEN_ID == ASTERISK || CURRENT_TOKEN_ID == SLASH)
        {
            Singleton op = TOK(token_str[CURRENT_TOKEN_ID]);
            current_token_index++;
            Singleton tp1 = PrimaryExpression();
            Singleton tp2 = MultiplyAndDivide();
            return TOK(op.content + tp1.content + tp2.content);
        }
        else
        {
            return TOK("");
        }
    }
    Singleton AdditionAndSubtraction()
    {
        if (CURRENT_TOKEN_ID == PLUS || CURRENT_TOKEN_ID == MINUS)
        {
            Singleton op = TOK(token_str[CURRENT_TOKEN_ID]);
            current_token_index++;
            Singleton tp1 = UnaryExpression();
            Singleton tp2 = AdditionAndSubtraction();
            return TOK(op.content + tp1.content + tp2.content);
        }
        else
        {
            return TOK("");
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
            quadruple_list[quadruple_list.size() - 1].result =
                SINGID(quadruple_list.size());
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
            quadruple_list[quadruple_list.size() - 2].result =
                SINGID(quadruple_list.size());
            BooleanConstant();
            LogicalAndExpression();
        }
    }
    void BooleanConstant()
    {
        switch (CURRENT_TOKEN_ID)
        {
        case NOT:
        {
            current_token_index++;
            BooleanConstant();
            break;
        }
        case FALSE:
        {
            current_token_index++;
            AddQuadruple(JNZ, FARG, NONE, TRES);
            AddQuadruple(JUMP, NONE, NONE, FRES);
            break;
        }
        case TRUE:
        {
            current_token_index++;
            AddQuadruple(JNZ, TARG, NONE, TRES);
            AddQuadruple(JUMP, NONE, NONE, FRES);
            break;
        }
        case LPAR:
        {
            Expect(LPAR, "expected '('");
            BooleanExpression();
            Expect(RPAR, "expected ')'");
            break;
        }
        default:
        {
            Singleton arg1 = MultiplicativeExpression();
            if (CURRENT_TOKEN_ID >= LESS && CURRENT_TOKEN_ID <= GEQL)
            {
                int tp = quadruple_list.size();
                string rop = token_str[CURRENT_TOKEN_ID];
                current_token_index++;
                AddQuadruple(JROP(rop), arg1, NONE, TRES);
                AddQuadruple(JUMP, NONE, NONE, FRES);
                Singleton arg2 = MultiplicativeExpression();
                quadruple_list[tp].arg2 = arg2;
                return;
            }
            AddQuadruple(JNZ, arg1, NONE, TRES);
            AddQuadruple(JNZ, NONE, NONE, FRES);
        }
        }
    }

    Singleton GenerateTempVar()
    {
        return TOK("T" + to_string(++temp_variable_index));
    }
    void AddQuadruple(Singleton op, Singleton arg1, Singleton arg2, Singleton result)
    {
        quadruple_list.push_back(Quadruple(op, arg1, arg2, result));
    }
    void Expect(int num, const char *message)
    {
        if (CURRENT_TOKEN_ID == num)
        {
            current_token_index++;
        }
        else
        {
            Error(message);
        }
    }
};

#endif
#include <iostream>
#include <list>
#include "lex.h"
using namespace std;

/*
enum Type
{
	ERROR = 0,
	KEY,
	DELIMITER,
	ARITHMETICOPTR,
	RELATIONOPTR,
	NUMBER,
	ID,
	CHAR,
	STRING,
	COMMENT
};

const string typestr[] = {
	"ERROR",
	"KEY",
	"DELIMITER",
	"ARITHMETICOPTR",
	"RELATIONOPTR",
	"NUMBER",
	"IDENTIFIER",
	"CHAR",
	"STRING",
	"COMMENT"};

#define TOKEN(a, b, c) a = b
enum
{
	FLOAT = 1,
	DOUBLE = 2,
	CHAR = 3,
	SHORT = 4,
	INT = 5,
	UNSIGNED = 6,
	POINTER = 7,
	VOID = 8,
	STRUCT = 9,
	UNION = 10,
	FUNCTION = 11,
	ARRAY = 12,
	ENUM = 13,
	LONG = 14,
	CONST = 15,
	VOLATILE = 16,
	ID = 32,
	FLTCON = 34,
	INTCON = 35,
	STRCON = 36,
	INCR = 39,
	DECR = 48,
	DEREF = 49,
	ANDAND = 50,
	OROR = 51,
	LEQL = 52,
	EQL = 53,
	NEQ = 54,
	GEQL = 55,
	RSHIFT = 56,
	LSHIFT = 57,
	ELLIPSIS = 64,
	SIZEOF = 65,
	AUTO = 67,
	BREAK = 68,
	CASE = 69,
	CONTINUE = 70,
	DEFAULT = 71,
	DO = 72,
	ELSE = 73,
	EXTERN = 74,
	FOR = 75,
	GOTO = 76,
	IF = 77,
	REGISTER = 78,
	RETURN = 79,
	SIGNED = 80,
	STATIC = 81,
	SWITCH = 82,
	TYPEDEF = 83,
	WHILE = 84,
	TYPECODE = 85,
	FIRSTARG = 86,
	EOI = 127,
};

class Token
{
public:
	Token(unsigned int number, string word, Type type, unsigned int row, unsigned int colomn)
	{
		this->number = number;
		this->word = word;
		this->type = type;
		this->position = {row, colomn};
	}

	friend ostream &operator<<(ostream &out, Token t)
	{
		out << "#" << t.number << ", "
			<< t.word << ", "
			<< typestr[t.type] << ", "
			<< "(" << t.position.row << ", " << t.position.colomn << ")" << endl;
		return out;
	}

private:
	unsigned int number;
	string word;
	struct Tuple
	{
		unsigned int x;
		unsigned int y;
	} tuple;
	Type type;
	struct Position
	{
		unsigned int row;
		unsigned int colomn;
	} position;
};

class TokenStream
{
public:
	TokenStream()
	{
	}
	void Add(Token t)
	{
		token_list.push_back(t);
	}
	void DeleteFirst()
	{
		token_list.pop_front();
	}
	void DeleteLast()
	{
		token_list.pop_back();
	}
	void Print()
	{
		for (Token t : token_list)
		{
			cout << t;
		}
	}

private:
	list<Token> token_list;
};
*/
#define BLACK "\e[30m"
#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define BLUE "\e[34m"
#define PURPLE "\e[35m"
#define CYAN "\e[36m"
#define WHITE "\e[37m"

#define BLACK_BACKGROUND "\e[40m"
#define RED_BACKGROUND "\e[41m"
#define GREEN_BACKGROUND "\e[42m"
#define YELLOW_BACKGROUND "\e[43m"
#define BLUE_BACKGROUND "\e[44m"
#define PURPLE_BACKGROUND "\e[45m"
#define CYAN_BACKGROUND "\e[46m"
#define WHITE_BACKGROUND "\e[47m"

#define RESET_COLOR "\e[0m"
int main()
{
	string v[128];
	int t[128];
#define TOKEN(num, type, name, str) v[num] = str;
#include "token.h"
#undef TOKEN

#define TOKEN(num, type, name, str) t[num] = type;
#include "token.h"
#undef TOKEN

	unsigned char *pp =
		(unsigned char *)"void Func(int i,int j){for(int i=1;i<=4;i++){if(a+b>=8/2)/*hello world*/{p=func(s);}else{p=r*2;return p;}printf(a+b*c-d/e);}}";
	unsigned char *qq =
		(unsigned char *)"void print(){printf(this);}int main(){int i;int n=1+3*2-5;for(i=1;i<=n;i++){/*hello*/printf(h);print();}printf(s);/*salve=hello*/}";
	cp = qq;
	while (*cp != '\0')
	{
		int tok = GetToken();
		switch (t[tok])
		{
		case KEYWORD:
			cout << PURPLE;
			break;
		case IDENTIFIER:
			cout << YELLOW;
			break;
		case NUMBER:
			cout << BLUE;
			break;
		case OPERATOR:
			cout << GREEN;
			break;
		default:
			break;
		}
		cout << v[tok] << RESET_COLOR << "";
	}
	cout << endl;
}
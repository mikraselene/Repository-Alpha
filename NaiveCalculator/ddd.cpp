#include <iostream>
#include <vector>
#include <cmath>
#include <stack>
using namespace std;

class Express
{
public:
	Express(string input)
	{
		express = input + "$";
		token = "";
		pos = 0;
		length = 1 + express.size();
		while (token != "$")
		{
			GetToken();
			cout << token << " ";
		}
	}

private:
	int GetOptIndex(string opt)
	{
		for (int i = 0; i < optSet.size(); i++)
		{
			if (opt == optSet[i])
			{
				return i;
			}
		}
		return -1;
	}
	int GetFuncIndex(string func)
	{
		for (int i = 0; i < funcSet.size(); i++)
		{
			if (func == funcSet[i])
			{
				return i;
			}
		}
		return -1;
	}

	double ElementaryOperation(string opt, double arg[])
	{
		double x = arg[0];
		double y = arg[1];
		enum
		{
			ADDITION = 1,
			SUBTRACTION = 2,
			MULTIPLICATION = 3,
			DIVISION = 4,
		};
		switch (GetOptIndex(opt))
		{
		case ADDITION:
			return x + y;
		case SUBTRACTION:
			return x - y;
		case MULTIPLICATION:
			return x * y;
		case DIVISION:
			return x / y;
		default:
			return x;
		}
	}
	double FunctionalOperation(string func, double arg[])
	{
		double x = arg[0];
		double y = arg[1];
		enum
		{
			SIN = 1,
			COS = 2,
			TAN = 3,
			ASIN = 4,
			ACOS = 5,
			ATAN = 6,
			SINH = 7,
			COSH = 8,
			TANH = 9,
			ASINH = 10,
			ACOSH = 11,
			ATANH = 12,
			LOG = 13,
			LOG2 = 14,
			LG = 15,
			LN = 16,
			EXP = 17,
			SQRT = 18,
			CBRT = 19,
			FRAC = 20,
			ABS = 21,
		};
		switch (GetFuncIndex(func))
		{
		case SIN:
			return sin(x);
		case COS:
			return cos(x);
		case TAN:
			return tan(x);
		case ASIN:
			return asin(x);
		case ACOS:
			return acos(x);
		case ATAN:
			return atan(x);
		case SINH:
			return sinh(x);
		case COSH:
			return cosh(x);
		case TANH:
			return tanh(x);
		case ASINH:
			return asinh(x);
		case ACOSH:
			return acosh(x);
		case ATANH:
			return atanh(x);
		case LOG:
			return log(y) / log(x);
		case LOG2:
			return log2(x);
		case LG:
			return log10(x);
		case LN:
			return log(x) / log(exp(1));
		case EXP:
			return exp(x);
		case SQRT:
			return sqrt(x);
		case CBRT:
			return cbrt(x);
		case FRAC:
			return 1;
		case ABS:
			return abs(x);
		default:
			return 0;
		}
	}

	void GetToken()
	{
		int posR = pos;

		while (posR != express.size() && express[posR] == ' ')
		{
			posR++;
		}

		char ch = express[pos];
		pos++;
		char next = pos < express.size() ? express[pos] : 0;
		if (isdigit(ch) || (ch == '-' && isdigit(next) && type != NUMBER))
		{
			if (ch == '-')
			{
				pos++;
			}
			while (pos != express.size() && isdigit(ch = express[pos]))
			{
				pos++;
			}
			if (ch == '.')
			{
				pos++;
				while (pos != express.size() && isdigit(express[pos]))
				{
					pos++;
				}
			}
			type = NUMBER;
		}
		else if (GetOptIndex(string(1, ch)) != -1)
		{
			type = OPERATOR;
		}
		else if (isalpha(ch))
		{

			while (pos != express.size() && (isalnum(ch) || ch == '_'))
			{
				pos++;
				ch = express[pos];
			}
			if (ch == '(')
			{
				if (GetFuncIndex(express.substr(posR, pos - posR)))
				{
					type = FUNCTION;
				}
				else
				{
					type = UNKNOWN;
				}
			}
			else
			{
				type = UNKNOWN;
			}
		}
		else
		{
			type = UNKNOWN;
		}
		token = express.substr(posR, pos - posR);
	}

	int ComparePriority(string opt1, string opt2)
	{
		int index1 = GetOptIndex(opt1);
		int index2 = GetOptIndex(opt2);
		return priorityMap[index1][index2];
	}

	void Calculate()
	{
		stack<string> optr;
		stack<string> opnd;
		optr.push("$");
		pos = 0;
		GetToken();
		while (type != ENDSIGN || !optr.empty())
		{
			if (type == UNKNOWN)
			{
				//TODO:
			}
			if (type == NUMBER)
			{
				opnd.push(token); //TODO:
				GetToken();
			}
			else
			{
				int priority = ComparePriority(optr.top(), token);
				switch (priority)
				{
				case L:
					optr.push(token);
					GetToken();
					break;
				case G:
				{
					string opt = optr.top();
					optr.pop();
					int index = GetOptIndex(opt);
					int cnt = 0;
					double args[4] = {0};
					double res = 0;
					if (index != -1)
					{
						cnt = optArg[index];
					}
					break;
				}
				case E:
					optr.pop();
					GetToken();
					break;
				}
			}
		}
	}

	enum
	{
		G = 1,
		L = -1,
		E = 0,
	};
	static const vector<const vector<const int>> priorityMap;
	static const vector<const string> optSet;
	static const vector<const int> optArg;
	static const vector<const string> funcSet;
	static const vector<const int> funcArg;

	string express;
	string token;
	typedef enum
	{
		NUMBER,
		OPERATOR,
		FUNCTION,
		ENDSIGN,
		UNKNOWN,
	} TokenType;
	TokenType type;

	int pos;
	int length;
};

#pragma region Initialize Static Data
const vector<const vector<const int>> Express::priorityMap =
	{
		{L, L, L, L, L, L, L, G, G},
		{G, G, G, G, G, G, G, G, G},
		{L, G, G, G, L, L, L, G, G},
		{L, G, G, G, L, L, L, G, G},
		{L, G, G, G, G, G, L, G, G},
		{L, G, G, G, G, G, L, G, G},
		{L, G, L, L, L, L, L, E, G},
		{G, G, G, G, G, G, G, G, G},
		{L, G, L, L, L, L, L, L, E},
};
const vector<const string> Express::optSet =
	{"f(", ",", "+", "-", "*", "/", "(", ")", "$"};
const vector<const int> Express::optArg =
	{0, 1, 2, 2, 2, 2, 0, 0, 0};
const vector<const string> Express::funcSet =
	{
		"sin(", "cos(", "tan(",
		"asin(", "acos(", "atan(",
		"sinh(", "cosh(", "tanh(",
		"asinh(", "acosh(", "atanh(",
		"log(", "log2(", "lg(", "ln(",
		"exp(",
		"sqrt(", "cbrt(",
		"frac(",
		"abs("

};
const vector<const int> Express::funcArg =
	{
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		1, 1, 1,
		2, 1, 1, 1,
		1,
		1, 1,
		1,
		1

};
#pragma endregion

string
Eat(string input)
{
	return input.erase(0, input.find_first_not_of(" "));
}

int main()
{
	string input;
	while (cin >> input)
	{
		Express A(input);
		cout << endl;
	}
}
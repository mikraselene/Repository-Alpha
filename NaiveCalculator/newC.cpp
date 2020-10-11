
/*
    Simple calculator

    This program implements a basic expression calculator.
    Input from cin; output to cout.

    The grammar for input is:

    Calculation:
        Statement
        Print
        Quit
        Calculation Statement
    
    Statement:
        Declaration
        Expression
    
    Declaration:
        "let" Name "=" Expression

    Print:
        ;

    Quit:
        q 

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        Name
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal


        Input comes from cin through the Token_stream called ts.
*/

#include "newC.h"
const char number = '8';
const char quit = 'q';
const char print = ';';
const string prompt = "> ";
const string result = "= ";
const char name = 'a';		  // name token
const char let = 'L';		  // declaration token
const string declkey = "let"; // declaration keyword

class Token
{ /* . to-do[1] . */
public:
	char kind;	  // 记录token的类型
	double value; // 对于浮点数而言：这是浮点数的值
	string name;  // 变量 names: name 自身
	Token(char ch) : kind{ch}, value{0} {}
	Token(char ch, double val) : kind{ch}, value{val} {}
	Token(char ch, string n) : kind{ch}, name{n} {}
};

class Token_stream
{ /* . to-do[2] . */
public:
	Token_stream();		   // 创建一个Token流，从cin读取字符
	Token get();		   // 获取一个Token
	void putback(Token t); // 放回一个Token
	void ignore(char c);   // 忽略直到字符c为止的全部字符（最后字符c也被忽略掉）
private:
	bool full{false}; // 缓冲区中是否有Token
	Token buffer;	  // 存放着通过putback(t)操作放回的Token，这个地方称之为缓冲区
};

void Token_stream::putback(Token t)
{				 /* . to-do[3] . */
	buffer = t;	 // 拷贝t到缓冲区
	full = true; // 表示缓冲区被占用
}

Token Token_stream::get()
{ /* . to-do[4] . */
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch; // >> 会跳过空白（空格、换行、制表符等）

	switch (ch)
	{
	case quit:
	case print:
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch); // 字符表示自己
	case '.':			  // 浮点数的开始
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.putback(ch); // 将数字(或小数点)放回到 标准输入cin 中
		double val;
		cin >> val;				   // cin 自动读取一个 double
		return Token{number, val}; // 用'8'表示读取了一个浮点数
	}
	default:
		if (isalpha(ch))
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
				s += ch;
			cin.putback(ch);
			if (s == declkey)
				return Token(let); // keyword "let"
			return Token{name, s};
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
// c 表示Token的类型
{
	// 先观察缓冲区
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	// 现在查找输入流
	char ch = 0;
	while (cin >> ch)
		if (ch == c)
			return;
}

// to-do[5]
// 构造函数 Token_stream()
Token_stream::Token_stream()
	: full{false}, buffer{0} // no Token in buffer
{
}

Token_stream ts; // provides get() and putback()  // to-do[5]

class Variable
{
public:
	string name;
	double value;
	Variable(string n, double v) : name{n}, value{v} {}
};

vector<Variable> var_table;

double get_value(string s)
// 返回 名字为 s 的变量的 值
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s)
			return var_table[i].value;
	error("get: undefined variable ", s);
}

void set_value(string s, double d)
// 赋值操作 设置命名为 s 的变量 的值 为 d
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == s)
		{
			var_table[i].value = d;
			return;
		}
	error("set: undefined variable ", s);
}

bool is_declared(string var)
//  变量 var 在 var_table 了吗？
{
	for (int i = 0; i < var_table.size(); ++i)
		if (var_table[i].name == var)
			return true;
	return false;
}

double define_name(string var, double val)
// 将(var, val) 加入到 var_table 表中
{
	if (is_declared(var))
		error(var, " declared twice");
	var_table.push_back(Variable{var, val});
	return val;
}

double expression(); // declaration so that primary() can call expression()

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(': // 处理 ‘(’ expression ‘)’
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')')
			error("')' expected");
		return d;
	}
	case number:		// 使用 ‘8’ 来表示一个浮点数
		return t.value; // 返回浮点数的值
	case name:
		return get_value(t.name); // 返回变量的值
	case '-':
		return -primary(); // 处理负数
	case '+':
		return primary();
	default:
		error("primary expected");
	}
}

double term()
{ /* . to-do[7] . */
	double left = primary();
	Token t = ts.get(); // 从 token流 中获取下一个 token

	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0)
				error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0)
				error("divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t); // put t back into the token stream
			return left;
		}
	}

} // deal with * and /

double expression()
{						  /* . to-do[6] . */
	double left = term(); // 读入并计算一个 Term
	Token t = ts.get();	  // 获取下一个 Token

	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term(); // 计算一个 Term 并且 相加
			t = ts.get();
			break;
		case '-':
			left -= term(); // 计算一个 Term 并且 相减
			t = ts.get();
			break;
		default:
			ts.putback(t); // 将 t 放回到 token 流
			return left;   // 再没有+ - 时返回计算结果
		}
	}

} // 处理 + 法 以及 - 法

double declaration()
// 处理: name = expression
// 声明一个变量 "name"，使用初始值 "expression"
{
	Token t = ts.get();
	if (t.kind != name)
		error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=')
		error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (cin)
		try
		{
			cout << prompt;
			Token t = ts.get();
			while (t.kind == print)
				t = ts.get(); // eat ‘;’
			if (t.kind == quit)
				return;
			ts.putback(t);
			cout << result << statement() << '\n';
		}
		catch (exception &e)
		{
			cerr << e.what() << '\n';
			clean_up_mess();
		}
}

int main()
{
	calculate();
	return 0;
}

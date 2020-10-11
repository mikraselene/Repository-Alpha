#include <iostream>

class HammingCode
{
public:
	HammingCode()
	{
		this->str = "";
		this->size = 0;
		this->code = NULL;
	}
	HammingCode(std::string str)
	{
		this->str = str;
		this->size = CheckSize(str.size());
		this->code = new bool[size];
		Encode();
		Print();
	}
	void Encode()
	{
		bool flag = false;
		int ans = 0;
		int j = 0;
		for (int i = 0; i < size; i++)
		{
			code[i] = (i + 1 & i ? str[j++] - '0' : false);
			if (code[i])
			{
				flag ? ans = ans ^ i + 1 : ans = i + 1;
				flag = true;
			}
		}
		for (int mask = 1; mask < size; mask <<= 1)
		{
			code[mask - 1] = mask & ans;
		}
	}
	void Print()
	{
		for (int i = 0; i < size; i++)
		{
			printf("%d", code[i]);
		}
	}

private:
	int CheckSize(int message_size)
	{
		int r = 1;
		do
		{
			r++;
		} while (message_size > (1 << r) - r - 1);
		return message_size + r;
	}

	int size;
	bool *code;
	std::string str;
};

int main()
{
	std::string s;
	int n = 10;
	s.resize(n);
	for (int i = 0; i < n; i++)
	{
		s[i] = rand() % 2 + '0';
	}
	std::cout << "Result:\n";
	HammingCode X(s);
}

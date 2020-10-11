#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node *prev;
	Node *next;
	Node()
	{
		data = 0;
		prev = NULL;
		next = NULL;
	}
};

template <class T>
class Linklist
{
public:
	Linklist(int n)
	{
		start = new Node<int>;
		start->data = n;
		Node<int> *temp = start;
		while (n--)
		{
			int data = n;
			Node<int> *here = new Node<int>;
			here->data = data;
			here->prev = temp;
			temp->next = here;
			temp = here;
		}
		temp->next = start;
		start->prev = temp;
	}
	void XX()
	{
		Node<int> *t = start;
		int n = 12;
		while (n--)
		{
			cout << t->data << " ";
			t = t->prev;
		}
	}

private:
	Node<int> *start;
};

int main()
{
	int n = 4;
	Linklist<int> x(n);
	x.XX();
}
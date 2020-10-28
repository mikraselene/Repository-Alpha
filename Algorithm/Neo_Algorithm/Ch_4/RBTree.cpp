#include <iostream>
using namespace std;

template <class T>
class Node
{
public:
	enum Color
	{
		RED = false,
		BLACK = true,
	};
	Color color;
	Node *left;
	Node *right;
	Node *parent;
	T data;
};

template <class T>
class RBTree
{
public:
	RBTree();
	~RBTree();
	class Iterator
	{
		typedef Node<T> *Pointer;

	public:
		Iterator()
		{
		}
		Iterator(Node<T> *x)
		{
			node = x;
		}
		Iterator(const Iterator &it)
		{
			node = it.node;
		}

		Iterator &operator++()
		{
			if (node->right != NULL)
			{
				node = node->right;
				while (node->left != NULL)
				{
					node = node->left;
				}
			}
			else
			{
				Pointer temp = node->parent;
				while (node == temp->right)
				{
					node = temp;
					temp = temp->parent;
				}
				if (node->right != temp)
				{
					node = temp;
				}
			}
			return *this;
		}
		Iterator &operator--()
		{
			if (node->color == Node<T>::RED && node->parent->parent == node)
			{
				node = node->right;
			}
			else if (node->left != NULL)
			{
				Pointer temp = node->left;
				while (node->left != NULL)
				{
					temp = temp->right;
				}
				node = temp;
			}
			else
			{
				Pointer temp = node->parent;
				while (node == temp->parent)
				{
					node = temp;
					temp = temp->parent;
				}
				node = temp;
			}
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator copy = *this;
			++(*this);
			return copy;
		}
		Iterator operator--(int)
		{
			Iterator copy = *this;
			--(*this);
			return copy;
		}

	private:
		Pointer node;
	};

private:
	Node<T> root;
};
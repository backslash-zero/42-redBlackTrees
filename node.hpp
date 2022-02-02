#pragma once

namespace ft
{

#define RED true
#define BLACK false

#define RIGHT true
#define LEFT false

	template <class T>
	struct Node
	{
	private:
		bool _color;

	public:
		T data;

		Node *left;
		Node *right;
		Node *parent;

		bool getColor(void) { return _color; };
		void setColor(bool color) { this->_color = color; };

		// Constructor with data
		Node(const T &src = T())
			: _color(RED),
			  data(src),
			  left(NULL),
			  right(NULL),
			  parent(NULL)

				  {};
	};

	template <class T>
	Node<T> *min_node(Node<T> *node)
	{
		while (node && node->left != NULL)
			node = node->left;
		return (node);
	};

	template <class T>
	Node<T> *max_node(Node<T> *node)
	{
		while (node && node->right != NULL)
			node = node->right;
		return (node);
	};
};
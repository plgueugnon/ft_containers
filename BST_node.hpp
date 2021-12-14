#ifndef __BST_NODE_H__
#define __BST_NODE_H__

namespace ft
{
	template<typename T>
	struct BST_node
	{
		/* la value reçue dans BST_node est une paire key, value */
		typedef T value_type;
		T			value;
		BST_node	*parent;
		BST_node	*left;
		BST_node	*right;

		/* default constructor */
		BST_node() : value(), parent(nullptr), left(nullptr), right(nullptr) {}
		/* constructor by value - giving a new value and a default color */
		BST_node(const T& value) : value(value), parent(nullptr), left(nullptr), right(nullptr) {}
		/* destructor */
		virtual ~BST_node() {}
		/* copy constructor */ // is_used ?
		BST_node(BST_node const &x) : value(x.value), parent(x.parent), left(x.left), right(x.right) {}

		/* assignement operator */
		BST_node	&operator=(BST_node const &rhs)
		{
			if (*this != rhs)
			{
				value =  rhs.value;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
			}
			return ( *this );
		}
	};
}

#endif // __BST_NODE_H__
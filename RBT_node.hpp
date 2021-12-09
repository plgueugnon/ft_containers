#ifndef __RBT_NODE_H__
#define __RBT_NODE_H__

enum e_color { RED, BLACK };

namespace ft
{
	template<typename T>
	struct RBT_node
	{
		/* la value reçue dans RBT_node est mapped_value */
		T			value;
		RBT_node	*parent;
		RBT_node	*left;
		RBT_node	*right;
		e_color		color;

		/* default constructor */
		RBT_node() : value(), parent(nullptr), left(nullptr), right(nullptr), color() {}
		/* constructor by value - giving a new value and a default color */
		RBT_node(const T& value, e_color color = RED) : parent(nullptr), right(nullptr), left(nullptr), value(value), color(color) {}
		/* destrutor */
		~RBT_node();
		/* copy constructor */ // is_used ?
		RBT_node(RBT_node const &x) : value(x.value), parent(x.parent), left(x.left), right(x.right), color(x.color) {}

		/* assignement operator */
		RBT_node	&operator(RBT_node const &rhs)
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

#endif // __RBT_NODE_H__
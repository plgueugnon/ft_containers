/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST_node.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:34:35 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 18:34:36 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BST_NODE_H__
#define __BST_NODE_H__

#include <cstddef>

/* wrapper around an object of class pair */
namespace ft
{
	template<typename T>
	struct BST_node
	{
		/*
		* value stored in object BST_node is an object of class pair,
		* with a key and a value as its first and second argument
		*/
		typedef T value_type;
		T			value;
		BST_node	*parent;
		BST_node	*left;
		BST_node	*right;

		/* default constructor */
		BST_node() : value(), parent(nullptr), left(nullptr), right(nullptr) {}

		/* constructor by value - giving a new value */
		BST_node(const T& value) : value(value)
		{
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}

		/* destructor */
		virtual ~BST_node() {}

		/* copy constructor */
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
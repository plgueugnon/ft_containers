/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 18:31:18 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 18:31:34 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BST_ITERATOR_H__
#define __BST_ITERATOR_H__

#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include "BST_node.hpp"

/* struct BST_iterator is a wrapper of a BST_node object to iterate through our BST */
namespace ft
{
	template<typename T>
	class BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T*																						node_ptr;
			typedef typename T::value_type																	value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

		private:
			node_ptr	_node;
			node_ptr	_parent;

		public:
			/* default constructor */
			BST_iterator() : _node(nullptr) {}
			BST_iterator(node_ptr node) : _node(node) {}
			BST_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {}

			/* copy constructor */
			BST_iterator(const BST_iterator &src) : _node(src._node), _parent(src._parent) {}

			/* assignment operator */
			BST_iterator	&operator=(const BST_iterator &rhs)
			{
				if (*this != rhs)
					_node = rhs._node;
					_parent = rhs._parent;
				return ( *this );
			}

			/* destructor */
			virtual ~BST_iterator() {}

			/* here we have to access the value element of struct BST_node received as argument */
			reference	operator*( void ) const { return ( _node->value ); }
			pointer	operator->( void ) const { return ( &( operator*() ) );}
			node_ptr	base() const { return ( _node ); }
			node_ptr	pbase() const { return (_parent); }

			 /*
			 * operator used to go to next value up in the tree 
			 * works as follows : if there is a right child,
			 * go right then go to leftmost value
			 * in other case go up the parent node until its child
			 * is the node from which we started
			 */
			BST_iterator	&operator++()
			{
				if (_node != NULL)
				{
					if (_node->right)
					{
						_node = _node->right;
						while (_node->left)
							_node = _node->left;
					}
					else
					{
						while (_node->parent && _node->parent->right == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return ( *this );
			}

			BST_iterator	operator++(int)
			{
				BST_iterator tmp = *this;
				operator++();
				return ( tmp );
			}

			/* operator used to go to next value down in the tree */
			BST_iterator	&operator--()
			{
				if (_node != NULL)
				{
					_parent = _node;
					if (_node->left)
					{
						_node = _node->left;
						while (_node->right)
							_node = _node->right;
					}
					else
					{
						while (_node->parent && _node->parent->left == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return ( *this );
			}

			BST_iterator	operator--(int)
			{
				BST_iterator tmp = *this;
				operator--();
				return ( tmp );
			}

			/* necessary to be able to use operator++ and operator-- */
			bool operator==(const BST_iterator &rhs) const { return ( _node == rhs._node ); }
			bool operator!=(const BST_iterator &rhs) const { return ( _node != rhs._node ); }
	};

	/* 
	* second class iterator almost identical to the first except allows 
	* to cast const iterator with const value in the node object wrapped within
	*/
	template<typename T>
	class BST_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T*																						node_ptr;
			typedef typename T::value_type const															value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type		difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer				pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

		private:
			node_ptr	_node;
			node_ptr	_parent;

		public:
			/* default constructor */
			BST_const_iterator() : _node(nullptr) {}
			BST_const_iterator(node_ptr node) : _node(node) {}
			BST_const_iterator(node_ptr node, node_ptr parent) : _node(node), _parent(parent) {}

			/* copy constructor */

			/* templated copy constructor to fix issue with construct in case of a const reverse iterator */
			template<typename BST_iterator>
			BST_const_iterator(const BST_iterator &src) : _node(src.base()), _parent(src.pbase()) {}
			BST_const_iterator(const BST_const_iterator &src) : _node(src._node), _parent(src._parent) {}

			/* assignment operator */
			BST_const_iterator	&operator=(const BST_const_iterator &rhs)
			{
				if (*this != rhs)
					_node = rhs._node;
					_parent = rhs._parent;
				return ( *this );
			}

			/* destructor */
			virtual ~BST_const_iterator() {}

			/* here we have to access the value element of struct BST_node received as argument */
			reference	operator*( void ) const { return ( _node->value ); }
			pointer	operator->( void ) const { return ( &( operator*() ) );}
			node_ptr	base() const { return ( _node ); }

			 /* used to go to next value up in the tree */
			BST_const_iterator	&operator++()
			{
				if (_node != NULL)
				{
					if (_node->right)
					{
						_node = _node->right;
						while (_node->left)
							_node = _node->left;
					}
					else
					{
						while (_node->parent && _node->parent->right == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				return ( *this );
			}

			BST_const_iterator	operator++(int)
			{
				BST_const_iterator tmp = *this;
				operator++();
				return ( tmp );
			}

			/* used to go to next value down in the tree */
			BST_const_iterator	&operator--()
			{
				if (_node != NULL)
				{
					_parent = _node;
					if (_node->left)
					{
						_node = _node->left;
						while (_node->right)
							_node = _node->right;
					}
					else
					{
						while (_node->parent && _node->parent->left == _node)
							_node = _node->parent;
						_node = _node->parent;
					}
				}
				else
					_node = _parent;
				return ( *this );
			}

			BST_const_iterator	operator--(int)
			{
				BST_const_iterator tmp = *this;
				operator--();
				return ( tmp );
			}

			/* necessary to be able to use operator++ and operator-- */
			bool operator==(const BST_const_iterator &rhs) const { return ( _node == rhs._node ); }
			bool operator!=(const BST_const_iterator &rhs) const { return ( _node != rhs._node ); }
	};
}


#endif // __BST_ITERATOR_H__
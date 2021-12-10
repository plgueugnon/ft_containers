#ifndef __BST_ITERATOR_H__
#define __BST_ITERATOR_H__

#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include "BST_node.hpp"

// va recevoir un pointeur sur un objet de type BST_node
namespace ft
{
	template<typename T>
	class BST_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T*																			node_ptr;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		private:
			node_ptr	_node;

		public:
			/* default constructor */
			BST_iterator() : _node(nullptr) {}
			/* copy constructor */
			BST_iterator(const node_ptr pointer ) : _node(pointer) {}
			/* assignment operator */
			BST_iterator	&operator=(const BST_iterator &rhs)
			{
				if (*this != rhs)
					_node = rhs._node;
				return ( *this );
			}

			/* destructor */
			~BST_iterator() {}

			/* const conversion operator */
			operator	BST_iterator<const T>() const { return ( BST_iterator<const T>(_node) ); }

			// je dois acceder a l'element value car mon pointeur est sur un objet BST_node et non sur 
			// un tableau comme dans vector me permettant d'accéder directement à l'information sous-jacente
			reference	operator*( void ) const { return ( *_node->value ); }
			pointer	operator->( void ) const { return ( &( operator*() ) );}
			node_ptr	base() { return ( _node ); }

			 /* used to go to next value up in the tree */
			BST_iterator	&operator++()
			{
				// peut etre necessaire securiser avec if !NULL
				if (_node->right) // si fils droite
				{
					_node = _node->right; // je vais a droite
					while (_node->left) // puis je vais trouver la valeur la plus a gauche
						_node = _node->left;
				}
				else
				{
					while (_node->parent && _node->parent->right == _node) // si ptr de droite est celui de depart => on est remonté de 1 // puis recheck
						_node = _node->parent;
					_node = _node->parent; // j'actualise toujours sur node parent pr cas ou on remonte de la gauche
				}
				return ( *this );
			}

			BST_iterator	operator++(int)
			{
				BST_iterator tmp = *this;
				operator++();
				return ( tmp );
			}

			/* used to go to next value down in the tree */
			BST_iterator	&operator--()
			{
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
}


#endif // __BST_ITERATOR_H__
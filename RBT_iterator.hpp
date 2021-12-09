#ifndef __RBT_ITERATOR_H__
#define __RBT_ITERATOR_H__

#include "ft_iterator.hpp"
#include "RBT_node.hpp"
// va recevoir un pointeur sur un objet de type RBT

namespace ft
{
	template<typename T>
	class RBT_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef T*																			node_ptr;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;

		private:
			node_ptr	_ptr;

		public:
			/* default constructor */
			RBT_iterator() : _ptr(nullptr) {}
			/* copy constructor */
			RBT_iterator(const node_ptr pointer ) : _ptr(pointer) {}
			/* assignment operator */
			RBT_iterator	&operator=(const RBT_iterator &rhs)
			{
				if (*this != rhs)
					_ptr = rhs._ptr;
				return ( *this );
			}

			/* destructor */
			~RBT_iterator() {}

			/* const conversion operator */
			operator	RBT_iterator<const T>() const { return ( RBT_iterator<const T>(_ptr) ); }

			// je dois acceder a l'element value car mon pointeur est sur un objet RBT_node et non sur 
			// un tableau comme dans vector me permettant d'accéder directement à l'information sous-jacente
			reference	operator*( void ) const { return ( *_ptr->value ); }
			pointer	operator->( void ) const { return ( &( operator*() ) );}
			node_ptr	base() { return ( _ptr ); }

			RBT_iterator	&operator++()
			{
				// peut etre necessaire securiser avec if !NULL
				if (_ptr->right) // si fils droite
				{
					_ptr = _ptr->right; // je vais a droite
					while (_ptr->left) // puis je vais trouver la valeur la plus a gauche
						_ptr = _ptr->left;
				}
				else
				{
					node_ptr parent = _ptr->parent; // je pointe sur le parent
					while (parent->right == _ptr) // si ptr de droite est celui de depart => on est remonté de 1
					{
						_ptr = parent; // actualise ptr sur parent
						parent = _ptr->parent; // remonte parent de 1
					}
					if (_ptr->right != parent) // si ptr droite
						_ptr = parent;
				}
			}

			RBT_iterator	operator++(int) {}
			RBT_iterator	&operator--() {}
			RBT_iterator	operator--(int) {}




	};
}


#endif // __RBT_ITERATOR_H__
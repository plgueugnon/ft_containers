#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>

namespace ft
{

/* https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls */

// creation d'un template iterator pour tout les types d'iterator
	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template<class T>
	class input_iterator : public ft::iterator<input_iterator_tag, T> {
		/* common to all iterator */
		iterator( const iterator& );
		~iterator( void );
		iterator&	operator=( const iterator& );
		iterator&	operator++( void ); // prefix increment
		iterator&	operator++( int ); // postfix increment

		/* input_iterator specific */
		bool	operator==(iterator const &rhs) const;
		bool	operator!=(iterator const &rhs) const;
		iterator&	operator*( void );
		iterator*	operator->( void );
	};

	class output_iterator : public ft::iterator<output_iterator_tag, T> {
		iterator

	};
// 	operator*
// operator->
// operator=
	// bool	operator==( Fixed const &rhs ) const;
	// bool	operator!=( Fixed const &rhs ) const;
	// bool	operator<( Fixed const &rhs ) const;
	// bool	operator>( Fixed const &rhs ) const;
	// bool	operator<=( Fixed const &rhs ) const;
	// bool	operator>=( Fixed const &rhs ) const;
	// Fixed	operator+( Fixed const &rhs );	
	// Fixed	operator-( Fixed const &rhs );
	// Fixed	operator*( Fixed const &rhs );
	// Fixed	operator/( Fixed const & rhs );
	// Fixed	&operator++( void ); // Prefix increment operator.
	// Fixed	operator++(int); // Postfix increment operator.
	// Fixed	&operator--( void );
	// Fixed	operator--(int);


}

#endif // __ITERATOR_H__
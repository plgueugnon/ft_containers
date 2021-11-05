#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>

namespace ft
{

/* https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls */

// creation d'un template iterator pour tout les types d'iterator
	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator_traits {
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
	class base_iterator {
		/* common to all iterator */
		iterator( const base_iterator& ); // constructeur par copie
		~iterator( void ); // constructeur par défaut
		iterator&	operator=( const iterator& ); // pb avoir assigmnment operator en pour input
		iterator&	operator++( void ); // prefix increment
		iterator	operator++( int ); // postfix increment
	};

	template<class T>
	class input_iterator : public base_iterator, public ft::iterator_traits<input_iterator_tag, T> {
		bool	operator==(input_iterator const &rhs) const;
		bool	operator!=(input_iterator const &rhs) const;
		input_iterator&	operator*( void );
		input_iterator*	operator->( void );
	};

	template<class T>
	class output_iterator : public base_iterator, public ft::iterator_traits<output_iterator_tag, T> {
		output_iterator&	operator*( void );
		output_iterator*	operator->( void );
	};

	template<class T>
	class forward_iterator : public input_iterator, public output_iterator, public ft::iterator_traits<forward_iterator_tag, T> {
		iterator( void ); // constructeur par défaut
	};

	template<class T>
	class bidirectionnal_iterator : public forward_iterator, public ft::iterator_traits<bidirectional_iterator_tag, T> {
		bidirectionnal_iterator&	operator--( void ); // prefix decrement
		bidirectionnal_iterator	operator--( int ); // postfix decrement
	};

	template<class T>
	class random_access_iterator : public bidirectionnal_iterator, public ft::iterator_traits<random_access_iterator_tag, T> {
		bool	operator<( random_access_iterator const &rhs ) const;
		bool	operator>( random_access_iterator const &rhs ) const;
		bool	operator<=( random_access_iterator const &rhs ) const;
		bool	operator>=( random_access_iterator const &rhs ) const;
		random_access_iterator	operator+( random_access_iterator const &rhs );
		random_access_iterator	operator-( random_access_iterator const &rhs );
		// iterator	operator+( const &T ); // a verifier mais potentiellement reponse a It + 1;
		// iterator	operator+( const &T );
		random_access_iterator&	operator+=( random_access_iterator const &rhs );
		random_access_iterator&	operator-=( random_access_iterator const &rhs );
		random_access_iterator&	operator[]( random_access_iterator const &rhs );
	};

}

#endif // __ITERATOR_H__
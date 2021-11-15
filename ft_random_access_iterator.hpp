#ifndef __FT_RANDOM_ACCESS_ITERATOR_H__
#define __FT_RANDOM_ACCESS_ITERATOR_H__

#include "ft_iterator.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
	protected:
		pointer _ptr;

	public:

		typedef typename ft::iterator_traits<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::difference_type<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::pointer<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::reference<ft::random_access_iterator_tag, T>::reference reference;
		typedef typename ft::iterator_category<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

		/* canonical form */
		random_access_iterator( void );
		random_access_iterator( const random_access_iterator& );
		~random_access_iterator( void );
		random_access_iterator	&operator=( const random_access_iterator& );

		/* 
		implementation https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
		https://en.cppreference.com/w/cpp/language/operators
		*/
		random_access_iterator	&operator++( void ); //prefix increment
		random_access_iterator	operator++( int ); // postfix increment
		bool	operator==( random_access_iterator const &rhs ) const;
		bool	operator!=( random_access_iterator const &rhs ) const;
		random_access_iterator	&operator*( void );
		random_access_iterator	&operator->( void );
		random_access_iterator	&operator--( void ); // prefix decrement
		random_access_iterator	operator--( int ); // postfix decrement
		bool	operator<( random_access_iterator const &rhs ) const;
		bool	operator>( random_access_iterator const &rhs ) const;
		bool	operator<=( random_access_iterator const &rhs ) const;
		bool	operator>=( random_access_iterator const &rhs ) const;

		random_access_iterator	operator+( const difference_type n ); // a + n
		random_access_iterator	operator-( const difference_type n ); // a - n
		random_access_iterator	&operator+=( const difference_type n );
		random_access_iterator	&operator-=( const difference_type n );
		random_access_iterator	&operator[]( const const difference_type n );


	};
	// potentielle solution pour contourner le pb du keyword friend = créer overload de fonctions
	// si marche pas ici, tenter overload des fonctions dans class vector directement
	template<typename T>
	ft::random_access_iterator<T>	operator+( size_t n, ft::random_access_iterator<T> const &rhs ); // cas n + a

	/*
	specific case of the STL which state that a subtraction between two iterators should be possible
	the return value is difference type = a - b
	https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
	https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator */
	template<typename T>
	typename ft::random_access_iterator<T>::difference_type	operator-( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs );

	template<typename T>
	bool	operator<( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs );

	template<typename T>
	bool	operator>( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs );

	template<typename T>
	bool	operator<=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs );

	template<typename T>
	bool	operator>=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs );

	// a voir si preferable de les rajouter
		// bool	operator==( random_access_iterator const &rhs ) const;
		// bool	operator!=( random_access_iterator const &rhs ) const;

}

#endif // __FT_RANDOM_ACCESS_ITERATOR_H__
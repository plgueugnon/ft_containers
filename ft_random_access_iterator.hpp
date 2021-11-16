#ifndef __FT_RANDOM_ACCESS_ITERATOR_H__
#define __FT_RANDOM_ACCESS_ITERATOR_H__

#include "ft_iterator.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : ft::iterator_traits<ft::random_access_iterator_tag, T>
	{
	protected:
		pointer _ptr; // error de type a fix
		// typedef ft::iterator_traits<T> rai;


	public:

		typedef typename ft::value_type<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::difference_type<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::random_access_iterator<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::reference<ft::random_access_iterator_tag, T>::reference reference;
		typedef typename ft::iterator_category<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

		/* canonical form */
		random_access_iterator( void ) : _ptr(NULL) { return ; }
		random_access_iterator( random_access_iterator const &src ) : _ptr(src) { return ; }
		~random_access_iterator( void ) { return ; }
		random_access_iterator	&operator=( random_access_iterator const &src )
		{
			if ( this != &src )
			{
				_ptr = src._ptr;
			}
			return ( *this );
		}

		/* 
		implementation https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
		https://en.cppreference.com/w/cpp/language/operators
		*/

//prefix increment
		random_access_iterator	&operator++( void )
		{
			++_ptr;
			return ( *this );
		}
// postfix increment
		random_access_iterator	operator++( int )
		{
			random_access_iterator tmp = *this;
			_ptr++;
			return ( tmp );
		}
		bool	operator==( random_access_iterator const &rhs ) const
		{
			return ( _ptr == rhs._ptr ); // return true or false selon si == ou non
		}

		bool	operator!=( random_access_iterator const &rhs ) const;
		{
			return ( _ptr != rhs._ptr ); // return true or false selon si != ou non
		}
		reference	operator*( void )
		{
			return ( *_ptr );
		}
		pointer	operator->( void )
		{
			return ( _ptr );
		}
// prefix decrement
		random_access_iterator	&operator--( void )
		{
			--_ptr;
			return ( *this );
		}
// postfix decrement
		random_access_iterator	operator--( int )
		{
			random_access_iterator tmp = *this;
			_ptr--;
			return ( tmp );
		}
		bool	operator<( random_access_iterator const &rhs ) const
		{
			return ( _ptr < rhs._ptr );
		}
		bool	operator>( random_access_iterator const &rhs ) const
		{
			return ( _ptr > rhs._ptr );
		}
		bool	operator<=( random_access_iterator const &rhs ) const
		{
			return ( _ptr <= rhs._ptr );
		}
		bool	operator>=( random_access_iterator const &rhs ) const
		{
			return ( _ptr >= rhs._ptr );
		}

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
	https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
	*/
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
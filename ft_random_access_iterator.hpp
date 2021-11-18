#ifndef __FT_RANDOM_ACCESS_ITERATOR_H__
#define __FT_RANDOM_ACCESS_ITERATOR_H__

#include "ft_iterator.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
			// alias typedef
	public:

		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

	protected:
		pointer _ptr;

	public:
		/* canonical form */
		random_access_iterator( void ) : _ptr(NULL) { return ; }
		random_access_iterator( random_access_iterator const &src ) : _ptr(src._ptr) { return ; }
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

		bool	operator!=( random_access_iterator const &rhs ) const
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

		random_access_iterator	operator+( const difference_type n ) const // a + n
		{
			return ( _ptr + n );
		}
		random_access_iterator	operator-( const difference_type n ) const // a - n
		{
			return ( _ptr - n );
		}
		random_access_iterator	&operator+=( const difference_type n )
		{
			_ptr += n;
			return ( *this );
		}
		random_access_iterator	&operator-=( const difference_type n )
		{
			_ptr -= n;
			return ( *this );
		}
		reference	operator[]( const difference_type n )
		{
			return ( *(_ptr + n) );
		}

		friend ft::random_access_iterator<T>	operator+( size_t n, ft::random_access_iterator<T> const &rhs ) // cas n + a
		{
			return ( n + rhs._ptr );
		}

		/*
		specific case of the STL which state that a subtraction between two iterators should be possible
		the return value is difference type = a - b
		https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
		https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
		*/
		friend typename ft::random_access_iterator<T>::difference_type	operator-( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
		{
			return ( lhs._ptr - rhs._ptr );
		}

		friend bool	operator<( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
		{
			return ( lhs._ptr < rhs._ptr );
		}

		friend bool	operator>( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
		{
			return ( lhs._ptr > rhs._ptr );
		}

		friend bool	operator<=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
		{
			return ( lhs._ptr <= rhs._ptr );
		}

		friend bool	operator>=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
		{
			return ( lhs._ptr >= rhs._ptr );
		}

	};

	// a voir si preferable de les rajouter
		// bool	operator==( random_access_iterator const &rhs ) const;
		// bool	operator!=( random_access_iterator const &rhs ) const;

}

#endif // __FT_RANDOM_ACCESS_ITERATOR_H__
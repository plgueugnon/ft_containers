/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:13:54 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 20:13:54 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_RANDOM_ACCESS_ITERATOR_H__
#define __FT_RANDOM_ACCESS_ITERATOR_H__

#include "ft_iterator.hpp"

namespace ft
{
	template<class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
	{
	public:

		typedef T																			iterator_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

	private:
		pointer _ptr;

	public:
		/* default constructor */
		random_access_iterator( void ) : _ptr(NULL) { return ; }
		random_access_iterator( pointer src ) : _ptr(src) {}

		/* copy constructor */
		random_access_iterator( const random_access_iterator &src ) : _ptr(src._ptr) { return ; }

		/* destructor */
		~random_access_iterator( void ) { return ; }

		/* assignment operator */
		random_access_iterator	&operator=( const random_access_iterator &src )
		{
			if ( this != &src )
			{
				_ptr = src._ptr;
			}
			return ( *this );
		}
		pointer base() const { return ( _ptr ); }

		/* 
		* implementation https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator
		* https://en.cppreference.com/w/cpp/language/operators
		*/

		reference	operator*( void ) const { return ( *_ptr ); }
		pointer	operator->( void ) const { return ( &( operator*() ) ); }

		random_access_iterator	&operator+=( const difference_type n )
		{
			_ptr += n;
			return ( *this );
		}

		/* a + n case */
		random_access_iterator	operator+( const difference_type n ) const
		{
			return ( _ptr + n );
		}

		random_access_iterator	&operator-=( const difference_type n )
		{
			_ptr -= n;
			return ( *this );
		}

		/* a - n case */
		random_access_iterator	operator-( const difference_type n ) const
		{
			return ( _ptr - n );
		}

		/* prefix increment */
		random_access_iterator	&operator++( void )
		{
			++_ptr;
			return ( *this );
		}

		/* postfix increment */
		random_access_iterator	operator++( int )
		{
			random_access_iterator tmp = *this;
			_ptr++;
			return ( tmp );
		}

		/* prefix decrement */
		random_access_iterator	&operator--( void )
		{
			--_ptr;
			return ( *this );
		}

		/* postfix decrement */
		random_access_iterator	operator--( int )
		{
			random_access_iterator tmp = *this;
			_ptr--;
			return ( tmp );
		}

		bool	operator==( const random_access_iterator &rhs ) const { return ( _ptr == rhs._ptr ); }
		bool	operator!=( const random_access_iterator &rhs ) const { return ( _ptr != rhs._ptr ); }
		bool	operator<( const random_access_iterator  &rhs ) const { return ( _ptr < rhs._ptr ); }
		bool	operator<=( const random_access_iterator &rhs ) const { return ( _ptr <= rhs._ptr ); }
		bool	operator>( const random_access_iterator &rhs ) const { return ( _ptr > rhs._ptr ); }
		bool	operator>=( const random_access_iterator &rhs ) const { return ( _ptr >= rhs._ptr ); }

		reference	operator[]( const difference_type n ) { return ( *(_ptr + n) ); }

		/* const conversion operator return a const iterator container _ptr with a const value */
		operator	random_access_iterator<const value_type>() const { return ( random_access_iterator<const value_type>(_ptr) ); }

	};

	template<typename T1, typename T2>
	bool	operator<( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() < rhs.base() );
	}

	template<typename T1, typename T2>
	bool	operator>( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() > rhs.base() );
	}

	template<typename T1, typename T2>
	bool	operator>=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() >= rhs.base() );
	}

	template<typename T1, typename T2>
	bool	operator<=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() <= rhs.base() );
	}

	template<typename T1, typename T2>
	bool	operator==( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() == rhs.base() );
	}

	template<typename T1, typename T2>
	bool	operator!=( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() != rhs.base() );
	}

	template<typename T>
	ft::random_access_iterator<T>	operator+( size_t n, const ft::random_access_iterator<T> &rhs ) // cas n + a
	{
		return ( n + rhs.base() );
	}

	/*
	* specific case of the STL which state that a subtraction between two iterators should be possible
	* the return value is difference type = a - b
	* https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
	* https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
	*/
	template<typename T>
	typename ft::random_access_iterator<T>::difference_type	operator-( const ft::random_access_iterator<T> &lhs, const ft::random_access_iterator<T> &rhs )
	{
		return ( lhs.base() - rhs.base() );
	}
	template<typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type	operator-( const ft::random_access_iterator<T1> &lhs, const ft::random_access_iterator<T2> &rhs )
	{
		return ( lhs.base() - rhs.base() );
	}
}

#endif // __FT_RANDOM_ACCESS_ITERATOR_H__
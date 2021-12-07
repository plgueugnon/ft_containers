#ifndef __FT_ITERATOR_H__
#define __FT_ITERATOR_H__

#include <cstddef>
// #include "ft_utils.hpp"
// #include "ft_type_resolution.hpp"
#include <iostream> // A SUPPR

namespace ft
{

/* https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls */

	// template<class Iterator> struct iterator_traits; // general class / fwd declaration
	// template<class T> struct iterator_traits<T*>; // specialisation class raw / fwd declaration
	// template<class T> struct iterator_traits<const T*>; // specialisation class const / fwd declaration

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

// creation d'un template iterator pour tout les types d'iterator
	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
	};

	// template generique des iterators
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
	};

	// template specialization for raw pointer
	template<class T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef T*								pointer;
		typedef T&								reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	// template specialization for const pointer
	template<class T>
	struct iterator_traits<const T*> {
		typedef ptrdiff_t						difference_type;
		typedef T								value_type;
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

/***************************************************************************/

// 	template<class T>
// 	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T>
// 	{
// 			// alias typedef
// 	public:

// 		typedef T																			iterator_type;
// 		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category	iterator_category;
// 		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
// 		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
// 		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
// 		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference			reference;

// 	private:
// 		pointer _ptr;

// 	public:
// 		/* canonical form */
// 		random_access_iterator( void ) : _ptr(NULL) { return ; }

// 		random_access_iterator( pointer src ) : _ptr(src) {} // ajout cas ptr en arg
// 		random_access_iterator( const random_access_iterator &src ) : _ptr(src._ptr) { return ; }
// 		~random_access_iterator( void ) { return ; }
// 		random_access_iterator	&operator=( const random_access_iterator &src )
// 		{
// 			if ( this != &src )
// 			{
// 				_ptr = src._ptr;
// 			}
// 			return ( *this );
// 		}
// 		pointer base() const { return ( _ptr ); } // ajout

// 		/* 
// 		implementation https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
// 		https://en.cppreference.com/w/cpp/language/operators
// 		*/

// 		bool	operator!=( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr != rhs._ptr ); // return true or false selon si != ou non
// 		}
// 		reference	operator*( void ) const // ajout const
// 		{
// 			return ( *_ptr );
// 		}
// 		pointer	operator->( void ) const // ajout const
// 		{
// 			return ( &( operator*() ) );
// 		}
// 		bool	operator==( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr == rhs._ptr ); // return true or false selon si == ou non
// 		}

// 		random_access_iterator	&operator+=( const difference_type n )
// 		{
// 			_ptr += n;
// 			return ( *this );
// 		}

// 		random_access_iterator	operator+( const difference_type n ) const // a + n
// 		{
// 			return ( _ptr + n );
// 		}

// 		random_access_iterator	&operator-=( const difference_type n )
// 		{
// 			_ptr -= n;
// 			return ( *this );
// 		}

// 		random_access_iterator	operator-( const difference_type n ) const // a - n
// 		{
// 			return ( _ptr - n );
// 		}

// //prefix increment
// 		random_access_iterator	&operator++( void )
// 		{
// 			++_ptr;
// 			return ( *this );
// 		}
// // postfix increment
// 		random_access_iterator	operator++( int )
// 		{
// 			random_access_iterator tmp = *this;
// 			_ptr++;
// 			return ( tmp );
// 		}
// // prefix decrement
// 		random_access_iterator	&operator--( void )
// 		{
// 			--_ptr;
// 			return ( *this );
// 		}
// // postfix decrement
// 		random_access_iterator	operator--( int )
// 		{
// 			random_access_iterator tmp = *this;
// 			_ptr--;
// 			return ( tmp );
// 		}

// 		bool	operator<( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr < rhs._ptr );
// 		}
// 		bool	operator>( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr > rhs._ptr );
// 		}
// 		bool	operator<=( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr <= rhs._ptr );
// 		}
// 		bool	operator>=( random_access_iterator const &rhs ) const
// 		{
// 			return ( _ptr >= rhs._ptr );
// 		}

// 		reference	operator[]( const difference_type n )
// 		{
// 			return ( *(_ptr + n) );
// 		}
// 	};

// 	template<typename T>
// 	ft::random_access_iterator<T>	operator+( size_t n, ft::random_access_iterator<T> const &rhs ) // cas n + a
// 	{
// 		return ( n + rhs._ptr );
// 	}

// 	/*
// 	specific case of the STL which state that a subtraction between two iterators should be possible
// 	the return value is difference type = a - b
// 	https://www.cplusplus.com/reference/iterator/RandomAccessIterator/
// 	https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator 
// 	*/
// 	template<typename T>
// 	typename ft::random_access_iterator<T>::difference_type	operator-( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
// 	{
// 		return ( lhs._ptr - rhs._ptr );
// 	}

// 	template<typename T>
// 	bool	operator<( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
// 	{
// 		return ( lhs._ptr < rhs._ptr );
// 	}

// 	template<typename T>
// 	bool	operator>( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
// 	{
// 		return ( lhs._ptr > rhs._ptr );
// 	}

// 	template<typename T>
// 	bool	operator<=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
// 	{
// 		return ( lhs._ptr <= rhs._ptr );
// 	}

// 	template<typename T>
// 	bool	operator>=( ft::random_access_iterator<T> const &lhs, ft::random_access_iterator<T> const &rhs )
// 	{
// 		return ( lhs._ptr >= rhs._ptr );
// 	}

	// a voir si preferable de les rajouter
		// bool	operator==( random_access_iterator const &rhs ) const;
		// bool	operator!=( random_access_iterator const &rhs ) const;

/***************************************************************************/

	// /* source reference : ISO+IEC+14882-1998 */
	// template<class Iterator>
	// class reverse_iterator {
	// //  : public 
	// // ft::iterator<typename iterator_traits<Iterator>::value_type,
	// // 		typename iterator_traits<Iterator>::difference_type,
	// // 		typename iterator_traits<Iterator>::pointer,
	// // 		typename iterator_traits<Iterator>::reference,
	// // 		typename iterator_traits<Iterator>::iterator_category>

	// // {

	// public:

	// 	typedef Iterator iterator_type; // NORME ISO a voir si utile
	// 	typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
	// 	typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
	// 	typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
	// 	typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
	// 	typedef typename ft::iterator_traits<Iterator>::reference			reference;

	// protected:
	// 	Iterator _current;

	// public:
	// 	reverse_iterator( void ) : _current(NULL) { return ; }
	// 	explicit reverse_iterator( Iterator x ) : _current(x) { return ; }

	// 	template<class U>
	// 	reverse_iterator( const reverse_iterator<U>& u) : _current(u._current) { return ; }

	// 	template<class U>
	// 	reverse_iterator&	operator=( const reverse_iterator<U>& u)
	// 	{
	// 		_current = u._current;
	// 		return ( *this );
	// 	}

	// 	Iterator base( void ) const { return ( _current ); }
	// 	reference operator*( void ) const 
	// 	{
	// 		Iterator tmp = _current;
	// 		return ( *--tmp );
	// 	}
	// 	pointer operator->( void ) const { return &( operator*() ); }

	// 	reference operator[]( difference_type n ) const { return ( _current[ -n -1 ] ); }
	// 	reverse_iterator operator+( difference_type n ) const { return ( _current - n ); }
	// 	reverse_iterator &operator++( void )
	// 	{
	// 		--_current;
	// 		return ( *this );
	// 	}
	// 	reverse_iterator operator++( int )
	// 	{
	// 		reverse_iterator tmp =  *this;
	// 		--_current;
	// 		return ( tmp );
	// 	}

	// 	reverse_iterator &operator+=( difference_type n )
	// 	{
	// 		_current -= n;
	// 		return ( *this );
	// 	}
	// 	reverse_iterator operator-( difference_type n ) const { return ( _current + n ); }

	// 	reverse_iterator &operator--( void )
	// 	{
	// 		++_current;
	// 		return ( *this );
	// 	}
	// 	reverse_iterator operator--( int )
	// 	{
	// 		reverse_iterator tmp = *this;
	// 		++_current;
	// 		return ( *this );
	// 	}

	// 	reverse_iterator &operator-=( difference_type n )
	// 	{
	// 		_current += n;
	// 		return ( *this );
	// 	}

	// 	bool operator==( const ft::reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current == x._current );
	// 	}
	// 	bool operator!=( const reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current != x._current );
	// 	}
	// 	bool operator<( const reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current > x._current );
	// 	}
	// 	bool operator<=( const reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current >= x._current );
	// 	}
	// 	bool operator>( const reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current < x._current );
	// 	}
	// 	bool operator>=( const reverse_iterator<Iterator>& x)
	// 	{
	// 		return ( _current <= x._current );
	// 	}

	// };

	// template<class Iterator>
	// bool operator==( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() == y.base() );
	// }
	// template<class Iterator>
	// bool operator!=( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() != y.base() );
	// }
	// template<class Iterator>
	// bool operator<( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() > y.base() );
	// }
	// template<class Iterator>
	// bool operator<=( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() >= y.base() );
	// }
	// template<class Iterator>
	// bool operator>( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() < y.base() );
	// }
	// template<class Iterator>
	// bool operator>=( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( x.base() <= y.base() );
	// }

	// template<class Iterator>
	// typename ft::reverse_iterator<Iterator>::difference_type operator-( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( y.base() - x.base() );
	// }
	// template<class Iterator>
	// typename ft::reverse_iterator<Iterator>::difference_type operator-(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& y)
	// {
	// 	return ( y - n );
	// }
	// template<class Iterator>
	// ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& x)
	// {
	// 	return ( x + n);
	// }

}

#endif // __FT_ITERATOR_H__
#ifndef __FT_REVERSE_ITERATOR_H__
#define __FT_REVERSE_ITERATOR_H__

#include <iostream> // a SUPPR

#include "ft_iterator.hpp"
#include "ft_random_access_iterator.hpp"

namespace ft
{

		/* source reference : ISO+IEC+14882-1998 */
	template<class Iterator>
	class reverse_iterator
	{

	public:

		typedef Iterator iterator_type; // NORME ISO a voir si utile
		typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename ft::iterator_traits<Iterator>::reference			reference;

	protected:
		Iterator _current;

	public:
		/* canonical form */
		/* default constructor */
		reverse_iterator( void ) : _current(NULL) { return ; }
		/* basic constructor */
		explicit reverse_iterator( Iterator x ) : _current(x) { return ; }

		Iterator base( void ) const { return ( _current ); }

		template<class U>
		reverse_iterator( const reverse_iterator<U>& u) : _current(u.base()) { return ; }

		template<class U>
		reverse_iterator&	operator=( const reverse_iterator<U>& u)
		{
			_current = u.base();
			return ( *this );
		}


		reference operator*( void ) const 
		{
			Iterator tmp = _current;
			return ( *--tmp );
		}
		pointer operator->( void ) const { return &( operator*() ); }

		reference operator[]( const difference_type n ) const { return ( *(_current -n -1) ); }
		reverse_iterator operator+( difference_type n ) const { return reverse_iterator( _current - n ); }
		reverse_iterator &operator++( void )
		{
			--_current;
			return ( *this );
		}
		reverse_iterator operator++( int )
		{
			reverse_iterator tmp =  *this;
			--_current;
			return ( tmp );
		}

		reverse_iterator &operator+=( const difference_type n )
		{
			_current -= n;
			return ( *this );
		}
		// force cast retour en reverse iterator
		reverse_iterator operator-( difference_type n ) const { return reverse_iterator( _current + n ); }

		reverse_iterator &operator--( void )
		{
			++_current;
			return ( *this );
		}
		reverse_iterator operator--( int )
		{
			reverse_iterator tmp = *this;
			_current++;
			return ( tmp );
		}

		reverse_iterator &operator-=( const difference_type n )
		{
			_current += n;
			return ( *this );
		}

		bool operator==( const ft::reverse_iterator<Iterator>& x) const
		{
			return ( _current == x._current );
		}
		bool operator!=( const reverse_iterator<Iterator>& x) const
		{
			return ( _current != x._current );
		}
		bool operator<( const reverse_iterator<Iterator>& x) const
		{
			return ( _current > x._current );
		}
		bool operator<=( const reverse_iterator<Iterator>& x) const
		{
			return ( _current >= x._current );
		}
		bool operator>( const reverse_iterator<Iterator>& x) const
		{
			return ( _current < x._current );
		}
		bool operator>=( const reverse_iterator<Iterator>& x) const
		{
			return ( _current <= x._current );
		}

	};

	template<class Iterator1, class Iterator2>
	bool operator==( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( x.base() == y.base() );
	}

	template<class Iterator1, class Iterator2>
	bool operator!=( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( x.base() != y.base() );
	}

	template<class Iterator1, class Iterator2>
	bool operator<( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( x.base() > y.base() );
	}

	template<class Iterator1, class Iterator2>
	bool operator<=( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( y.base() <= x.base() );
	}

	template<class Iterator1, class Iterator2>
	bool operator>( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( x.base() < y.base() );
	}

	template<class Iterator1, class Iterator2>
	bool operator>=( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( y.base() >= x.base() );
	}

	template<class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
	{
		return ( y.base() - x.base() );
	}
	template<class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-( const ft::reverse_iterator<Iterator1>& x, const ft::reverse_iterator<Iterator2>& y)
	{
		return ( y.base() - x.base() );
	}

	template<class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& y)
	{
		return ( y - n );
	}
	template<class Iterator>
	ft::reverse_iterator<Iterator> operator+(const typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& x)
	{
		return ( x + n);
	}

}

#endif // __FT_REVERSE_ITERATOR_H__
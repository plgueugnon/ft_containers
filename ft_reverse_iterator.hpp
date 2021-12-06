#ifndef __FT_REVERSE_ITERATOR_H__
#define __FT_REVERSE_ITERATOR_H__

#include "ft_iterator.hpp"
#include "ft_random_access_iterator.hpp"

namespace ft
{

	/* source reference : ISO+IEC+14882-1998 */
	template<class Iterator>
	class reverse_iterator : public 
	ft::iterator<typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference,
			typename iterator_traits<Iterator>::iterator_category>

	{

	protected:
		Iterator _current;

	public:

		// typedef Iterator iterator_type; // NORME ISO a voir si utile
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;

		reverse_iterator( void ) : _current(NULL) { return ; }
		explicit reverse_iterator( Iterator x ) : _current(x) { return ; }

		template<class U>
		reverse_iterator( const reverse_iterator<U>& u) : _current(u._current) { return ; }

		Iterator base( void ) const { return ( _current ); }
		reference operator*( void ) const 
		{
			Iterator tmp = _current;
			return ( *--tmp );
		}
		pointer operator->( void ) const { return &( operator*() ); }

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
		reverse_iterator &operator--( void )
		{
			++_current;
			return ( *this );
		}
		reverse_iterator operator--( int )
		{
			reverse_iterator tmp = *this;
			++_current;
			return ( *this );
		}

		reverse_iterator operator+( difference_type n ) const { return ( _current - n ); }
		reverse_iterator &operator+=( difference_type n )
		{
			_current -= n;
			return ( *this );
		}
		reverse_iterator operator-( difference_type n ) const { return ( _current + n ); }
		reverse_iterator &operator-=( difference_type n )
		{
			_current += n;
			return ( *this );
		}
		reference operator[]( difference_type n ) const { return ( _current[ -n -1 ] ); }

		friend bool operator==( const ft::reverse_iterator<Iterator>& x, const ft::reverse_iterator<Iterator>& y)
		{
			return ( x._current == y._current );
		}
		friend bool operator<( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( x._current > y._current );
		}
		friend bool operator>( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( x._current < y._current );
		}
		friend bool operator!=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( x._current != y._current );
		}
		friend bool operator>=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( x._current <= y._current );
		}
		friend bool operator<=( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( x._current >= y._current );
		}
		friend typename reverse_iterator<Iterator>::difference_type operator-( const reverse_iterator<Iterator>& x, const reverse_iterator<Iterator>& y)
		{
			return ( y._current - x._current );
		}
		friend reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x)
		{
			return ( reverse_iterator<Iterator>(x._current - n) );
		}

	};

}

#endif // __FT_REVERSE_ITERATOR_H__
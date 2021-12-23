#ifndef __FT_UTILS_H__
#define __FT_UTILS_H__

// #include "ft_iterator.hpp"
// #include "ft_random_access_iterator.hpp"
// #include "ft_type_resolution.hpp"

namespace ft
{
	/* https://www.cplusplus.com/reference/algorithm/equal/ */
	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1!=last1)
		{
			if ( !( *first1 == *first2 ) )
				return ( false );
			++first1;
			++first2;
		}
		return ( true );
	}

	/* https://www.cplusplus.com/reference/algorithm/lexicographical_compare/ */
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if ( first2 == last2 || *first2 < *first1 )
				return ( false );
			else if ( *first1 < *first2)
				return ( true );
			++first1; ++first2;
		}
		return ( first2 != last2 );
	}

	/* https://www.cplusplus.com/reference/utility/swap/ */
	template <typename T>
	void swap ( T& a, T& b )
	{
		T c(a);
		a = b;
		b = c;
	}

	template <class T>
	typename iterator_traits<T>::difference_type distance (T first, T last)
	{
		typename iterator_traits<T>::difference_type i = 0;
		for (; first != last; ++first, ++i);
		return i;
	}

	/* https://www.cplusplus.com/reference/utility/pair/ */
	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;
		pair() : first(), second() {}
		pair(const T1& x, const T2& y) : first(x), second(y) {}
		
		template<class U, class V>
		pair(const pair<U, V> &p) : first(p.first), second(p.second) {}

		pair& operator=(const pair &p)
		{
			if (*this != p)
			{
				first = p.first;
				second = p.second;
			}
			return ( *this );
		}
	};

	/* https://www.cplusplus.com/reference/utility/make_pair/ */
	template <class T1,class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return ( pair<T1,T2>( x, y ) );
	}

	template <class Arg1, class Arg2, class Result>
	struct binary_function
	{
		typedef Arg1 first_argument_type;
		typedef Arg2 second_argument_type;
		typedef Result result_type;
	};

	/* https://www.cplusplus.com/reference/functional/less/?kw=less */
	template <class T> struct less : ft::binary_function <T,T,bool>
	{
		bool operator() (const T& x, const T& y) const 
		{ return ( x < y );}
	};


	template <class T1, class T2>
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( lhs.first == rhs.first && lhs.second == rhs.second ); }

	template <class T1, class T2>
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !( lhs == rhs ); }

	template <class T1, class T2>
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( lhs.first < rhs.first  || (!( rhs.first < lhs.first ) && lhs.second < rhs.second ) ); }

	template <class T1, class T2>
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !( rhs < lhs ); }

	template <class T1, class T2>
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return ( rhs < lhs ); }

	template <class T1, class T2>
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return !( lhs < rhs ); }
	
	// template <class T1, class T2>
	// pair<T1,T2> make_pair(const T1 &x, const T2 &y)
	// {
	// 	return ( pair<T1, T2>(x, y) );
	// }


}

#endif // __FT_UTILS_H__
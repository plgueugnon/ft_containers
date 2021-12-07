#ifndef __FT_UTILS_H__
#define __FT_UTILS_H__

// #include "ft_iterator.hpp"
// #include "ft_random_access_iterator.hpp"
// #include "ft_type_resolution.hpp"

namespace ft
{
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

	// pas demandé
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

}

#endif // __FT_UTILS_H__
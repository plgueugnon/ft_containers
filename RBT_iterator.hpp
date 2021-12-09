#ifndef __RBT_ITERATOR_H__
#define __RBT_ITERATOR_H__

#include "ft_iterator.hpp"

namespace ft
{
	template<typename T>
	class RBT_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category	iterator_category;




	};
}


#endif // __RBT_ITERATOR_H__
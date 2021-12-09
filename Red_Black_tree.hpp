#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

#include "RBT_iterator.hpp"
#include "RBT_node.hpp"
#include "ft_utiils.hpp"

#include <memory>


/*
			typedef Key key_type;
			typedef T mapped_type;
			typedef pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef ft::random_access_iterator<value_type> iterator; // See 23.1
			typedef ft::random_access_iterator<value_type> const_iterator; // See 23.1
			typedef size_t size_type; // See 23.1
			typedef ptrdiff_t difference_type;// See 23.1
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

*/

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class RBT
	{
		public:
			typedef Key							key_type; // cle de tri
			typedef T							mapped_type; // valeur trie
			typedef ft::pair<const Key, T>		value_type; // valeur contenu dans les nodes
			typedef Compare						key_compare; // 


	};

}

#endif // __RED_BLACK_TREE_H__
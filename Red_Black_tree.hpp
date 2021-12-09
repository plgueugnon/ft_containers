#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

#include "RBT_iterator.hpp"
#include "RBT_node.hpp"
#include "ft_utils.hpp"

#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class RBT
	{
		public:
			/* basic typedef of MAP */
			typedef Key										key_type; // cle de tri
			typedef T										mapped_type; // valeur trie
			typedef ft::pair<const Key, T>					value_type; // valeur contenu dans les nodes
			typedef Compare									key_compare; // boolen de comparaison a < b

			/* typedef of RB_tree node */
			typedef	ft::RBT_node<T>							node_type; // contenu d'une node
			typedef node_type*								node_pointer; // ptr sur node
			typedef std::allocator<node_type>				node_allocator; // allocator de node

			/* pointer & reference */
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference 	const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		pointer;

			/* iterators */
			typedef ft::RBT_iterator<T>						iterator;
			typedef ft::RBT_iterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;

		private:
			node_type		_head;
			size_type		_size;
			allocator_type _alloc;

		public:
			/* default constructor */
			explicit RBT();
			/* range constructor */
			RBT();
			/* copy constructor */
			RBT(const RBT& x);
			/* assignment operator */
			RBT	&operator=();
			reference	operator*();
			pointer		operator->();

			/* destructor */
			~RBT(); // pe a mettre en virtuel

			iterator	begin();
			const_iterator begin();
			iterator	end();
			const_iterator	end();
			reverse_iterator	rbegin();
			const_reverse_iterator	rbegin();
			reverse_iterator	rend();
			const_reverse_iterator	rend();

			size_type	max_size();
			bool		empty();
			size_type	size();

			/* insert */
			iterator insert();
			void	insert();
			pair<iterator, bool> insert();

			void	erase();
			size_type	erase();
			void	erase();

			void	swap();
			void	clear();

			/* other */
			iterator	find();
			const_iterator	find();
			size_type	count();
			iterator	lower_bounds();
			const_iterator	lower_bounds();
			iterator	upper_bound();
			const_iterator	upper_bound();
			equal_range();

			void	rotateL();
			void	rotateR();
			node_pointer	get_root();
			node_pointer	LeftMost();
			node_pointer	RightMost();

	};

}

#endif // __RED_BLACK_TREE_H__
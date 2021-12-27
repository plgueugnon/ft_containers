/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:49:28 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 19:49:39 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_MAP_H__
#define __FT_MAP_H__

#include "BST.hpp"
#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class map
	{
		public:
			typedef Key															key_type;
			typedef T															mapped_type;
			typedef ft::pair<Key, T>											value_type;
			typedef Compare														key_compare;
			typedef Allocator													allocator_type;
			typedef typename Allocator::reference								reference;
			typedef typename Allocator::const_reference							const_reference;
			typedef typename ft::BST<value_type, key_compare>::node_type		node_type;
			typedef typename ft::BST<value_type, key_compare>::iterator			iterator;
			typedef typename ft::BST<value_type, key_compare>::const_iterator	const_iterator;
			typedef size_t														size_type;
			typedef ptrdiff_t													difference_type;
			typedef typename Allocator::pointer									pointer;
			typedef typename Allocator::const_pointer							const_pointer;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		class value_compare : public ft::binary_function<value_type,value_type,bool>
		{
			friend class map;

			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}
			public:
				bool operator()( const value_type& x, const value_type& y ) const { return comp(x.first, y.first); }
		};

		private:
			ft::BST<value_type, key_compare>		_tree;
			key_compare								_comp;
			allocator_type							_alloc;

		public:

			/* construct/copy/destroy */
			explicit map(const Compare& comp = Compare(), const Allocator& a = Allocator())
						: _tree(comp), _alloc(a) {}
	
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& a = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr )
				: _tree(comp), _comp(comp), _alloc(a)
			{
				_tree.insert(first, last);
			}

			map(const map<Key,T,Compare,Allocator>& x) : _tree(x._tree), _alloc(x._alloc) {}
			~map() {}

			map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x)
			{
				if ( *this != x )
				{
					_alloc = x._alloc;
					_tree.clear();
					_tree.insert(x.begin(), x.end());
				}
				return ( *this );
			}

			/* iterators */
			iterator	begin() { return ( (_tree.begin()) ); }
			const_iterator	begin() const { return ( (_tree.begin()) ); }
			iterator	end() { return ( (_tree.end()) ); }
			const_iterator	end() const { return ( (_tree.end()) ); }
			reverse_iterator	rbegin() { return ( (_tree.rbegin()) ); }
			const_reverse_iterator	rbegin() const { return ( (_tree.rbegin()) ); }
			reverse_iterator	rend() { return ( (_tree.rend()) ); }
			const_reverse_iterator	rend() const { return ( (_tree.rend()) ); }

			/* capacity */
			bool	empty() const { return ( size() == 0 ); }
			size_type	size() const { return ( _tree.size() ); }
			size_type	max_size() const { return ( _tree.max_size() ); }

			/* element access */
			T& operator[](const key_type& x)
			{
				iterator it = find(x);
				if (it == end())
					it = insert(ft::make_pair(x, T())).first;
				return ( it->second );
			}

			/* modifiers */
			ft::pair<iterator, bool>	insert(const value_type& x)
			{
				ft::pair<iterator, bool> res =_tree.insert(x);
				return ( res );
			}

			iterator	insert(iterator position, const value_type& x)
			{
				(void)position;
				ft::pair<iterator, bool> res =_tree.insert(x);
				return ( res.first );
			}
			
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
			{
				for(; first != last; first++)
					insert(*first);
			}

			void erase(iterator position) { _tree.erase(position); }
			size_type erase(const key_type& x) { return ( _tree.erase(x) ); }
			void erase(iterator first, iterator last) { _tree.erase(first, last); }

			void swap(map<Key,T,Compare,Allocator>& x)
			{
				_tree.swap(x._tree);
				ft::swap(_comp, x._comp);
				ft::swap(_alloc, x._alloc);
			}

			void clear() { _tree.clear(); }

			/* observers */
			key_compare key_comp() const { return ( _comp ); }
			value_compare value_comp() const { return ( _comp ); }

			/* map operations */
			iterator find(const key_type& x) { return ( iterator( _tree.find(x)) ); }
			const_iterator find(const key_type& x) const { return ( const_iterator( _tree.find(x)) ); }

			size_type	count(const key_type &k) const
			{
				size_type n = 0;
				for(const_iterator it = begin(); it != end(); it++)
				{
					if (k == it->first)
						n++;
				}
				return ( n );
			}

			/* returns iterator to first node before */
			iterator lower_bound(const key_type& x)
			{
				iterator first = begin();
				iterator last = end();
				while (first != last)
				{
					if (!_comp(first->first, x))
						break ;
					first++;
				}
				return (first);
			}

			const_iterator lower_bound(const key_type& x) const
			{
				const_iterator first = begin();
				const_iterator last = end();
				while (first != last)
				{
					if (!_comp(first->first, x))
						break ;
					first++;
				}
				return (first);
			}

			/* returns iterator to first node after */
			iterator upper_bound(const key_type& x)
			{
				iterator first = begin();
				iterator last = end();
				while (first != last)
				{
					if (_comp(x, first->first))
						break ;
					first++;
				}
				return (first);
			}

			const_iterator upper_bound(const key_type& x) const
			{
				const_iterator first = begin();
				const_iterator last = end();
				while (first != last)
				{
					if (_comp(x, first->first))
						break ;
					first++;
				}
				return (first);
			}

			allocator_type get_allocator() const { return ( _alloc ); }
			ft::pair<iterator,iterator>
			equal_range(const key_type& x) { return ( ft::make_pair(lower_bound(x), upper_bound(x)) ); }
			
			ft::pair<const_iterator,const_iterator>
			equal_range(const key_type& x) const { return ( ft::make_pair(lower_bound(x), upper_bound(x)) ); }
	};

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator==(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		typename map<Key, T, Compare, Allocator>::const_iterator	it = lhs.begin();
		typename map<Key, T, Compare, Allocator>::const_iterator	ite = lhs.end();
		typename map<Key, T, Compare, Allocator>::const_iterator	it2 = rhs.begin();

		while (it != ite && it2 != rhs.end())
		{
			if (it->first != it2->first || it->second != it2->second)
				return (false);
			it++;
			it2++;
		}
		return (it == ite && it2 == rhs.end());
	}
	
	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator!=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return ( ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) );
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator<=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	bool operator>=(const map<Key, T, Compare, Allocator> &lhs, const map<Key, T, Compare, Allocator> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	void swap(map<Key, T, Compare, Allocator> &lhs, map<Key, T, Compare, Allocator> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif // __FT_MAP_H__
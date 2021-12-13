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
			// types:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const Key, T> value_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::reference reference;
			typedef typename Allocator::const_reference const_reference;
			typedef typename ft::BST<value_type, key_compare>::node_type node_type;
			typedef typename ft::BST<value_type, key_compare>::iterator iterator; // See 23.1
			typedef typename ft::BST<value_type, key_compare>::const_iterator const_iterator; // See 23.1
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef typename Allocator::pointer pointer;
			typedef typename Allocator::const_pointer const_pointer;
			typedef std::reverse_iterator<iterator> reverse_iterator;
			typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

		class value_compare : public binary_function<value_type,value_type,bool>
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
			size_type								_size;

		public:

			// 23.3.1.1 construct/copy/destroy:
			explicit map(const Compare& comp = Compare(), const Allocator& a = Allocator())
						: _tree(comp), _alloc(a), _size(0) {}
	
			template <class InputIterator>
			map(InputIterator first, InputIterator last, const Compare& comp = Compare(), const Allocator& a = Allocator(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr )
				: _size(0), _tree(node_type(comp)), _alloc(a)
			{
				for(; first != last; ++first)
					insert(*first);
			}


			map(const map<Key,T,Compare,Allocator>& x) : _tree(x._tree), _alloc(x._alloc), _size(x._size) {}
			~map() {}// pe a mettre en virtual
			
			// map<Key,T,Compare,Allocator>& operator=(const map<Key,T,Compare,Allocator>& x);

			// iterators:
			iterator	begin() { return ( iterator(_tree.LeftMost()) ); }
			const_iterator	begin() const { return ( const_iterator(_tree.LeftMost()) ); }
			iterator	end() { return ( iterator(_tree.RightMost()) ); }
			const_iterator	end() const { return ( const_iterator(_tree.RightMost()) ); }
			reverse_iterator	rbegin() { return ( reverse_iterator(_tree.RightMost()) ); }
			const_reverse_iterator	rbegin() const { return ( const_reverse_iterator(_tree.RightMost()) ); }
			reverse_iterator	rend() { return ( reverse_iterator(_tree.LeftMost()) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator(_tree.LeftMost()) ); }

			// capacity:
			bool	empty() const { return ( _size == 0 ); }
			size_type	size() const { return ( _size ); }
			size_type	max_size() const { return ( _tree.max_size() ); }

			// // 23.3.1.2 element access:
			// T& operator[](const key_type& x);

			// modifiers:
			ft::pair<iterator, bool>	insert(const value_type& x)
			{
				ft::pair<iterator, bool> res =_tree.insert(x);
				if (res.second == true)// si value a bien été trouvée 
					_size++; // alors j'ai ajouté un node
				return ( res );
			}

			iterator	insert(iterator position, const value_type& x)
			{
				(void)position;
				ft::pair<iterator, bool> res =_tree.insert(x);
				if (res.second == true )
					_size++;
				return ( res.first );
			}
			
			template <class InputIterator>
			void	insert(InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
			{
				for(; first != last; ++first)
					insert(*insert);
			}

			// void erase(iterator position);
			// size_type erase(const key_type& x);
			// void erase(iterator first, iterator last);
			// void swap(map<Key,T,Compare,Allocator>&);
			void clear() 
			{
				_tree.clear();
				_size = 0;
			}

			// // observers:
			// key_compare key_comp() const;
			// value_compare value_comp() const;

			// 23.3.1.3 map operations:
			iterator find(const key_type& x) { return ( iterator( _tree.find(k) ) ); }
			const_iterator find(const key_type& x) const { return ( const_iterator( _tree.find(k) ); }

			// size_type count(const key_type& x) const;
			// iterator lower_bound(const key_type& x);
			// const_iterator lower_bound(const key_type& x) const;
			// iterator upper_bound(const key_type& x);
			// const_iterator upper_bound(const key_type& x) const;
			
			// ft::pair<iterator,iterator>
			// equal_range(const key_type& x);
			
			// ft::pair<const_iterator,const_iterator>
			// equal_range(const key_type& x) const;

	};

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator==(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator< (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator!=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator> (const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator>=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// bool operator<=(const map<Key,T,Compare,Allocator>& x, const map<Key,T,Compare,Allocator>& y);

	// template <class Key, class T, class Compare, class Allocator>
	// void swap(map<Key,T,Compare,Allocator>& x, map<Key,T,Compare,Allocator>& y);


}

#endif // __FT_MAP_H__
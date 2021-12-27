/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BST.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 19:38:08 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 19:38:09 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __BST_H__
#define __BST_H__

#include "BST_node.hpp"
#include "BST_iterator.hpp"
#include "ft_utils.hpp"
#include "ft_type_resolution.hpp"

#include <memory>

namespace ft
{
	template <class T, class Compare = ft::less<typename T::first_type>, class Allocator = std::allocator<T> >
	class BST
	{
		public:
			/*
			* basic typedef of MAP
			* T being the pair object wrapper containing
			* key_type as the sorting key used in the BST
			* and mapped_type as the value being sorted
			* Compare is the usual boolean comparison object used in map, by default set on <
			*/
			typedef T										value_type;
			typedef typename T::first_type					key_type;
			typedef typename T::second_type					mapped_type;
			typedef Compare									key_compare;

			/* typedef of RB_tree node */
			typedef	ft::BST_node<value_type>				node_type;
			typedef node_type*								node_pointer;
			typedef node_type&								node_reference;

			/* 
			* below expression is identical to typedef std::allocator<node_type>	node_allocator;
			*/
			typedef typename Allocator::template rebind<node_type>::other node_allocator;

			/* pointer & reference */
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference 	const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			/* iterators */
			typedef ft::BST_iterator<node_type>				iterator;
			typedef ft::BST_const_iterator<node_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;


		/*
		* key attributes used in the BST
		* _root value is by default always the first node at the beginning of the tree and
		* is used as starting point of almost every operations in our BST
		* _comp object is used in case Compare object used in map is reversed
		*/
		private:
			node_pointer		_root;
			size_type			_size;
			node_allocator		_node_alloc;
			key_compare			_comp;


		public:
			/* Member type key_compare is the internal comparison object type used by the container */
			BST(const key_compare &c = key_compare())
			{
				_root = nullptr;
				_comp = c;
				_size = 0;
			} 

			/* copy constructor */
			BST(const BST& x) : _root(nullptr), _comp(x._comp)
			{
				_size = 0;
				insert(x.begin(), x.end());
			}

			/* assignment operator */
			BST	&operator=(const BST &x)
			{
				if (*this != x)
					_root = x._root;
				return ( *this );
			}

			/* destructor */
			virtual ~BST() { clear(); }

			/* insert */
			iterator insert(iterator position, const value_type &v)
			{
				(void)position;
				return ( _node_insert(_root , v) );
			}

			template<class InputIterator>
			void	insert(InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
			{
				for (; first != last; ++first)
					_node_insert(_root, *first);
			}

			ft::pair<iterator, bool> insert(const value_type &v) { return ( _node_insert(_root, v) ); }

			/* find */
			iterator	find(const key_type &k) { return ( _searchNode(_root, k) ); }
			const_iterator	find(const key_type &k) const { return ( _searchNode(_root, k) ); }

			/* size */
			size_type	size() const { return ( _size ); }
			size_type	max_size() const { return ( _node_alloc.max_size() ); }

			/* returns a pointer to min value in tree */
			node_pointer	LeftMost(node_pointer root) const
			{
				node_pointer iter = root;
				if ( iter )
				{
					while (iter->left != NULL)
						iter = iter->left;
				}
				return ( iter );
			}

			/* returns a pointer to max value in tree */
			node_pointer	RightMost(node_pointer root) const
			{
				node_pointer iter = root;
				if (iter)
				{
					while (iter->right )
						iter = iter->right;
				}
				return ( iter );
			}

			/* clear entire tree */
			void	clear() 
			{
				_destroy(_root);
				_size = 0;
			}

			/* iterators */
			iterator	begin() { return ( iterator(LeftMost(_root)) ); }
			const_iterator begin() const { return ( const_iterator(LeftMost(_root)) ); }
			iterator	end() { return ( iterator(NULL, RightMost(_root)) ); }
			const_iterator	end() const { return ( const_iterator(NULL, RightMost(_root)) ); }
			reverse_iterator	rbegin() { return ( reverse_iterator(end()) ); }
			const_reverse_iterator	rbegin() const { return ( const_reverse_iterator(end()) ); }
			reverse_iterator	rend() { return ( reverse_iterator(begin()) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator(begin()) ); }

			/* erase */

			/*
			* Following function manages all cases of node deletion non recursively
			* Case 1 : if node to delete has two childs
			*	then find leftmost value of its right child and takes its value
			*	then delete child whose value has been copied but after updating pointer to its child
			*	but if child to be deleted as no child of his own, we update node pointer to null
			* Case 2: if node to delete has only one, or no child
			*	then we update its child parent to be the node own parent
			*	if the parent is null, its mean node to be deleted is _root is such case we update _root with its child
			*	if node to delete as no child, we simply set its parent node pointer to it to null
			*	if right or left child is not null, we update node's parent node to point to node's child
			*	and last, if only _root is left we simply delete it
			*/
			void erase(iterator position)
			{
				if (position == end() || !_size )
					return ;
				node_pointer del = _searchNode(_root, position->first);
				if (del->left && del->right)
				{
					node_pointer child = LeftMost(del->right);
					del->value = child->value;
					if (child->right)
					{
						child->right->parent = del;
						del->right = child->right;
					}
					else if (child->left)
					{
						child->left->parent = del;
						del->left = child->left;
					}
					if (!child->right && !child->left)
					{
						if (child->parent->right == child)
							child->parent->right = NULL;
						else if (child->parent->left == child)
							child->parent->left = NULL;
					}
					_node_alloc.destroy(child);
					_node_alloc.deallocate(child, 1);
					_size--;
				}
				else
				{
					node_pointer child = (del->left != NULL) ? del->left : del->right;
					if (child)
					{
						child->parent = del->parent;
						if (!child->parent)
						{
							_node_alloc.destroy(del);
							_node_alloc.deallocate(del, 1);
							del = child;
							_root = child;
							_size--;
							return ;
						}
					}
					else if (del->parent)
					{
						if (del->parent->right == del)
							del->parent->right = NULL;
						if (del->parent->left == del)
							del->parent->left = NULL;
					}
					if (del->left)
					{
						if (del->parent->left == del)
							del->parent->left = child;
						else
							del->parent->right = child;
					}
					else if (del->right)
					{
						if (del->parent->right == del)
							del->parent->right = child;
						else
							del->parent->left = child;
					}
					if (del == _root && !del->right && !del->left)
					{
						_node_alloc.destroy(del);
						_node_alloc.deallocate(del, 1);
						del = _root = NULL;
						_size--;
						return ;
					}
					_node_alloc.destroy(del);
					_node_alloc.deallocate(del, 1);
					del = NULL;
					_size--;
				}
			}

			size_type erase(const key_type& x)
			{
				iterator it = find(x);
				if (it != end())
				{
					erase(it);
					return ( 1 );
				}
				return ( 0 );
			}

			/* we update iterator value after deleting preceding node */
			void erase(iterator first, iterator last)
			{
				for (; first != last;)
				{
					iterator tmp = first;
					++tmp;
					erase(first);
					first = tmp;
				}
			}

			void	swap(BST &x)
			{
				ft::swap(_root, x._root);
				ft::swap(_node_alloc, x._node_alloc);
				ft::swap(_comp, x._comp);
				ft::swap(_size, x._size);
			}

		/* assist functions */
		protected:

			/* will find node with corresponding key going left if possible, otherwise right */
			node_pointer	_searchNode(node_pointer node, const key_type &k) const
			{
				node_pointer res = node;
				while ( res )
				{
					if ( res->value.first == k )
						return ( res );
					else if (k < res->value.first) 
						res = res->left;
					else
						res = res->right;
				}
				return ( NULL );
			}

			/*
			* Insert assist function, if _root is null, tree is empty
			* otherwise searches for a node with the same key prior to insertion
			* if key is found, returns an iterator to node with same key and boolean value set to false
			* if key is not found, insert value under closest node with a superior key and
			* returns iterator to newly insert node with boolean value set to true
			*/
			ft::pair<iterator, bool>	_node_insert(node_pointer node, const value_type &k)
			{
				if (_root == NULL)
				{
					_root = _node_alloc.allocate(1);
					_node_alloc.construct(_root, node_type(k));
					_size++;
					return ( ft::pair<iterator, bool>(iterator(_root), true) );
				}
				else
				{
					node_pointer current = node;
					node_pointer parent = NULL;
					while (current)
					{
						parent = current;
						if ( _comp(k.first, current->value.first) )
							current = current->left;
						else if ( _comp(current->value.first, k.first) )
							current = current->right;
						else
							return ( ft::pair<iterator, bool>(iterator(current), false) );
					}
					current = _node_alloc.allocate(1);
					_node_alloc.construct(current, node_type(k));
					_size++;
					if ( _comp(k.first, parent->value.first) )
						parent->left = current;
					else
						parent->right = current;
					current->parent = parent;
					return ( ft::pair<iterator, bool>(iterator(current), true) );
				}
			}

			/* assist function that clears the entire tree of its node */
			void	_destroy(node_pointer& root)
			{
				if (root)
				{
					_destroy(root->left);
					_destroy(root->right);
					_node_alloc.destroy(root);
					_node_alloc.deallocate(root, 1);
					root = nullptr;
				}
			}
	};

}

#endif // __BST_H__
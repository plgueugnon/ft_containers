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
			/* basic typedef of MAP */
			// typedef Key										key_type; // cle de tri
			// typedef T										mapped_type; // valeur trie
			// typedef ft::pair<const Key, T>					value_type; // valeur contenu dans les nodes
			typedef T										value_type;
			typedef typename T::first_type					key_type;
			typedef typename T::second_type					mapped_type;
			typedef Compare									key_compare; // boolen de comparaison a < b

			/* typedef of RB_tree node */
			typedef	ft::BST_node<value_type>				node_type; // contenu d'une node
			// typedef	ft::BST_node<const value_type>				const_node_type;
			typedef node_type*								node_pointer; // ptr sur node
			typedef node_type&								node_reference;
			typedef std::allocator<node_type>				node_allocator; // allocator de node

			/* pointer & reference */
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference 	const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;

			/* iterators */
			typedef ft::BST_iterator<node_type>						iterator;
			typedef ft::BST_const_iterator<node_type>				const_iterator; // erreur ici en enlevant const
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;


		private:
			node_pointer		_root; // ptr sur node // sert de point depart depuis le haut de l'arbre pour chaque operation
			//node_pointer		_end; // a voir si utile
			size_type			_size;
			node_allocator		_node_alloc;
			key_compare			_comp;


		public:

			/* construit node a partir comparateur booleen Compare */
			/* Member type key_compare is the internal comparison object type used by the container */
			BST(const key_compare &c = key_compare())
			{
				// a voir si obligatoire de allocate un node null pour que marche
				_root = nullptr; // init la root sur NULL car arbre vide / avec 1 seule node
				_comp = c; // stocke la premiere valeur clé
				_size = 0;
				// _end = _node_alloc.allocate(1);
				// _node_alloc.construct(_end, node_type(ft::pair<0, 0>));
			} 

			/* copy constructor */
			BST(const BST& x) : _root(nullptr), _comp(x._comp)
			{
				// std::cout << "BST RANGE construct\n";
				// idem - voir si besoin de faire un alloc pour init le tree ou si peut fonctionner sans
				// _end = _node_alloc.allocate(1);
				// _node_alloc.construct(_end, node_type(ft::pair<0, 0>));
				_size = 0;
				insert(x.begin(), x.end());
			}
			/* assignment operator */
			BST	&operator=(const BST &x)
			{
				if (*this != x)
					_root = x._root; // simple swap d'adresse ici mais recopie complete arbre dans map
				return ( *this );
			}
			/* destructor */
			virtual ~BST() 
			{
				clear();
				// _node_alloc.destroy(_end);
				// _node_alloc.deallocate(_end, 1);
			} // pe a mettre en virtuel si pb lors heritage

			/* insert */
			iterator insert(iterator position, const value_type &v)
			{
				// std::cout << "BST insert1\n";
				(void)position;
				return ( _node_insert(_root , v) ); // a verif mais en principe suffit
			}

			template<class InputIterator>
			void	insert(InputIterator first, InputIterator last, 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
			{
				// std::cout << "BST insert2 (RANGE)\n";
				// std::cout << &first << "\n";
				// std::cout << &(*first) << "\n";
				// std::cout << &last<< "\n";
				// std::cout << &(*last) << "\n";
				// std::cout << "check first " << first->second << " + " << first->first << '\n';
				// std::cout << "check second " << last->second << " + " << last->first << '\n';
				// std::cout << first->first << "\n";
				// std::cout << "addr parent " << first
				for (; first != last; ++first)
				{
					// std::cout << "sending with address: " << &first << '\n';
					// std::cout << "sending with address: " << &(*first) << '\n';
					// std::cout << "sending : " << first->first << '\n';
					_node_insert(_root, *first);
				}
				// _node_insert(_root, *first); // RUSTINE A PB ++ !!
			}

			ft::pair<iterator, bool> insert(const value_type &v)
			{
				// std::cout << "BST insert3\n";
				return ( _node_insert(_root, v) );
			}

			/* find */
			iterator	find(const key_type &k)
			{
				return ( _searchNode(_root, k) );
			}

			const_iterator	find(const key_type &k) const
			{
				return ( _searchNode(_root, k) );
			}

			size_type	size() const { return ( _size ); }
			size_type	max_size() const { return ( _node_alloc.max_size() ); }

			node_pointer	LeftMost(node_pointer root) const
			{
				// std::cout << "BST Leftmost\n";
				node_pointer iter = root;
				// while (iter && iter->left != NULL)
				if ( iter )
				{
					while (iter->left != NULL)
						iter = iter->left;
				}
				return ( iter );
			}

			node_pointer	RightMost(node_pointer root) const
			{
				// std::cout << "BST Rightmost\n";
				node_pointer iter = root;
				// while (iter && iter->right != NULL)
				if (iter)
				{
					// while (iter->right != NULL)
					while (iter->right )
						iter = iter->right;
				}
				return ( iter );
			}

			void	clear() 
			{
				_destroy(_root);
				_size = 0;
			}

			// size_type	count(const key_type &k) const
			// {
			// 	size_type n = 0;
			// 	for(const_iterator it = begin(); it != end(); it++)
			// 	{
			// 		if (k == it->first)
			// 			n++
			// 	}
			// 	return ( n );
			// }

			iterator	begin() 
			{
				return ( iterator(LeftMost(_root)) );
			}
			const_iterator begin() const 
			{
				return ( const_iterator(LeftMost(_root)) );
			}
			iterator	end() 
			{
				// node_pointer past_end = RightMost();
				return ( iterator(NULL, RightMost(_root)) );
			}
			const_iterator	end() const
			{
				// node_pointer past_end = RightMost();
				return ( const_iterator(NULL, RightMost(_root)) );
			}
			reverse_iterator	rbegin()
			{
				return ( reverse_iterator(end()) );
			}
			const_reverse_iterator	rbegin() const
			{
				return ( const_reverse_iterator(end()) );
			}
			reverse_iterator	rend() { return ( reverse_iterator(begin()) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator(begin()) ); }

			node_reference	operator*() const
			{
				return ( _root );
			}

			node_pointer	operator->() const
			{
				return ( &(operator*()) );
			}

	// if (key < root->key)
	// 	root->left = deleteNode(root->left, key);
	// else if (key > root->key)
	// 	root->right = deleteNode(root->right, key);
	// else
	// {
	// 	// si node seule ou avec 1 child => suppr et remplacer par son fils
	// 	if (root->left == NULL)
	// 	{
	// 		t_node *tmp = root->right;
	// 		delete root;
	// 		return tmp;
	// 	}
	// 	else if (root->right == NULL)
	// 	{
	// 		t_node *tmp = root->left;
	// 		delete root;
	// 		return tmp;
	// 	}
	// 	// si node avec deux fils => va dans son fils droite, prendre le fils gauche le plus bas
	// 	t_node * tmp = minValueNode(root->right);
	// 	root->key = tmp->key; // la valeur de la node la plus a gauche du fils droite est copié a la place de la node a suppr
	// 	root->right = deleteNode(root->right, tmp->key);

			void erase(iterator position)
			{
				if (position == end() || !_size )
					return ;
				node_pointer del = _searchNode(_root, position->first);
				// std::cout << del << "key: " << del->value.first << "\n";
				// std::cout << "d parent: " << del->parent << "\n";
				// if (del->parent)
				// 	std::cout << "d parent: " << del->parent->value.first << "\n";
				// std::cout << "d right: " << del->right << "\n";
				// std::cout << "d left: " << del->right << "\n";
				// // std::cout << "d right: " << del->right->parent << "\n";
				// std::cout << _root << "rkey: " << _root->value.first << "\n";
				// std::cout << "r parent: " << _root->parent << "\n";
				// std::cout << "r parent v: " << _root->parent->value.first << "\n"; // rien
				// std::cout << "r parent l: " << _root->parent->left << "\n";
				// std::cout << "r parent r: " << _root->parent->right << "\n";
				if (del->left && del->right)
				{
					// std::cout << "check1\n";
					// std::cout << "l val " << del->left->value.first << '\n';
					// std::cout << "r val " << del->right->value.first << '\n';
					// std::cout << "r val " << del->right->right->value.first << '\n';
					node_pointer child = LeftMost(del->right);
					del->value = child->value;
					// child->parent->right = child->right;
					// std::cout << "child val " << child->value.first << '\n';
					// std::cout << "child pval " << child->parent->right->value.first << '\n';
					// std::cout << "child pval " << child->right->value.first << '\n';
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
					// del->right->parent =  del;
					_size--;
				}
				else
				{
					// std::cout << "check2\n";
					node_pointer child = (del->left != NULL) ? del->left : del->right;
					if (child)
					{
						// std::cout << "child ? " << child << "\n";
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
						// std::cout << "check del " << del->value.first << '\n';
						// std::cout << "check del from parent " << del->parent->left << '\n';
						// std::cout << "check parent " << del->parent->value.first << '\n';
						// if (del->parent->left)
						// 	std::cout << "check del parent left " << del->parent->left->value.first << '\n';
						
						if (del->parent->right == del)
							del->parent->right = NULL;
						if (del->parent->left == del)
							del->parent->left = NULL;
					}
					// else if (!child && !del->parent)
					// 	return ;
					if (del->left)
					{
						// std::cout << "check3\n";
						if (del->parent->left == del)
							del->parent->left = child;
						else
							del->parent->right = child;
					}
					else if (del->right)
					{
						// std::cout << "check4\n";
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


					// if (del->left == NULL)
					// {
					// 	node_pointer tmp = del->right;
					// 	_node_alloc.destroy(del);
					// 	_node_alloc.deallocate(del, 1);
					// 	return ;
					// }
					// else if (del->right == NULL)
					// {
					// 	node_pointer tmp = del->left;
					// 	_node_alloc.destroy(del);
					// 	_node_alloc.deallocate(del, 1);
					// 	return ;
					// }

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
			void erase(iterator first, iterator last)
			{
				// for(iterator it = first; it != last; it++)
				// 	erase(it);
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

			node_pointer	_searchNode(node_pointer node, const key_type &k) const
			{
				node_pointer res = node;
				// if (res == NULL)
				// 	return res;
				// else
				// {
				// 	if (res->value.first == k)
				// 		return ( res );
				// 	if (k < res->value.first)
				// 		return _searchNode(res->left, k);
				// 	else
				// 		return _searchNode(res->right, k);

				// node_pointer res = NULL;
				// if (node)
				// {
				// 	if (node->value.first == k)
				// 		return ( node );
				// 	if (node->left)
				// 		res = _searchNode(node->left, k);
				// 	if (node->right && res == NULL)
				// 		res = _searchNode(node->right, k);
				// }
				// return ( res );




				while ( res ) // res != NULL
				{
					if ( res->value.first == k ) // si cle trouvee
						return ( res );
					else if (k < res->value.first) // sinon avance droite ou gauche
						res = res->left;
					else
						res = res->right;
				}
				// node_pointer past_end = RightMost();
				return ( NULL );
				// return ( RightMost() ); // si trouve pas => renvoie end()
			}

			ft::pair<iterator, bool>	_node_insert(node_pointer node, const value_type &k)
			{
				// node_pointer newnode = NULL;
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
						if ( k.first < current->value.first )
							current = current->left;
						else if (k.first > current->value.first)
							current = current->right;
						else
							return ( ft::pair<iterator, bool>(iterator(current), false) );
					}
					current = _node_alloc.allocate(1);
					_node_alloc.construct(current, node_type(k));
					_size++;
					if ( k.first < parent->value.first ) // si inf => fils gauche
						parent->left = current;
					else
						parent->right = current;
					current->parent = parent;
					// node_pointer actu = RightMost();
					// actu->right = _end;
					// _end->parent = actu;
					return ( ft::pair<iterator, bool>(iterator(current), true) );
				}

				// std::cout << "BST node insert\n";
				// std::cout << "inserting : " << k.first << " + " << k.second << '\n';
				// node_pointer	iter = NULL;
				// while (node) // je cherche la node
				// {
				// 	std::cout << "BST node insert check 1\n";
				// 	iter = node; // prend addresse root / pt depart insertion
				// 	std::cout << "1 key :" << k.first << "\n";
				// 	std::cout << "2 value addr : " << &node->value << "\n";
				// 	std::cout << "3 node content : " << node->value.first << " + " << node->value.second << "\n";
				// 	if ( k.first < node->value.first )
				// 		node = node->left;
				// 	else if (k.first > node->value.first)
				// 		node = node->right;
				// 	else
				// 		return ( ft::pair<iterator, bool>(iterator(node), false) ); // renvoie un iterateur sur la position dans l'arbre avec faux car key deja existant
				// } //si node pas trouvée = revient a dire node == NULL
				// node = _node_alloc.allocate(1);

				// _node_alloc.construct(node, node_type(k)); // je construit une node avec la clé valeur passée en arg

				// if (iter) // if iter != NULL
				// {
				// 	std::cout << "BST node insert check 2\n";
				// 	if ( k.first < iter->value.first ) // si inf => fils gauche
				// 		iter->left = node;
				// 	else
				// 		iter->right = node; // sinon fils droite
				// }
				// else
				// 	_root = node;// si aucune node existe => root prend adresse
				// std::cout << "checking root value = " << _root->value.first << '\n';
				// return ( ft::pair<iterator, bool>(iterator(node), true) ); // renvoie iterator true si nouvelle node créée
			}

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


			/**************************************************************/ // TO DO



			// bool		empty();
			// size_type	size();









			
			// iterator	lower_bounds();
			// const_iterator	lower_bounds();
			// iterator	upper_bound();
			// const_iterator	upper_bound();
			// equal_range();

			// void	rotateL();
			// void	rotateR();
			// node_pointer	get_root();


	};

}

#endif // __BST_H__
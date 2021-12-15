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
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;


		private:
			node_pointer		_root; // ptr sur node // sert de point depart depuis le haut de l'arbre pour chaque operation
			node_pointer		_nil; // a voir si utile
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
			} 

			/* copy constructor */
			BST(const BST& x) : _root(nullptr), _comp(x._comp)
			{
				// std::cout << "BST RANGE construct\n";
				// idem - voir si besoin de faire un alloc pour init le tree ou si peut fonctionner sans
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
			virtual ~BST() { clear(); } // pe a mettre en virtuel si pb lors heritage

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
				for (; first != last; first++)
				{
					std::cout << "sending with address: " << &first << '\n';
					std::cout << "sending with address: " << &(*first) << '\n';
					std::cout << "sending : " << first->first << '\n';
					_node_insert(_root, *first);
				}
				_node_insert(_root, *first); // RUSTINE A PB ++ !!
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

			size_type	max_size() const { return ( _node_alloc.max_size() ); }

			node_pointer	LeftMost() const
			{
				// std::cout << "BST Leftmost\n";
				node_pointer iter = _root;
				// while (iter && iter->left != NULL)
				if ( iter )
				{
					while (iter->left != NULL)
						iter = iter->left;
				}
				return ( iter );
			}

			node_pointer	RightMost() const
			{
				// std::cout << "BST Rightmost\n";
				node_pointer iter = _root;
				// while (iter && iter->right != NULL)
				if (iter)
				{
					while (iter->right != NULL)
						iter = iter->right;
				}
				return ( iter );
			}

			void	clear() { _destroy(_root); }

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
				return ( iterator(LeftMost()) );
			}
			const_iterator begin() const 
			{
				return ( const_iterator(LeftMost()) );
			}
			iterator	end() 
			{
				return ( iterator(RightMost()) );
			}
			const_iterator	end() const
			{
				return ( const_iterator(RightMost()) );
			}
			reverse_iterator	rbegin() 
			{
				return ( reverse_iterator(RightMost(), NULL) );
			}
			const_reverse_iterator	rbegin() const
			{
				return ( const_reverse_iterator(RightMost(), NULL) );
			}
			reverse_iterator	rend() { return ( reverse_iterator(LeftMost(), NULL) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator(LeftMost(), NULL) ); }

			node_reference	operator*() const
			{
				return ( _root );
			}

			node_pointer	operator->() const
			{
				return ( &(operator*()) );
			}

		/* assist functions */
		protected:

			node_pointer	_searchNode(node_pointer node, const key_type &k)
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

				while ( res ) // res != NULL
				{
					if ( res->value.first == k ) // si cle trouvee
						return ( res );
					else if (k < res->value.first) // sinon avance droite ou gauche
						res = res->left;
					else
						res = res->right;
				}
				return ( RightMost() ); // si trouve pas => renvoie end()
			}

	// // on va trouver le point d'insertion correct
	// if (!n)
	// 	return newNode(key);
	// if (key < n->key)
	// 	n->left = insertNode(n->left, key);
	// else if (key > n->key)
	// 	n->right = insertNode(n->right, key);
	// else
	// 	return n;


			ft::pair<iterator, bool>	_node_insert(node_pointer node, const value_type &k)
			{
				// node_pointer newnode = NULL;
				if (_root == NULL)
				{
					_root = _node_alloc.allocate(1);
					_node_alloc.construct(_root, node_type(k));
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
					if ( k.first < parent->value.first ) // si inf => fils gauche
						parent->left = current;
					else
						parent->right = current;
					current->parent = parent;
					return ( ft::pair<iterator, bool>(iterator(current), true) );
				}




				// if (!_root) // si pas root => d'abord on créé root
				// {
				// 	std::cout << "check 1\n";
				// 	node = _node_alloc.allocate(1);
				// 	node->parent = nullptr;
				// 	node->left = nullptr;
				// 	node->right = nullptr;
				// 	_node_alloc.construct(node, node_type(k));
				// 	_root = node; // _root devient première node
				// 	return ( ft::pair<iterator, bool>(iterator(node), true) );
				// }

				// node_pointer	iter = _searchNode(node, k.first); // va chercher depuis root la valeur k
				// if (iter != RightMost()) // j'ai trouvé le ptr => renvoie addresse
				// 	return ( ft::pair<iterator, bool>(iterator(iter), false) );
				// else // pas de node existante
				// {
				// 	std::cout << "check 2\n";
				// 	node_pointer iter2 = _root;
				// 	while (iter2)
				// 	{
				// 		if ( k.first < iter2->value.first )
				// 			iter2 = iter2->left;
				// 		else if (k.first > iter2->value.first)
				// 			iter2 = iter2->right;
				// 	}
				// 	node_pointer tmp = NULL;
				// 	tmp = _node_alloc.allocate(1);
				// 	node->left = nullptr;
				// 	node->right = nullptr;
				// 	_node_alloc.construct(tmp, node_type(k));
				// 	if ( k.first < iter2->value.first ) // si inf => fils gauche
				// 		iter2->left = tmp;
				// 	else
				// 		iter2->right = tmp;
				// 	return ( ft::pair<iterator, bool>(iterator(tmp), true) );
				// }
				// return ( ft::pair<iterator, bool>(iterator(_root), false) );

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



			// void	erase();
			// size_type	erase();
			// void	erase();

			// void	swap();



			
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
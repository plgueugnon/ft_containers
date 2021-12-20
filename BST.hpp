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
					_root = x._root; // simple swap d'adresse ici mais recopie complete arbre dans map
				return ( *this );
			}
			/* destructor */
			virtual ~BST() { clear(); }

			/* insert */
			iterator insert(iterator position, const value_type &v)
			{
				(void)position;
				return ( _node_insert(_root , v) ); // a verif mais en principe suffit
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

			void	clear() 
			{
				_destroy(_root);
				_size = 0;
			}

			iterator	begin() { return ( iterator(LeftMost(_root)) ); }
			const_iterator begin() const { return ( const_iterator(LeftMost(_root)) ); }
			iterator	end() { return ( iterator(NULL, RightMost(_root)) ); }
			const_iterator	end() const { return ( const_iterator(NULL, RightMost(_root)) ); }
			reverse_iterator	rbegin() { return ( reverse_iterator(end()) ); }
			const_reverse_iterator	rbegin() const { return ( const_reverse_iterator(end()) ); }
			reverse_iterator	rend() { return ( reverse_iterator(begin()) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator(begin()) ); }

			void erase(iterator position)
			{
				if (position == end() || !_size )
					return ;
				node_pointer del = _searchNode(_root, position->first); // si position != null va chercher ptr a suppr
				if (del->left && del->right) // si node a deux fils (case 1)
				{
					node_pointer child = LeftMost(del->right); // va cherche le plus a gauche depuis droite
					del->value = child->value; // copie valeur trouve dans node vise par suppr
					if (child->right)// si fils droite de node qui va etre suppr (child)
					{
						child->right->parent = del; // node visee par suppr (del) devient son parent
						del->right = child->right; // actualise fils droite avec fils droite de node qui va etre suppr
					}
					else if (child->left)
					{
						child->left->parent = del;
						del->left = child->left;
					}
					if (!child->right && !child->left) // si aucun fils (parent seul), je set a null le ptr sur le fils qui va etre suppr (pr eviter acces lecture valeur suppr)
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
				else // node a un seul, ou aucun fils (case 2)
				{
					node_pointer child = (del->left != NULL) ? del->left : del->right; // child prend adresse fils non nul
					if (child)
					{
						child->parent = del->parent; // parent du fils devient celui node a suppr
						if (!child->parent) // si parent null => veut dire que node a suppr == root
						{
							_node_alloc.destroy(del);
							_node_alloc.deallocate(del, 1);
							del = child;
							_root = child; // actualise root sur fils droite ou gauche non nul
							_size--;
							return ;
						}
					}
					else if (del->parent) // si aucun fils, node va simplement etre suppr => besoin de set ptr de son parent sur null
					{
						if (del->parent->right == del)
							del->parent->right = NULL;
						if (del->parent->left == del)
							del->parent->left = NULL;
					}
					if (del->left) // si fils droit != null
					{
						if (del->parent->left == del) // si fils parent est del => actualise ptr sur child
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
					if (del == _root && !del->right && !del->left) // si il ne reste que root sur l'arbre
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
			void erase(iterator first, iterator last)
			{
				for (; first != last;)
				{
					iterator tmp = first;
					++tmp; // pour eviter increment en trop par tour
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
				while ( res ) // res != NULL
				{
					if ( res->value.first == k ) // si cle trouvee
						return ( res );
					else if (k < res->value.first) // sinon avance droite ou gauche
						res = res->left;
					else
						res = res->right;
				}
				return ( NULL ); // si rien n'est trouvé => null
			}

			ft::pair<iterator, bool>	_node_insert(node_pointer node, const value_type &k)
			{
				if (_root == NULL) // si arbre vide
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
					while (current) // je cherche la node
					{
						parent = current; // prend addresse root / pt depart insertion
						if ( k.first < current->value.first )
							current = current->left;
						else if (k.first > current->value.first)
							current = current->right;
						else
							return ( ft::pair<iterator, bool>(iterator(current), false) ); // renvoie un iterateur sur la position dans l'arbre avec faux car key deja existant
					}
					current = _node_alloc.allocate(1);
					_node_alloc.construct(current, node_type(k));
					_size++;
					if ( k.first < parent->value.first ) // si inf => fils gauche
						parent->left = current;
					else
						parent->right = current;
					current->parent = parent; // set le parent
					return ( ft::pair<iterator, bool>(iterator(current), true) ); // renvoie iterator true si nouvelle node créée
				}
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
	};

}

#endif // __BST_H__
#ifndef __BST_H__
#define __BST_H__

#include "BST_iterator.hpp"
#include "BST_node.hpp"
#include "ft_utils.hpp"

#include <memory>

namespace ft
{
	template <class Key, class T, class Compare = ft::less<Key>, class Allocator = std::allocator<pair<const Key, T> > >
	class BST
	{
		public:
			/* basic typedef of MAP */
			typedef Key										key_type; // cle de tri
			typedef T										mapped_type; // valeur trie
			typedef ft::pair<const Key, T>					value_type; // valeur contenu dans les nodes
			typedef Compare									key_compare; // boolen de comparaison a < b

			/* typedef of RB_tree node */
			typedef	ft::BST_node<T>							node_type; // contenu d'une node
			typedef node_type*								node_pointer; // ptr sur node
			typedef std::allocator<node_type>				node_allocator; // allocator de node

			/* pointer & reference */
			typedef Allocator								allocator_type;
			typedef typename Allocator::reference			reference;
			typedef typename Allocator::const_reference 	const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		pointer;

			/* iterators */
			typedef ft::BST_iterator<T>						iterator;
			typedef ft::BST_iterator<const T>				const_iterator;
			typedef ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

			typedef std::size_t								size_type;
			typedef ptrdiff_t								difference_type;


		private:
			node_pointer		_root; // ptr sur node // sert de point depart depuis le haut de l'arbre pour chaque operation
			//node_pointer		_nil; // a voir si utile
			size_type			_size;
			node_allocator		_node_alloc;
			key_compare			_comp;


		public:

			/* construit node a partir comparateur booleen Compare */
			/* Member type key_compare is the internal comparison object type used by the container */
			BST(key_compare &c = key_compare())
			{
				// a voir si obligatoire de allocate un node null pour que marche
				_root = nullptr; // init la root sur NULL car arbre vide / avec 1 seule node
				_comp = c; // stocke la premiere valeur clé
			} 

			/* copy constructor */
			BST(const BST& x) : _root(nullptr), _cmp(x._cmp)
			{
				// idem - voir si besoin de faire un alloc pour init le tree ou si peut fonctionner sans
				insert(x.begin(), x.end())
			}
			/* assignment operator */
			BST	&operator=(const BST& x)
			{
				if (*this != x)
					_root = x._root; // simple swap d'adresse ici mais recopie complete arbre dans map
				return ( *this );
			}
			/* destructor */
			~BST(); // pe a mettre en virtuel si pb lors heritage







			/* insert */
			iterator insert(iterator position, const value_type &v);
			
			template<class InputIterator>
			// rajouter typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr
			void	insert(InputIterator first, InputIterator last);
			
			pair<iterator, bool> insert(const value_type &v);
			{

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


			/* assist functions */
		protected:

			node_pointer	_searchNode(node_pointer node, const key_type &k)
			{
				node_pointer res = node;
				if (res == NULL)
					return res;
				else
				{
					if (res->value == key)
						return res;
					else if (key < res->value)
						return _searchNode(res->left, key);
					else
						return _searchNode(res->right, key);
			}

	// if (node == NULL)
	// 	return newNode(key);
	// if (key < node->key)
	// 	node->left = insert(node->left, key);
	// else
	// 	node->right = insert(node->right, key);
	// return node;

			ft::pair<iterator, bool> _node_insert(node_pointer node, const key_type &k)
			{
				node_pointer	iter;
				while (node) // je cherche la node
				{
					iter = node; // prend addresse root / pt depart insertion
					if ( k < node->value )
						node = node->left;
					else if (k > node->right)
						node = node->right;
					else
						return ( ft::pair<iterator, bool>(iterator(node), false) ); // renvoie un iterateur sur la position dans l'arbre avec faux car key deja existant
				} //si node pas trouvée = revient a dire node == NULL
				iter = _node_alloc.allocate(1);
				_node_alloc.construct(node, node_type(k, iter)) // je construit une node avec la clé valeur passée en arg
				if (iter) // if iter != NULL
				{
					if ( k < iter->value ) // si inf => fils gauche
						iter->left = node;
					else
						iter->right = node; // sinon fils droite
				}
				else
					_root = node;// si aucune node existe => root prend adresse
				return ( ft::pair<iterator, bool>(iterator(node), true) ); // renvoie iterator true si nouvelle node créée
			}

/**************************************************************/
// TO DO
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



			void	erase();
			size_type	erase();
			void	erase();

			void	swap();
			void	clear();


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

#endif // __BST_H__
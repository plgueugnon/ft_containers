#ifndef __FT_VECTOR_H__
#define __FT_VECTOR_H__

#include <memory>
#include "ft_random_access_iterator.hpp"
#include "ft_reverse_iterator.hpp"
#include "ft_type_resolution.hpp"
#include "ft_utils.hpp"

namespace ft {

	template<class T, class Allocator = std::allocator<T> >
	class vector {

		public:
			typedef T												value_type;
			typedef Allocator										allocator_type;
			typedef typename Allocator::reference					reference;
			typedef typename Allocator::const_reference				const_reference;
			typedef typename Allocator::pointer						pointer;
			typedef typename Allocator::const_pointer				const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator; // je defini ce qu'est un iterator pour allocator
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
			typedef	std::size_t	size_type; // a check si ces deux alias suffisent pour simplifier les valeurs de retours
			typedef	std::ptrdiff_t	difference_type;

			/* 1 - construct/copy/destroy */

			/* default constructor */
			explicit vector(const Allocator& a = Allocator()) : _allocator(a), _buffer(NULL), _size(0), _capacity(0) {}
			/* fill constructor */
			explicit vector(size_type n, const value_type& value = T(), const Allocator& a = Allocator()) : _allocator(a), _buffer(NULL), _size(n), _capacity(n)
			{

				// equivaut a ecrire ::operateur new(n * sizeof(T)) et a renvoyer un T* (ptr sur objet allocator en l'occurence)
				// plutot que de construire un objet de type T, on a d'abord alloué l'espace pour n type T sans en creer d'instance (donc sans appel du constructor)
				// puis on va creer une instance pour n objet T et y stocker la value correspondante
				if (n) // pour eviter allocation de 0 bytes
					_buffer = _allocator.allocate(n);
				for(size_type i = 0; i < n; i++)
					_buffer.construct(&_buffer[i], value);
			}
			
			/* range constructor */
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const Allocator& a = Allocator(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type) // a retravailler + recheck la logique
					: _allocator(a), _buffer(NULL), _size(0), _capacity(std::distance(first, last))
			{
				if (_capacity)  // pour eviter allocation de 0 bytes
					_buffer = _allocator.allocate(_capacity);
				for(NULL; first != last; first++)
					_allocator.construct(&_buffer[_size++], *first); // size sera incremente a meme valeur que capacity a fin construction
			}

			/* copy constructor */
			vector(const vector<T, Allocator>& x) : _allocator(x._allocator), _size(x._size), _capacity(x._capacity)
			{
				if (_capacity)
					_buffer = _allocator.allocate(_capacity);
				for(size_type i = 0; i < _size; i++)
					_allocator.construct(&_buffer[i], x._buffer[i]);
			}

			/* default destructor */
			~vector()
			{
				for(size_type i = 0; i < _size; i++)
					_allocator.destroy(&_buffer[i]); // appel le destructeur de chacun des elements instanciés
				if (_buffer)
					_allocator.deallocate(_buffer, _capacity); // je free mon buffer de l'ensemble de sa capacité
			}

			/* assignment operator */
			vector<T, Allocator>& operator=(const vector<T, Allocator>& x)
			{
				if (x != *this) // protection contre autoreferencement
				{
					clear();
					insert(begin(), x.begin(), x.end());
				}
				return ( *this );
			}

			/* assign function - need to erase previous content before assigning new value */
			/* range assign */
			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type)
			{
				erase(begin(), end());
				insert(begin(), first, last);
			}

			/* fill assign */
			void	assign(size_type n, const T& u)
			{
				erase(begin(), end());
				insert(begin(), n, u);
			}

			/* getter for private variable _allocator */
			allocator_type	get_allocator() const { return ( _allocator ); }

			/* 2 - iterators */
			/* each one will return an iterator pointing to a position in the vector 
			here represented by the allocated space _vector. Using simple pointer arithmetics 
			we will get an iterator on the beginning or the end */
			iterator			begin() { return ( iterator( _buffer ) ); }
			const_iterator		begin() const { return ( const_iterator( _buffer ) ); }
			iterator			end() { return ( iterator( _buffer + _size ) ); }
			const_iterator		end() const { return ( const_iterator( _buffer + _size ) ); }
			reverse_iterator	rbegin() { return ( reverse_iterator( _buffer + _size ) ); }
			const_reverse_iterator	rbegin() const { return ( const_reverse_iterator( _buffer + _size ) ); }
			reverse_iterator		rend() { return ( reverse_iterator( _buffer ) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator( _buffer ) ); }

			/* 3 - capacity */
			size_type	size() const { return ( _size ); }
			size_type	max_size() const { return ( _allocator.max_size() ); }
			void		resize(size_type sz, T c = T())
			{
				if ( sz > size() )
					insert(end(), sz - size(), c );
				else if ( sz < size() )
					erase(begin() + sz, end());
			}
			size_type	capacity() const { return ( _capacity ); }
			bool	empty() const { return ( !size() ); }
			void	reserve( size_type n )
			{
				if ( n > max_size() )
					throw std::length_error;
				else if ( n > _capacity )
				{
					_capacity = n;
					value_type *tmp = _allocator.allocate( _capacity );
					for (size_type i = 0; i < _size; i++)
					{
						_allocator.construct( &tmp[i], _buffer[i] );
						_allocator.destroy( &_buffer[i] );
					}
					_allocator.deallocate( _buffer, _capacity );
					_buffer = tmp;
				}
			}

			/* 4 - element access */
			reference		operator[](size_type n) { return ( _buffer[n] ); }
			const_reference	operator[](size_type n) const { return ( _buffer[n] ); }
			const_reference	at(size_type n) const
			{
				if ( n > size() )
					throw std::out_of_range;
				return ( _buffer[n] );
			}
			reference		at(size_type n)
			{
				if ( n > size() )
					throw std::out_of_range;
				return ( _buffer[n] );
			}
			reference		front() { return ( _buffer[0] ); }
			const_reference	front() const { return ( _buffer[0] ); }
			reference		back() { return ( _buffer[size() - 1] ); }
			const_reference	back() const { return ( _buffer[size() - 1] ); }

			/* 5 - modifiers */
			void		push_back(const T& x);
			void		pop_back()
			{
				if ( size() > 0 )
				{
					_allocator.destroy( &_buffer[ size() - 1] );
					_size--;
				}
			}

			iterator	insert(iterator position, const T& x)
			{
				difference_type offset = std::distance(begin(), position);
				reserve( size() + 1 );
				pointer last = end(); // check si pas problème lié decalage
				while(last != begin() + offest )
				{
					_allocator.construct(last, *(last - 1));
					_allocator.destroy(last);
					--last;
				}
				_allocator.construct(&_buffer[offset], x)
				_size += 1;
				return ( &_buffer[offset] );
			}

			/* 
				we insert n elements x at position, thus moving every elements to
				the right of position by n and then we insert n times x elements
			*/
			void	insert(iterator position, size_type n, const T& x);
			{
				difference_type offset = std::distance(begin(), position);
				reserve( size() + n );
				pointer last = end(); // check si pas problème lié decalage
				while(last != begin() + offest )
				{
					_allocator.construct(last, *(last - 1));
					_allocator.destroy(last);
					--last;
				}
				for (size_type i = 0; i < n; i++)
					_allocator.construct(&_buffer[offset + i], x)
				_size += n;
			}

			template<class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type)
			{
				difference_type offset = std::distance(begin(), position);
				size_type n = std:distance(first, last);
				reserve( size() + n );
				pointer last_object = end(); // check si pas problème lié decalage
				while(last_object != begin() + offest )
				{
					_allocator.construct(last, *(last - 1));
					_allocator.destroy(last);
					--last;
				}
				for (size_type i = 0; first != last; first++, i++)
					_allocator.construct(&_buffer[offset + i], *first);
				_size += n;
			}

			iterator	erase(iterator position);
			iterator	erase(iterator first, iterator last);
			void		swap(vector<T, Allocator>& x)
			{
				ft::swap( _buffer, x._buffer );
				ft::swap( _size, x._buffer );
				ft::swap( _capacity, x._capacity );
			}

			void		clear()
			{
				if ( _buffer )
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy( &_vector[i] );
				}
				_size = 0;
			}

			/* 
			capacity = size of the currently allocated storage capacity 
			size = number of elements currently present in the vector
			
			*/
			private:
				allocator_type		_allocator; // equivaut a declarer un objet _allocator de class allocator 
				pointer				_buffer; // equivaut a dire T* _buffer
				std::size_type		_size; // longueur du vector instancié
				std::size_type		_capacity; // n element que je peux stocker avant de devoir reallouer

	};

	template<class T, class Allocator>
	bool	operator==(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		if ( x.size() != y.size() )
			return ( false );
		for (size_t i = 0; i < x.size(); i++)
		{
			if ( x[i] != y[i] )
				return ( false );
		}
		return ( true );
	}

	template<class T, class Allocator>
	bool	operator<(const vector<T, Allocator>& x, const vector<T, Allocator>& y)
	{
		return ( ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()) );
	}

	template<class T, class Allocator>
	bool	operator!=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return !( x == y ); }

	template<class T, class Allocator>
	bool	operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return ( y < x ); }

	template<class T, class Allocator>
	bool	operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return !( x < y ); }

	template<class T, class Allocator>
	bool	operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return !( y < x ); }

	template<class T, class Allocator>
	void	swap(vector<T, Allocator>& x, vector<T, Allocator>& y) { x.swap(y); }

}

#endif // __FT_VECTOR_H__
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:13:20 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 21:13:21 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			typedef T																value_type;
			typedef Allocator														allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef  ft::random_access_iterator<value_type>							iterator;
			typedef  ft::random_access_iterator<const value_type>					const_iterator;
			typedef  ft::reverse_iterator<iterator>									reverse_iterator;
			typedef  ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef	std::size_t														size_type;
			typedef	std::ptrdiff_t													difference_type;


		/* 
		* capacity = size of the currently allocated storage capacity 
		* size = number of elements currently present in the vector
		* _buffer = is equivalent to T* _buffer, it is an array that we used to store values
		*/
		private:
			allocator_type		_allocator; 
			pointer				_buffer;
			size_type			_size;
			size_type			_capacity;


		public:

			/* constructors */

			/* default constructor */
			explicit vector(const allocator_type& a = allocator_type()) : _allocator(a), _buffer(NULL), _size(0), _capacity(0) {}
			
			/* fill constructor */
			
			/*
			* in the following case, is the same as writing ::operateur new(n * sizeof(T)) and then returning T* (a pointer to allocator object)
			* instead of creating an object of type T, we first allocated enough space for n object of type T without instanciation (constructor call)
			* then we instanciate n object T and store our value in it
			* the if check is to avoid allocating objects of size 0 (still a leak)
			*/
			explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& a = allocator_type()) : _allocator(a), _buffer(NULL), _size(n), _capacity(n)
			{
				if (n)
					_buffer = _allocator.allocate(n);
				for(size_type i = 0; i < n; i++)
					_allocator.construct(&_buffer[i], value);
			}

			/* range constructor */

			/*
			* on the use of a void ** as second argument for enable if
			* https://stackoverflow.com/questions/29040059/enable-if-to-add-a-function-parameter-that-has-a-default-argument
			*/
			template<class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& a = allocator_type(), 
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
					: _allocator(a), _buffer(NULL), _size(0), _capacity(ft::distance(first, last))
			{
				if (_capacity)
					_buffer = _allocator.allocate(_capacity);
				for(; first != last; first++)
					_allocator.construct(&_buffer[_size++], *first);
			}

			/* copy constructor */
			vector(const vector& x) : _allocator(x._allocator), _size(x._size), _capacity(x._capacity)
			{
				if (_capacity)
					_buffer = _allocator.allocate(_capacity);
				for(size_type i = 0; i < _size; i++)
					_allocator.construct(&_buffer[i], x[i]);
			}

			/* default destructor */
			~vector()
			{
				for(size_type i = 0; i < _size; i++)
					_allocator.destroy(&_buffer[i]);
				if (_buffer)
					_allocator.deallocate(_buffer, _capacity);
			}

			/* iterators */

			/* 
			* each one will return an iterator pointing to a position in the vector 
			* here represented by the allocated space _vector. Using simple pointer arithmetics 
			* we will get an iterator on the beginning or the end
			*/
			iterator			begin() { return ( iterator( _buffer ) ); }
			const_iterator		begin() const { return ( const_iterator( _buffer ) ); }
			iterator			end() { return ( iterator( _buffer + _size ) ); }
			const_iterator		end() const { return ( const_iterator( _buffer + _size ) ); }
			reverse_iterator	rbegin() { return ( reverse_iterator( _buffer + _size ) ); }
			const_reverse_iterator	rbegin() const { return ( const_reverse_iterator( _buffer + _size ) ); }
			reverse_iterator		rend() { return ( reverse_iterator( _buffer ) ); }
			const_reverse_iterator	rend() const { return ( const_reverse_iterator( _buffer ) ); }

			/* reserve more space if capacity is not sufficient */
			void	reserve( size_type n )
			{
				if ( n > max_size() )
					throw std::length_error("vector");
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

			/* insert values */
			iterator	insert(iterator position, const T& x)
			{
				difference_type offset = ft::distance(begin(), position);
				reserve( _size + 1 );
				pointer last = _buffer + _size;
				pointer first = _buffer;
				while ( last != first + offset )
				{
					_allocator.construct(last, *(last - 1));
					_allocator.destroy(last);
					--last;
				}
				_allocator.construct(&_buffer[offset], x);
				_size += 1;
				return ( &_buffer[offset] );
			}

			/* 
			* we insert n elements x at position, thus moving every elements to
			* the right of position by n and then we insert n times x elements
			*/
			void	insert(iterator position, size_type n, const T& x)
			{
				difference_type offset = ft::distance(begin(), position);
				reserve( _size + n );
				pointer last = _buffer + _size;
				pointer first = _buffer;
				while ( last != first + offset )
				{
					_allocator.construct(last + n - 1, *(last - 1));
					_allocator.destroy(last - 1);
					--last;
				}
				for (size_type i = 0; i < n; i++)
					_allocator.construct(&_buffer[offset + i], x);
				_size += n;
			}

			template<class InputIterator>
			void	insert(iterator position, InputIterator first, InputIterator last,
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
			{
				difference_type offset = ft::distance(begin(), position);
				size_type n = ft::distance(first, last);
				reserve( _size + n );
				pointer last_object = _buffer + _size;
				pointer first_object = _buffer;

				while ( last_object != first_object + offset )
				{
					_allocator.construct(last_object + n - 1, *(last_object - 1));
					_allocator.destroy(last_object - 1);
					--last_object;
				}
				for (size_type i = 0; first != last; first++, i++)
					_allocator.construct(&_buffer[offset + i], *first);
				_size += n;
			}

			/* erase values */
			iterator	erase(iterator position)
			{
				difference_type offset = ft::distance(begin(), position);
				for (size_type i = offset; i < _size - 1; i++)
				{
					_allocator.destroy(&_buffer[i]);
					_allocator.construct(&_buffer[i], _buffer[i + 1]);
				}
				_allocator.destroy( &_buffer[ _size - 1] );
				_size--;
				return ( &_buffer[offset] );
			}

			/*
			* destroys all element starting from the beginning,
			* then move all elements int the array from n value deleted to the left
			* then delete duplicates values at the end
			*/
			iterator	erase(iterator first, iterator last)
			{
				difference_type offset = ft::distance(begin(), first);
				difference_type deleted = ft::distance(first, last);
				for (size_type i = offset; i < _size - deleted; i++)
				{
					_allocator.destroy(&_buffer[i]);
					_allocator.construct(&_buffer[i], _buffer[i + deleted]);
				}
				for (size_type i = _size - deleted; i < _size; i++) 
					_allocator.destroy(&_buffer[i]);
				_size -= deleted;
				return ( &_buffer[offset] );
			}

			void		clear()
			{
				if ( _buffer )
				{
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy( &_buffer[i] );
				}
				_size = 0;
			}

			/* assignment operator */
			vector<T, Allocator>& operator=(const vector<T, Allocator>& x)
			{
				if (x != *this)
				{
					clear();
					insert(begin(), x.begin(), x.end());
				}
				return ( *this );
			}

			/* assign functions - need to erase previous content before assigning new value */
			
			/* range assign */
			template<class InputIterator>
			void	assign(InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, void **>::type = nullptr)
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

			/* capacity */
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

			/* element access */
			reference		operator[](size_type n) { return ( _buffer[n] ); }
			const_reference	operator[](size_type n) const { return ( _buffer[n] ); }
			const_reference	at(size_type n) const
			{
				if ( n > size() )
					throw std::out_of_range("vector");
				return ( _buffer[n] );
			}
			reference		at(size_type n)
			{
				if ( n > size() )
					throw std::out_of_range("vector");
				return ( _buffer[n] );
			}
			reference		front() { return ( _buffer[0] ); }
			const_reference	front() const { return ( _buffer[0] ); }
			reference		back() { return ( _buffer[size() - 1] ); }
			const_reference	back() const { return ( _buffer[size() - 1] ); }

			/* modifiers */
			void		push_back(const T& x)
			{
				if ( _capacity > 0 && _size >= _capacity )
				{
					pointer tmp = _allocator.allocate( _capacity * 2 );

					pointer iter = _buffer;
					pointer end = _buffer + _size;
					pointer iter2 = tmp;
					while( iter != end )
					{
						_allocator.construct(iter2, *iter);
						_allocator.destroy(iter);
						iter++;
						iter2++;
					}
					_allocator.deallocate(_buffer, _capacity);
					_buffer = tmp;
					_capacity *= 2;
				}
				else if ( _capacity == 0 )
				{
					_capacity++;
					_buffer = _allocator.allocate( _capacity );
				}
				_allocator.construct(&_buffer[_size], x);
				_size++;
			}

			void		pop_back()
			{
				if ( size() > 0 )
				{
					_allocator.destroy( &_buffer[ size() - 1] );
					_size--;
				}
			}

			void	swap(vector& x)
			{
				ft::swap( _buffer, x._buffer );
				ft::swap( _size, x._size );
				ft::swap( _capacity, x._capacity );
			}

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
	bool	operator<=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return !( y < x ); }

	template<class T, class Allocator>
	bool	operator>(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return ( y < x ); }

	template<class T, class Allocator>
	bool	operator>=(const vector<T, Allocator>& x, const vector<T, Allocator>& y) { return !( x < y ); }

	template<class T, class Allocator>
	void	swap(vector<T, Allocator>& x, vector<T, Allocator>& y) { x.swap(y); }

}

#endif // __FT_VECTOR_H__
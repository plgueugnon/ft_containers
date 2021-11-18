#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include <cstddef>

namespace ft
{

/* https://stackoverflow.com/questions/8054273/how-to-implement-an-stl-style-iterator-and-avoid-common-pitfalls */

template<class Iterator> struct iterator_traits; // general class / fwd declaration
template<class T> struct iterator_traits<T*>; // specialisation class raw / fwd declaration
template<class T> struct iterator_traits<const T*>; // specialisation class const / fwd declaration

// creation d'un template iterator pour tout les types d'iterator
	template<class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	// template generique des iterators
	template<class Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag: public input_iterator_tag {};
	struct bidirectional_iterator_tag: public forward_iterator_tag {};
	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	// template specialization for raw pointer
	template<class T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	// template specialization for const pointer
	template<class T>
	struct iterator_traits<const T*> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/* iterators_traits integral type specialization
	"the effects are undefined in the following cases: 
	for types used as template arguments when instantiating a template component, 
	if the operations on the type do not implement the semantics of 
	the applicable Requirements subclause (20.1.5, 23.1, 24.1, 26.1).
	Source: ISO/IEC 14882:1998(E), page 323
	see also : https://stackoverflow.com/questions/14830112/stditerator-traits-for-integral-types-in-microsoft-standard-library
	We have to specialize interator_traits with each signed integral type as T type is 
	not knowned during compile time which could lead to undefined behavior
	*/
	template<> struct iterator_traits<bool>{};
	template<> struct iterator_traits<char>{};
	template<> struct iterator_traits<char16_t>{};
	template<> struct iterator_traits<char32_t>{};
	template<> struct iterator_traits<wchar_t>{};
	template<> struct iterator_traits<signed char>{};
	template<> struct iterator_traits<short int>{};
	template<> struct iterator_traits<int>{};
	template<> struct iterator_traits<long>{};
	template<> struct iterator_traits<long long>{};
	template<> struct iterator_traits<unsigned char>{};
	template<> struct iterator_traits<unsigned short int>{};
	template<> struct iterator_traits<unsigned int>{};
	template<> struct iterator_traits<unsigned long>{};
	template<> struct iterator_traits<unsigned long long>{};

	// template<class T>
	// class base_iterator {
	// 	/* common to all iterator */
	// 	iterator( const base_iterator& ); // constructeur par copie
	// 	~iterator( void ); // constructeur par défaut
	// 	iterator&	operator=( const iterator& ); // pb avoir assigmnment operator en pour input
	// 	iterator&	operator++( void ); // prefix increment
	// 	iterator	operator++( int ); // postfix increment
	// };

	// template<class T>
	// class input_iterator : public base_iterator, public ft::iterator_traits<input_iterator_tag, T> {
	// 	bool	operator==(input_iterator const &rhs) const;
	// 	bool	operator!=(input_iterator const &rhs) const;
	// 	input_iterator&	operator*( void );
	// 	input_iterator*	operator->( void );
	// };

	// template<class T>
	// class output_iterator : public base_iterator, public ft::iterator_traits<output_iterator_tag, T> {
	// 	output_iterator&	operator*( void );
	// 	output_iterator*	operator->( void );
	// };

	// template<class T>
	// class forward_iterator : public input_iterator, public output_iterator, public ft::iterator_traits<forward_iterator_tag, T> {
	// 	iterator( void ); // constructeur par défaut
	// };

	// template<class T>
	// class bidirectionnal_iterator : public forward_iterator, public ft::iterator_traits<bidirectional_iterator_tag, T> {
	// 	bidirectionnal_iterator&	operator--( void ); // prefix decrement
	// 	bidirectionnal_iterator	operator--( int ); // postfix decrement
	// };

	// template<class T>
	// class random_access_iterator : public bidirectionnal_iterator, public ft::iterator_traits<random_access_iterator_tag, T> {
	// 	bool	operator<( random_access_iterator const &rhs ) const;
	// 	bool	operator>( random_access_iterator const &rhs ) const;
	// 	bool	operator<=( random_access_iterator const &rhs ) const;
	// 	bool	operator>=( random_access_iterator const &rhs ) const;
	// 	random_access_iterator	operator+( random_access_iterator const &rhs );
	// 	random_access_iterator	operator-( random_access_iterator const &rhs );
	// 	// iterator	operator+( const &T ); // a verifier mais potentiellement reponse a It + 1;
	// 	// iterator	operator+( const &T );
	// 	random_access_iterator&	operator+=( random_access_iterator const &rhs );
	// 	random_access_iterator&	operator-=( random_access_iterator const &rhs );
	// 	random_access_iterator&	operator[]( random_access_iterator const &rhs );
	// };

}

#endif // __ITERATOR_H__
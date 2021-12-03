#ifndef __FT_ENABLE_IF_H__
#define __FT_ENABLE_IF_H__


namespace ft
{

	template<bool B, class T = void>
	struct enable_if {};

// au moment de la compilation le compilateur va essayer de constuire la struct
// avec les 2 templates donnes en arg, si cela echoue il renvoie un false au lieu de true
// si il renvoie true => le typedef T sera activé
	template<class T>
	struct enable_if<true, T> {typedef T type; };



	/* https://en.cppreference.com/w/cpp/types/integral_constant
	Here we take part of integral_constant implementation
	*/
	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type; 


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







}

// Potentielle solution https://stackoverflow.com/questions/41534517/issue-with-enable-if-and-multiple-conditions

// if needed use https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time
// and https://www.ibm.com/docs/en/xl-c-and-cpp-aix/12.1.0?topic=SSGH3R_12.1.0/com.ibm.xlcpp121.aix.doc/standlib/header_type_traits.html

#endif // __FT_ENABLE_IF_H__
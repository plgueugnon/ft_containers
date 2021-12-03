#ifndef __FT_TYPE_RESOLUTION_H__
#define __FT_TYPE_RESOLUTION_H__

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
	Here we take part of integral_constant implementation but instead of 
	returning a const value type of the type passed as parameter
	we only use it to do a boolean test of the value passed, while combined with enable_if it
	will allow us to typedef the value passed as parameter in
	*/
	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	/* we create an alias for each boolean test */
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

	/* we recreate the struct is_integral to check if value is integral or not, inheriting from
		integral_constant with the value type true for the value we want to compile with, the
		rest will be false:
		https://en.cppreference.com/w/cpp/types/is_integral
	*/

	/* default template for false type if not integral value. 
	"template <typename>" is the preferred writing to explicitly indicate that the argument is either a class or any other type */
	template <typename T>
	struct is_integral_v  : false_type {};

	/* template specialization which return true if value passed corresponds to value type in specialization */
	template<> struct is_integral_v<bool> : true_type {};
	template<> struct is_integral_v<char> : true_type {};
	template<> struct is_integral_v<char16_t> : true_type {};
	template<> struct is_integral_v<char32_t> : true_type {};
	template<> struct is_integral_v<wchar_t> : true_type {};
	template<> struct is_integral_v<signed char> : true_type {};
	template<> struct is_integral_v<short int> : true_type {};
	template<> struct is_integral_v<int> : true_type {};
	template<> struct is_integral_v<long> : true_type {};
	template<> struct is_integral_v<long long> : true_type {};
	template<> struct is_integral_v<unsigned char> : true_type {};
	template<> struct is_integral_v<unsigned short int> : true_type {};
	template<> struct is_integral_v<unsigned int> : true_type {};
	template<> struct is_integral_v<unsigned long> : true_type {};
	template<> struct is_integral_v<unsigned long long> : true_type {};

	template<> struct is_integral_v<const bool> : true_type {};
	template<> struct is_integral_v<const char> : true_type {};
	template<> struct is_integral_v<const char16_t> : true_type {};
	template<> struct is_integral_v<const char32_t> : true_type {};
	template<> struct is_integral_v<const wchar_t> : true_type {};
	template<> struct is_integral_v<const signed char> : true_type {};
	template<> struct is_integral_v<const short int> : true_type {};
	template<> struct is_integral_v<const int> : true_type {};
	template<> struct is_integral_v<const long> : true_type {};
	template<> struct is_integral_v<const long long> : true_type {};
	template<> struct is_integral_v<const unsigned char> : true_type {};
	template<> struct is_integral_v<const unsigned short int> : true_type {};
	template<> struct is_integral_v<const unsigned int> : true_type {};
	template<> struct is_integral_v<const unsigned long> : true_type {};
	template<> struct is_integral_v<const unsigned long long> : true_type {};

	template <class T>
	struct is_integral : is_integral_v<T> {};


}

// Potentielle solution https://stackoverflow.com/questions/41534517/issue-with-enable-if-and-multiple-conditions

// if needed use https://stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time
// and https://www.ibm.com/docs/en/xl-c-and-cpp-aix/12.1.0?topic=SSGH3R_12.1.0/com.ibm.xlcpp121.aix.doc/standlib/header_type_traits.html


#endif // __FT_TYPE_RESOLUTION_H__
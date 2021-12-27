/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_resolution.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 20:53:11 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 20:53:11 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FT_TYPE_RESOLUTION_H__
#define __FT_TYPE_RESOLUTION_H__

/*
* How all of the following works :
* enable_if takes is_integral as its first argument, and a bogus second argument
* is_integral inherits from is_integral_v and takes as argument the value whose
* type it has to check.
* is_integral_v inherits from specific typedef of integral_constant so that
* when value passed as argument of is_integral is set to to "true_type",
* it will return true to enable_if, otherwise false which will make compilation fail
*/

namespace ft
{

	/*
	* enable if struct is a metaprogrammation struct that will be execute at compile time
	* it will typedef value passed in argument in the wanted type if its first argument is
	* set to true, otherwise typedef will not work and compilator may signal a compile error
	*/
	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {typedef T type; };

	/* 
	* https://en.cppreference.com/w/cpp/types/integral_constant
	* Here we take part of integral_constant implementation but instead of 
	* returning a const value type of the type passed as parameter
	* we only use it to do a boolean test of the value passed, while combined with enable_if it
	* will allow us to typedef the value passed as parameter
	*/
	template<class T, T v>
	struct integral_constant {
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
	};

	/* we create an alias for each boolean test to return a boolean value true or false */
	typedef integral_constant<bool, true> true_type;
	typedef integral_constant<bool, false> false_type; 


	/*
	* iterators_traits integral type specialization
	* "the effects are undefined in the following cases: 
	* for types used as template arguments when instantiating a template component, 
	* if the operations on the type do not implement the semantics of 
	* the applicable Requirements subclause (20.1.5, 23.1, 24.1, 26.1).
	* Source: ISO/IEC 14882:1998(E), page 323
	* see also : https://stackoverflow.com/questions/14830112/stditerator-traits-for-integral-types-in-microsoft-standard-library
	* We have to specialize interator_traits with each signed integral type as T type is 
	* not knowned during compile time which could lead to undefined behavior
	*/

	/* 
	* we recreate the struct is_integral to check if value is integral or not, inheriting from
	* integral_constant with the value type true for the value we want to compile with, the
	* rest will be false:
	* https://en.cppreference.com/w/cpp/types/is_integral
	*/

	/* 
	* default template for false type if not integral value. 
	* "template <typename>" is the preferred writing to explicitly indicate that the argument is either a class or any other type 
	*/
	template <typename T>
	struct is_integral_v : false_type {};

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

#endif // __FT_TYPE_RESOLUTION_H__
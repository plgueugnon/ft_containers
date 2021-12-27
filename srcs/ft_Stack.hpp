/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_Stack.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:22:30 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 21:22:31 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_H__
#define __STACK_H__

#include <deque>
#include <memory>

namespace ft {

	template <class T, class Container = std::deque<T> >
	class stack
	{	
		public:
			typedef Container						container_type;
			typedef typename Container::value_type	value_type;
			typedef typename Container::size_type	size_type;

		protected:
			Container c;
		
		public:
			explicit stack(const Container& ctnr = Container()) : c(ctnr) {}
			bool empty() const { return c.empty(); }
			size_type size() const { return c.size(); }
			value_type& top() { return c.back(); }
			const value_type& top() const { return c.back(); }
			void push(const value_type& x) { c.push_back(x); }
			void pop() { c.pop_back(); }

		bool	operator==( const stack<T, Container>& x ) const { return ( c == x.c ); }
		bool	operator!=( const stack<T, Container>& x ) const { return ( c != x.c ); }
		bool	operator<( const stack<T, Container>& x ) const { return ( c < x.c ); }
		bool	operator<=( const stack<T, Container>& x ) const { return ( c <= x.c ); }
		bool	operator>( const stack<T, Container>& x ) const { return ( c > x.c ); }
		bool	operator>=( const stack<T, Container>& x ) const { return ( c >= x.c ); }
	};

	template <class T, class Container>
		bool operator==(const stack<T, Container>& x, const stack<T, Container>& y) { return ( x.c == y.c ); }
	template <class T, class Container>
		bool operator< (const stack<T, Container>& x, const stack<T, Container>& y) { return ( x.c < y.c ); }
	template <class T, class Container>
		bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y) { return !( x.c == y.c ); }
	template <class T, class Container>
		bool operator> (const stack<T, Container>& x, const stack<T, Container>& y) { return ( x.c > y.c ); }
	template <class T, class Container>
		bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y) { return ( x.c >= y.c ); }
	template <class T, class Container>
		bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y) { return ( x.c <= y.c ); }
}


#endif // __STACK_H__
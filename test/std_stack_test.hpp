/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_stack_test.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:24:56 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 21:24:56 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STD_STACK_TEST_H__
#define __STD_STACK_TEST_H__

#include "test.hpp"

template <typename T>
class Mutantstack : virtual public std::stack<T> {

public:

	/* Canonical */
	Mutantstack( void ) : std::stack<T>() { return ; };
	~Mutantstack( void ) {};
	Mutantstack( Mutantstack const &rhs ) : std::stack<T>( rhs ) {};
	Mutantstack	&operator=( Mutantstack const &rhs ) {
		
		if (this != &rhs)
			this->c = rhs.c;

		return ( *this );
	};

	/* Non canonical */

	/* we reuse the iterator of the container passed as apram */
	typedef typename std::stack<T>::container_type::iterator	iterator;
	typedef typename std::stack<T>::container_type::const_iterator	const_iterator;

	/* container received by std::stack is called c */
	iterator begin( void ) { return ( std::stack<T>::c.begin() ); };
	const_iterator begin( void ) const { return ( std::stack<T>::c.begin() ); };
	iterator end( void ) { return ( std::stack<T>::c.end() ); };
	const_iterator end( void ) const { return ( std::stack<T>::c.end() ); };

};

int std_stack_test( void )
{
	std::string	container = "std_test";
	std::string	inc[20] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
	int i = 0;
	std::vector<std::string> testsname;

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Constructors");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................1 - TESTING CONSTRUCTORS.................................\n";
	ofs << "................................................................................\n";

	std::deque<int> mydeque (3,100);	// deque with 3 elements
	std::vector<int> myvector (2,200);	// vector with 2 elements

	std::stack<int> first;				// empty stack
	std::stack<int> second (mydeque);	// stack initialized to copy of deque

	std::stack<int,std::vector<int> > third;	// empty stack using vector
	std::stack<int,std::vector<int> > fourth (myvector);

	ofs << "size of first: " << first.size() << '\n';
	ofs << "size of second: " << second.size() << '\n';
	ofs << "size of third: " << third.size() << '\n';
	ofs << "size of fourth: " << fourth.size() << '\n';

	std::stack<int> c1;
	c1.push(5);
	ofs << c1.size() << '\n';
 
	std::stack<int> c2(c1);
	ofs << c2.size() << '\n';

	int myints[] = {16,2,77,29};
	std::deque<int> deq (myints, myints + sizeof(myints) / sizeof(int) );
	std::stack<int> c3(deq);
	ofs << c3.size() << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Empty");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................2 - TESTING EMPTY........................................\n";
	ofs << "................................................................................\n";
	
	std::stack<int> mystack;
	int sum (0);

	for (int i=1;i<=10;i++) mystack.push(i);

	while (!mystack.empty())
	{
		 sum += mystack.top();
		 mystack.pop();
	}

	ofs << "total: " << sum << '\n';

	ofs << std::boolalpha;
	std::stack<int> container;
	ofs << "Initially, container.empty(): " << container.empty() << '\n';
	container.push(42);
	ofs << "After adding elements, container.empty(): " << container.empty() << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Size");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................3 - TESTING SIZE.........................................\n";
	ofs << "................................................................................\n";

	std::stack<int> myints;
	ofs << "0. size: " << myints.size() << '\n';

	for (int i=0; i<5; i++) myints.push(i);
	ofs << "1. size: " << myints.size() << '\n';

	myints.pop();
	ofs << "2. size: " << myints.size() << '\n';

	std::stack<int> container;
	ofs << "Initially, container.size(): " << container.size() << '\n';
	for (int i = 0; i < 7; ++i)
		container.push(i);
	ofs << "After adding elements, container.size(): " << container.size() << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Top");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................4 - TESTING TOP..........................................\n";
	ofs << "................................................................................\n";

	std::stack<int> mystack;

	mystack.push(10);
	mystack.push(20);

	mystack.top() -= 5;

	ofs << "mystack.top() is now " << mystack.top() << '\n';

	std::stack<int> s;
	s.push(2);
	s.push(6);
	s.push(51);

	ofs << s.size() << " elements on stack\n";
	ofs << "Top element: " << s.top() << '\n';

	ofs << s.size() << " elements on stack\n";
	s.pop();

	ofs << s.size() << " elements on stack\n";
	ofs << "Top element: " << s.top() << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Push & Pop");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................5 - TESTING PUSH/POP.....................................\n";
	ofs << "................................................................................\n";

	std::stack<int> mystack;

	for (int i=0; i<5; ++i) mystack.push(i);

	ofs << "Popping out elements...";
	while (!mystack.empty())
	{
		ofs << ' ' << mystack.top();
		mystack.pop();
	}
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Mutantstack");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................6 - TESTING MUTANTSTACK..................................\n";
	ofs << "................................................................................\n";

	Mutantstack<int>	mstack;

	mstack.push(5);
	mstack.push(17);

	ofs << "____getting last value____" << std::endl;
	ofs << mstack.top() << std::endl;

	mstack.pop();
	ofs << ".........................." << std::endl;
	ofs << "____getting size value____" << std::endl;
	ofs << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	Mutantstack<int>::iterator it = mstack.begin();
	Mutantstack<int>::iterator ite = mstack.end();

	++it;
	--it;
	ofs << ".........................." << std::endl;
	ofs << "____listing all values____" << std::endl;
	while ( ++it != ite )
		ofs << *it << std::endl;

	ofs << ".........................." << std::endl;

	std::stack<int>	s(mstack);

}
	return ( i );
}

#endif // __STD_STACK_TEST_H__
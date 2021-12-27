/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_map_test.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgueugno <pgueugno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 21:24:52 by pgueugno          #+#    #+#             */
/*   Updated: 2021/12/27 21:24:53 by pgueugno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STD_MAP_TEST_H__
#define __STD_MAP_TEST_H__

#include "test.hpp"

int std_map_test( void )
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

	std::map<char,int> first;

	first['b']=30;
	first['a']=10;
	first['c']=50;
	first['d']=70;

	ofs << "elements in first:" << '\n';
	ofs << "a => " << first.find('a')->second << '\n';
	ofs << "b => " << first.find('b')->second << '\n';
	ofs << "c => " << first.find('c')->second << '\n';
	ofs << "d => " << first.find('d')->second << '\n';

	ofs << "min value = " << first.begin()->second << '\n';

	ofs << "\n..END FIRST..\n";

	std::map<char,int> second (first.begin(),first.end());

	ofs << "elements in second:" << '\n';
	ofs << "a => " << second.find('a')->second << '\n';
	ofs << "b => " << second.find('b')->second << '\n';
	ofs << "c => " << second.find('c')->second << '\n';
	ofs << "d => " << second.find('d')->second << '\n';

	ofs << "\n..END SECOND..\n";

	std::map<char,int> third (second);

	ofs << "elements in third:" << '\n';
	ofs << "a => " << third.find('a')->second << '\n';
	ofs << "b => " << third.find('b')->second << '\n';
	ofs << "c => " << third.find('c')->second << '\n';
	ofs << "d => " << third.find('d')->second << '\n';

	ofs << "\n..END THIRD..\n";

	// (1) Default constructor
	std::map<std::string, int> map1;
	map1["something"] = 69;
	map1["anything"] = 199;
	map1["that thing"] = 50;

	ofs << "elements in map1:" << '\n';
	std::map<std::string, int>::iterator mit = map1.begin();
	std::map<std::string, int>::iterator mite = map1.end();
	for(; mit != mite; ++mit)
		ofs << "map1 key : " << mit->first << " & value " << mit->second << '\n';

	// (2) Range constructor
	std::map<std::string, int> iter(map1.find("anything"), map1.end());
	std::map<std::string, int>::iterator it = iter.begin();
	std::map<std::string, int>::iterator ite = iter.end();
	for(; it != ite; ++it)
		ofs << "iter key : " << it->first << " & value " << it->second << '\n';

	// (3) Copy constructor
	std::map<std::string, int> copied(map1);
	std::map<std::string, int>::iterator cit = copied.begin();
	std::map<std::string, int>::iterator cite = copied.end();
	for(; cit != cite; ++cit)
		ofs << "copied key : " << cit->first << " & value " << cit->second << '\n';
	ofs.close();
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Assignment operator");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................2 - TESTING ASSIGNMENT OPERATOR..........................\n";
	ofs << "................................................................................\n";

	std::map<char,int> first;
	std::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second = first;					// second now contains 3 ints
	first = std::map<char,int>();	// and first is now empty

	ofs << "Size of first: " << first.size() << '\n';
	ofs << "Size of second: " << second.size() << '\n';
	ofs.close();
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Iterators");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................3 - TESTING ITERATORS....................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;

	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;

	// show content:
	for (std::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';

	std::map<char,int> rmymap;

	rmymap['x'] = 100;
	rmymap['y'] = 200;
	rmymap['z'] = 300;

	// show content:
	std::map<char,int>::reverse_iterator rit;
	for (rit = rmymap.rbegin(); rit != rmymap.rend(); ++rit)
		ofs << rit->first << " => " << rit->second << '\n';
	ofs.close();
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Empty");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................4 - TESTING EMPTY........................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	while (!mymap.empty())
	{
		ofs << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
		mymap.erase(mymap.begin());
	}
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Size");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................5 - TESTING SIZE.........................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;

	ofs << "mymap.size() is " << mymap.size() << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Max Size");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................6 - TESTING MAX SIZE.....................................\n";
	ofs << "................................................................................\n";
	
	std::map<int,int> mymap;

	if (mymap.max_size()>1000)
	{
		for (int i = 0; i < 1000; i++) mymap[i] = 0;
		ofs << "The map contains 1000 elements.\n";
	}
	else ofs << "The map could not hold 1000 elements.\n";
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Operator at");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................7 - TESTING OPERATOR AT..................................\n";
	ofs << "................................................................................\n";
	std::map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];

	ofs << "mymap['a'] is " << mymap['a'] << '\n';
	ofs << "mymap['b'] is " << mymap['b'] << '\n';
	ofs << "mymap['c'] is " << mymap['c'] << '\n';
	ofs << "mymap['d'] is " << mymap['d'] << '\n';

	ofs << "mymap now contains " << mymap.size() << " elements.\n";
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Insert");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................8 - TESTING INSERT.......................................\n";
	ofs << "................................................................................\n";
	std::map<char,int> mymap;

	// first insert function version (single parameter):
	mymap.insert ( std::pair<char,int>('a',100) );
	mymap.insert ( std::pair<char,int>('z',200) );

	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = mymap.insert ( std::pair<char,int>('z',500) );
	if (ret.second==false) {
		ofs << "element 'z' already existed";
		ofs << " with a value of " << ret.first->second << '\n';
	}

	// second insert function version (with hint position):
	std::map<char,int>::iterator it = mymap.begin();
	mymap.insert (it, std::pair<char,int>('b',300));	// max efficiency inserting
	mymap.insert (it, std::pair<char,int>('c',400));	// no max efficiency inserting

	// third insert function version (range insertion):
	std::map<char,int> anothermap;
	anothermap.insert(mymap.begin(),mymap.find('c'));

	// showing contents:
	ofs << "mymap contains:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';

	ofs << "anothermap contains:\n";
	for (it=anothermap.begin(); it!=anothermap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Erase");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................9 - TESTING ERASE........................................\n";
	ofs << "................................................................................\n";
	std::map<char,int> mymap;
	std::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	it = mymap.find('b');
	mymap.erase (it);	// erasing by iterator

	mymap.erase ('c');	// erasing by key

	it = mymap.find ('e');
	mymap.erase ( it, mymap.end() );	// erasing by range

	// show content:
	for (it = mymap.begin(); it != mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Swap");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................10 - TESTING SWAP........................................\n";
	ofs << "................................................................................\n";
	std::map<char,int> foo,bar;

	foo['x']=100;
	foo['y']=200;

	bar['a']=11;
	bar['b']=22;
	bar['c']=33;

	foo.swap(bar);

	ofs << "foo contains:\n";
	for (std::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';

	ofs << "bar contains:\n";
	for (std::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Clear");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................11 - TESTING CLEAR.......................................\n";
	ofs << "................................................................................\n";
	std::map<char,int> mymap;

	mymap['x']=100;
	mymap['y']=200;
	mymap['z']=300;

	ofs << "mymap contains:\n";
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';

	mymap.clear();
	mymap['a']=1101;
	mymap['b']=2202;

	ofs << "mymap contains:\n";
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Key_comp");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................12 - TESTING KEY_COMP....................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;

	std::map<char,int>::key_compare mycomp = mymap.key_comp();

	mymap['a']=100;
	mymap['b']=200;
	mymap['c']=300;

	ofs << "mymap contains:\n";

	char highest = mymap.rbegin()->first;		 // key value of last element

	std::map<char,int>::iterator it = mymap.begin();
	do {
		ofs << it->first << " => " << it->second << '\n';
	} while ( mycomp((*it++).first, highest) );

	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Value_comp");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................13 - TESTING VALUE_COMP..................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;

	mymap['x']=1001;
	mymap['y']=2002;
	mymap['z']=3003;

	ofs << "mymap contains:\n";

	std::pair<char,int> highest = *mymap.rbegin();	// last element

	std::map<char,int>::iterator it = mymap.begin();
	do {
		ofs << it->first << " => " << it->second << '\n';
	} while ( mymap.value_comp()(*it++, highest) );
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Find");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................14 - TESTING FIND........................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;
	std::map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
		mymap.erase (it);

	// print content:
	ofs << "elements in mymap:" << '\n';
	ofs << "a => " << mymap.find('a')->second << '\n';
	ofs << "c => " << mymap.find('c')->second << '\n';
	ofs << "d => " << mymap.find('d')->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Count");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................15 - TESTING COUNT.......................................\n";
	ofs << "................................................................................\n";
	std::map<char,int> mymap;
	char c;

	mymap ['a']=101;
	mymap ['c']=202;
	mymap ['f']=303;

	for (c='a'; c<'h'; c++)
	{
		ofs << c;
		if (mymap.count(c)>0)
			ofs << " is an element of mymap.\n";
		else 
			ofs << " is not an element of mymap.\n";
	}
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Lower/Upper bound");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................16 - TESTING LOWER/UPPER_BOUND...........................\n";
	ofs << "................................................................................\n";
	std::map<char,int> mymap;
	std::map<char,int>::iterator itlow,itup;

	mymap['a']=20;
	mymap['b']=40;
	mymap['c']=60;
	mymap['d']=80;
	mymap['e']=100;

	itlow=mymap.lower_bound ('b');	// itlow points to b
	itup=mymap.upper_bound ('d');	 // itup points to e (not d!)

	mymap.erase(itlow,itup);	// erases [itlow,itup)

	// print content:
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		ofs << it->first << " => " << it->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Equal range");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................17 - TESTING EQUAL_RANGE.................................\n";
	ofs << "................................................................................\n";

	std::map<char,int> mymap;

	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;

	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> ret;
	ret = mymap.equal_range('b');

	ofs << "lower bound points to: ";
	ofs << ret.first->first << " => " << ret.first->second << '\n';

	ofs << "upper bound points to: ";
	ofs << ret.second->first << " => " << ret.second->second << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Get_allocator");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................18 - TESTING GET_ALLOCATOR...............................\n";
	ofs << "................................................................................\n";

	int psize;
	std::map<char,int> mymap;
	std::pair<const char,int>* p;

	// allocate an array of 5 elements using mymap's allocator:
	p=mymap.get_allocator().allocate(5);

	// assign some values to array
	psize = sizeof(std::map<char,int>::value_type)*5;

	ofs << "The allocated array has a size of " << psize << " bytes.\n";

	mymap.get_allocator().deallocate(p,5);
}
	return ( i );
}
#endif // __STD_MAP_TEST_H__
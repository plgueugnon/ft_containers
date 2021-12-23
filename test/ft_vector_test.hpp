#ifndef __FT_VECTOR_TEST_H__
#define __FT_VECTOR_TEST_H__

#include "test.hpp"

std::vector<std::string> ft_vector_test( void )
{
	std::string	container = "ft_test";
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

	// constructors used in the same order as described above:
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second(4,100);                       // four ints with value 100
	ft::vector<int> third(second.begin(), second.end());  // iterating through second
	ft::vector<int> fourth(third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int) );

	ofs << "The contents of fifth are:";
	for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
		ofs << ' ' << *it;
	ofs << '\n';
}


{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Assignment operator");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................2 - TESTING OPERATOR=....................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> foo(3,0);
	ft::vector<int> bar(5,0);

	bar = foo;
	foo = ft::vector<int>();

	ofs << "Size of foo: " << int(foo.size()) << '\n';
	ofs << "Size of bar: " << int(bar.size()) << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Iterators");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................3 - TESTING ITERATORS....................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;
	for (int i = 1; i <= 5; i++) myvector.push_back(i);

	ofs << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		ofs << ' ' << *it;
	ofs << '\n';

	ft::vector<int> myrevector(5);  // 5 default-constructed ints

	int i = 0;

	ft::vector<int>::reverse_iterator rit = myrevector.rbegin();
	for (; rit != myrevector.rend(); ++rit)
		*rit = ++i;

	ofs << "myrevector contains:";
	for (ft::vector<int>::iterator it = myrevector.begin(); it != myrevector.end(); ++it)
		ofs << ' ' << *it;
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Size & capacity");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................4 - TESTING SIZE & CAPACITY..............................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myints;
	ofs << "0. size: " << myints.size() << '\n';

	for (int i = 0; i < 10; i++) myints.push_back(i);
		ofs << "1. size: " << myints.size() << '\n';

	myints.insert(myints.end(),10,100);
	ofs << "2. size: " << myints.size() << '\n';

	myints.pop_back();
	ofs << "3. size: " << myints.size() << '\n';

	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i = 0; i < 100; i++) myvector.push_back(i);

	ofs << "size: " << myvector.size() << "\n";
	ofs << "capacity: " << myvector.capacity() << "\n";
	ofs << "max_size: " << myvector.max_size() << "\n";
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Resize");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................5 - TESTING RESIZE.......................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;

	// set some initial content:
	for (int i = 1; i < 10; i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	ofs << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		ofs << ' ' << myvector[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Reserve");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................6 - TESTING RESERVE......................................\n";
	ofs << "................................................................................\n";

	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	ofs << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz!=foo.capacity())
		{
		sz = foo.capacity();
		ofs << "capacity changed: " << sz << '\n';
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	ofs << "making bar grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		bar.push_back(i);
		if (sz!=bar.capacity())
		{
			sz = bar.capacity();
			ofs << "capacity changed: " << sz << '\n';
		}
	}
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Operator at");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................7 - TESTING OPERATOR[]...................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector(10);   // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i = 0; i < sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i = 0; i < sz/2; i++)
	{
		int temp;
		temp = myvector[sz -1 -i];
		myvector[sz -1 -i]=myvector[i];
		myvector[i]=temp;
	}

	ofs << "myvector contains:";
	for (unsigned i = 0; i < sz; i++)
		ofs << ' ' << myvector[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("At");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................8 - TESTING AT...........................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector(10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i = 0; i < myvector.size(); i++)
		myvector.at(i) = i;

	ofs << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		ofs << ' ' << myvector.at(i);
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Front & back");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................9 - TESTING FRONT & BACK.................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);

	// now front equals 78, and back 16

	myvector.front() -= myvector.back();

	ofs << "myvector.front() is now " << myvector.front() << '\n';

	ft::vector<int> myvector2;

	myvector2.push_back(10);

	while (myvector2.back() != 0)
	{
		myvector2.push_back( myvector2.back() -1 );
	}

	ofs << "myvector contains:";
	for (unsigned i = 0; i < myvector2.size() ; i++)
	ofs << ' ' << myvector2[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Assign");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................10 - TESTING ASSIGN.......................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	first.assign(7,100);             // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign( it, first.end() - 1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign( myints, myints + 3);   // assigning from array.

	ofs << "Size of first: " << int (first.size()) << '\n';
	ofs << "Size of second: " << int (second.size()) << '\n';
	ofs << "Size of third: " << int (third.size()) << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Push & Pop back");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................11 - TESTING PUSH/POP_BACK................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;
	int sum(0);
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}

	ofs << "The elements of myvector add up to " << sum << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Insert");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................12 - TESTING INSERT.......................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector(3,100);
	ft::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert( it, 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector(2,400);
	myvector.insert( it + 2, anothervector.begin(), anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	ofs << "myvector contains:";
	for (it = myvector.begin(); it < myvector.end(); it++)
		ofs << ' ' << *it;
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Erase");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................13 - TESTING ERASE........................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i = 1; i <= 10; i++) myvector.push_back(i);

	// erase the 6th element
	myvector.erase (myvector.begin() + 5);

	// erase the first 3 elements:
	myvector.erase (myvector.begin(),myvector.begin() + 3);

	ofs << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); ++i)
		ofs << ' ' << myvector[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Swap");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................14 - TESTING SWAP.........................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> foo(3,100);   // three ints with a value of 100
	ft::vector<int> bar(5,200);   // five ints with a value of 200

	foo.swap(bar);

	ofs << "foo contains:";
	for (unsigned i = 0; i < foo.size(); i++)
		ofs << ' ' << foo[i];
	ofs << '\n';

	ofs << "bar contains:";
	for (unsigned i = 0; i < bar.size(); i++)
		ofs << ' ' << bar[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Clear");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................15 - TESTING CLEAR........................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;
	myvector.push_back(100);
	myvector.push_back(200);
	myvector.push_back(300);

	ofs << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		ofs << ' ' << myvector[i];
	ofs << '\n';

	myvector.clear();
	myvector.push_back(1101);
	myvector.push_back(2202);

	ofs << "myvector contains:";
	for (unsigned i = 0; i < myvector.size(); i++)
		ofs << ' ' << myvector[i];
	ofs << '\n';
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Get_allocator");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................16 - TESTING GET_ALLOCATOR................................\n";
	ofs << "................................................................................\n";

	ft::vector<int> myvector;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i = 0; i < 5; i++) myvector.get_allocator().construct(&p[i],i);

	ofs << "The allocated array contains:";
	for (i = 0; i < 5; i++) ofs << ' ' << p[i];
		ofs << '\n';

	// destroy and deallocate:
	for (i = 0; i < 5; i++) myvector.get_allocator().destroy(&p[i]);
	myvector.get_allocator().deallocate(p,5);
}

{
	std::string	filename = container + "_" + inc[i++] + ".log";
	testsname.push_back("Relational operators");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << "......................17 - TESTING RELATIONAL OPERATORS.........................\n";
	ofs << "................................................................................\n";

	ft::vector<int> foo(3,100);   // three ints with a value of 100
	ft::vector<int> bar(2,200);   // two ints with a value of 200

	if (foo == bar) ofs << "foo and bar are equal\n";
	if (foo != bar) ofs << "foo and bar are not equal\n";
	if (foo < bar) ofs << "foo is less than bar\n";
	if (foo > bar) ofs << "foo is greater than bar\n";
	if (foo <= bar) ofs << "foo is less than or equal to bar\n";
	if (foo >= bar) ofs << "foo is greater than or equal to bar\n";
}
	return ( testsname );
}
#endif // __FT_VECTOR_TEST_H__
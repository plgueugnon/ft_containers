#include <algorithm>
#include "ft_Map.hpp"
#include <map>
#include <iostream>
#include <string>
#include <iterator>

#include <list>

//#include "./containers_test/srcs/map/common.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};


// #define T1 int
// #define T2 int
// typedef _pair<const T1, T2> T3;

// template<typename Map>
// void print_map(Map& m)
// {
//		std::cout << '{';
//		for(auto& p: m)
//				 std::cout << p.first << ':' << p.second << ' ';
//		std::cout << "}\n";
// }

// template <typename T_MAP>
// void	printSize(T_MAP const &mp, bool print_content = 1)
// {
// 	std::cout << "size: " << mp.size() << std::endl;
// 	std::cout << "max_size: " << mp.max_size() << std::endl;
// 	if (print_content)
// 	{
// 		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
// 		std::cout << std::endl << "Content is:" << std::endl;
// 		for (; it != ite; ++it)
// 			std::cout << "- " << printPair(it, false) << std::endl;
// 	}
// 	std::cout << "###############################################" << std::endl;
// }


int main()
{
	std::cout << "................................................................................\n";
	std::cout << ".......................1 - TESTING CONSTRUCTORS.................................\n";
	std::cout << "................................................................................\n";

{
	// std::map<char,int> first;

	// std::cout << "alim first\n";

	// first['b']=30;
	// first['a']=10;

	// first['c']=50;
	// first['d']=70;

	// std::cout << "elements in first:" << '\n';
	// std::cout << "a => " << first.find('a')->second << '\n';
	// std::cout << "b => " << first.find('b')->second << '\n';
	// std::cout << "c => " << first.find('c')->second << '\n';
	// std::cout << "d => " << first.find('d')->second << '\n';
	// // std::cout << "z => " << first.find('z')->second << '\n'; // map envoie valeur au pif

	// std::cout << "min value = " << first.begin()->second << '\n';
	// std::cout << "max value = " <<first.end()->second << '\n';

	// std::cout << "\n..END FIRST..\n";

	// std::map<char,int> second (first.begin(),first.end());

	// std::cout << "elements in second:" << '\n';
	// std::cout << "a => " << second.find('a')->second << '\n';
	// std::cout << "b => " << second.find('b')->second << '\n';
	// std::cout << "c => " << second.find('c')->second << '\n';
	// std::cout << "d => " << second.find('d')->second << '\n';

	// std::cout << "\n..END SECOND..\n";

	// std::map<char,int> third (second);

	// std::cout << "elements in third:" << '\n';
	// std::cout << "a => " << third.find('a')->second << '\n';
	// std::cout << "b => " << third.find('b')->second << '\n';
	// std::cout << "c => " << third.find('c')->second << '\n';
	// std::cout << "d => " << third.find('d')->second << '\n';

	// std::cout << "\n..END THIRD..\n";

	// std::map<char,int,classcomp> fourth;					// class as Compare

	// bool(*fn_pt)(char,char) = fncomp;
	// std::map<char,int,bool(*)(char,char)> fifth (fn_pt);	// function pointer as Compare
	// // (1) Default constructor
	// std::map<std::string, int> map1;
	// map1["something"] = 69;
	// map1["anything"] = 199;
	// map1["that thing"] = 50;
	// //  std::cout << "map1 = "; print_map(map1);
 
	// std::cout << "elements in map1:" << '\n';
	// std::cout << "something => " << map1.find('something')->second << '\n';
	// std::cout << "anything => " << map1.find('anything')->second << '\n';
	// std::cout << "that thing => " << map1.find('that thing')->second << '\n';

 	// std::cout << "max value = " << map1.end()->first << '\n';
	// // (2) Range constructor
	// ft::map<std::string, int> iter(map1.find("anything"), map1.end());
	// std::cout << "\niter = "; //print_map(iter);
 
	// // (3) Copy constructor
	// std::map<std::string, int> copied(map1);
	// std::cout << "\ncopied = "; //print_map(copied);


}

{
	ft::map<char,int> first;

	first['b']=30;
	first['a']=10; // si ordre des clés pas ordonnés => crash lors range copy car pas rééquilibrage
	first['c']=50;
	first['d']=70;

	std::cout << "elements in first:" << '\n';
	std::cout << "a => " << first.find('a')->second << '\n';
	std::cout << "b => " << first.find('b')->second << '\n';
	std::cout << "c => " << first.find('c')->second << '\n';
	std::cout << "d => " << first.find('d')->second << '\n';
	// std::cout << "z => " << first.find('z')->second << '\n'; // map envoie valeur au pif

	std::cout << "min value = " << first.begin()->second << '\n';
	// std::cout << "max value = " << first.end()->second << '\n';

	std::cout << "\n..END FIRST..\n";

	ft::map<char,int> second (first.begin(),first.end());

	std::cout << "elements in second:" << '\n';
	std::cout << "a => " << second.find('a')->second << '\n';
	std::cout << "b => " << second.find('b')->second << '\n';
	std::cout << "c => " << second.find('c')->second << '\n';
	std::cout << "d => " << second.find('d')->second << '\n';

	std::cout << "\n..END SECOND..\n";

	ft::map<char,int> third (second);

	std::cout << "elements in third:" << '\n';
	std::cout << "a => " << third.find('a')->second << '\n';
	std::cout << "b => " << third.find('b')->second << '\n';
	std::cout << "c => " << third.find('c')->second << '\n';
	std::cout << "d => " << third.find('d')->second << '\n';

	std::cout << "\n..END THIRD..\n";

	ft::map<char,int,classcomp> fourth;					// class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);	// function pointer as Compare

	std::cout << "\n..END FOURTH..\n";

	// (1) Default constructor
	ft::map<std::string, int> map1;
	map1["something"] = 69;
	map1["anything"] = 199;
	map1["that thing"] = 50;
	std::cout << "\nHAHA\n";
//	 std::cout << "map1 = "; print_map(map1);
 
	std::cout << "elements in map1:" << '\n';
	ft::map<std::string, int>::iterator mit = map1.begin();
	ft::map<std::string, int>::iterator mite = map1.end();
	for(; mit != mite; ++mit)
		std::cout << "iter key : " << mit->first << " & value " << mit->second << '\n';
	// std::cout << "something => " << map1.find('something')->second << '\n';
	// std::cout << "anything => " << map1.find('anything')->second << '\n';
	// std::cout << "that thing => " << map1.find('that thing')->second << '\n';

 	// std::cout << "max value = " << map1.end()->first << '\n';
	// (2) Range constructor
	ft::map<std::string, int> iter(map1.find("anything"), map1.end());
	ft::map<std::string, int>::iterator it = iter.begin();
	ft::map<std::string, int>::iterator ite = iter.end();
	std::cout << "\niter = ";
	for(; it != ite; ++it)
		std::cout << "iter key : " << it->first << " & value " << it->second << '\n';
//	 std::cout << "map1 = "; print_map(map1);
 
	// (3) Copy constructor
	ft::map<std::string, int> copied(map1);
	std::cout << "\ncopied = "; //print_map(copied);
//	 std::cout << "map1 = "; print_map(map1);

}

// {
// 	std::list<T3> lst;
// 	unsigned int lst_size = 7;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3(lst_size - i, i));

// 	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
// 	TESTED_NAMESPACE::map<T1, T2>::iterator it = mp.begin(), ite = mp.end();

// 	TESTED_NAMESPACE::map<T1, T2> mp_range(it, --(--ite));
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 5;

// 	it = mp.begin(); ite = --(--mp.end());
// 	TESTED_NAMESPACE::map<T1, T2> mp_copy(mp);
// 	for (int i = 0; it != ite; ++it)
// 		it->second = ++i * 7;

// 	std::cout << "\t-- PART ONE --" << std::endl;
// 	printSize(mp);
// 	printSize(mp_range);
// 	printSize(mp_copy);

// 	mp = mp_copy;
// 	mp_copy = mp_range;
// 	mp_range.clear();

// 	std::cout << "\t-- PART TWO --" << std::endl;
// 	printSize(mp);
// 	printSize(mp_range);
// 	printSize(mp_copy);
// }


	return 0;
}
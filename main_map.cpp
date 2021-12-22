#include <algorithm>
#include "ft_Map.hpp"
#include <map>
#include <iostream>
#include <string>
#include <iterator>
#include <list>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

int ft_map_test()
{
	std::cout << "................................................................................\n";
	std::cout << ".......................1 - TESTING CONSTRUCTORS.................................\n";
	std::cout << "................................................................................\n";

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

	// (2) Range constructor
	ft::map<std::string, int> iter(map1.find("anything"), map1.end());
	ft::map<std::string, int>::iterator it = iter.begin();
	ft::map<std::string, int>::iterator ite = iter.end();
	std::cout << "\niter = ";
	for(; it != ite; ++it)
		std::cout << "iter key : " << it->first << " & value " << it->second << '\n';
 
	// (3) Copy constructor
	ft::map<std::string, int> copied(map1);
	std::cout << "\ncopied = "; //print_map(copied);
//	 std::cout << "map1 = "; print_map(map1);

}
	return 0;
}
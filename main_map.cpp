#include <algorithm>
#include "ft_Map.hpp"
#include <iostream>
#include <string>

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};

int main()
{
	std::cout << "................................................................................\n";
	std::cout << ".......................1 - TESTING CONSTRUCTORS.................................\n";
	std::cout << "................................................................................\n";

{
	ft::map<char,int> first;

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	ft::map<char,int> second (first.begin(),first.end());

	std::cout << "third test\n";

	ft::map<char,int> third (second);

	// ft::map<char,int,classcomp> fourth;					// class as Compare

	// bool(*fn_pt)(char,char) = fncomp;
	// ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);	// function pointer as Compare

}

	return 0;
}
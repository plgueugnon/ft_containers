#include <algorithm>
#include "ft_Map.hpp"
#include <map>
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
	std::map<char,int> first;

	std::cout << "alim first\n";

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	std::map<char,int> second (first.begin(),first.end());

	std::cout << "third test\n";

	std::map<char,int> third (second);

	std::map<char,int,classcomp> fourth;					// class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	std::map<char,int,bool(*)(char,char)> fifth (fn_pt);	// function pointer as Compare

	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << first.find('a')->second << '\n';
	std::cout << "b => " << first.find('b')->second << '\n';
	std::cout << "c => " << first.find('c')->second << '\n';
	std::cout << "d => " << first.find('d')->second << '\n';
	std::cout << "z => " << first.find('z')->second << '\n';

	std::cout << "elements in second:" << '\n';
	std::cout << "a => " << second.find('a')->second << '\n';
	std::cout << "b => " << second.find('b')->second << '\n';
	std::cout << "c => " << second.find('c')->second << '\n';
	std::cout << "d => " << second.find('d')->second << '\n';

}



{
	ft::map<char,int> first;

	std::cout << "alim first\n";

	first['a']=10;
	first['b']=30;
	first['c']=50;
	first['d']=70;

	std::cout << "elements in first:" << '\n';
	std::cout << "a => " << first.find('a')->second << '\n';
	std::cout << "b => " << first.find('b')->second << '\n';
	std::cout << "c => " << first.find('c')->second << '\n';
	std::cout << "d => " << first.find('d')->second << '\n';

	std::cout << "\n..END FIRST..\n";

	ft::map<char,int> second (first.begin(),first.end());

	std::cout << "elements in second:" << '\n';
	std::cout << "a => " << second.find('a')->second << '\n';
	std::cout << "b => " << second.find('b')->second << '\n';
	std::cout << "c => " << second.find('c')->second << '\n';
	std::cout << "d => " << second.find('d')->second << '\n';

	std::cout << "\n..END SECOND..\n";

	ft::map<char,int> third (second);

	ft::map<char,int,classcomp> fourth;					// class as Compare

	bool(*fn_pt)(char,char) = fncomp;
	ft::map<char,int,bool(*)(char,char)> fifth (fn_pt);	// function pointer as Compare


	// std::cout << "z => " << first.find('z')->second << '\n'; // map envoie valeur au pif


}

	return 0;
}
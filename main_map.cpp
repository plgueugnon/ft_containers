#include <algorithm>
#include "ft_Map.hpp"
#include <map>
#include <iostream>
#include <string>
#include <iterator>

#include <list>

#include "./containers_test/srcs/map/common.hpp"

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

#define T1 int
#define T2 std::string
typedef _pair<const T1, T2> T3;

static int iter = 0;

template <typename MAP, typename U>
void	ft_erase(MAP &mp, U param)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param);
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_erase(MAP &mp, U param, V param2)
{
	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	mp.erase(param, param2);
	printSize(mp);
}


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




{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_erase(mp, ++mp.begin());

	std::cout << "check min value = " << mp.begin()->first << '\n';

	ft_erase(mp, mp.begin());
	ft_erase(mp, --mp.end());

	ft_erase(mp, mp.begin(), ++(++(++mp.begin())));
	ft_erase(mp, --(--(--mp.end())), --mp.end());

	mp[10] = "Hello";
	mp[11] = "Hi there";
	printSize(mp);
	ft_erase(mp, --(--(--mp.end())), mp.end());

	mp[12] = "ONE";
	mp[13] = "TWO";
	mp[14] = "THREE";
	mp[15] = "FOUR";
	printSize(mp);
	ft_erase(mp, mp.begin(), mp.end());
}

{
	std::list<T3> lst;
	unsigned int lst_size = 6;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i, std::string((lst_size - i), i + 65)));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	for (int i = 2; i < 4; ++i)
		ft_erase(mp, i);

	ft_erase(mp, mp.begin()->first);
	ft_erase(mp, (--mp.end())->first);

	mp[-1] = "Hello";
	mp[10] = "Hi there";
	mp[10] = "Hi there";
	printSize(mp);

	ft_erase(mp, 0);
	ft_erase(mp, 1);
}

{
	TESTED_NAMESPACE::map<T1, T2> mp;

	mp[42] = "lol";

	mp[50] = "mdr";
	mp[25] = "funny";

	mp[46] = "bunny";
	mp[21] = "fizz";
	mp[30] = "buzz";
	mp[55] = "fuzzy";

	mp[18] = "bee";
	mp[23] = "coconut";
	mp[28] = "diary";
	mp[35] = "fiesta";
	mp[44] = "hello";
	mp[48] = "world";
	mp[53] = "this is a test";
	mp[80] = "hey";

	mp[12] = "no";
	mp[20] = "idea";
	mp[22] = "123";
	mp[24] = "345";
	mp[27] = "27";
	mp[29] = "29";
	mp[33] = "33";
	mp[38] = "38";

	mp[43] = "1";
	mp[45] = "2";
	mp[47] = "3";
	mp[49] = "4";
	mp[51] = "5";
	mp[54] = "6";
	mp[60] = "7";
	mp[90] = "8";

	printSize(mp);

	/* A classic btree should give this:
	 *                                      42
	 *                     /                                            \
	 *                    25                                            50
	 *           /                 \                         /                       \
	 *          21                 30                       46                       55
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /    \    /    \     /   \        /   \       /   \     /    \         /     \
	 *  12   20  22    24  27    29  33    38     43    45    47    49   51    54       60      90
	 *
	 * */

	ft_erase(mp, 25); // right != NULL; left != NULL
	ft_erase(mp, 55); // right != NULL; left != NULL

	/* After deleting 25 and 55, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    24                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      54
	 *      /       \           /      \                /       \             /           \
	 *     18       23        28        35            44         48         53             80
	 *   /   \    /         /    \     /   \        /   \       /   \     /              /     \
	 *  12   20  22        27    29  33    38     43    45    47    49   51             60      90
	 *
	 * */

	ft_erase(mp, 24); // right != NULL; left != NULL
	ft_erase(mp, 54); // right != NULL; left != NULL

	/* After deleting 24 and 54, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          21                 30                       46                      53
	 *      /       \           /      \                /       \             /           \
	 *     18       22        28        35            44         48         51             80
	 *   /   \              /    \     /   \        /   \       /   \                    /     \
	 *  12   20            27    29  33    38     43    45    47    49                  60      90
	 *
	 * */

	ft_erase(mp, 22); // right == NULL; left == NULL
	ft_erase(mp, 51); // right == NULL; left == NULL

	ft_erase(mp, 21); // right == NULL; left != NULL
	ft_erase(mp, 53); // right != NULL; left == NULL

	/* After deleting 22, 51 and then 21, 53, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          20                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     18                 28        35            44         48             60         90
	 *   /                  /    \     /   \        /   \       /   \
	 *  12                 27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 20); // right == NULL; left != NULL

	/* After deleting 20, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    23                                            50
	 *           /                 \                         /                      \
	 *          18                 30                       46                      80
	 *      /                   /      \                /       \                /        \
	 *     12                 28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 23); // right != NULL; left != NULL

	/* After deleting 23, I would get:
	 *                                      42
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /   \        /   \       /   \
	 *                     27    29  33    38     43    45    47    49
	 *
	 * */

	ft_erase(mp, 42); // right != NULL; left != NULL; parent == NULL

	/* After deleting 42, I would get:
	 *                                      38
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        35            44         48             60         90
	 *                      /    \     /            /   \       /   \
	 *                     27    29  33           43    45    47    49
	 *
	 * */

	ft_erase(mp, 38); // right != NULL; left != NULL; parent == NULL

	/* After deleting 38, I would get:
	 *                                      35
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /      \                /       \                /        \
	 *                        28        33            44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 35); // right != NULL; left != NULL; parent == NULL

	/* After deleting 35, I would get:
	 *                                      33
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 30                       46                      80
	 *                          /                       /       \                /        \
	 *                        28                      44         48             60         90
	 *                      /    \                  /   \       /   \
	 *                     27    29               43    45    47    49
	 *
	 * */

	ft_erase(mp, 33); // right != NULL; left != NULL; parent == NULL

	/* After deleting 33, I would get:
	 *                                      30
	 *                     /                                            \
	 *                    18                                            50
	 *           /                 \                         /                      \
	 *          12                 28                       46                      80
	 *                          /      \                /       \                /        \
	 *                        27       29             44         48             60         90
	 *                                              /   \       /   \
	 *                                            43    45    47    49
	 *
	 * */

}

	return 0;
}
#include "test.hpp"

std::pair< std::vector<std::string>,std::vector<std::string> > ft_map_test( void )
{
	std::string	container = "ft_map";
	std::string	inc[20] = {"1", "2", "3", "4", "5", "6", "7", "8", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20"};
	int i = 0;
	std::vector<std::string> filetests;
	std::vector<std::string> testsname;
{
	std::string	filename = container + "_" + inc[i++] + "_.log";
	filetests.push_back(filename);
	testsname.push_back("Constructors");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................1 - TESTING CONSTRUCTORS.................................\n";
	ofs << "................................................................................\n";

	ft::map<char,int> first;

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

	ft::map<char,int> second (first.begin(),first.end());

	ofs << "elements in second:" << '\n';
	ofs << "a => " << second.find('a')->second << '\n';
	ofs << "b => " << second.find('b')->second << '\n';
	ofs << "c => " << second.find('c')->second << '\n';
	ofs << "d => " << second.find('d')->second << '\n';

	ofs << "\n..END SECOND..\n";

	ft::map<char,int> third (second);

	ofs << "elements in third:" << '\n';
	ofs << "a => " << third.find('a')->second << '\n';
	ofs << "b => " << third.find('b')->second << '\n';
	ofs << "c => " << third.find('c')->second << '\n';
	ofs << "d => " << third.find('d')->second << '\n';

	ofs << "\n..END THIRD..\n";

	// (1) Default constructor
	ft::map<std::string, int> map1;
	map1["something"] = 69;
	map1["anything"] = 199;
	map1["that thing"] = 50;

	ofs << "elements in map1:" << '\n';
	ft::map<std::string, int>::iterator mit = map1.begin();
	ft::map<std::string, int>::iterator mite = map1.end();
	for(; mit != mite; ++mit)
		ofs << "map1 key : " << mit->first << " & value " << mit->second << '\n';

	// (2) Range constructor
	ft::map<std::string, int> iter(map1.find("anything"), map1.end());
	ft::map<std::string, int>::iterator it = iter.begin();
	ft::map<std::string, int>::iterator ite = iter.end();
	for(; it != ite; ++it)
		ofs << "iter key : " << it->first << " & value " << it->second << '\n';

	// (3) Copy constructor
	ft::map<std::string, int> copied(map1);
	ft::map<std::string, int>::iterator cit = copied.begin();
	ft::map<std::string, int>::iterator cite = copied.end();
	for(; cit != cite; ++cit)
		ofs << "copied key : " << cit->first << " & value " << cit->second << '\n';
	ofs.close();
}

{
	std::string	filename = container + "_" + inc[i++] + "_.log";
	filetests.push_back(filename);
	testsname.push_back("Assignment operator");
	std::ofstream	ofs(filename.c_str());

	ofs << "................................................................................\n";
	ofs << ".......................2 - TESTING ASSIGNMENT OPERATOR..........................\n";
	ofs << "................................................................................\n";

	ft::map<char,int> first;
	ft::map<char,int> second;

	first['x']=8;
	first['y']=16;
	first['z']=32;

	second = first;					// second now contains 3 ints
	first = ft::map<char,int>();	// and first is now empty

	ofs << "Size of first: " << first.size() << '\n';
	ofs << "Size of second: " << second.size() << '\n';
	ofs.close();
}

{
	std::string	filename = container + "_" + inc[i++] + "_.log";
	filetests.insert(filename);
	testsname.push_back("Iterators");
	std::ofstream	ofs(filename.c_str());

// 	ofs << "................................................................................\n";
// 	ofs << ".......................2 - TESTING Iterators....................................\n";
// 	ofs << "................................................................................\n";

// 	ft::map<char,int> mymap;

// 	mymap['b'] = 100;
// 	mymap['a'] = 200;
// 	mymap['c'] = 300;

// 	// show content:
// 	for (ft::map<char,int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
// 		ofs << it->first << " => " << it->second << '\n';

	// ft::map<char,int> rmymap;

	// rmymap['x'] = 100;
	// rmymap['y'] = 200;
	// rmymap['z'] = 300;

	// // show content:
	// ft::map<char,int>::reverse_iterator rit;
	// for (rit = rmymap.rbegin(); rit != rmymap.rend(); ++rit)
	// 	ofs << rit->first << " => " << rit->second << '\n';
	ofs.close();
}

	std::pair< std::vector<std::string>,std::vector<std::string> > tests(filetests, testsname);
	return ( tests );
}
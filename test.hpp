#ifndef __TEST_H__
#define __TEST_H__

#include <algorithm>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <list>
#include <vector>

#include "ft_Map.hpp"
#include "ft_Vector.hpp"
#include "ft_Stack.hpp"

#include "ft_map_test.hpp"
#include "std_map_test.hpp"

#define BOLDRED		"\033[1m\033[31m"
#define BOLDGREEN	"\033[1m\033[32m"
#define BOLDWHITE	"\033[1m\033[37m"
#define RESET		"\033[0m"

template <typename T1, typename T2>
void	compare_file(T1 filename1, T2 filename2, std::string testname)
{
	std::ifstream	file1(filename1, std::ifstream::in);
	std::ifstream	file2(filename2, std::ifstream::in);
	while ( (!file1.eof()) && (!file2.eof()) )
	{
		std::string line1, line2;
		std::getline(file1, line1);
		std::getline(file2, line2);
		if (line1 != line2)
		{
			std::cout << testname << " : " << "[" << BOLDRED"X"RESET"]" << '\n';
			file1.close();
			file2.close();
			return ;
		}
	}
	std::cout << testname << " : " << "[" << BOLDGREEN"√"RESET"]" << '\n';
	file1.close();
	file2.close();
}


#endif // __TEST_H__
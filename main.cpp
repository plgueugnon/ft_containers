#include "test.hpp"

int	main( void )
{
	std::pair< std::vector<std::string>,std::vector<std::string> > ft_tests;
	std::pair< std::vector<std::string>,std::vector<std::string> > std_tests;
	std::vector<std::string>::iterator ftb;
	std::vector<std::string>::iterator fte;
	std::vector<std::string>::iterator stb;
	std::vector<std::string>::iterator testname;
	ft_tests = ft_map_test();
	std_tests= std_map_test();
	for (ftb = ft_tests.first.begin(), fte = ft_tests.first.end(), stb = std_tests.first.begin(),
		testname = std_tests.second.begin(); ftb != fte; ftb++, stb++, testname++)
		compare_file(*ftb, *stb, *testname);

	return ( 0 );
}
#include "test.hpp"

int	main( void )
{
	/* Suboptimized but will have to do */
	std::string ftfiles[20] = { "ft_test_1.log", "ft_test_2.log", "ft_test_3.log", "ft_test_4.log",
	 "ft_test_5.log", "ft_test_6.log", "ft_test_7.log", "ft_test_8.log", "ft_test_9.log",
	 "ft_test_10.log", "ft_test_11.log", "ft_test_12.log", "ft_test_13.log", "ft_test_14.log", 
	 "ft_test_15.log", "ft_test_16.log", "ft_test_17.log", "ft_test_18.log", "ft_test_19.log" };
	std::string stdfiles[20] = { "std_test_1.log", "std_test_2.log", "std_test_3.log",
	 "std_test_4.log", "std_test_5.log", "std_test_6.log", "std_test_7.log", "std_test_8.log", "std_test_9.log",
	 "std_test_10.log", "std_test_11.log", "std_test_12.log", "std_test_13.log", "std_test_14.log", 
	 "std_test_15.log", "std_test_16.log", "std_test_17.log", "std_test_18.log", "std_test_19.log" };

	std::vector<std::string> ft_tests;
	int limit = 0;
	std::vector<std::string>::iterator ftb;
	std::vector<std::string>::iterator fte;
	std::vector<std::string>::iterator stb;
	ft_tests = ft_map_test();
	limit = std_map_test();
	ftb = ft_tests.begin();
	std::cout << BOLDWHITE"TESTING FT vs STD MAP CONTAINER\n"RESET;
	for (int i = 0; i < limit; i++)
	{
		std::cout << "[" << i + 1 << "]";
		compare_file(ftfiles[i], stdfiles[i], *(ftb++));
	}
	for (int i = 0; i < limit; i++)
		remove_tests_files(ftfiles[i], stdfiles[i]);

	return ( 0 );
}
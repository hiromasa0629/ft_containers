/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/12/20 23:18:31 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "container.hpp"
#include "tests.hpp"
#include "tests.tpp"
#include <iterator>
#include <map>
#include <unistd.h>

template < typename T >
void	myprint(T value)
{
	std::cout << *value;
}

// class tmp {
// 	public:
// 		tmp(void) {std::cout << "constructor" << std::endl;}
// 		tmp(const tmp& a) {(void)a; std::cout << "copy" << std::endl; }
// 		~tmp(void) {std::cout << "destructor" << std::endl;}
// };

int	main(void)
{

	ft::map<char, int> mp1;
	ft::map<char, int> mp2;

	mp1['a'] = 2; mp1['b'] = 3; mp1['c'] = 4; mp1['d'] = 5;
	mp2['a'] = 2; mp2['b'] = 3; mp2['c'] = 4; mp2['d'] = 5;
	mp2['e'] = 6; mp2['f'] = 7; mp2['h'] = 8; mp2['h'] = 9;
	(++(++mp1.begin()))->second = 42;
	std::cout << mp1 << std::endl;
	std::cout << mp2 << std::endl;
	std::cout << "eq: " << (mp1 == mp2) << " | ne: " << (mp1 != mp2) << std::endl;
	std::cout << "lt: " << (mp1 <  mp2) << " | le: " << (mp1 <= mp2) << std::endl;
	// std::cout << "gt: " << (mp1 >  mp2) << " | ge: " << (mp1 >= mp2) << std::endl;



	{		// Vector Tests
		// print_header("Vector");
		// std::vector<int>	lst;
		// pre_test_int(x, y);
		// pre_test_string(x, y);
		// test_constructor(x, y);
		// test_element_access(x, y);
		// test_capacity(x, y);
		// test_iterator(x, y);
		// test_clear(x, y);
		// test_insert(x, y);
		// test_erase(x, y);
		// test_push_back(x, y);
		// test_pop_back(x, y);
		// test_resize(x, y);
		// test_operators_n_lexicographical(x, y);
		// test_reverse_iterator(x, y);
	}

	// {		// Stack Tests
	// 	print_header("Stack");
	// 	ft::stack<int>		x;
	// 	std::stack<int>	y;
	// 	pre_test_stack(x, y);
	// 	test_stack(x, y);
	// }

	// {		// Pair Tests
	// 	print_header("Pair");
	// 	ft::pair<std::string, int>	x("Hello world", 10);
	// 	std::pair<std::string, int>	y("Hello world", 10);
	// 	test_pair(x, y);
	// }

	// {
	// 	print_header("Map");
	// 	ft::map<int, std::string>	x;
	// 	std::map<int, std::string>	y;
	// 	pre_test_map(x, y);
	// 	test_map_constructor(x, y);
	// 	test_map_capacity(x, y);
	// 	test_map_element_access(x, y);
	// 	test_map_lookup(x, y);
	// 	test_map_insert(x, y);
	// 	test_map_erase(x, y);
	// 	test_map_swap(x, y);
	// 	test_map_iterator(x, y);
	// 	test_map_reverse_iterator(x, y);
	// 	test_map_lexicographical(x, y);
	// }
	int	diff = g_total - g_correct;
	std::stringstream	ss;
	if (diff > 0)
		ss << RED << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;
	else
		ss << GREEN << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;;
	std::cout << ss.str() << std::endl;

	// pid_t	pid = getpid();
	// std::cout << pid << std::endl;
	// std::stringstream	sss;

	// std::string	s;
	// std::cin >> s;
	// sss << "leaks " << pid;
	// system(sss.str().c_str());
	// system("leaks main");
	return (0);
}

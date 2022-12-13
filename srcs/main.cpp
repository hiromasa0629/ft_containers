/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/12/14 02:45:38 by hyap             ###   ########.fr       */
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

template < typename T >
void	myprint(T value)
{
	std::cout << *value;
}

int	main(void)
{
	// {		// Vector Tests
	// 	print_header("Vector");
	// 	ft::Vector<int>		x;
	// 	std::vector<int>	y;
	// 	pre_test_int(x, y);
	// 	// pre_test_string(x, y);
	// 	test_element_access(x, y);
	// 	test_capacity(x, y);
	// 	test_iterator(x, y);
	// 	test_clear(x, y);
	// 	test_insert(x, y);
	// 	test_erase(x, y);
	// 	test_push_back(x, y);
	// 	test_pop_back(x, y);
	// 	test_resize(x, y);
	// 	test_operators_n_lexicographical(x, y);
	// 	test_reverse_iterator(x, y);
	// }

	// {		// Stack Tests
	// 	print_header("Stack");
	// 	ft::Stack<int>		x;
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

	{
		print_header("Map");
		ft::Map<int, std::string>	x;
		std::map<int, std::string>	y;

		pre_test_map(x, y);
		test_map_capacity(x, y);
		test_map_lookup(x, y);
		test_map_insert(x, y);
		// x.insert(ft::make_pair(6, std::string("six")));
		// x.print_tree(myprint);
	}

	int	diff = g_total - g_correct;
	std::stringstream	ss;
	if (diff > 0)
		ss << RED << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;
	else
		ss << GREEN << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;;
	std::cout << ss.str() << std::endl;
	return (0);
}

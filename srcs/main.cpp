/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/12/12 11:11:13 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "map.hpp"
#include "stack.hpp"
#include "container.hpp"
#include <iterator>
#include <map>

template < typename T >
void	myprint(T value)
{
	std::cout << value;
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
	// 	int	diff = g_total - g_correct;
	// 	std::stringstream	ss;
	// 	if (diff > 0)
	// 		ss << RED << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;
	// 	else
	// 		ss << GREEN << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;;
	// 	std::cout << ss.str() << std::endl;
	// }

	// {		// Stack Tests
	// 	print_header("Stack");
	// 	ft::Stack<int>		x;
	// 	std::stack<int>	y;
	// 	pre_test_stack(x, y);
	// 	test_stack(x, y);
	// 	int	diff = g_total - g_correct;
	// 	std::stringstream	ss;
	// 	if (diff > 0)
	// 		ss << RED << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;
	// 	else
	// 		ss << GREEN << diff << " Error found " << RESET << DIM << "(" << g_correct << "/" << g_total << ")" << RESET;;
	// 	std::cout << ss.str() << std::endl;
	// }

	// {		// Pair Tests
	// 	ft::pair<std::string, int>	x("Hello world", 10);
	// 	std::pair<std::string, int>	y("Hello world", 10);
	// 	test_pair(x, y);
	// }

	ft::Map<int, std::string>	x;
	std::map<int, std::string>	y;
	ft::pair<int, std::string>	p10(10, std::string("ten"));
	ft::pair<int, std::string>	p5(5, std::string("five"));
	ft::pair<int, std::string>	p15(15, std::string("fifteen"));
	ft::pair<int, std::string>	p7(8, std::string("eight"));
	ft::pair<int, std::string>	p1(1, std::string("one"));
	ft::pair<int, std::string>	p6(6, std::string("six"));
	ft::pair<int, std::string>	p8(7, std::string("seven"));
	ft::pair<ft::Map<int, std::string>::iterator, bool>	it;
	x.insert(p10);
	x.insert(p5);
	x.insert(p15);
	x.insert(p7);
	it = x.insert(p1);
	x.insert(p6);
	x.insert(p8);
	std::cout << it.first->first << std::endl;
	x.print_tree(myprint);

	// std::map<int, std::string>	x;
	// std::map<int, std::string>	y;
	// std::pair<int, std::string>	p10(10, std::string("ten"));
	// std::pair<int, std::string>	p5(5, std::string("five"));
	// std::pair<int, std::string>	p15(15, std::string("fifteen"));
	// std::pair<int, std::string>	p7(8, std::string("eight"));
	// std::pair<int, std::string>	p1(1, std::string("one"));
	// std::pair<int, std::string>	p6(6, std::string("six"));
	// std::pair<int, std::string>	p8(7, std::string("seven"));
	// std::pair<std::map<int, std::string>::iterator, bool>	it;
	// it = x.insert(p10);
	// x.insert(p5);
	// x.insert(p15);
	// x.insert(p7);
	// it = x.insert(p1);
	// x.insert(p6);
	// x.insert(p8);
	// std::cout << it.first->first << std::endl;
	return (0);
}

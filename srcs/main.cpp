/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/11/30 21:01:24 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "colors.hpp"
#include <sstream>
#include "tests.hpp"
#include "tests.tpp"

void	test(std::vector<int> w)
{
	std::cout << w << std::endl;
}

int	main(void)
{
	{
		print_header("Default Constructor");
		ft::Vector<int>		x;
		std::vector<int>	y;
		
		pre_test(x, y);
		// test_element_access(x, y);
		// test_capacity(x, y);
		// test_iterator(x, y);
		// test_clear(x, y);
		// test_insert(x, y);
		// test_erase(x, y);
		// test_push_back(x, y);
		// test_pop_back(x, y);
		// test_resize(x, y);
		// ft::Vector<int> z;
		// z.push_back(8);
		// z.push_back(9);
		// std::cout << "y: " << x << std::endl;
		// std::cout << "z: " << z << std::endl;
		// x.swap(z);
		// std::cout << "y: " << x << std::endl;
		// std::cout << "z: " << z << std::endl;
		// ft::swap(x, z);
		// std::cout << "y: " << x << std::endl;
		// std::cout << "z: " << z << std::endl;
		// test_swap(x, y);
		test_operators_n_lexicographical(x, y);
		
		
		// x.reserve(10);
		// ft::Vector<int> z;
		// z.reserve(10);
		// z = x;
		// std::vector<int> w;
		
		// std::cout << x << std::endl;
		// std::cout << z << std::endl;
		// test(y);
		
	}
	return (0);
}

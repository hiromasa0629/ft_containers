/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/11/30 15:27:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "colors.hpp"
#include <sstream>
#include "tests.hpp"
#include "tests.tpp"

int	main(void)
{
		print_header("Fill constructor");
		print_content("fill constructor: ", "(5, 10)");
		ft::Vector<int>		x(5, 10);
		ft::Vector<int>		w(5, 99);

		std::vector<int>	y(5, 10);
		std::vector<int>	z(5, 99);

		// test_capacity(x, y);
		// test_element_access(x, y);
		// test_iterator(x, y);
		// test_insert(x, y);
		x.insert(x.begin(), w.begin() + 5, w.begin() + 3);
		std::cout << x << std::endl;
		// std::vector<int>::iterator it = y.erase(y.begin() + 1);
		// std::cout << y << std::endl;
		// std::cout << std::distance(it, y.begin());
		// x.reserve(20);
		// x.erase(x.begin() + 1);
		// std::cout << x << std::endl;
		// x.insert(x.end(), 99);
		// std::cout << x << std::endl;
		
		// for (int i = 0; i < 5; i++)
		// 	y.push_back(i);
		// std::vector<int>	a(y);
		// a.insert(a.begin(), y.begin() + 6, y.end());
		// std::cout << a << std::endl;
		// y.insert(y.begin(), std::string("iajdioa"), std::string("dhaidai"));
		// x.insert(x.begin(), std::string("hello"), std::string("lol"));
		
		// std::vector<int>	z(5, 10);
		// z.insert(z.end(), 99);
		// z.insert(z.begin(), 33);
		// z.insert(z.begin(), z.begin() + 5, z.end());
		// std::cout << z << std::endl;
		// x.clear();
		// std::vector<int>	z(10, 20);
		// std::vector<int>::iterator	zit = z.begin();
		// y.assign(y.begin(), y.begin() + 7);
		// y.insert(y.end() + 7, 20);
		// std::cout << y << std::endl;
		// std::cout << y.size() << std::endl;
		// std::cout << y.capacity() << std::endl;


		// print_subcontent_header("insert(end(), 20)", "");
		// {
		// 	x.insert(x.end(), 20);
		// 	y.insert(y.end(), 20);
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("insert(end(), 20)", "", myss.str(), ss.str());
		// }
		// {
		// 	x.insert(x.begin(), 20);
		// 	y.insert(y.begin(), 20);
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("insert(begin(), 20)", "", myss.str(), ss.str());
		// }
		// {
		// 	x.insert(x.begin() + 3, 20);
		// 	y.insert(y.begin() + 3, 20);
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("insert(begin() + 3, 20)", "", myss.str(), ss.str());
		// }
		// {
		// 	x.insert(x.begin(), x.begin() + 3, x.end());
		// 	y.insert(y.begin(), y.begin() + 3, y.end());
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("insert(begin(), begin() + 3, end())", "", myss.str(), ss.str());
		// }
		// {
		// 	x.assign(3, 20);
		// 	y.assign(3, 20);
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("assign(3, 20)", "", myss.str(), ss.str());
		// }
		// {
		// 	x.assign(x.begin(), x.begin() + 1);
		// 	y.assign(y.begin(), y.begin() + 1);
		// 	std::stringstream	myss;
		// 	std::stringstream	ss;
		// 	for (size_t i = 0; i < x.size(); i++)
		// 		myss << x[i] << " ";
		// 	myss << "| " << x.size() << " | " << x.capacity();
		// 	ss << y;
		// 	print_subsubcontent_compare("assign(begin(), begin() + 1)", "", myss.str(), ss.str());
		// }
		// ft::Vector<int>	z(x);
		// std::vector<int> w(y);
		// std::stringstream	myss;
		// std::stringstream	ss;
		// for (size_t i = 0; i < z.size(); i++)
		// 	myss << z[i] << " ";
		// myss << "| " << z.size() << " | " << z.capacity();
		// ss << w;
		// print_subsubcontent_compare("assign(begin(), begin() + 1)", "", myss.str(), ss.str());

		// ft::Vector<int>	z;
		// std::vector<int> w;
		// z = x;
		// w = y;
		// std::stringstream	myss;
		// std::stringstream	ss;
		// for (size_t i = 0; i < z.size(); i++)
		// 	myss << z[i] << " ";
		// myss << "| " << z.size() << " | " << z.capacity();
		// ss << w;
		// print_subsubcontent_compare("assign(begin(), begin() + 1)", "", myss.str(), ss.str());

		// system("leaks main");

	return (0);
}

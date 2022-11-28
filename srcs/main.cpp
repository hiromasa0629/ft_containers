/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/11/28 18:08:53 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"
#include "colors.hpp"
#include <sstream>

void									print_header(const std::string& s) { std::cout << BOLD << RED << HR20 << UNDERLINED << s << RESET_UNDERLINED << HR20 << RESET << std::endl; }
void									print_content_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT << BLUE << lhs << YELLOW << rhs << RESET << std::endl; }
void									print_subcontent_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT2 << CYAN << lhs << YELLOW << rhs << RESET << std::endl; }
template < typename T > void			print_content(const std::string& lhs, T rhs ) { std::cout << ANGRT << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subcontent(const std::string& lhs, T rhs ) { std::cout << ANGRT2 << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subsubcontent(const std::string& lhs, T s) { std::cout << ANGRT3 << DIM << lhs << RESET << s << std::endl;  }
template < typename T > void			print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected ) { print_subcontent_header(header_lhs, header_rhs); std::cout << ANGRT3 << DIM << "My:       " << RESET << my << std::endl; std::cout << ANGRT3 << DIM << "Expected: " << RESET << expected << std::endl;  }
template < typename T > std::ostream&	operator<<(std::ostream& o, const std::vector<T> rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; o << "| " << rhs.size() << " | " << rhs.capacity(); return (o); }
// template < typename T > std::ostream&	operator<<(std::ostream& o, const ft::Vector<T> rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; return (o); }

template < typename T, typename U >
void	test_capacity(T x, U y)
{
	print_content_header("Member Functions: ", "Capacity");
	print_subsubcontent_compare("size()", "", x.size(), y.size());
	print_subsubcontent_compare("max_size()", "", x.max_size(), y.max_size());
	print_subsubcontent_compare("capacity()", "", x.capacity(), y.capacity());
	std::cout << std::endl;
}

template < typename T, typename U >
void	test_element_access(T x, U y)
{
	print_content_header("Member functions: ", "Element access");
	print_subsubcontent_compare("operator[2]", "", x[2], y[2]);
	print_subsubcontent_compare("at(2)", "", x.at(2), y.at(2));
	print_subcontent_header("at(6) ", "Exception");
	try { x.at(6); } catch (const std::out_of_range& e) { print_subsubcontent(MY, e.what()); }
	try { y.at(6); } catch (const std::out_of_range& e) { print_subsubcontent(EXPECTED, e.what()); }
	print_subsubcontent_compare("front()", "", x.front(), y.front());
	print_subsubcontent_compare("back()", "", x.back(), y.back());
	print_subsubcontent_compare("data()", "", x.data(), y.data());
	print_subsubcontent_compare("data() ", "dereference", *(x.data()), *(y.data()));
	std::cout << std::endl;
}

template < typename T, typename U >
void	test_iterator(T x, U y)
{
	ft::Vector<int>::iterator	myit;
	ft::Vector<int>::iterator	endmyit;
	std::vector<int>::iterator	it;
	std::vector<int>::iterator	endit;

	print_content_header("Member functions: ", "Iterators");
	myit = x.begin();
	it = y.begin();
	print_subcontent("it = begin()", "");
	print_subsubcontent_compare("begin()", "", *myit, *it);
	endmyit = x.end();
	endit = y.end();
	print_subsubcontent_compare("it[2]", "", myit[2], it[2]);
	print_subsubcontent_compare("++it", "", *(++myit), *(++it));
	print_subsubcontent_compare("it++", "", *(myit++), *(it++));
	print_subsubcontent_compare("--it", "", *(--myit), *(--it));
	print_subsubcontent_compare("it--", "", *(myit--), *(it--));
	print_subsubcontent_compare("it += 2", "", *(myit += 2), *(it += 2));
	print_subsubcontent_compare("it -= 2", "", *(myit -= 2), *(it -= 2));
	print_subsubcontent_compare("it + 2", "", *(myit = myit + 2), *(it = it + 2));
	print_subsubcontent_compare("it - 2", "", *(myit = myit - 2), *(it = it - 2));
	print_subsubcontent_compare("end() - begin()", "", x.end() - x.begin(), y.end() - y.begin());
	print_subsubcontent_compare("*(begin())", "", *(x.begin()), *(y.begin()));
	print_subsubcontent_compare("end() == begin()", "", x.end() == x.begin(), y.end() == y.begin());
	print_subsubcontent_compare("end() != begin()", "", x.end() != x.begin(), y.end() != y.begin());
	print_subsubcontent_compare("begin() > end()", "", x.begin() > x.end(), y.begin() > y.end());
	print_subsubcontent_compare("begin() < end()", "", x.begin() < x.end(), y.begin() < y.end());
	print_subsubcontent_compare("begin() <= begin()", "", x.begin() <= x.begin(), y.begin() <= y.begin());
	print_subsubcontent_compare("end() >= end()", "", x.end() >= x.end(), y.end() >= y.end());
	std::cout << std::endl;
}

int	main(void)
{
		print_header("Fill constructor");
		print_content("fill constructor: ", "(5, 10)");
		ft::Vector<int>		x(5, 10);
		std::vector<int>	y(5, 10);
		
		// test_capacity(x, y);
		// test_element_access(x, y);
		// test_iterator(x, y);
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
		{
			x.assign(3, 20);
			y.assign(3, 20);
			std::stringstream	myss;
			std::stringstream	ss;
			for (size_t i = 0; i < x.size(); i++)
				myss << x[i] << " ";
			myss << "| " << x.size() << " | " << x.capacity();
			ss << y;
			print_subsubcontent_compare("assign(3, 20)", "", myss.str(), ss.str());
			
		}

	return (0);
}

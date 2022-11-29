/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:26:10 by hyap              #+#    #+#             */
/*   Updated: 2022/11/29 19:32:19 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

void									print_header(const std::string& s) { std::cout << BOLD << RED << HR20 << UNDERLINED << s << RESET_UNDERLINED << HR20 << RESET << std::endl; }
void									print_content_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT << BLUE << lhs << YELLOW << rhs << RESET << std::endl; }
void									print_subcontent_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT2 << CYAN << lhs << YELLOW << rhs << RESET << std::endl; }
template < typename T > void			print_content(const std::string& lhs, T rhs ) { std::cout << ANGRT << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subcontent(const std::string& lhs, T rhs ) { std::cout << ANGRT2 << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subsubcontent(const std::string& lhs, T s) { std::cout << ANGRT3 << DIM << lhs << RESET << s << std::endl;  }
template < typename T > void			print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected ) { print_subcontent_header(header_lhs, header_rhs); std::cout << ANGRT3 << DIM << "My:       " << RESET << my << std::endl; std::cout << ANGRT3 << DIM << "Expected: " << RESET << expected << std::endl;  }
template < typename T > std::ostream&	operator<<(std::ostream& o, const std::vector<T> rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; o << "| " << rhs.size() << " | " << rhs.capacity(); return (o); }
template < typename T > std::ostream&	operator<<(std::ostream& o, const ft::Vector<T> rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; return (o); }

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

template < typename T, typename U >
void	test_insert(T x, U y)
{
	typename T::iterator	myit;
	typename U::iterator	it; 
	
	{
		myit = x.insert(x.end(), 99);
		it = y.insert(y.end(), 99);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | ";
		ss << ft::distance(it, y.begin()) << " | ";
		for (size_t i = 0; i < x.size(); i++)
			myss << x[i] << " ";
		myss << "| " << x.size() << " | " << x.capacity();
		ss << y;
		print_subsubcontent_compare("insert(end(), 99)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.begin(), 33);
		it = y.insert(y.begin(), 33);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | ";
		ss << ft::distance(it, y.begin()) << " | ";
		for (size_t i = 0; i < x.size(); i++)
			myss << x[i] << " ";
		myss << "| " << x.size() << " | " << x.capacity();
		ss << y;
		print_subsubcontent_compare("insert(begin(), 33)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.begin(), 33);
		it = y.insert(y.begin(), 33);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | ";
		ss << ft::distance(it, y.begin()) << " | ";
		for (size_t i = 0; i < x.size(); i++)
			myss << x[i] << " ";
		myss << "| " << x.size() << " | " << x.capacity();
		ss << y;
		print_subsubcontent_compare("insert(begin(), 33)", "", myss.str(), ss.str());
	}
	// {
	// 	myit = x.insert(x.begin(), 33);
	// 	it = y.insert(y.begin(), 33);
	// 	std::stringstream	myss;
	// 	std::stringstream	ss;
	// 	myss << ft::distance(myit, x.begin()) << " | ";
	// 	ss << ft::distance(it, y.begin()) << " | ";
	// 	for (size_t i = 0; i < x.size(); i++)
	// 		myss << x[i] << " ";
	// 	myss << "| " << x.size() << " | " << x.capacity();
	// 	ss << y;
	// 	print_subsubcontent_compare("insert(begin(), 33)", "", myss.str(), ss.str());
	// }
	// {
	// 	myit = x.insert(x.begin() + 3, 11);
	// 	it = y.insert(y.begin() + 3, 11);
	// 	std::stringstream	myss;
	// 	std::stringstream	ss;
	// 	myss << ft::distance(myit, x.begin()) << " | ";
	// 	ss << ft::distance(it, y.begin()) << " | ";
	// 	for (size_t i = 0; i < x.size(); i++)
	// 		myss << x[i] << " ";
	// 	myss << "| " << x.size() << " | " << x.capacity();
	// 	ss << y;
	// 	print_subsubcontent_compare("insert(begin() + 3, 11)", "", myss.str(), ss.str());
	// }
	{
		for (int i = 0; i < 5; i++)
			x.insert(x.end(), i);
		for (int i = 0; i < 5; i++)
			y.insert(y.end(), i);
		myit = x.insert(x.begin(), x.begin() + 7, x.end());
		
		for (int i = 7; y.begin() + i != y.end(); i++)
			std::cout << *(y.begin() + i) << " ";
			
		std::cout << std::endl;
		it = y.insert(y.begin(), y.begin() + 7, y.end());
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | ";
		ss << ft::distance(it, y.begin()) << " | ";
		for (size_t i = 0; i < x.size(); i++)
			myss << x[i] << " ";
		myss << "| " << x.size() << " | " << x.capacity();
		ss << y;
		print_subsubcontent_compare("insert(begin(), begin() + 5, end())", "", myss.str(), ss.str());
	}
}

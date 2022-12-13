/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:26:10 by hyap              #+#    #+#             */
/*   Updated: 2022/12/14 00:41:09 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.hpp"

int	g_correct = 0;
int	g_total = 0;

void									print_header(const std::string& s) { std::cout << BOLD << RED << HR20 << UNDERLINED << s << RESET_UNDERLINED << HR20 << RESET << std::endl; }
void									print_content_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT << BLUE << lhs << YELLOW << rhs << RESET << std::endl; }
void									print_subcontent_header(const std::string& lhs, const std::string& rhs) { 	std::cout << ANGRT2 << CYAN << lhs << YELLOW << rhs << RESET << std::endl; }
template < typename T > void			print_content(const std::string& lhs, T rhs ) { std::cout << ANGRT << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subcontent(const std::string& lhs, T rhs ) { std::cout << ANGRT2 << DIM << lhs << RESET << rhs << std::endl; }
template < typename T > void			print_subsubcontent(const std::string& lhs, T s) { std::cout << ANGRT3 << DIM << lhs << RESET << s << std::endl;  }
template < typename T >
void			print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected )
{
	bool	same = my == expected ? 1 : 0;
	if (same) g_correct++;
	g_total++;
	print_subcontent_header(header_lhs, header_rhs);
	std::cout << ANGRT3 << DIM << "My:       " << RESET << my << " " << (same ? TICK : CROSS) << std::endl;
	std::cout << ANGRT3 << DIM << "Expected: " << RESET << expected << std::endl;
}
template < typename T, typename U > void			print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, U expected ) { print_subcontent_header(header_lhs, header_rhs); std::cout << ANGRT3 << DIM << "My:       " << RESET << my << " " << (my == expected ? TICK : CROSS) << std::endl; std::cout << ANGRT3 << DIM << "Expected: " << RESET << expected << std::endl;  }
template < typename T > std::ostream&				operator<<(std::ostream& o, const std::vector<T>& rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; o << "| " << rhs.size() << " | " << rhs.capacity(); return (o); }
template < typename T > std::ostream&				operator<<(std::ostream& o, const ft::Vector<T>& rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; o << "| " << rhs.size() << " | " << rhs.capacity(); return (o); }
template < typename T > std::ostream&				operator<<(std::ostream& o, std::stack<T> rhs) { while (rhs.empty()) { o << rhs.top() << " "; rhs.pop(); } o << "| " << rhs.size(); return (o); }
template < typename T > std::ostream&				operator<<(std::ostream& o, ft::Stack<T> rhs) { while (rhs.empty()) { o << rhs.top() << " "; rhs.pop(); } o << "| " << rhs.size(); return (o); }

template < typename T, typename U > std::ostream&				operator<<(std::ostream& o, ft::Map<T, U>& rhs)
{
	typename ft::Map<T, U>::iterator it = rhs.begin();

	o << "{";
	for (size_t i = 0; i < rhs.size(); i++, it++)
		o << " {" << it->first << ", " << it->second << (i + 1 == rhs.size() ? "} " : "}, ");
	o << "}";
	o << " | " << rhs.size();
	return (o);
}

template < typename T, typename U > std::ostream&	operator<<(std::ostream& o, std::map<T, U>& rhs)
{
	typename std::map<T, U>::iterator it = rhs.begin();

	o << "{";
	for (size_t i = 0; i < rhs.size(); i++, it++)
		o << " {" << it->first << ", " << it->second << (i + 1 == rhs.size() ? "} " : "}, ");
	o << "}";
	o << " | " << rhs.size();
	return (o);
}

template < typename T, typename U >
void	pre_test_int(T& x, U& y)
{
	print_content_header("Pre test: ", "push_back({0, 1, 2, 3, 4})");
	for (size_t i = 0; i < 5; i++)
		x.push_back(i);
	for (size_t i = 0; i < 5; i++)
		y.push_back(i);
}

template < typename T, typename U >
void	pre_test_string(T& x, U& y)
{
	print_content_header("Pre test: ", "push_back({\"One\", \"Two\", \"Three\"}})");
	x.push_back("One");
	x.push_back("Two");
	x.push_back("Three");
	y.push_back("One");
	y.push_back("Two");
	y.push_back("Three");
}

template < typename T, typename U >
void	test_capacity(T x, U y)
{
	std::stringstream	s;
	s << "Capacity [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member Functions: ", s.str());
	print_subsubcontent_compare("empty()", "", x.empty(), y.empty());
	print_subsubcontent_compare("size()", "", x.size(), y.size());
	print_subsubcontent_compare("max_size()", "", x.max_size(), y.max_size());
	print_subsubcontent_compare("capacity()", "", x.capacity(), y.capacity());
	x.reserve(10);
	y.reserve(10);
	std::stringstream	myss;
	std::stringstream	ss;
	myss << x;
	ss << y;
	print_subsubcontent_compare("reserve(10): ", "Check capacity", myss.str(), ss.str());
	std::cout << std::endl;
}

template < typename T, typename U >
void	test_element_access(T x, U y)
{
	std::stringstream	s;
	s << "Element access [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
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
	ft::Vector<int>::iterator			myit;
	std::vector<int>::iterator			it;
	ft::Vector<int>::const_iterator		cmyit;
	std::vector<int>::const_iterator	cit;

	std::stringstream	s;
	s << "Iterators [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	myit = x.begin();
	it = y.begin();
	print_subcontent("it = begin()", "");
	print_subsubcontent_compare("begin()", "", *myit, *it);
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

	s.str(std::string());
	s << "Modify Iterators [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	{
		myit = x.begin();
		it = y.begin();
		*myit = 99;
		*it = 99;
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("it = begin() ", "*it = 99", myss.str(), ss.str());
	}
	{
		myit = x.begin() + 3;
		it = y.begin() + 3;
		*myit = -3;
		*it = -3;
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("it = begin() + 3 ", "*it = -3", myss.str(), ss.str());
	}
	{
		myit = x.end() - 1;
		it = y.end() - 1;
		*myit = 0;
		*it = 0;
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("it = end() - 1 ", "*it = 0", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_clear(T x, U y)
{
	x.clear();
	y.clear();
	std::stringstream	myss;
	std::stringstream	ss;
	myss << x;
	ss << y;
	print_subsubcontent_compare("clear() ", "", myss.str(), ss.str());
}

template < typename T, typename U >
void	test_insert(T x, U y)
{
	std::stringstream	s;
	s << "Modifiers (Insert) [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	T	a(x);
	U	b(y);

	typename T::iterator	myit;
	typename U::iterator	it;
	typename T::iterator	myit2;
	typename U::iterator	it2;

	{
		myit = x.insert(x.end(), 5);
		it = y.insert(y.end(), 5);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | ";
		ss << ft::distance(it, y.begin()) << " | ";
		for (size_t i = 0; i < x.size(); i++)
			myss << x[i] << " ";
		myss << "| " << x.size() << " | " << x.capacity();
		ss << y;
		print_subsubcontent_compare("insert(end(), 5)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.begin(), -1);
		it = y.insert(y.begin(), -1);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("insert(begin(), -1)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.begin() + 1, 2, 0);
		it = y.insert(y.begin() + 1, 2, 0);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("insert(begin(), 2, 0)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.end(), 2, 5);
		it = y.insert(y.end() , 2, 5);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("insert(end(), 2, 5)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.begin(), a.begin(), a.begin() + 4);
		it = y.insert(y.begin(), b.begin(), b.begin() + 4);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("insert(begin(), a.begin(), a.begin() + 4)", "", myss.str(), ss.str());
	}
	{
		myit = x.insert(x.end(), a.begin(), a.begin() + 4);
		it = y.insert(y.end(), b.begin(), b.begin() + 4);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("insert(end(), a.begin(), a.begin() + 4)", "", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_erase(T x, U y)
{
	std::stringstream	s;
	s << "Modifiers (Erase) [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	typename T::iterator	myit;
	typename U::iterator	it;

	{
		myit = x.erase(x.begin());
		it = y.erase(y.begin());
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("erase(begin())", "", myss.str(), ss.str());
	}
	{
		myit = x.erase(x.begin(), x.begin() + 2);
		it = y.erase(y.begin(), y.begin() + 2);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << ft::distance(myit, x.begin()) << " | " << x;
		ss << ft::distance(it, y.begin()) << " | " << y;
		print_subsubcontent_compare("erase(begin(), x.begin() + 2)", "", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_push_back(T x, U y)
{
	std::stringstream	s;
	s << "Modifiers (push_back) [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	{
		x.push_back(5);
		y.push_back(5);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("push_back(5)", "", myss.str(), ss.str());
	}
	{
		x.push_back(6);
		y.push_back(6);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("push_back(6)", "", myss.str(), ss.str());
	}
	{
		T	w(x);
		U	z(y);
		w.clear();
		z.clear();
		w.push_back(0);
		z.push_back(0);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << w;
		ss << z;
		print_subsubcontent_compare("push_back(0) ", "empty vector", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_pop_back(T x, U y)
{
	std::stringstream	s;
	s << "Modifiers (pop_back) [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	{
		x.pop_back();
		y.pop_back();
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("pop_back()", "", myss.str(), ss.str());
	}
	{
		x.pop_back();
		y.pop_back();
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("pop_back()", "", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_resize(T x, U y)
{
	std::stringstream	s;
	s << "Modifiers (resize) [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	{
		x.resize(3, 99);
		y.resize(3, 99);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("resize(3, 99)", "", myss.str(), ss.str());
	}
	{
		x.resize(10, 99);
		y.resize(10, 99);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << x;
		ss << y;
		print_subsubcontent_compare("resize(10, 99)", "", myss.str(), ss.str());
	}
	{
		T	w(x);
		U	z(y);
		w.clear();
		z.clear();
		w.resize(5, 99);
		z.resize(5, 99);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << w;
		ss << z;
		print_subsubcontent_compare("resize(5, 99) ", "empty vector", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_swap(T x, U y)
{
	print_content_header("Member functions: ", "swap");
	T	w;
	w.push_back(8);
	w.push_back(9);
	U	z;
	z.push_back(8);
	z.push_back(9);
	{
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "[" << x << "]  [" << w << "]";
		ss << "[" << y << "]  [" << z << "]";
		print_subsubcontent_compare("swap() ", "Before", myss.str(), ss.str());
	}
	x.swap(w);
	z.swap(y);
	{
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "[" << x << "]  [" << w << "]";
		ss << "[" << y << "]  [" << z << "]";
		print_subsubcontent_compare("swap() ", "After", myss.str(), ss.str());
	}
	print_content_header("Non-Member functions: ", "swap");
	ft::swap(x, w);
	std::swap(y, z);
	{
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "[" << x << "]  [" << w << "]";
		ss << "[" << y << "]  [" << z << "]";
		print_subsubcontent_compare("ft::swap() ", "After", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_operators_n_lexicographical(T x, U y)
{
	T	w;
	w.push_back(0); w.push_back(2); w.push_back(3); w.push_back(4); w.push_back(5);
	U	z;
	z.push_back(0); z.push_back(2); z.push_back(3); z.push_back(4); z.push_back(5);
	{
		std::stringstream	s;
		s << "[" << x << "] < [" << w << "]";
		print_subsubcontent_compare(s.str(), "", x < w, y < z);
	}
	{
		std::stringstream	s;
		s << "[" << x << "] > [" << w << "]";
		print_subsubcontent_compare(s.str(), "", x > w, y > z);
	}
	{

		std::stringstream	s;
		s << "[" << x << "] <= [" << w << "]";
		print_subsubcontent_compare(s.str(), "", x <= w, y <= z);
	}
	{
		std::stringstream	s;
		s << "[" << x << "] >= [" << w << "]";
		print_subsubcontent_compare(s.str(), "", x >= w, y >= z);
	}
	T	a(x);
	U	b(y);
	{

		std::stringstream	s;
		s << "[" << x << "] <= [" << a << "]";
		print_subsubcontent_compare(s.str(), "", x <= a, y <= b);
	}
	{
		std::stringstream	s;
		s << "[" << x << "] >= [" << a << "]";
		print_subsubcontent_compare(s.str(), "", x >= a, y >= b);
	}
}

template < typename T, typename U >
void	test_reverse_iterator(T x, U y)
{
	typename T::reverse_iterator	rmyit(x.rbegin());
	typename T::reverse_iterator	rbmyit(x.rend());
	typename U::reverse_iterator	rit(y.rbegin());
	typename U::reverse_iterator	rbit(y.rend());

	std::stringstream	s;
	s << "Reverse Iterators [";
	for (size_t i = 0; i < x.size(); i++)
		s << x[i] << (i == x.size() - 1 ? "" : ", ");
	s << "]";
	print_content_header("Member functions: ", s.str());
	print_subcontent("it(end())", "");
	print_subsubcontent_compare("*it", "", *rmyit, *rit);
	print_subsubcontent_compare("it[4]", "", rmyit[4], rit[4]);
	print_subsubcontent_compare("++it", "", *(++rmyit), *(++rit));
	print_subsubcontent_compare("it++", "", *(rmyit++), *(rit++));
	print_subsubcontent_compare("--it", "", *(--rmyit), *(--rit));
	print_subsubcontent_compare("it--", "", *(rmyit--), *(rit--));
	print_subsubcontent_compare("it += 2", "", *(rmyit += 2), *(rit += 2));
	print_subsubcontent_compare("it -= 2", "", *(rmyit -= 2), *(rit -= 2));
	print_subsubcontent_compare("it + 2", "", *(rmyit = rmyit + 2), *(rit = rit + 2));
	print_subsubcontent_compare("it - 2", "", *(rmyit = rmyit - 2), *(rit = rit - 2));
	// print_subsubcontent_compare("end() - begin()", "", x.end() - x.begin(), y.end() - y.begin());
	print_subsubcontent_compare("end() == begin()", "", rmyit == rbmyit, rit == rbit);
	print_subsubcontent_compare("end() != begin()", "", rmyit != rbmyit, rit != rbit);
	print_subsubcontent_compare("begin() > end()", "", rbmyit > rmyit, rbit > rit);
	print_subsubcontent_compare("begin() < end()", "", rbmyit < rmyit, rbit < rit);
	print_subsubcontent_compare("begin() <= begin()", "", rbmyit <= rbmyit, rbit <= rbit);
	print_subsubcontent_compare("end() >= end()", "", rmyit >= rmyit, rit >= rit);

	print_subsubcontent_compare("3 + end()", "", *(3 + rmyit), *(3 + rit));
	print_subsubcontent_compare("end() - (begin() - 3)", "", (rmyit - (rbmyit - 3)), (rit - (rbit - 3)));
	// print_subsubcontent_compare("->at(1)", "", rmyit->at(1), rit->at(1));
}

template < typename T, typename U >
void	pre_test_stack(T& x, U& y)
{
	for (int i = 0; i < 5; i++)
		x.push(i);
	for (int i = 0; i < 5; i++)
		y.push(i);
}

template < typename T, typename U >
void	test_stack(T x, U y)
{
	print_content_header("Stack: ", "[0, 1, 2, 3, 4]");
	print_subsubcontent_compare("top()", "", x.top(), y.top());
	print_subsubcontent_compare("empty()", "", x.empty(), y.empty());
	print_subsubcontent_compare("size()", "", x.size(), y.size());
	{
		std::stringstream	myss;
		std::stringstream	ss;
		x.push(5);
		y.push(5);
		myss << x;
		ss << y;
		print_subsubcontent_compare("push(5)", "", myss.str(), ss.str());
	}
	{
		std::stringstream	myss;
		std::stringstream	ss;
		x.push(6);
		y.push(6);
		myss << x;
		ss << y;
		print_subsubcontent_compare("push(6)", "", myss.str(), ss.str());
	}
	{
		std::stringstream	myss;
		std::stringstream	ss;
		x.pop();
		y.pop();
		myss << x;
		ss << y;
		print_subsubcontent_compare("pop()", "", myss.str(), ss.str());
	}
	{
		std::stringstream	myss;
		std::stringstream	ss;
		x.pop();
		y.pop();
		myss << x;
		ss << y;
		print_subsubcontent_compare("pop()", "", myss.str(), ss.str());
	}
}

template < typename T, typename U >
void	test_pair(T x, U y)
{
	T	mypair("Hi there", 20);
	U	pair("Hi there", 20);

	print_content_header("pair<std::string, int>: ", "( Hello world, 10 ) ( Hi there, 20 )");
	print_subsubcontent_compare("( Hello world, 10 ) < ( Hi there, 20 )", "", x < mypair, y < pair);
	print_subsubcontent_compare("( Hello world, 10 ) <= ( Hi there, 20 )", "", x <= mypair, y <= pair);
	print_subsubcontent_compare("( Hello world, 10 ) > ( Hi there, 20 )", "", x > mypair, y > pair);
	print_subsubcontent_compare("( Hello world, 10 ) >= ( Hi there, 20 )", "", x >= mypair, y >= pair);
	print_subsubcontent_compare("( Hello world, 10 ) == ( Hi there, 20 )", "", x == mypair, y == pair);
	print_subsubcontent_compare("( Hello world, 10 ) != ( Hi there, 20 )", "", x != mypair, y != pair);
}

template < typename T, typename U >
void	pre_test_map(T& x, U& y)
{
	print_content_header("Pre test: ", "insert( {1, one}, {3, three}, {5, five}, {7, seven}, {9, nine} )");
	std::string	s[5] = {"one", "three", "five", "seven", "nine"};

	for (int i = 0; i < 5; i++)
		x.insert(ft::make_pair(((i * 2) + 1), s[i]));
	for (int i = 0; i < 5; i++)
		y.insert(std::make_pair(((i * 2) + 1), s[i]));
}

template < typename T, typename U >
void	test_map_capacity(T x, U y)
{
	std::stringstream	s;
	s << "Capacity ";
	s << x;
	print_content_header("Member Functions: ", s.str());
	print_subsubcontent_compare("empty()", "", x.empty(), y.empty());
	print_subsubcontent_compare("size()", "", x.size(), y.size());
	print_subsubcontent_compare("max_size()", "", x.max_size(), y.max_size());
	std::cout << std::endl;
}

template < typename T, typename U >
void	test_map_lookup(T x, U y)
{
	std::stringstream	s;
	s << "Look up ";
	s << x;
	print_content_header("Member Functions: ", s.str());
	print_subsubcontent_compare("count(1)", "", x.count(1), y.count(1));
	print_subsubcontent_compare("count(99)", "Doesnt exist", x.count(99), y.count(99));
	{
		typename T::iterator			myit = x.find(3);
		typename U::iterator			it = y.find(3);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myit->first << ", " << myit->second << "} | " << x;
		ss << "{" << it->first << ", " << it->second << "} | " << y;
		print_subsubcontent_compare("find(3)", "", myss.str(), ss.str());
	}
	{
		ft::pair<typename T::iterator, typename T::iterator>			myitpair = x.equal_range(2);
		std::pair<typename U::iterator, typename U::iterator>			itpair = y.equal_range(2);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myitpair.first->first << ", " << myitpair.first->second << "} {" << myitpair.second->first << ", " << myitpair.second->second << "} | " << x;
		ss << "{" << itpair.first->first << ", " << itpair.second->second << "} {" << itpair.second->first << ", " << itpair.second->second << "} | " << y;
		print_subsubcontent_compare("equal_range(2)", "", myss.str(), ss.str());
	}
	{
		ft::pair<typename T::iterator, typename T::iterator>			myitpair = x.equal_range(3);
		std::pair<typename U::iterator, typename U::iterator>			itpair = y.equal_range(3);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myitpair.first->first << ", " << myitpair.first->second << "} {" << myitpair.second->first << ", " << myitpair.second->second << "} | " << x;
		ss << "{" << itpair.first->first << ", " << itpair.second->second << "} {" << itpair.second->first << ", " << itpair.second->second << "} | " << y;
		print_subsubcontent_compare("equal_range(3)", "", myss.str(), ss.str());
	}
	{
		typename T::iterator			myit = x.lower_bound(8);
		typename U::iterator			it = y.lower_bound(8);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myit->first << ", " << myit->second << "} | " << x;
		ss << "{" << it->first << ", " << it->second << "} | " << y;
		print_subsubcontent_compare("lower_bound(8)", "", myss.str(), ss.str());
	}
	{
		typename T::iterator			myit = x.lower_bound(-2);
		typename U::iterator			it = y.lower_bound(-2);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myit->first << ", " << myit->second << "} | " << x;
		ss << "{" << it->first << ", " << it->second << "} | " << y;
		print_subsubcontent_compare("lower_bound(-2)", "", myss.str(), ss.str());
	}
	{
		typename T::iterator			myit = x.upper_bound(3);
		typename U::iterator			it = y.upper_bound(3);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myit->first << ", " << myit->second << "} | " << x;
		ss << "{" << it->first << ", " << it->second << "} | " << y;
		print_subsubcontent_compare("upper_bound(3)", "", myss.str(), ss.str());
	}
	{
		typename T::iterator			myit = x.upper_bound(20);
		typename U::iterator			it = y.upper_bound(20);
		std::stringstream	myss;
		std::stringstream	ss;
		myss << "{" << myit->first << ", " << myit->second << "} | " << x;
		ss << "{" << it->first << ", " << it->second << "} | " << y;
		print_subsubcontent_compare("upper_bound(20)", "", myss.str(), ss.str());
	}
}

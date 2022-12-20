/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:27:16 by hyap              #+#    #+#             */
/*   Updated: 2022/12/20 23:05:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include "vector.hpp"
# include "container.hpp"
# include "stack.hpp"
# include "map.hpp"
# include <map>
# include <iterator>
# include <utility>
# include <sstream>
# include <iostream>
# include <stack>

int	g_correct = 0;
int	g_total = 0;

void										print_header(const std::string& s);
void										print_content_header(const std::string& lhs, const std::string& rhs);
void										print_subcontent_header(const std::string& lhs, const std::string& rhs);
template < typename T > void				print_content(const std::string& lhs, T rhs );
template < typename T > void				print_subcontent(const std::string& lhs, T rhs );
template < typename T > void				print_subsubcontent(const std::string& lhs, T s);
template < typename T > void				print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected);

template < typename T, typename U > void	pre_test_int(T& x, U& y);
template < typename T, typename U > void	pre_test_string(T& x, U& y);
template < typename T, typename U > void	test_constructor(T x, U y);
template < typename T, typename U > void	test_capacity(T x, U y);
template < typename T, typename U > void	test_element_access(T x, U y);
template < typename T, typename U > void	test_iterator(T x, U y);
template < typename T, typename U > void	test_insert(T x, U y);
template < typename T, typename U > void	test_erase(T x, U y);
template < typename T, typename U > void	test_push_back(T x, U y);
template < typename T, typename U > void	test_pop_back(T x, U y);
template < typename T, typename U > void	test_resize(T x, U y);
template < typename T, typename U > void	test_swap(T x, U y);
template < typename T, typename U > void	test_operators_n_lexicographical(T x, U y);
template < typename T, typename U > void	test_reverse_iterator(T x, U y);

template < typename T, typename U > void	pre_test_stack(T& x, U& y);
template < typename T, typename U > void	test_stack(T x, U y);

template < typename T, typename U > void	test_pair(T x, U y);

template < typename T, typename U > void	pre_test_map(T& x, U& y);
template < typename T, typename U > void	test_map_constructor(T x, U y);
template < typename T, typename U > void	test_map_capacity(T x, U y);
template < typename T, typename U > void	test_map_lookup(T x, U y);
template < typename T, typename U > void	test_map_insert(T x, U y);
template < typename T, typename U > void	test_map_erase(T x, U y);
template < typename T, typename U > void	test_map_swap(T x, U y);
template < typename T, typename U > void	test_map_element_access(T x, U y);
template < typename T, typename U > void	test_map_iterator(T x, U y);
template < typename T, typename U > void	test_map_reverse_iterator(T x, U y);
template < typename T, typename U > void	test_map_lexicographical(T x, U y);


/* ============================ ostream overload Functions ============================ */

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
template < typename T > std::ostream&				operator<<(std::ostream& o, const ft::vector<T>& rhs) { for (size_t i = 0; i < rhs.size(); i++) o << rhs[i] << " "; o << "| " << rhs.size() << " | " << rhs.capacity(); return (o); }
template < typename T > std::ostream&				operator<<(std::ostream& o, std::stack<T> rhs) { size_t size = rhs.size(); while (!rhs.empty()) { o << rhs.top() << " "; rhs.pop(); } o << "| " << size; return (o); }
template < typename T > std::ostream&				operator<<(std::ostream& o, ft::stack<T> rhs) { size_t size = rhs.size(); while (!rhs.empty()) { o << rhs.top() << " "; rhs.pop(); } o << "| " << size; return (o); }
template < typename T, typename U> std::ostream&	operator<<(std::ostream& o, const ft::pair<T, U>* rhs) {o << "{" << rhs->first << ", " << rhs->second << "}"; return (o); }
template < typename T, typename U> std::ostream&	operator<<(std::ostream& o, const ft::pair<T, U>& rhs) {o << "{" << rhs.first << ", " << rhs.second << "}"; return (o); }
template < typename T, typename U> std::ostream&	operator<<(std::ostream& o, const std::pair<T, U>& rhs) {o << "{" << rhs.first << ", " << rhs.second << "}"; return (o); }

template < typename T, typename U > std::ostream&				operator<<(std::ostream& o, const ft::map<T, U>& rhs)
{
	typename ft::map<T, U>::const_iterator it = rhs.begin();

	o << "{";
	for (size_t i = 0; i < rhs.size(); i++, it++)
		o << " {" << it->first << ", " << it->second << (i + 1 == rhs.size() ? "} " : "}, ");
	o << "}";
	o << " | " << rhs.size();
	return (o);
}

template < typename T, typename U > std::ostream&	operator<<(std::ostream& o, const std::map<T, U>& rhs)
{
	typename std::map<T, U>::const_iterator it = rhs.begin();

	o << "{";
	for (size_t i = 0; i < rhs.size(); i++, it++)
		o << " {" << it->first << ", " << it->second << (i + 1 == rhs.size() ? "} " : "}, ");
	o << "}";
	o << " | " << rhs.size();
	return (o);
}

template <typename T> std::ostream&	operator<<(std::ostream& o, const ft::RBTNode<T>& rhs) {o << rhs.content; return (o); }

#endif

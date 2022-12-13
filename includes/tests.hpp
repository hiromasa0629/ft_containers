/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:27:16 by hyap              #+#    #+#             */
/*   Updated: 2022/12/14 02:38:37 by hyap             ###   ########.fr       */
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

void										print_header(const std::string& s);
void										print_content_header(const std::string& lhs, const std::string& rhs);
void										print_subcontent_header(const std::string& lhs, const std::string& rhs);
template < typename T > void				print_content(const std::string& lhs, T rhs );
template < typename T > void				print_subcontent(const std::string& lhs, T rhs );
template < typename T > void				print_subsubcontent(const std::string& lhs, T s);
template < typename T > void				print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected);

template < typename T, typename U > void	pre_test_int(T& x, U& y);
template < typename T, typename U > void	pre_test_string(T& x, U& y);
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
template < typename T, typename U > void	test_map_capacity(T x, U y);
template < typename T, typename U > void	test_map_lookup(T x, U y);
template < typename T, typename U > void	test_map_insert(T x, U y);



#endif

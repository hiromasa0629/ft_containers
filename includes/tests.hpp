/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:27:16 by hyap              #+#    #+#             */
/*   Updated: 2022/11/29 14:07:48 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H
# include "vector.hpp"
# include "container.hpp"
# include <sstream>
# include <iostream>

void										print_header(const std::string& s);
void										print_content_header(const std::string& lhs, const std::string& rhs);
void										print_subcontent_header(const std::string& lhs, const std::string& rhs);
template < typename T > void				print_content(const std::string& lhs, T rhs );
template < typename T > void				print_subcontent(const std::string& lhs, T rhs );
template < typename T > void				print_subsubcontent(const std::string& lhs, T s);
template < typename T > void				print_subsubcontent_compare(const std::string& header_lhs, const std::string& header_rhs , T my, T expected);

template < typename T, typename U > void	test_capacity(T x, U y);
template < typename T, typename U > void	test_element_access(T x, U y);
template < typename T, typename U > void	test_iterator(T x, U y);
template < typename T, typename U > void	test_insert(T x, U y);

#endif
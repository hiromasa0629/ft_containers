/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:26:20 by hyap              #+#    #+#             */
/*   Updated: 2022/11/30 21:28:30 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H
# include <iostream>

namespace ft {

/* ============================ Enable if ============================ */
template< bool B, class T = void >
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T	type;
};

/* ============================ is_integral ============================ */
template< bool is_integral, typename T >
struct is_integral_base
{
	typedef T				type;
	typedef bool			value_type;
	static const value_type	value = is_integral;
};

/* default is_integral */
template< typename T >
struct is_integral : is_integral_base<false, bool> {};

template<> struct is_integral<bool> : is_integral_base<true, bool> {};
template<> struct is_integral<char> : is_integral_base<true, char> {};
template<> struct is_integral<char16_t> : is_integral_base<true, char16_t> {};
template<> struct is_integral<char32_t> : is_integral_base<true, char32_t> {};
template<> struct is_integral<wchar_t> : is_integral_base<true, wchar_t> {};
template<> struct is_integral<short int> : is_integral_base<true, short int> {};
template<> struct is_integral<int> : is_integral_base<true, int> {};
template<> struct is_integral<long> : is_integral_base<true, long> {};
template<> struct is_integral<unsigned char> : is_integral_base<true, unsigned char> {};
template<> struct is_integral<unsigned int> : is_integral_base<true, unsigned int> {};
template<> struct is_integral<unsigned short int> : is_integral_base<true, unsigned short int> {};
template<> struct is_integral<unsigned long> : is_integral_base<true, unsigned long> {};

template < class InputIt1, class InputIt2 >
bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
{
	for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
	{
		if (*first1 < *first2)
            return true;
        if (*first2 < *first1)
            return false;
	}
	return (first1 == last1) && (first2 != last2);
}

}

#endif

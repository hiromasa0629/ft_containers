/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:26:20 by hyap              #+#    #+#             */
/*   Updated: 2022/12/01 20:55:25 by hyap             ###   ########.fr       */
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

template < class T1, class T2 >
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;

	first_type	first;
	second_type	second;

	/* Default constructor */
	pair(void) : first(first_type()), second(second_type());
	/* Copy constructor */
	template < class U, class V > pair(const pair<U, V>& src) : first(src.first), second(src.second) {}
	/* Initialization */
	pair(const first_type& a, const second_type& b) : first(a), second(b) {}
	/* Copy assignment */
	pair&	operator=(const pair& rhs) { first = rhs.first; second = rhs.second; return (*this); }
};

template < class T1, class T2 > bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return (lhs.first == rhs.first && lhs.second == rhs.second); }
template < class T1, class T2 > bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return (!(lhs == rhs)); }
template < class T1, class T2 > bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
{ 
	if (lhs.first < rhs.first) 
		return (true); 
	else if (lhs.first > rhs.first)
		return (false);
	if (lhs.second < lhs.second)
		return (true);
	else if (lhs.second > rhs.second)
		return (false);
	return (false);
}
template < class T1, class T2 > bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return (lhs == rhs || lhs < rhs); }
template < class T1, class T2 > bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return (!(lhs <= rhs)); }
template < class T1, class T2 > bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) { return (!(lhs < rhs)); }


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

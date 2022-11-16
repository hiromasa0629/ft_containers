/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:26:20 by hyap              #+#    #+#             */
/*   Updated: 2022/11/16 19:16:05 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTAINER_H
# define CONTAINER_H
# include <iostream>

namespace ft {
	
template< bool B, class T = void >
struct enable_if {};

template<class T>
struct enable_if<true, T>
{
	typedef T	type;
};

template< typename T >
struct is_integral

}

#endif
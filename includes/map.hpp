/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:25:53 by hyap              #+#    #+#             */
/*   Updated: 2022/12/01 21:00:40 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "container.hpp"
# include <iostream>
# include <map>

template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
class Map
{
	public:
		typedef Key									key_type;
		typedef T									mapped_type;
		typedef std::pair<const Key, T>				value_type;
		typedef typename std::size_t				size_type;
		typedef typename std::ptrdiff_t				difference_type;
		typedef Compare								key_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename allocator_type::pointer	pointer;
		typedef	typename allocator_type::pointer	const_pointer;
}


#endif
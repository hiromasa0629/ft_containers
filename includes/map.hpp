/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:25:53 by hyap              #+#    #+#             */
/*   Updated: 2022/12/09 16:56:19 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "container.hpp"
# include <iostream>
# include <map>
# include "trees.hpp"
# include <functional>

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
class Map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef typename std::size_t						size_type;
		typedef typename std::ptrdiff_t						difference_type;
		typedef Compare										key_compare;
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef	typename allocator_type::pointer			const_pointer;

		class value_compare : std::binary_function<value_type, value_type, bool>
		{
			protected:
				key_compare	comp;

			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				value_compare(key_compare c) : comp(c) { std::cout << "value_compare()" << std::endl; }
				bool	operator()(const value_type& lhs, const value_type& rhs) const { return(comp(lhs.first, rhs.first)); }
		};

		key_compare		key_comp(void) const { return (key_compare()); }
		value_compare	value_comp(void) const { return (value_compare(key_comp())); }

		typedef ft::RBTTree<value_type, value_compare>	RBTTree;

		/* Default Constructor */
		Map(void) : _tree(RBTTree(value_comp())) {}

		void	insert(const value_type& value)
		{
			_tree.rbt_insert(value);
		}

	private:
		RBTTree	_tree;
};

}


#endif

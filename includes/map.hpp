/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:25:53 by hyap              #+#    #+#             */
/*   Updated: 2022/12/13 23:53:23 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "container.hpp"
# include "iterators.hpp"
# include "trees.hpp"

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<Key, T> > >
class Map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<key_type, mapped_type>				value_type;
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
			friend class Map;

			protected:
				key_compare	comp;
				value_compare(key_compare c) : comp(c) { /* std::cout << "value_compare()" << std::endl; */ }

			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				bool	operator()(const value_type& lhs, const value_type& rhs) const { return(comp(lhs.first, rhs.first)); }
		};

		typedef ft::RBTree<key_type, value_type, key_compare, value_compare>	RBTree;
		typedef typename RBTree::node_type										node_type;
		typedef typename RBTree::iterator										iterator;
		typedef typename RBTree::const_iterator									const_iterator;
		typedef ft::reverse_iterator<iterator>									reverse_iterator;
		typedef const ft::reverse_iterator<iterator>							const_reverse_iterator;

		key_compare		key_comp(void) const { return (key_compare()); }
		value_compare	value_comp(void) const { return (value_compare(key_comp())); }

		/* Default Constructor */
		Map(const allocator_type& alloc = allocator_type()) : _tree(RBTree(key_comp(), value_comp())), _alloc(alloc) {}

		ft::pair<iterator, bool>		insert(const value_type& value) { return (_tree.rbt_insert(value)); }
		iterator						insert(iterator pos, const value_type& value) { return (_tree.rbt_insert(pos, value)); }
		// template < class InputIt > void	insert(InputIt first, InputIt last) {}

		iterator					erase(iterator pos) { return (_tree.rbt_erase(pos)); }
		allocator_type				get_allocator(void) const { return (allocator_type()); }
		void						clear(void) { _tree.clear(); }

		iterator					begin(void) { return (iterator(_tree.rbt_findmin())); }
		const_iterator				begin(void) const { return (iterator(_tree.rbt_findmin())); }
		iterator					end(void) { return (iterator(_tree.get_nil())); }
		const_iterator				end(void) const { return (iterator(_tree.get_nil())); }
		reverse_iterator			rbegin(void) { return (reverse_iterator(iterator(_tree.rbt_findmax()))); }
		const_reverse_iterator		crbegin(void) const { return (reverse_iterator(iterator(_tree.rbt_findmax()))); }
		reverse_iterator			rend(void) { return (reverse_iterator(iterator(_tree.rbt_findmin()))); }
		const_reverse_iterator		crend(void) const { return (reverse_iterator(iterator(_tree.rbt_findmin()))); }

		// mapped_type&				operator[](const key_type&)

		/* ============================ Look up functions ============================ */
		size_type									count(const key_type& key) const { return (_tree.rbt_search(key) == _tree.get_nil() ? 0 : 1); }
		iterator									find(const key_type& key) { return (iterator(_tree.rbt_search(key))); }
		const_iterator								find(const key_type& key) const { return (iterator(_tree.rbt_search(key))); }
		iterator									lower_bound(const key_type& key) { return (_tree.rbt_lower_bound(key)); }
		const_iterator								lower_bound(const key_type& key) const { return (_tree.rbt_lower_bound(key)); }
		iterator									upper_bound(const key_type& key) { return (_tree.rbt_upper_bound(key)); }
		const_iterator								upper_bound(const key_type& key) const { return (_tree.rbt_upper_bound(key)); }
		ft::pair<iterator, iterator>				equal_range(const key_type& key) { return (_tree.rbt_equal_range(key)); }
		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const { return (_tree.rbt_equal_range(key)); }

		/* ============================ Capacity functions ============================ */
		size_type					size(void) const { return (_tree.rbt_size()); }
		bool						empty(void) const { return (this->size() == 0); }
		size_type					max_size(void) const { return (_alloc.max_size()); }

		/* ============================ Print tree ============================ */
		void	print_tree(void (*f)(node_type *)) { _tree.rbt_iter(f); }

	private:
		RBTree			_tree;
		allocator_type	_alloc;
};

}


#endif

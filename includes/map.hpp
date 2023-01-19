/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 20:25:53 by hyap              #+#    #+#             */
/*   Updated: 2023/01/18 22:49:34 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# include "container.hpp"
# include "iterators.hpp"
# include "trees.hpp"

namespace ft {

template < class Key, class T, class Compare = std::less<Key>, class Equal = std::equal_to<Key>, class Allocator = std::allocator< ft::pair<Key, T> > >
class map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef ft::pair<const key_type, mapped_type>		value_type;
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
			friend class map;

			protected:
				key_compare	comp;
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				value_compare(key_compare c) : comp(c) { /* std::cout << "value_compare()" << std::endl; */ }
				bool	operator()(const value_type& lhs, const value_type& rhs) const { return(comp(lhs.first, rhs.first)); }
		};

		class key_equal_compare : std::binary_function<value_type, value_type, bool>
		{
			friend class map;

			protected:
				Equal comp;
			public:
				typedef bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				key_equal_compare(void) : comp() {}
				key_equal_compare(const key_equal_compare& src) : comp(src.comp) {}
				key_equal_compare&	operator=(const key_equal_compare& rhs) { comp = rhs.comp; return (*this); }
				bool	operator()(const value_type& lhs, const value_type& rhs) const { return(comp(lhs.first, rhs.first)); }
		};

		typedef ft::RBTree<value_type, key_compare, value_compare, key_equal_compare>	RBTree;
		typedef typename RBTree::node_type						node_type;
		typedef typename RBTree::iterator						iterator;
		typedef typename RBTree::const_iterator					const_iterator;
		typedef ft::reverse_iterator<iterator>					reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		key_compare		key_comp(void) const { return (key_compare()); }
		value_compare	value_comp(void) const { return (value_compare(key_comp())); }

		/* ============================ Constructors and Destructor ============================ */
		map(const allocator_type& alloc = allocator_type()) : _tree(RBTree(key_comp())), _alloc(alloc), _comp(key_compare()) {}
		template < class InputIt >
		map(InputIt first, InputIt last, const key_compare& comp = Compare(), const allocator_type& alloc = allocator_type()) : _tree(RBTree(key_comp())), _alloc(alloc), _comp(comp)
		{
			for (; first != last; first++)
				this->insert(ft::make_pair(first->first, first->second));
		}

		map(const map& src) : _alloc(src.get_allocator()) { *this = src; }
		map&	operator=(const map& rhs) { _tree = rhs.get_tree(); return (*this); }
		~map(void) {}

		ft::pair<iterator, bool>		insert(const value_type& value) { return (_tree.rbt_insert(value)); }
		iterator						insert(iterator pos, const value_type& value) { return (_tree.rbt_insert(pos, value)); }
		template < class InputIt > void	insert(InputIt first, InputIt last) { _tree.rbt_insert(first, last); }

		void						erase(iterator pos) { _tree.rbt_erase(pos); }
		void						erase(iterator first, iterator last) { _tree.rbt_erase(first, last); }
		size_type					erase(const key_type& key) { return (_tree.rbt_erase(value_type(key, mapped_type()))); }
		allocator_type				get_allocator(void) const { return (allocator_type()); }
		void						clear(void) { _tree.rbt_clear(); }

		iterator					begin(void) { return (iterator(_tree.rbt_findmin())); }
		const_iterator				begin(void) const { return (iterator(_tree.rbt_findmin())); }
		iterator					end(void) { return (iterator(_tree.get_nil())); }
		const_iterator				end(void) const { return (iterator(_tree.get_nil())); }
		reverse_iterator			rbegin(void) { return (reverse_iterator(_tree.get_nil())); }
		const_reverse_iterator		crbegin(void) const { return (rbegin()); }
		reverse_iterator			rend(void) { return (reverse_iterator(_tree.rbt_findmin())); }
		const_reverse_iterator		crend(void) const { return (rend()); }

		/* ============================ Element access ============================ */
		mapped_type&		at(const key_type& key)
		{
			node_type*	node;

			node = _tree.rbt_search(value_type(key, mapped_type()));
			if (node->isnil)
				throw std::out_of_range("ft::map::at key not found");
			return (node->content->second);
		}

		const mapped_type&	at(const key_type& key) const
		{
			node_type*	node;

			node = _tree.rbt_search(value_type(key, mapped_type()));
			if (node->isnil)
				throw std::out_of_range("ft::map::at key not found");
			return (node->content->second);
		}

		mapped_type&				operator[](const key_type& key)
		{
			node_type*	node;

			node = _tree.rbt_search(value_type(key, mapped_type()));
			if (!(node->isnil))
				return (node->content->second);
			return ((insert(ft::make_pair(key, mapped_type()))).first->second);
		}

		/* ============================ Look up functions ============================ */
		size_type									count(const key_type& key) const { return (_tree.rbt_search(value_type(key, mapped_type())) == _tree.get_nil() ? 0 : 1); }
		iterator									find(const key_type& key) { return (iterator(_tree.rbt_search(value_type(key, mapped_type())))); }
		const_iterator								find(const key_type& key) const { return (iterator(_tree.rbt_search(value_type(key, mapped_type())))); }
		iterator									lower_bound(const key_type& key) { return (_tree.rbt_lower_bound(value_type(key, mapped_type()))); }
		const_iterator								lower_bound(const key_type& key) const { return (_tree.rbt_lower_bound(value_type(key, mapped_type()))); }
		iterator									upper_bound(const key_type& key) { return (_tree.rbt_upper_bound(value_type(key, mapped_type()))); }
		const_iterator								upper_bound(const key_type& key) const { return (_tree.rbt_upper_bound(value_type(key, mapped_type()))); }
		ft::pair<iterator, iterator>				equal_range(const key_type& key) { return (_tree.rbt_equal_range(value_type(key, mapped_type()))); }
		ft::pair<const_iterator, const_iterator>	equal_range(const key_type& key) const { return (_tree.rbt_equal_range(value_type(key, mapped_type()))); }

		/* ============================ Capacity functions ============================ */
		size_type					size(void) const { return (_tree.rbt_size()); }
		bool						empty(void) const { return (this->size() == 0); }
		size_type					max_size(void) const { return (_alloc.max_size()); }

		void						swap(map& other)
		{
			allocator_type	tmp_alloc;

			tmp_alloc = _alloc;
			_alloc = other._alloc;
			other._alloc = tmp_alloc;
			_tree.rbt_swap(other._tree);
		}

		/* ============================ Print tree ============================ */
		void	print_tree(void (*f)(node_type *)) { _tree.rbt_iter(f); }

		const RBTree&	get_tree(void) const { return (_tree); }

	private:
		RBTree			_tree;
		allocator_type	_alloc;
		key_compare		_comp;
};

template < class Key, class T, class Compare, class Alloc >
bool	operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
{
	typename map<Key, T, Compare, Alloc>::const_iterator lhs_it;
	typename map<Key, T, Compare, Alloc>::const_iterator rhs_it;

	lhs_it = lhs.begin();
	rhs_it = rhs.begin();
	if (lhs.size() != rhs.size())
		return (false);
	while (lhs_it != lhs.end() && rhs_it != rhs.end())
	{
		if (*lhs_it != *rhs_it)
			return (false);
		lhs_it++;
		rhs_it++;
	}
	return (true);
}

template < class Key, class T, class Compare, class Alloc > bool	operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs == rhs)); }
template < class Key, class T, class Compare, class Alloc > bool	operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
template < class Key, class T, class Compare, class Alloc > bool	operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (lhs < rhs || lhs == rhs); }
template < class Key, class T, class Compare, class Alloc > bool	operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (!(lhs <= rhs)); }
template < class Key, class T, class Compare, class Alloc > bool	operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return (lhs > rhs || lhs == rhs); }

}


#endif

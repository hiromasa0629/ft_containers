/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:27:35 by hyap              #+#    #+#             */
/*   Updated: 2023/01/14 15:50:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H
# include "container.hpp"
# include "iterators.hpp"

namespace ft {

template < class value_type, class key_compare_type, class value_compare_type, class key_equal_compare_type>
class RBTree
{
	public:
		typedef struct RBTNode<value_type>					node_type;
		typedef std::size_t									size_type;
		typedef	std::allocator<value_type>					allocator_type;
		typedef std::allocator<node_type>					node_allocator;
		typedef ft::BidirectionalIterator<value_type>		iterator;
		typedef ft::BidirectionalIterator<const value_type>	const_iterator;

		RBTree(const allocator_type &alloc = allocator_type(), const node_allocator& node_alloc = node_allocator())
			: _nil(create_nil()), _root(_nil), _alloc(alloc), _node_alloc(node_alloc), _key_compare(), _value_compare(_key_compare), _key_equal_compare() {};

		/* Construct an empty RBT Tree */
		RBTree(const key_compare_type& key_compare, const allocator_type &alloc = allocator_type(), const node_allocator& node_alloc = node_allocator())
			: _nil(create_nil()), _root(_nil), _alloc(alloc), _node_alloc(node_alloc), _key_compare(key_compare), _value_compare(key_compare), _key_equal_compare() {}

		~RBTree(void) 
		{ 
			rbt_clear();
			rbt_destroyone(_nil); 
		}

		RBTree&	operator=(const RBTree& rhs)
		{
			this->rbt_clear();
			this->rbt_destroyone(this->_nil);
			this->_nil					= create_nil();
			this->_root					= this->_nil;
			this->_alloc				= rhs.get_allocator();
			this->_node_alloc			= rhs.get_node_allocator();
			this->_key_compare			= rhs.get_key_compare();
			this->_value_compare		= rhs.get_value_compare();
			this->_key_equal_compare	= rhs.get_key_equal_compare();
			this->rbt_insert(iterator(rhs.rbt_findmin()), iterator(rhs.get_nil()));
			return (*this);
		}

		ft::pair<iterator, bool>	rbt_insert(const value_type& content)
		{
			node_type*	inserted;
			node_type*	exist;

			exist = rbt_search(_root, content);
			if (!rbt_isnil(exist))
				return (ft::make_pair(iterator(exist), false));
			inserted = rbt_preinsert(&_root, content, _nil);
			rbt_insert_fixup(&_root, inserted);
			_nil->parent = _root;
			return (ft::make_pair(iterator(inserted), true));
		}

		iterator rbt_insert(iterator pos, const value_type& content)
		{
			(void)pos;
			return(rbt_insert(content).first);
		}

		template < class InputIt >
		void	rbt_insert(InputIt first, InputIt last)
		{
			for (InputIt tmp = first; tmp != last; tmp++)
				rbt_insert(*tmp);
		}

		iterator	rbt_lower_bound(const value_type& value)
		{
			iterator	it;

			it = rbt_findmin();
			for (; it != _nil; it++)
			{
				if (!_value_compare(*it, value))
					break ;
			}
			return (iterator(it));
		}

		const_iterator	rbt_lower_bound(const value_type& value) const
		{
			iterator	it;

			it = rbt_findmin();
			for (; it != _nil; it++)
			{
				if (!_value_compare(*it, value))
					break ;
			}
			return (iterator(it));
		}

		iterator	rbt_upper_bound(const value_type& value)
		{
			iterator	it;

			it = rbt_findmin();
			for (; it != _nil; it++)
			{
				if (!_value_compare(*it, value))
					break ;
			}
			if (_key_equal_compare(*it, value))
				it++;
			return (iterator(it));
		}

		const_iterator	rbt_upper_bound(const value_type& value) const
		{
			iterator	it;

			it = rbt_findmin();
			for (; it != _nil; it++)
			{
				if (!_value_compare(*it, value))
					break ;
			}
			if (_key_equal_compare(*it, value))
				it++;
			return (iterator(it));
		}

		ft::pair<iterator, iterator>	rbt_equal_range(const value_type& value)
		{
			return (ft::make_pair(rbt_lower_bound(value), rbt_upper_bound(value)));
		}

		ft::pair<const_iterator, const_iterator>	rbt_equal_range(const value_type& value) const
		{
			return (ft::make_pair(rbt_lower_bound(value), rbt_upper_bound(value)));
		}

		void	rbt_erase(iterator pos)
		{
			node_type*	searched;

			searched = rbt_search(_root, *pos);
			if (rbt_isnil(searched))
				return ;
			rbt_erase(&_root, searched);
			_nil->parent = _root;
		}

		void	rbt_erase(iterator first, iterator last)
		{
			while (first != last)
				rbt_erase(first++);
		}

		size_type	rbt_erase(const value_type& value)
		{
			node_type*	searched;

			searched = rbt_search(_root, value);
			if (rbt_isnil(searched))
				return (0);
			rbt_erase(&_root, searched);
			_nil->parent = _root;
			return (1);
		}

		void		rbt_clear(void) {if (_root == _nil) return; rbt_iter(&RBTree::rbt_destroyone); _root = _nil; }
		void		rbt_iter(void (*f)(node_type *)) { rbt_iter(_root, f); }
		void		rbt_iter(void (RBTree::*f)(node_type *)) { rbt_iter(_root, f); }
		node_type*	rbt_findmin(void) const { return (rbt_findmin(_root)); }
		node_type*	rbt_findmax(void) const { return (rbt_findmax(_root)); }
		size_type	rbt_size(void) const { return (rbt_size(_root)); }

		void		rbt_destroyone(node_type* node)
		{
			_alloc.destroy(node->content);
			_alloc.deallocate(node->content, 1);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}

		void	rbt_swap(RBTree& other)
		{
			node_type*				tmp_nil(_nil);
			node_type*				tmp_root(_root);
			allocator_type			tmp_alloc(_alloc);
			node_allocator			tmp_node_alloc(_node_alloc);
			key_compare_type		tmp_key_compare(_key_compare);
			value_compare_type		tmp_value_compare(_key_compare);
			key_equal_compare_type	tmp_key_equal_compare(_key_equal_compare);

			_nil				= other._nil;
			_root				= other._root;
			_alloc				= other._alloc;
			_node_alloc			= other._node_alloc;
			_key_compare 		= other._key_compare;
			_value_compare		= other._value_compare;
			_key_equal_compare	= other._key_equal_compare;

			other._nil					= tmp_nil;
			other._root					= tmp_root;
			other._alloc				= tmp_alloc;
			other._node_alloc			= tmp_node_alloc;
			other._key_compare			= tmp_key_compare;
			other._value_compare		= tmp_value_compare;
			other._key_equal_compare	= tmp_key_equal_compare;
		}

		node_type*	rbt_search(const value_type& value) const { return (rbt_search(_root, value)); }

		node_type*	get_nil(void) const { return (_nil); }
		node_type*	get_root(void) const { return (_root); }

		allocator_type			get_allocator(void) const { return (allocator_type()); }
		node_allocator			get_node_allocator(void) const { return (node_allocator()); }
		key_compare_type		get_key_compare(void) const { return (_key_compare); }
		value_compare_type		get_value_compare(void) const { return (_value_compare); }
		key_equal_compare_type	get_key_equal_compare(void) const { return (_key_equal_compare); }

	private:
		node_type*				_nil;
		node_type*				_root;
		allocator_type			_alloc;
		node_allocator			_node_alloc;
		key_compare_type		_key_compare;
		value_compare_type		_value_compare;
		key_equal_compare_type	_key_equal_compare;

		bool		rbt_isnil(node_type* node) const { return ((node == _nil) || (node == NULL)); }

		node_type*	rbt_findmin(node_type* root) const
		{
			if (rbt_isnil(root))
				return (_nil);
			if (rbt_isnil(root->left))
				return (root);
			return (rbt_findmin(root->left));
		}

		node_type*	rbt_findmax(node_type* root) const
		{
			if (rbt_isnil(root))
				return (_nil);
			if (rbt_isnil(root->right))
				return (root);
			return (rbt_findmax(root->right));
		}

		node_type*	create_nil(void)
		{
			node_type* newnode;

			newnode = _node_alloc.allocate(1);
			newnode->color = nodeBLACK;
			newnode->content = _alloc.allocate(1);
			_alloc.construct(newnode->content, value_type());
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->parent = _root;
			newnode->isnil = true;
			return (newnode);
		}

		node_type*	rbt_new(const value_type& content, node_type* parent)
		{
			node_type*	newnode;

			newnode = _node_alloc.allocate(1);
			newnode->color = nodeRED;
			newnode->content = _alloc.allocate(1);
			_alloc.construct(newnode->content, content);
			newnode->parent = parent;
			newnode->left = _nil;
			newnode->right = _nil;
			newnode->isnil = false;
			return (newnode);
		}

		node_type*	rbt_search(node_type *node, const value_type& value) const
		{
			if (node == _nil)
				return (_nil);
			if (_key_equal_compare(*(node->content), value))
				return (node);
			if (_value_compare(value, *(node->content)))
				return (rbt_search(node->left, value));
			else
				return (rbt_search(node->right, value));
		}

		node_type*	rbt_preinsert(node_type** node, const value_type& content, node_type* parent)
		{
			if (rbt_isnil(*node))
			{
				*node = rbt_new(content, parent);
				return (*node);
			}
			else if (_value_compare(content, *((*node)->content)))
				return (rbt_preinsert(&((*node)->left), content, *node));
			else
				return (rbt_preinsert(&((*node)->right), content, *node));
		}

		void		rbt_left_rotate(node_type** root, node_type* node)
		{
			node_type*	tmp;

			tmp = node->right;
			node->right = tmp->left;
			if (!rbt_isnil(tmp->left))
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (rbt_isnil(node->parent)) // If (*node) was root and tmp is now root
				*root = tmp;
			else if (node->parent->left == node) // If (*node) was a left child
				node->parent->left  = tmp;
			else if (node->parent->right == node) // If (*node) was a right child
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
		}

		void		rbt_right_rotate(node_type** root, node_type* node)
		{
			node_type *tmp;

			tmp = node->left;
			node->left = tmp->right;
			if (!rbt_isnil(tmp->left))
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (rbt_isnil(node->parent))
				*root = tmp;
			else if (node->parent->left == node)
				node->parent->left = tmp;
			else if (node->parent->right == node)
				node->parent->right = tmp;
			tmp->right = node;
			node->parent = tmp;
		}

		void		rbt_insert_fixup(node_type** root, node_type *node)
		{
			node_type*	uncle;

			while (node->parent->color == nodeRED)
			{
				if (node->parent == node->parent->parent->left) // node parent is a left child
				{
					uncle = node->parent->parent->right;
					if (uncle->color == nodeRED)
					{
						node->parent->color = nodeBLACK;
						node->parent->parent->color = nodeRED;
						uncle->color = nodeBLACK;
						node = node->parent->parent;
					}
					else if (uncle->color == nodeBLACK)
					{
						if (node == node->parent->right) // node is a right child
						{
							node = node->parent;
							rbt_left_rotate(root, node);
						}
						node->parent->color = nodeBLACK;
						node->parent->parent->color = nodeRED;
						rbt_right_rotate(root, node->parent->parent);
					}
				}
				else if (node->parent == node->parent->parent->right) // node parent is a right child
				{
					uncle = node->parent->parent->left;
					if (uncle->color == nodeRED)
					{
						node->parent->color = nodeBLACK;
						node->parent->parent->color = nodeRED;
						uncle->color = nodeBLACK;
						node = node->parent->parent;
					}
					else if (uncle->color == nodeBLACK)
					{
						if (node == node->parent->left) // node is a left child
						{
							node = node->parent;
							rbt_right_rotate(root, node);
						}
						node->parent->color = nodeBLACK;
						node->parent->parent->color = nodeRED;
						rbt_left_rotate(root, node->parent->parent);
					}
				}
			}
			(*root)->color = nodeBLACK;
		}

		void		rbt_iter(node_type* root, void (*f)(node_type *))
		{
			if (!rbt_isnil(root->left))
				rbt_iter(root->left, f);
			f(root);
			// if (!rbt_isnil(root->parent))
			// 	std::cout << " | parent: " << root->parent->content->first << " " << root->parent->content->second;
			// std::cout << (root->color == nodeRED ? " | RED" : " | BLACK") << std::endl;
			if (!rbt_isnil(root->right))
				rbt_iter(root->right, f);
		}

		void		rbt_iter(node_type* root, void (RBTree::*f)(node_type *))
		{
			if (!rbt_isnil(root->left))
				rbt_iter(root->left, f);
			// std::cout << root->content->first << " " << root->content->second << std::endl;
			(this->*f)(root);
			if (!rbt_isnil(root->right))
				rbt_iter(root->right, f);
		}

		void		rbt_transplant(node_type** root, node_type* u, node_type* v)
		{
			if (u->parent == _nil)
				*root = v;
			else if (u->parent->left == u)
				u->parent->left = v;
			else
				u->parent->right = v;
			v->parent = u->parent;
		}

		void		rbt_erasefixup(node_type** root, node_type *node)
		{
			node_type	*w;

			while (node != *root && node->color == nodeBLACK)
			{
				if (node == node->parent->left)
				{
					w = node->parent->right;
					if (w->color == nodeRED)
					{
						w->color = nodeBLACK;
						node->parent->color = nodeRED;
						rbt_left_rotate(root, node->parent);
						w = node->parent->right;
					}
					if (w->left->color == nodeBLACK && w->right->color == nodeBLACK)
					{
						w->color = nodeRED;
						node = node->parent;
					}
					else
					{
						if (w->right->color == nodeBLACK)
						{
							w->left->color = nodeBLACK;
							w->color = nodeRED;
							rbt_right_rotate(root, w);
							w = node->parent->right;
						}
						w->color = node->parent->color;
						node->parent->color = nodeBLACK;
						w->right->color = nodeBLACK;
						rbt_left_rotate(root, node->parent);
						node = *root;
					}
				}
				else if (node == node->parent->right)
				{
					w = node->parent->left;
					if (w->color == nodeRED)
					{
						w->color = nodeBLACK;
						node->parent->color = nodeRED;
						rbt_right_rotate(root, node->parent);
						w = node->parent->left;
					}
					if (w->left->color == nodeBLACK && w->right->color == nodeBLACK)
					{
						w->color = nodeRED;
						node = node->parent;
					}
					else
					{
						if (w->left->color == nodeBLACK)
						{
							w->right->color = nodeBLACK;
							w->color = nodeRED;
							rbt_left_rotate(root, w);
							w = node->parent->left;
						}
						w->color = node->parent->color;
						node->parent->color = nodeBLACK;
						w->left->color = nodeBLACK;
						rbt_right_rotate(root, node->parent);
						node = *root;
					}
				}
			}
			node->color = nodeBLACK;
		}

		void		rbt_erase(node_type** root, node_type* tbd)
		{
			enum color	ori;
			node_type	*x;
			node_type	*small;

			if (!tbd || tbd == _nil)
				return ;
			ori = tbd->color;

			if (tbd->left == _nil)
			{
				x = tbd->right;
				rbt_transplant(root, tbd, tbd->right);
			}
			else if (tbd->right == _nil)
			{
				x = tbd->left;
				rbt_transplant(root, tbd, tbd->left);
			}
			else
			{
				small = rbt_findmin(tbd->right);
				ori = small->color;
				x = small->right;
				if (small->parent != tbd)
				{
					rbt_transplant(root, small, small->right);
					small->right = tbd->right;
					small->right->parent = small;
				}
				else
					x->parent = small;
				rbt_transplant(root, tbd, small);
				small->left = tbd->left;
				small->left->parent = small;
				small->color = tbd->color;
			}
			if (ori == nodeBLACK)
				rbt_erasefixup(root, x);
			rbt_destroyone(tbd);
		}

		size_type	rbt_size(node_type* root) const
		{
			size_type	left_size;
			size_type	right_size;

			if (rbt_isnil(root))
				return (0);
			left_size = rbt_size(root->left);
			right_size = rbt_size(root->right);
			return (1 + left_size + right_size);
		}

};

}

#endif

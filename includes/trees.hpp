/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:27:35 by hyap              #+#    #+#             */
/*   Updated: 2022/12/13 01:59:28 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H
# include "container.hpp"
# include "iterators.hpp"

namespace ft {

template < class T, class value_compare>
class RBTree
{
	public:
		typedef struct RBTNode<T>							node_type;
		typedef T											value_type;
		typedef std::size_t									size_type;
		typedef	std::allocator<T>							allocator_type;
		typedef std::allocator<node_type>					node_allocator;
		typedef ft::BidirectionalIterator<value_type>		iterator;
		typedef const ft::BidirectionalIterator<value_type>	const_iterator;

		/* Construct an empty RBT Tree */
		RBTree(const value_compare& compare, const allocator_type &alloc = allocator_type(), const node_allocator& node_alloc = node_allocator())
			: _nil(create_nil()), _root(_nil), _alloc(alloc), _node_alloc(node_alloc), _compare(compare) {}

		ft::pair<iterator, bool>	rbt_insert(const value_type& content)
		{
			node_type*	inserted;

			if ((inserted = rbt_search(_root, content)))
				return (ft::make_pair(iterator(inserted), false));
			inserted = rbt_preinsert(&_root, content, _nil);
			rbt_insert_fixup(&_root, inserted);
			return (ft::make_pair(iterator(inserted), true));
		}

		iterator	rbt_erase(iterator pos)
		{
			node_type*	searched;
			searched = rbt_search(_root, *pos);
			rbt_erase(&_root, searched);
			return (NULL);
		}

		void		clear(void) { rbt_iter(rbt_destroyone()); rbt_destroyone(_nil); }
		void		rbt_iter(void (*f)(node_type *)) { rbt_iter(_root, f); }
		node_type*	rbt_findmin(void) const { return (rbt_findmin(_root)); }
		node_type*	rbt_findmax(void) const { return (rbt_findmax(_root)); }
		size_type	rbt_size(void) const { return (rbt_size(_root)); }

	private:
		node_type*		_nil;
		node_type*		_root;
		allocator_type	_alloc;
		node_allocator	_node_alloc;
		value_compare	_compare;

		bool		rbt_isnil(node_type* node) const { return ((node == _nil) || (node == NULL)); }
		bool		rbt_key_issame(const value_type& lhs, const value_type& rhs) const { return (lhs.first == rhs.first); }

		node_type*	rbt_findmin(node_type* root) const
		{
			if (rbt_isnil(root))
				return (NULL);
			if (rbt_isnil(root->left))
				return (root);
			return (rbt_findmin(root->left));
		}

		node_type*	rbt_findmax(node_type* root) const
		{
			if (rbt_isnil(root))
				return (NULL);
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
			newnode->parent = NULL;
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
			return (newnode);
		}

		node_type*	rbt_preinsert(node_type** node, const value_type& content, node_type* parent)
		{
			if (rbt_isnil(*node))
			{
				*node = rbt_new(content, parent);
				return (*node);
			}
			else if (_compare(content, *((*node)->content)))
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
			if (!rbt_isnil(root->parent))
				std::cout << " | parent: " << root->parent->content->first << " " << root->parent->content->second;
			std::cout << (root->color == nodeRED ? " | RED" : " | BLACK") << std::endl;
			if (!rbt_isnil(root->right))
				rbt_iter(root->right, f);
		}

		node_type*	rbt_search(node_type *node, const value_type& content)
		{
			if (node == _nil)
				return (NULL);
			if (rbt_key_issame(*(node->content), content))
				return (node);
			if (_compare(content, *(node->content)))
				return (rbt_search(node->left, content));
			else
				return (rbt_search(node->right, content));
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
				rbt_delfixup(root, x);
			rbt_destroyone(tbd);
		}

		void		rbt_destroyone(node_type* node)
		{
			_alloc.destroy(node->content);
			_alloc.deallocate(node->content, 1);
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
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

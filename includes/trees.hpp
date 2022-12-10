/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:27:35 by hyap              #+#    #+#             */
/*   Updated: 2022/12/10 21:37:40 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H
# include "container.hpp"
# include "iterators.hpp"

namespace ft {

enum color {
	nodeRED,
	nodeBLACK
};

/* ============================ Tree nodes struct ============================ */
template < class T, class NodeType >
struct Node
{
	T*			content;
	NodeType*	parent;
	NodeType*	left;
	NodeType*	right;
};

template < class T >
struct RBTNode : public Node<T, RBTNode<T> >
{
	enum color	color;
};

template < class T, class value_compare >
class RBTree
{
	public:
		typedef struct RBTNode<T>							node_type;
		typedef T											value_type;
		typedef	std::allocator<T>							allocator_type;
		typedef std::allocator<node_type>					node_allocator;
		typedef ft::BidirectionalIterator<node_type>		iterator;
		typedef const ft::BidirectionalIterator<node_type>	const_iterator;

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

		void		rbt_iter(void (*f)(value_type *)) { rbt_iter(_root, f); }

	private:
		node_type*		_nil;
		node_type*		_root;
		allocator_type	_alloc;
		node_allocator	_node_alloc;
		value_compare	_compare;

		bool		rbt_isnil(node_type* node) { return ((node == _nil) || (node == NULL)); }

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

		void		rbt_iter(node_type* root, void (*f)(value_type *))
		{
			if (!rbt_isnil(root->left))
				rbt_iter(root->left, f);
			f(root->content);
			if (!rbt_isnil(root->parent))
				std::cout << " | parent: " << root->parent->content->first << " " << root->parent->content->second;
			std::cout << (root->color == nodeRED ? " | RED" : " | BLACK") << std::endl;
			if (!rbt_isnil(root->right))
				rbt_iter(root->right, f);
		}

		bool		rbt_key_issame(const value_type& lhs, const value_type& rhs) { return (lhs.first == rhs.first); }

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
};

}

#endif

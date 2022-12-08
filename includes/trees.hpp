/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:27:35 by hyap              #+#    #+#             */
/*   Updated: 2022/12/08 21:49:18 by hyap             ###   ########.fr       */
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
	T			content;
	NodeType*	parent;
	NodeType*	left;
	NodeType*	right;
};

template < class T >
struct BSTNode : public Node<T, BSTNode>
{

};

template < class T >
struct RBTNode : public Node<T, RBTNode>
{
	enum color	color;
};

template < class T, class key_compare, class Allocator = std::allocator< RBTNode<T> > >
class RBTTree
{
	public:
		typedef struct RBTNode<T>							node;
		typedef T											value_type;
		typedef Allocator									allocator_type;		
		typedef ft::BidirectionalIterator<value_type>		iterator;
		typedef const ft::BidirectionalIterator<value_type>	const_iterator;
		
		/* Construct an empty RBT Tree */
		RBTTree(const allocator_type &alloc = allocator_type()) : _nil(create_nil()), _root(_nil), _alloc(alloc) {}
		
		ft::pair<iterator, bool>	rbt_insert(const value_type& value)
		{
			
		}
		
		
	
	private:
		node*			_nil;
		node*			_root;
		allocator_type	_alloc;
		
		node*	create_nil(void) const
		{
			node* newnode;
			
			newnode = alloc.allocate(1);
			newnode->color = nodeBLACK;
			newnode->content = value_type();
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->parent = NULL;
			return (node);
		}
};

}

#endif
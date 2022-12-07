/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trees.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 21:27:35 by hyap              #+#    #+#             */
/*   Updated: 2022/12/07 21:31:52 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREES_H
# define TREES_H
# include "container.hpp"

enum color {
	RED,
	BLACK
};

/* ============================ Tree nodes struct ============================ */
typedef struct	s_bstnode
{
	struct s_bstnode*	parent;
	struct s_bstnode*	left;
	struct s_bstnode*	right;
}				t_bstnode;

typedef struct	s_rbtnode : public virtual t_bstnode
{
	enum color	color;
}				t_rbtnode;



#endif
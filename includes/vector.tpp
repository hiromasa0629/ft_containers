/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.tpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 20:15:43 by hyap              #+#    #+#             */
/*   Updated: 2022/10/23 20:47:35 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.hpp"

namespace ft {

/***********************************
 * Constructor
***********************************/

template <typename T, typename Allocator>
vector<T, Allocator>::vector(void)
{
	std::cout << "Constructor !" << std::endl;
}

/***********************************
 * Public Functions
***********************************/

template <typename T, typename Allocator>
size_t	vector<T, Allocator>::size(void) const
{
	return (this->_size);
}

/***********************************
 * Destructor
***********************************/

template <typename T, typename Allocator>
vector<T, Allocator>::~vector(void)
{
	std::cout << "Destructing..." << std::endl;
}


}

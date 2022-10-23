/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/10/23 20:47:54 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <iostream>

namespace ft {
	
template <typename T, typename Allocator = std::allocator<T> >
class vector {
	public:
		vector(void);
		~vector(void);
		vector(const vector &src);
		vector	&operator=(const vector &rhs);
		vector(const Allocator &alloc);
		
		size_t	size(void) const;

	private:
		T		*_data;
		size_t	_size;
};

}

#endif

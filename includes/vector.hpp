/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/13 22:09:14 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <iostream>
# include <vector>

namespace ft {
	
template <typename T, typename Allocator = std::allocator<T> >
class vector {
	typedef typename std::size_t	size_type;
	typedef	typename Allocator		allocator_type;
	typedef typename T				value_type;

	private:
		value_type		*_data;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:
		/* default constructor */
		explicit vector(const allocator_type &alloc = allocator_type())
			: _data(NULL), _capacity(1), _size(0), _alloc(alloc)
		{
			std::cout << "Default constructor called" << std::endl;
		}
		/* fill construcotr */
		explicit vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type())
			: _size(n), _alloc(alloc)
		{
			
			std::cout << "Fill constructor called" << std::endl;
		}
		/* copy */
		vector(const vector &src);
		/* copy assignment */
		vector	&operator=(const vector &rhs);
		/* destructor */
		~vector(void);
		
		/* capacity functions */
		size_type	capacity(void) const;
		size_type	size(void) const;
};
}

#endif

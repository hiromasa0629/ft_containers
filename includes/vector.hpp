/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/15 15:33:37 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <iostream>
# include <vector>

namespace ft {
	
template <typename T, typename Allocator = std::allocator<T> >
class vector {
	typedef typename std::size_t							size_type;
	typedef	Allocator										allocator_type;
	typedef T												value_type;
	typedef typename allocator_type::value_type&			reference;
	typedef const typename allocator_type::value_type&		const_reference;
	typedef typename  allocator_type::pointer				pointer;
	typedef	const typename allocator_type::const_pointer	const_pointer;

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
			: _capacity(n), _size(n), _alloc(alloc)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_data[i] = val;
			std::cout << "Fill constructor called" << std::endl;
		}

		/* copy */
		vector(const vector &src)
		{
			(void)src;
		}

		/* copy assignment */
		vector	&operator=(const vector &rhs)
		{
			(void)rhs;
		}

		/* destructor */
		~vector(void)
		{
			
		}
		
		/* Returns vector capacity */
		size_type	capacity(void) const
		{
			return (this->_capacity);
		}
		
		/* Returns vector size */
		size_type	size(void) const
		{
			return (this->_size);
		}
		
		/* Random access using array index operator */
		reference	operator[](size_type n)
		{
			return (_data[n]);
		}
		
};

}

#endif

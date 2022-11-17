/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/17 21:47:28 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <iostream>
# include <vector>
# include "container.hpp"

namespace ft {
	
template <typename T, typename Allocator = std::allocator<T> >
class Vector {
	typedef typename std::size_t							size_type;
	typedef	Allocator										allocator_type;
	typedef T												value_type;
	typedef typename allocator_type::value_type&			reference;
	typedef const typename allocator_type::value_type&		const_reference;
	typedef typename  allocator_type::pointer				pointer;
	typedef	const typename allocator_type::const_pointer	const_pointer;

	private:
		pointer			_data;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

	public:
		/* Default constructor */
		explicit vector(const allocator_type &alloc = allocator_type())
			: _data(NULL), _capacity(1), _size(0), _alloc(alloc)
		{
			std::cout << "Default constructor called" << std::endl;
		}

		/* Fill construcotr */
		explicit vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type())
			: _capacity(n), _size(n), _alloc(alloc)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_data[i] = _alloc.construct(&_data[i], val);
			std::cout << "Fill constructor called" << std::endl;
		}
		/* Copy constructor */
		vector(const vector &src)
		{
			(void)src;
		}

		/* Copy assignment */
		vector	&operator=(const vector &rhs)
		{
			(void)rhs;
		}

		/* Destructor */
		~vector(void)
		{
			_alloc.deallocate(_data, _capacity);
			std::cout << "Destructing..." << std::endl;
		}
		
		/* ============================ Capacity functions ============================ */
		size_type	size(void) const 
		{
			return (_size); 
		}
		
		size_type	max_size(void) const 
		{ 
			return (_alloc.max_size());  
		}
		
		size_type	capacity(void) const { 
			return (_capacity); 
		}
		
		void		reserve(size_type n)
		{
			pointer		new_data;
			
			if (n > this->max_size())
				throw (std::length_error("ft::vector::reserve"));
			if (n <= this->capacity())
				return ;
			new_data = _alloc.allocate(n);
			for (size_type i = 0; i < this->size(); i++)
				new_data[i] = _alloc.construct(&new_data[i], _data[i]);
			_alloc.deallocate(_data, this->capacity());
			_capacity = n;
			_data = new_data;
		}
		
		void		resize(size_type n, value_type val = value_type())
		{
			pointer		new_data;
			size_type	end;
			size_type	i;
			
			if (n > this->max_size())
				throw (std::length_error("ft::vector::resize"));
			if (n < this->size())
				for (size_type i = n - 1; i < this->size(); i++)
					_alloc.destroy(&_data[i];)
			if (n > this->size())
				for (size_type i = this->size() - 1; i < n; i++)
					
			
		}
		
		/* Random access using array index operator */
		reference	operator[](size_type n)
		{
			return (_data[n]);
		}
		
};

}

#endif

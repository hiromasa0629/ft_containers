/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/29 21:07:13 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <iostream>
# include <vector>
# include "container.hpp"
# include "iterators.hpp"
# include "colors.hpp"

namespace ft {

template <typename T, typename Allocator = std::allocator<T> >
class Vector {
	public:
		typedef typename std::size_t									size_type;
		typedef	Allocator												allocator_type;
		typedef T														value_type;
		typedef typename allocator_type::value_type&					reference;
		typedef const typename allocator_type::value_type&				const_reference;
		typedef typename  allocator_type::pointer						pointer;
		typedef	const typename allocator_type::const_pointer			const_pointer;
		typedef ft::RandomAccessIterator<T>								iterator;
		typedef const ft::RandomAccessIterator<T>						const_iterator;
		typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;

		/* Default constructor */
		explicit Vector(const allocator_type &alloc = allocator_type())
			: _data(NULL), _capacity(1), _size(0), _alloc(alloc)
		{

		}

		/* Fill construcotr */
		explicit Vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type())
			: _capacity(n), _size(n), _alloc(alloc)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], val);
		}

		/* Copy constructor */
		Vector(const Vector &src)
			: _data(NULL), _capacity(0), _size(0), _alloc(src.get_allocator())
		{
			this->insert(this->begin(), src.begin(), src.end());
		}

		/* Copy assignment */
		Vector&	operator=(const Vector &rhs)
		{
			this->clear();
			_alloc = rhs.get_allocator();
			_alloc.deallocate(_data, _capacity);
			_capacity = 0;
			_size = 0;
			_data = NULL;
			this->insert(this->begin(), rhs.begin(), rhs.end());
			return (*this);
		}

		/* Destructor */
		~Vector(void)
		{
			_alloc.deallocate(_data, _capacity);
			std::cout << DIM << ANGRT << DIM << "Destructing..." << RESET << std::endl;
		}

		/* ============================ Capacity functions ============================ */
		size_type	size(void) const { return (_size); } /* Returns the number of elements */
		size_type	max_size(void) const { return (_alloc.max_size()); } /* Returns the maximum number of elements the vector can hold */
		size_type	capacity(void) const { return (_capacity); } /* Returns size of allocated storage capacity */

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
			this->clear();
			_alloc.deallocate(_data, this->capacity());
			_capacity = n;
			_data = new_data;
		}

		// void		resize(size_type n, value_type val = value_type())
		// {
		// 	pointer		new_data;
		// 	size_type	end;

		// 	if (n > this->max_size())
		// 		throw (std::length_error("ft::vector::resize"));
		// 	if (n < this->size())
		// 		for (size_type i = n - 1; i < this->size(); i++)
		// 			_alloc.destroy(&_data[i]);
		// 	if (n > this->size())
		// 		for (size_type i = this->size() - 1; i < n; i++)
		// }

		/* Replaces the contents of the container */
		template < class InputIt >
		void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		{
			pointer		newdata;
			size_type	oldcapacity;

			oldcapacity = _capacity;
			_size = ft::distance(last, first);
			_capacity = _size;
			newdata = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&(newdata[i]), first[i]);
			this->clear();
			_alloc.deallocate(_data, oldcapacity);
			_size = ft::distance(last, first);
			_data = newdata;
		}

		void	assign(size_type count, const_reference value)
		{
			this->clear();
			_alloc.deallocate(_data, _capacity);
			_size = count;
			_capacity = _size;
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&(_data[i]), value);
		}

		/* Inserts elements at the specified location in the container */
		iterator	insert(const_iterator pos, const_reference value)
		{
			size_type	ipos;
			bool		inserted;
			pointer		newdata;
			size_type	oldcapacity;
			size_type	i;

			ipos = ft::distance(pos, this->begin());
			oldcapacity = _capacity;
			newdata = double_realloc();
			// std::cout << "value: " << value << std::endl;
			if (ipos == _size)
			{
				for (i = 0; i < _size; i++)
					_alloc.construct(&(newdata[i]), _data[i]);
				_alloc.construct(&(newdata[ipos]), value);
				this->clear();
				_size = i + 1;
				_alloc.deallocate(_data, oldcapacity);
				_data = newdata;
				return (iterator(_data + ipos));
			}
			inserted = 0;
			for (i = 0; i < _size + 1; i++)
			{
				if (i == ipos && !inserted)
				{
					_alloc.construct(&(newdata[i]), value);
					inserted = 1;
					continue;
				}
				_alloc.construct(&(newdata[i]), _data[i - inserted]);
			}
			this->clear();
			_size = i;
			_alloc.deallocate(_data, oldcapacity);
			_data = newdata;
			return (iterator(_data + ipos));
		}

		iterator	insert(const_iterator pos, size_type count, const_reference value)
		{
			size_type	i;
			size_type	ipos;
			iterator	tmppos;

			ipos = ft::distance(pos, this->begin());
			tmppos = pos;
			for (i = 0; i < count; i++)
				tmppos = this->insert(tmppos, value);
			return (iterator(_data + ipos + i - 1));
		}

		template< class InputIt >
		iterator	insert(const_iterator pos, InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
		{
			size_type	ipos;
			iterator	tmppos;

			ipos = ft::distance(pos, this->begin());
			tmppos = pos;
			for (iterator end = last - 1; end >= first; end--)
			{
				// std::cout << "*end: " << *end << std::endl;
				tmppos = this->insert(tmppos, *end);
			}
			return (iterator(_data + ipos));
		}

		 /* Erases all elements from the container */
		void	clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&(_data[i]));
			_size = 0;
		}

		/* ============================ Element access ============================ */
		reference			operator[](size_type n) { return (_data[n]); }			/* Returns a reference to the element at position n */
		const_reference		operator[](size_type n) const { return (_data[n]); }	/* Returns a const reference to the element at position n */
		reference			front(void) { return (_data[0]); }						/* Returns a reference to the first element */
		const_reference		front(void) const { return (_data[0]); }				/* Returns a const reference to the first element */
		reference			back(void) { return (_data[_size - 1]); }				/* Returns a reference to the last element */
		const_reference		back(void) const { return (_data[_size - 1]); }			/* Returns a const reference to the last element */
		value_type*			data(void) { return (_data); }							/* Returns a direct pointer to the memory array */
		const value_type*	data(void) const { return (_data); }					/* Returns a const direct pointer to the memory array */
		/* Returns a reference to the element at position n, throw out_of_range if n >= size */
		reference			at(size_type n) { if (n >= _size) throw std::out_of_range("ft::Vector::at"); return (_data[n]); }
		/* Returns a reference to the element at position n, throw out_of_range if n >= size */
		const_reference		at(size_type n) const { if (n >= _size) throw std::out_of_range("const ft::Vector::at"); return (_data[n]); }

		/* ============================ Allocator ============================ */
		allocator_type	get_allocator(void) const { return (allocator_type()); }

		/* ============================ Iterator ============================ */
		iterator		begin(void) { return (_data); }
		const_iterator	begin(void) const { return (_data); }
		iterator		end(void) { return (&(_data[_size])); }
		const_iterator	end(void) const { return (&(_data[_size])); }



	private:
		pointer			_data;
		size_type		_capacity;
		size_type		_size;
		allocator_type	_alloc;

		pointer	double_realloc(void)
		{
			pointer		newdata;

			if (_size == _capacity)
			{
				if (_capacity == 0)
				{
					_capacity = 1;
					newdata = _alloc.allocate(_capacity);
				}
				else
				{
					newdata = _alloc.allocate(_capacity * 2);
					_capacity *= 2;
				}
			}
			else
				newdata = _alloc.allocate(_capacity);
			return (newdata);
		}
};

}

#endif

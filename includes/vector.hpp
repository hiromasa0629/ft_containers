/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:11:45 by hyap              #+#    #+#             */
/*   Updated: 2022/11/30 15:28:08 by hyap             ###   ########.fr       */
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

		/* ============================ Member Functions ============================ */

		/* Default constructor */
		explicit Vector(const allocator_type &alloc = allocator_type()) : _data(NULL), _capacity(1), _size(0), _alloc(alloc) {}

		/* Fill construcotr */
		explicit Vector(size_type n, const value_type &val, const allocator_type &alloc = allocator_type()) : _capacity(n), _size(n), _alloc(alloc)
		{
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_data[i], val);
		}

		/* Copy constructor */
		Vector(const Vector &src) : _data(NULL), _capacity(src.capacity()), _size(src.size()), _alloc(src.get_allocator()) 
		{ 
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < this->size(); i++)
				_alloc.construct(&(_data[i]), src[i]);
		}

		/* Copy assignment */
		Vector&	operator=(const Vector &rhs)
		{
			this->clear();
			_alloc = rhs.get_allocator();
			_alloc.deallocate(_data, _capacity);
			_capacity = rhs.capacity();
			_size = rhs.size();
			_data = _alloc.allocate(_capacity);
			for (size_type i = 0; i < this->size(); i++)
				_alloc.construct(&(_data[i]), rhs[i]);
			return (*this);
		}

		/* Destructor */
		~Vector(void)
		{
			_alloc.deallocate(_data, _capacity);
			std::cout << DIM << ANGRT << DIM << "Destructing..." << RESET << std::endl;
		}

		/* Return allocator type */
		allocator_type	get_allocator(void) const { return (allocator_type()); }

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


		/* ============================ Capacity functions ============================ */
		
		bool		empty(void) const { if (this->begin() == this->end()) return true; return false; }
		size_type	size(void) const { return (_size); } /* Returns the number of elements */
		size_type	max_size(void) const { return (_alloc.max_size()); } /* Returns the maximum number of elements the vector can hold */
		size_type	capacity(void) const { return (_capacity); } /* Returns size of allocated storage capacity */

		void		reserve(size_type n)
		{
			pointer		new_data;
			size_type	i;

			if (n > this->max_size())
				throw (std::length_error("ft::vector::reserve"));
			if (n <= this->capacity())
				return ;
			new_data = _alloc.allocate(n);
			for (i = 0; i < this->size(); i++)
				_alloc.construct(&new_data[i], _data[i]);
			this->clear();
			_alloc.deallocate(_data, this->capacity());
			_capacity = n;
			_size = i;
			_data = new_data;
		}


		/* ============================ Modifiers ============================ */

		 /* Erases all elements from the container */
		void	clear(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&(_data[i]));
			_size = 0;
		}

		/* Inserts elements at the specified location in the container */
		iterator	insert(const_iterator pos, const_reference value)
		{
			size_type	ipos;
			size_type	inserted;
			pointer		newdata;
			size_type	oldsize;

			ipos = ft::distance(pos, this->begin());
			oldsize = _size;
			inserted = 0;
			if (_size == _capacity)
			{
				newdata = _alloc.allocate(_capacity + 1);
				for (size_type i = 0; (i - inserted) < _size; i++)
				{
					if (i == ipos)
					{
						_alloc.construct(&(newdata[i]), value);
						inserted = 1;
						continue;
					}
					_alloc.construct(&(newdata[i]), _data[i - inserted]);
				}
				if (ipos == _size)
					_alloc.construct(&(newdata[ipos]), value);
				this->clear();
				_alloc.deallocate(_data, _capacity);
				_capacity += 1;
				_size = oldsize + 1;
				_data = newdata;
			}
			else
			{
				if (ipos == _size)
					_alloc.construct(&(_data[ipos]), value);
				else
				{
					for (size_type i = _size; i > ipos; i--)
					{
						_alloc.construct(&(_data[i]), _data[i - 1]);
						_alloc.destroy(&(_data[i - 1]));
					}
					_alloc.construct(&(_data[ipos]), value);
				}
				_size++;
				_capacity += 1;
			}
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
			for (InputIt end = last - 1; end >= first; end--)
				tmppos = this->insert(tmppos, *end);
			return (iterator(_data + ipos));
		}

		iterator	erase(iterator pos)
		{
			size_type	ipos;
			pointer		newdata;
			size_type	i = 0;
			size_type	found;
			
			ipos = ft::distance(pos, this->begin());
			newdata = _alloc.allocate(_capacity - 1);
			found = 0;
			while (i < this->size())
			{
				if (i == ipos)
				{
					found = 1;
					i++;
					continue;
				}
				_alloc.construct(&(newdata[i - found]), _data[i]);
				i++;
			}
			this->clear();
			_alloc.deallocate(_data, _capacity);
			_capacity = _capacity - 1;
			_size = _capacity;
			_data = newdata;
			return (iterator(_data + ipos));
		}

		void		resize(size_type n, value_type val = value_type())
		{
			pointer		newdata;
			size_type	i;

			if (n > this->max_size())
				throw (std::length_error("ft::vector::resize"));
			newdata = _alloc.allocate(n);
			for (i = 0; i < _size && i < n; i++)
				_alloc.construct(&(newdata[i]), _data[i]);
			for (size_type j = i; j < n; j++)
				_alloc.construct(&(newdata[j]), val);
			this->clear();
			_alloc.deallocate(_data, _capacity);
			_capacity = n;
			_size = n;
			_data = newdata;
		}

		/* ============================ Element access ============================ */
		/* Returns a reference to the element at position n, throw out_of_range if n >= size */
		reference			at(size_type n) { if (n >= _size) throw std::out_of_range("ft::Vector::at"); return (_data[n]); }
		/* Returns a reference to the element at position n, throw out_of_range if n >= size */
		const_reference		at(size_type n) const { if (n >= _size) throw std::out_of_range("const ft::Vector::at"); return (_data[n]); }
		reference			operator[](size_type n) { return (_data[n]); }			/* Returns a reference to the element at position n */
		const_reference		operator[](size_type n) const { return (_data[n]); }	/* Returns a const reference to the element at position n */
		reference			front(void) { return (_data[0]); }						/* Returns a reference to the first element */
		const_reference		front(void) const { return (_data[0]); }				/* Returns a const reference to the first element */
		reference			back(void) { return (_data[_size - 1]); }				/* Returns a reference to the last element */
		const_reference		back(void) const { return (_data[_size - 1]); }			/* Returns a const reference to the last element */
		value_type*			data(void) { return (_data); }							/* Returns a direct pointer to the memory array */
		const value_type*	data(void) const { return (_data); }					/* Returns a const direct pointer to the memory array */

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
};

}

#endif

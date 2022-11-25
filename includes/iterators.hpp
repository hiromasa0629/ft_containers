/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:25:09 by hyap              #+#    #+#             */
/*   Updated: 2022/11/25 19:56:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_H
# define ITERATORS_H
# include <iterator>
# include "container.hpp"

namespace ft {

struct random_access_iterator_tag {};

template<  class Category, class T,  class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
struct IteratorBase {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
	
};

template< class Category, class T,  class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
struct RandomAccessIterator : public IteratorBase<ft::random_access_iterator_tag, T>{
	private:
		pointer	_ptr;
	
	public:
		/* Iterator constructor */
		RandomAccessIterator(void) : _ptr(NULL) {}
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) { _ptr = rhs.ptr; return (*this) };
		RandomAccessIterator(pointer ptr) : _ptr(ptr) {}
		
		/* Operators */
		reference					operator*(void) const { return (*_ptr); }
		reference					operator[](int n) { return *(_ptr + n); }
		pointer						operator->(void) { return (_ptr); }
		RandomAccessIterator&		operator++(void) { _ptr++; return (*this); }
		RandomAccessIterator		operator++(value_type) { RandomAccessIterator	tmp = *this; _ptr++; return (tmp); }
		RandomAccessIterator&		operator--(void) { _ptr--; return (*this); }
		RandomAccessIterator		operator--(value_type) { RandomAccessIterator	tmp = *this; _ptr--; return (tmp); }
		bool						operator==(const RandomAccessIterator& rhs) { return (lhs._ptr == rhs._ptr); }
		bool						operator!=(const RandomAccessIterator& rhs) { return (lhs._ptr != rhs._ptr); }
		bool						operator<(const RandomAccessIterator& rhs) { return (_ptr < rhs._ptr); }
		bool						operator>(const RandomAccessIterator& rhs) { return (_ptr > rhs._ptr); }
		bool						operator<=(const RandomAccessIterator& rhs) { return (_ptr <= rhs._ptr); }
		bool						operator>=(const RandomAccessIterator& rhs) { return (_ptr >= rhs._ptr); }
		RandomAccessIterator&		operator+=(int n) { _ptr += n; return (*this); }
		RandomAccessIterator&		operator-=(int n) { _ptr -= n; return (*this); }
		friend RandomAccessIterator	operator+(int n, const RandomAccessIterator& rhs) { return (RandomAccessIterator(n + rhs._ptr)); }
		friend RandomAccessIterator	operator+(const RandomAccessIterator& lhs, int n) { return (RandomAccessIterator(rhs._ptr + n)); }
		friend RandomAccessIterator	operator-(int n, const RandomAccessIterator& rhs) { return (RandomAccessIterator(n - rhs._ptr)); }
		friend RandomAccessIterator	operator-(const RandomAccessIterator& lhs, int n) { return (RandomAccessIterator(rhs._ptr - n)); }
		
		~RandomAccessIterator(void) {}
};

template< class T >
struct iterator_traits {
	
};

}

#endif
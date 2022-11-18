/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:25:09 by hyap              #+#    #+#             */
/*   Updated: 2022/11/18 13:59:50 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_H
# define ITERATORS_H
# include <iterator>



template< class T, class Category = std::random_access_iterator_tag,  class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
struct RandomAccessIterator {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
	
	private:
		pointer	_ptr;
	
	public:
		/* Iterator constructor */
		RandomAccessIterator(void) : _ptr(NULL) {}
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) {  };	
		RandomAccessIterator(pointer ptr) : _ptr(ptr) {}
		
		/* Operators */
		reference					operator*(void) const { return (*_ptr); }
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

#endif
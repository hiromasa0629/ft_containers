/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:25:09 by hyap              #+#    #+#             */
/*   Updated: 2022/11/17 22:09:38 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_H
# define RANDOM_ACCESS_ITERATOR_H
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
		RandomAccessIterator(pointer ptr) : _ptr(ptr) {}
		
		/* Operators */
		reference				operator*() const { return (*_ptr); }
		pointer					operator->() { return (_ptr); }
		RandomAccessIterator&	operator++() { _ptr++; return (*this); }
		RandomAccessIterator	operator++(value_type) { RandomAccessIterator	tmp = *this; _ptr++; return (tmp); }
		RandomAccessIterator&	operator--() { _ptr--; return (*this); }
		RandomAccessIterator	operator--(value_type) { RandomAccessIterator	tmp = *this; _ptr--; return (tmp); }
		friend bool				operator==(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs._ptr == rhs._ptr); }
		friend bool				operator!=(const RandomAccessIterator& lhs, const RandomAccessIterator& rhs) { return (lhs._ptr != rhs._ptr); }
		
};

#endif
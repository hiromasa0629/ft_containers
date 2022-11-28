/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:25:09 by hyap              #+#    #+#             */
/*   Updated: 2022/11/28 17:04:07 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_H
# define ITERATORS_H
# include <iterator>
# include "container.hpp"

namespace ft {

struct random_access_iterator_tag {};

template< class T >
struct iterator_traits {
	typedef typename T::value_type			value_type;
	typedef typename T::difference_type		difference_type;
	typedef typename T::iterator_category	iterator_category;
	typedef typename T::pointer				pointer;
	typedef typename T::reference			reference;
};

template <class T> 
class iterator_traits<T*> {
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef random_access_iterator_tag	iterator_category;
	typedef	T*							pointer;
	typedef T&							reference;
};

template <class T> 
class iterator_traits<const T*> {
	typedef T							value_type;
	typedef ptrdiff_t					difference_type;
	typedef random_access_iterator_tag	iterator_category;
	typedef	const T*					pointer;
	typedef const T&					reference;
};

template<  class Category, class T,  class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
struct IteratorBase {
	typedef T			value_type;
	typedef Distance	difference_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
	typedef Category	iterator_category;
};

template< class T, class Category = ft::random_access_iterator_tag >
struct RandomAccessIterator : public virtual IteratorBase<Category, T>{
	private:
		typename IteratorBase<Category, T>::pointer	_ptr;
	
	public:
		/* Iterator constructor */
		RandomAccessIterator(void) : _ptr(NULL) {}
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) { _ptr = rhs._ptr; return (*this); };
		RandomAccessIterator(typename IteratorBase<Category, T>::pointer ptr) : _ptr(ptr) { /* std::cout << "Iterator construct" << std::endl; */ }
		
		/* Operators */
		typename IteratorBase<Category, T>::reference		operator*(void) const { return (*_ptr); }
		typename IteratorBase<Category, T>::reference		operator[](int n) { return *(_ptr + n); }
		typename IteratorBase<Category, T>::pointer			operator->(void) { return (_ptr); }
		RandomAccessIterator&								operator++(void) { _ptr++; return (*this); }
		RandomAccessIterator								operator++(int) { RandomAccessIterator<T>	tmp = *this; _ptr++; return (tmp); }
		RandomAccessIterator&								operator--(void) { _ptr--; return (*this); }
		RandomAccessIterator								operator--(int) { RandomAccessIterator<T>	tmp = *this; _ptr--; return (tmp); }
		bool												operator==(const RandomAccessIterator<T>& rhs) { return (_ptr == rhs._ptr); }
		bool												operator!=(const RandomAccessIterator<T>& rhs) { return (_ptr != rhs._ptr); }
		bool												operator<(const RandomAccessIterator<T>& rhs) { return (_ptr < rhs._ptr); }
		bool												operator>(const RandomAccessIterator<T>& rhs) { return (_ptr > rhs._ptr); }
		bool												operator<=(const RandomAccessIterator<T>& rhs) { return (_ptr <= rhs._ptr); }
		bool												operator>=(const RandomAccessIterator<T>& rhs) { return (_ptr >= rhs._ptr); }
		RandomAccessIterator&								operator+=(int n) { _ptr += n; return (*this); }
		RandomAccessIterator&								operator-=(int n) { _ptr -= n; return (*this); }
		typename IteratorBase<Category, T>::difference_type	operator-(const RandomAccessIterator<T>& rhs) { return (_ptr - rhs._ptr); };
		typename IteratorBase<Category, T>::difference_type	operator-(const RandomAccessIterator<T>& rhs) const { return (_ptr - rhs._ptr); };
		friend RandomAccessIterator							operator+(int n, const RandomAccessIterator<T>& rhs) { return (RandomAccessIterator<T>(n + rhs._ptr)); }
		friend RandomAccessIterator							operator+(const RandomAccessIterator<T>& lhs, int n) { return (RandomAccessIterator<T>(lhs._ptr + n)); }
		friend RandomAccessIterator							operator-(int n, const RandomAccessIterator<T>& rhs) { return (RandomAccessIterator<T>(n - rhs._ptr)); }
		friend RandomAccessIterator							operator-(const RandomAccessIterator<T>& lhs, int n) { return (RandomAccessIterator<T>(lhs._ptr - n)); }
		
		/* Destructor */
		~RandomAccessIterator(void) {}
};

template< class InputIt >
typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first, InputIt last)
{
	if (last > first)
		return (last - first);
	return (first - last);
}

}

#endif

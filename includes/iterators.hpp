/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterators.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:25:09 by hyap              #+#    #+#             */
/*   Updated: 2022/12/22 19:08:44 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_H
# define ITERATORS_H
# include "container.hpp"

namespace ft {

struct random_access_iterator_tag {};
struct bidirectional_iterator_tag {};

template< class T >
struct iterator_traits
{
	public:
		typedef typename T::value_type			value_type;
		typedef typename T::difference_type		difference_type;
		typedef typename T::iterator_category	iterator_category;
		typedef typename T::pointer				pointer;
		typedef typename T::reference			reference;
};

template <class T>
class iterator_traits<T*>
{
	public:
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef	T*							pointer;
		typedef T&							reference;
};

template <class T>
class iterator_traits<const T*>
{
	public:
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef random_access_iterator_tag	iterator_category;
		typedef	const T*					pointer;
		typedef const T&					reference;
};

template<  class Category, class T,  class Distance = ptrdiff_t, class Pointer = T*, class Reference = T& >
struct IteratorBase
{
	public:
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
};

template< class T, class Category = ft::random_access_iterator_tag >
struct RandomAccessIterator : public virtual IteratorBase<Category, T>
{
	private:
		typename IteratorBase<Category, T>::pointer	_ptr;

	public:
		/* Iterator constructor */
		RandomAccessIterator(void) : _ptr(NULL) {}
		RandomAccessIterator(typename IteratorBase<Category, T>::pointer ptr) : _ptr(ptr) { /* std::cout << "Iterator construct" << std::endl; */ }
		RandomAccessIterator(const RandomAccessIterator& it) : _ptr(it._ptr) {}
		RandomAccessIterator&	operator=(const RandomAccessIterator& rhs) { _ptr = rhs.base(); return (*this); };

		operator	RandomAccessIterator<const T>(void) const { return (RandomAccessIterator<const T>(_ptr)); }

		typename IteratorBase<Category, T>::pointer			base(void) const { return (_ptr); }
		/* Operators */
		typename IteratorBase<Category, T>::reference		operator*(void) const { return (*_ptr); }
		typename IteratorBase<Category, T>::reference		operator[](size_t n) { return *(_ptr + n); }
		typename IteratorBase<Category, T>::pointer			operator->(void) { return (_ptr); }
		RandomAccessIterator&								operator++(void) { _ptr++; return (*this); }
		RandomAccessIterator								operator++(int) { RandomAccessIterator<T>	tmp = *this; _ptr++; return (tmp); }
		RandomAccessIterator&								operator--(void) { _ptr--; return (*this); }
		RandomAccessIterator								operator--(int) { RandomAccessIterator<T>	tmp = *this; _ptr--; return (tmp); }

		bool												operator==(const RandomAccessIterator& rhs) const { return (_ptr == rhs._ptr); }
		bool												operator!=(const RandomAccessIterator& rhs) const { return (_ptr != rhs._ptr); }
		bool												operator< (const RandomAccessIterator& rhs) const { return (_ptr < rhs._ptr); }
		bool												operator> (const RandomAccessIterator& rhs) const { return (_ptr > rhs._ptr); }
		bool												operator<=(const RandomAccessIterator& rhs) const { return (_ptr <= rhs._ptr); }
		bool												operator>=(const RandomAccessIterator& rhs) const { return (_ptr >= rhs._ptr); }


		RandomAccessIterator&								operator+=(int n) { _ptr += n; return (*this); }
		RandomAccessIterator&								operator-=(int n) { _ptr -= n; return (*this); }
		typename IteratorBase<Category, T>::difference_type	operator-(const RandomAccessIterator& rhs) { return (_ptr - rhs._ptr); };
		typename IteratorBase<Category, T>::difference_type	operator-(const RandomAccessIterator& rhs) const { return (_ptr - rhs._ptr); };
		friend RandomAccessIterator							operator+(int n, const RandomAccessIterator& rhs) { return (RandomAccessIterator<T>(n + rhs._ptr)); }
		friend RandomAccessIterator							operator+(const RandomAccessIterator& lhs, int n) { return (RandomAccessIterator<T>(lhs._ptr + n)); }
		friend RandomAccessIterator							operator-(int n, const RandomAccessIterator& rhs) { return (RandomAccessIterator<T>(n - rhs._ptr)); }
		friend RandomAccessIterator							operator-(const RandomAccessIterator& lhs, int n) { return (RandomAccessIterator<T>(lhs._ptr - n)); }

		/* Destructor */
		~RandomAccessIterator(void) {}
};

/* ============================ Const iterators ============================ */

template < typename T, typename U > bool		operator==(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() == rhs.base()); }
template < typename T, typename U > bool		operator!=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() != rhs.base()); }
template < typename T, typename U > bool		operator< (const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() <  rhs.base()); }
template < typename T, typename U > bool		operator> (const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() >  rhs.base()); }
template < typename T, typename U > bool		operator<=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() <= rhs.base()); }
template < typename T, typename U > bool		operator>=(const RandomAccessIterator<T>& lhs, const RandomAccessIterator<U>& rhs) { return (lhs.base() >= rhs.base()); }

template < class T, class Category = ft::bidirectional_iterator_tag >
struct BidirectionalIterator : public virtual IteratorBase<Category, T>
{
	typedef T																value_type;
	typedef typename IteratorBase<Category, const value_type>::reference	const_value_reference;
	typedef typename IteratorBase<Category, const value_type>::pointer		const_value_pointer;
	typedef ft::RBTNode<value_type>											node_type;
	typedef ft::RBTNode<const value_type>									const_node_type;
	typedef typename IteratorBase<Category, node_type>::pointer				node_pointer;
	typedef typename IteratorBase<Category, const_node_type>::pointer		const_node_pointer;
	typedef typename IteratorBase<Category, value_type>::reference			value_reference;
	typedef typename IteratorBase<Category, value_type>::pointer			value_pointer;

	private:
		node_pointer	_ptr;

	public:
		BidirectionalIterator(void) : _ptr(NULL) {}
		BidirectionalIterator(node_pointer ptr) : _ptr(ptr) {}
		BidirectionalIterator&	operator=(const BidirectionalIterator& rhs) { _ptr = rhs._ptr; return (*this); }

		operator	BidirectionalIterator<const value_type>(void) { return (BidirectionalIterator<const value_type>(reinterpret_cast<const_node_pointer>(_ptr))); }

		bool													operator==(const BidirectionalIterator& rhs) const { return (_ptr == rhs._ptr); }
		bool													operator!=(const BidirectionalIterator& rhs) const { return (_ptr != rhs._ptr); }
		value_reference			operator*(void) { return (*(_ptr->content)); }
		const_value_pointer		operator->(void) const { return (_ptr->content); }
		value_pointer			operator->(void) { return (_ptr->content); }
		const_value_reference	operator*(void) const { return (*(_ptr->content)); }
		BidirectionalIterator									operator++(int)
		{
			BidirectionalIterator	it = *this;

			_ptr = _ptr->node_find_nextgreater();
			return (it);
		}
		BidirectionalIterator&									operator++(void) { this->operator++(1); return (*this); }
		BidirectionalIterator									operator--(int)
		{
			BidirectionalIterator	it = *this;

			_ptr = _ptr->node_find_nextlesser();
			return (it);
		}
		BidirectionalIterator&									operator--(void) { this->operator--(1); return (*this); }

		node_pointer	get_ptr(void) const	 { return (_ptr); }
};

template < class Iter >
class reverse_iterator
{
	public:
		typedef Iter													iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

		/* Default constructor */
		reverse_iterator(void) : _current(NULL) {};

		/* Initialization constructor */
		explicit reverse_iterator(iterator_type x) : _current(x) {};

		/* Copy constructor */
		template < class U >
		reverse_iterator(const reverse_iterator<U>& rev_it) : _current(rev_it.base()) {};

		/* Copy assignment */
		template < class U >
		reverse_iterator&	operator=(const reverse_iterator<U>& other) { _current = other.base(); return (*this); }

		/* Returns a copy of the base iterator */
		iterator_type	base(void) const { return(iterator_type(_current)); }

		reference			operator*(void) const { iterator_type tmp = _current; return (*(--tmp)); }
		reverse_iterator	operator+(difference_type n) const { return (reverse_iterator(_current - n)); }
		reverse_iterator	operator-(difference_type n) const { return (reverse_iterator(_current + n)); }
		reverse_iterator&	operator++(void) { _current--; return (*this); }
		reverse_iterator	operator++(int) { iterator_type tmp = _current; _current--; return (reverse_iterator(tmp)); }
		reverse_iterator&	operator+=(difference_type n) { _current -= n; return (*this); }
		reverse_iterator&	operator--(void) { _current++; return (*this); }
		reverse_iterator	operator--(int) { iterator_type tmp = _current; _current++; return (reverse_iterator(tmp)); }
		reverse_iterator&	operator-=(difference_type n) { _current += n; return (*this); }
		pointer				operator->(void) const { return (&(operator*())); }
		pointer				operator->(void) { return (&(operator*())); }
		reference			operator[](difference_type n) const { return *(_current - n - 1); }

		bool	operator==(const reverse_iterator& rhs) const { return (_current == rhs.base()); }
		bool	operator!=(const reverse_iterator& rhs) const { return (_current != rhs.base()); }
		bool	operator<(const reverse_iterator& rhs) const { return (_current > rhs.base()); }
		bool	operator<=(const reverse_iterator& rhs) const { return (_current >= rhs.base()); }
		bool	operator>(const reverse_iterator& rhs) const { return (_current < rhs.base()); }
		bool	operator>=(const reverse_iterator& rhs) const { return (_current <= rhs.base()); }

		difference_type	operator-(const reverse_iterator& rhs) { return (rhs._current - _current); }
		friend reverse_iterator		operator+(difference_type n, const reverse_iterator& rev_it) { return (reverse_iterator(rev_it + n)); }

	protected:
		iterator_type	_current;
};

/* ============================ Const reverse_iterators ============================ */

template < typename T, typename U > bool		operator==(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() == rhs.base()); }
template < typename T, typename U > bool		operator!=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() != rhs.base()); }
template < typename T, typename U > bool		operator< (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() >  rhs.base()); }
template < typename T, typename U > bool		operator> (const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() <  rhs.base()); }
template < typename T, typename U > bool		operator<=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() >= rhs.base()); }
template < typename T, typename U > bool		operator>=(const reverse_iterator<T>& lhs, const reverse_iterator<U>& rhs) { return (lhs.base() <= rhs.base()); }

template< class InputIt >
typename ft::iterator_traits<InputIt>::difference_type	distance(InputIt first, InputIt last)
{
	typename ft::iterator_traits<InputIt>::difference_type	d;
	InputIt													tmp;

	d = 0;
	tmp = first;
	for (; tmp != last; tmp++)
		d++;
	return (d);
}

}

#endif

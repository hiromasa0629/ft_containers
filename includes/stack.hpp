/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:42:13 by hyap              #+#    #+#             */
/*   Updated: 2022/12/10 21:08:22 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "container.hpp"
# include "vector.hpp"

namespace ft {
	
template < class T, class Container = ft::Vector<T> >
class Stack 
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		/* Default constructor */
		explicit Stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
		~Stack(void) { _c.clear(); }
		
		bool							empty(void) const { return (_c.empty()); }			/* Returns whether thestack is empty */
		size_type						size(void) const { return (_c.size()); }			/* Returns the number of elements in the stack */	
		value_type&						top(void) { return (_c.back()); }					/* Returns a reference to the top element in the stack */
		const value_type&				top(void) const { return (_c.back()); }				/* Returns a const reference to the top element in the stack */
		void							push(const value_type& val) { _c.push_back(val); }	/* Inserts a new element above its current top element */
		void							pop(void) { _c.pop_back(); }						/* Removes the top element */

	private:
		container_type	_c;
};

template < class T, class Container > bool	operator==(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c == rhs._c); }
template < class T, class Container > bool	operator!=(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c != rhs._c); }
template < class T, class Container > bool	operator>(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c > rhs._c); }
template < class T, class Container > bool	operator>=(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c >= rhs._c); }
template < class T, class Container > bool	operator<(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c < rhs._c); }
template < class T, class Container > bool	operator<=(const ft::Stack<T, Container>& lhs, const ft::Stack<T, Container>& rhs) { return (lhs._c <= rhs._c); }

}

#endif

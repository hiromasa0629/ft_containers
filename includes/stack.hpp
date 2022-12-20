/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:42:13 by hyap              #+#    #+#             */
/*   Updated: 2022/12/20 20:41:48 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H
# include "container.hpp"
# include "vector.hpp"

namespace ft {

template < class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		/* Default constructor */
		explicit stack(const container_type& ctnr = container_type()) : _c(ctnr) {}
		stack&	operator=(const stack& other) { _c = other._c; return (*this); }
		~stack(void) { _c.clear(); }

		bool							empty(void) const { return (_c.empty()); }			/* Returns whether thestack is empty */
		size_type						size(void) const { return (_c.size()); }			/* Returns the number of elements in the stack */
		value_type&						top(void) { return (_c.back()); }					/* Returns a reference to the top element in the stack */
		const value_type&				top(void) const { return (_c.back()); }				/* Returns a const reference to the top element in the stack */
		void							push(const value_type& val) { _c.push_back(val); }	/* Inserts a new element above its current top element */
		void							pop(void) { _c.pop_back(); }						/* Removes the top element */

		bool	operator==(const stack& rhs) const { return (_c == rhs._c); }
		bool	operator!=(const stack& rhs) const { return (_c != rhs._c); }
		bool	operator>(const stack& rhs) const { return (_c > rhs._c); }
		bool	operator>=(const stack& rhs) const { return (_c >= rhs._c); }
		bool	operator<(const stack& rhs) const { return (_c < rhs._c); }
		bool	operator<=(const stack& rhs) const { return (_c <= rhs._c); }

	private:
		container_type	_c;
};


}

#endif

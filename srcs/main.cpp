/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyap <hyap@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 14:12:04 by hyap              #+#    #+#             */
/*   Updated: 2022/11/25 19:36:41 by hyap             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "vector.hpp"
// #include <vector>
# include <iostream>
# include <vector>

int	main(void)
{
	// ft::vector<int>	intv(5, 10);
	
	// std::cout << intv[2] << std::endl;
	// std::cout << "int: " << ft::is_integral<int>::value << std::endl;

	std::vector<int>	vec(5, 100);
	std::vector<int>::iterator	it;
	
	it = vec.begin();
	std::cout << it[3] << std::endl;

	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:19:46 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/02 19:46:48 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter.hpp"
int main(void) {
	std::string s[4] = { "jinyoo", "soo", "gshim", "jinkim2" };
	int i[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	float f[9] = { 0.0f, 1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f, 7.7f, 8.8f };
	char c[6] = { 'a', 'b', 'c', 'd', 'e', 'f' };

	std::cout << "String" << std::endl;
	iter(s, sizeof(s) / sizeof(*s), ft_print);
	std::cout << std::endl;
	std::cout << "Int" << std::endl;
	iter(i, sizeof(i) / sizeof(*i), ft_print);
	std::cout << std::endl;
	std::cout << "float" << std::endl;
	iter(f, sizeof(f) / sizeof(*f), ft_print);
	std::cout << std::endl;
	std::cout << "Char" << std::endl;
	iter(c, sizeof(c) / sizeof(*c), ft_print);
	std::cout << std::endl;
	return 0;
}
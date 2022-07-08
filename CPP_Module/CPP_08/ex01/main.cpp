/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:05:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/08 20:40:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <ostream>
#include <vector>

int main()
{
	Span sp = Span(11);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	Span ps(14);

	ps = sp;
	
	try {
		std::cout << "[sp]\n";
		std::cout << "Shortest Span : " << sp.shortestSpan() << std::endl;
		std::cout << "Longest Span : " << sp.longestSpan() << std::endl;
	
		std::cout << std::endl;

		std::vector<int> ps_copy = ps.getData();
		sp.addRange(ps_copy.begin(), ps_copy.end());
		std::vector<int> sp_cpy = sp.getData();
		for (std::vector<int>::iterator iter = sp_cpy.begin(); iter != sp_cpy.end();iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;

		std::cout << std::endl;

		std::cout << "Shortest Span : " << sp.shortestSpan() << std::endl;
		std::cout << "Longest Span : " << sp.longestSpan() << std::endl;

		std::cout << "\n[ps]\n";
		std::cout << "Shortest Span : " << ps.shortestSpan() << std::endl;
		std::cout << "Longest Span : " << ps.longestSpan() << std::endl;
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

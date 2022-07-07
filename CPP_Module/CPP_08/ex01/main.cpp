/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:05:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/07 17:44:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"
#include <iostream>
#include <ostream>

int main()
{
	Span sp = Span(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	Span ps(7);

	ps = sp;
	try {
		std::cout << "[sp]\n";
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;

		std::cout << "\n[ps]\n";
		std::cout << ps.shortestSpan() << std::endl;
		std::cout << ps.longestSpan() << std::endl;
	} catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
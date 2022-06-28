/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:50:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 16:20:21 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	try
	{
		Bureaucrat A("jinyoo", 10);
		Bureaucrat B("soo", 150);

		std::cout << std::endl;

		std::cout << A << std::endl;
		std::cout << B << std::endl;
		std::cout << std::endl;

		A.incre_grade(9);
		// A.incre_grade(10);
		// B.decre_grade(1);

		std::cout << std::endl;

		std::cout << A << std::endl;
		std::cout << B << std::endl;
		std::cout << std::endl;

	}
	catch (std::exception &e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}
	return 0;
}
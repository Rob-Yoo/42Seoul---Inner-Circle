/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 20:21:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 16:21:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

int	main(void)
{
	try
	{
		Bureaucrat a("jinyoo", 6);
		Form f1("Report", 5, 5);
		// Form f1("Report", 151, 5);

		std::cout << std::endl;

		std::cout << a << std::endl;
		std::cout << f1 << std::endl;

		a.signForm(f1);
		std::cout << std::endl;

		a.incre_grade(1);
		a.signForm(f1);
		std::cout << std::endl;

		std::cout << a << std::endl;
		std::cout << f1 << std::endl;
		std::cout << std::endl;

	}
	catch (std::exception &e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}
	return 0;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:00:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/26 21:00:52 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat a("jinyoo", 6);
		Form f1("Report", 5, 5);
		// Form f1("Report", 151, 5);

		std::cout << std::endl;

		//표준출력
		std::cout << a << std::endl;
		std::cout << f1 << std::endl;

		a.signForm(f1);
		std::cout << std::endl;

		a.incre_grade(1);
		a.signForm(f1);
		std::cout << std::endl;

		//표준출력
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:00:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 14:46:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <exception>

int	main(void) {
	Bureaucrat b1("Boss", 1);
	Bureaucrat b2("jinyoo", 15);
	Bureaucrat b3("soo", 70);
	Bureaucrat b4("gshim", 140);

	std::cout << std::endl;

	Form *f1 = new PresidentialPardonForm("Presidential");
	Form *f2 = new RobotomyRequestForm("Roboto");
	Form *f3 = new ShrubberyCreationForm("Shrubbery");

	std::cout << std::endl;

	std::cout << b1 << std::endl << b2 << std::endl << b3 << std::endl << b4 << std::endl;

	std::cout << std::endl;

	std::cout << *f1 << std::endl << *f2 << std::endl << *f3 << std::endl;

	std::cout << std::endl;

	b2.signForm(*f1);
	b3.signForm(*f2);
	b4.signForm(*f3);

	std::cout << std::endl;

	b2.executeForm(*f1);
	b3.executeForm(*f2);
	b4.executeForm(*f3);

	std::cout << std::endl;

	b1.executeForm(*f1);
	b1.executeForm(*f2);
	b1.executeForm(*f3);

	std::cout << std::endl;

	delete f3;
	delete f2;
	delete f1;
	return 0;
}
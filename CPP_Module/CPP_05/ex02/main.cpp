/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:00:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:55:43 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.cpp"
#include "RobotomyRequestForm.cpp"
#include "PresidentialPardonForm.cpp"

int	main(void)
{
	try
	{
		Bureaucrat jinyoo("jinyoo", 1);
		PresidentialPardonForm p("Presidential");
		RobotomyRequestForm r("Roboto");
		ShrubberyCreationForm s("Shrubbery");
		std::cout << std::endl;

		std::cout << jinyoo << std::endl;
		std::cout << p << std::endl;
		std::cout << r << std::endl;
		std::cout << s << std::endl;
		std::cout << std::endl;


		jinyoo.signForm(p);
		std::cout << std::endl;

		jinyoo.incre_grade(1);
		jinyoo.signForm(p);

		//jinyoo.executeForm(r);
		jinyoo.executeForm(p);
		std::cout << std::endl;

		std::cout << jinyoo << std::endl;
		std::cout << p << std::endl;
		std::cout << std::endl;

	}
	catch (std::exception &e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}
	return 0;
}


// int	main(void) {
// 	Bureaucrat b1("Admin", 1);
// 	Bureaucrat b2("Jseo", 15);
// 	Bureaucrat b3("Dohykim", 70);
// 	Bureaucrat b4("Hyson", 140);

// 	std::cout << std::endl;

// 	Form *f1 = new PresidentialPardonForm("Chang Chen");
// 	Form *f2 = new RobotomyRequestForm("Terminator");
// 	Form *f3 = new ShrubberyCreationForm("Fangorn");

// 	std::cout << std::endl;

// 	std::cout << b1 << std::endl << b2 << std::endl << b3 << std::endl << b4 << std::endl;

// 	std::cout << std::endl;

// 	std::cout << *f1 << std::endl << *f2 << std::endl << *f3 << std::endl;

// 	std::cout << std::endl;

// 	b2.signForm(*f1);
// 	b3.signForm(*f2);
// 	b4.signForm(*f3);

// 	std::cout << std::endl;

// 	b2.executeForm(*f1);
// 	b3.executeForm(*f2);
// 	b4.executeForm(*f3);

// 	std::cout << std::endl;

// 	b1.executeForm(*f1);
// 	b1.executeForm(*f2);
// 	b1.executeForm(*f3);

// 	std::cout << std::endl;

// 	delete f3;
// 	delete f2;
// 	delete f1;
// 	return 0;
// }
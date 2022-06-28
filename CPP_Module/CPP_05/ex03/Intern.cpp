/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 15:46:18 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 16:13:29 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

const char* Intern::NoMatchingTypeException::what(void) const throw() {
	return "Form Name Does Not Exist!";
}

Intern::Intern(void) {}

Intern::~Intern(void) {}

Intern&	Intern::operator=(Intern const &src) { (void)src; return (*this); }

Intern::Intern(Intern const &src) { (void)src; }

Form* Intern::makeForm(std::string const &name, std::string const &target) {
	std::string form_names[3] = { "presidential pardon", "robotomy request", "shrubbery creation" };
	
	try {
		for (int i = 0 ; i < 3 ; ++i) {
			if (form_names[i] == name) {
				std::cout << "Intern creates " << name << std::endl;
				switch (i) {
					case 0:
						return new PresidentialPardonForm(target);
					case 1:
						return new RobotomyRequestForm(target);
					case 2:
						return new ShrubberyCreationForm(target);
					default:
    					break;
				}
			}
		}
		throw NoMatchingTypeException();
	} catch (std::exception& e) {
		std::cerr << "Intern cannot create " << name << " because " << e.what() << std::endl;
		return NULL;
	}
}
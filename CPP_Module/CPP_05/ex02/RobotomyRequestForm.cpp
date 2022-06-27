/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:20 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:42:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(void): Form() {}

RobotomyRequestForm::~RobotomyRequestForm(void) { std::cout << "RobotomyRequestForm Destructor called" << std::endl; }

RobotomyRequestForm::RobotomyRequestForm(std::string target)
	: Form(target, 72, 45)
{
	std::cout << "RobotomyRequestForm Constructor called" << std::endl;
}

RobotomyRequestForm&	RobotomyRequestForm::operator=(RobotomyRequestForm const &src) {
	(void)src;
	return (*this);
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src): Form(src) {
	std::cout << "RobotomyRequestForm Copy Constructor called" << std::endl;
}

void	RobotomyRequestForm::execute(Bureaucrat const &executor) const {
	executable(executor);
	std::srand(std::time(nullptr));
	int success = std::rand() % 2;
	if (success)
		std::cout << getName() << " has been robotomized successfully" << std::endl;
	else
		std::cout << "The robotomy failed" << std::endl;
}
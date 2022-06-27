/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:42:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(void): Form() {}

PresidentialPardonForm::~PresidentialPardonForm(void) { std::cout << "PresidentialPardonForm Destructor called" << std::endl; }

PresidentialPardonForm::PresidentialPardonForm(std::string target)
	: Form(target, 25, 5)
{
	std::cout << "PresidentialPardonForm Constructor called" << std::endl;
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(PresidentialPardonForm const &src) {
	(void)src;
	return (*this);
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src): Form(src) {
	std::cout << "PresidentialPardonForm Copy Constructor called" << std::endl;
}

void	PresidentialPardonForm::execute(Bureaucrat const &executor) const {
	executable(executor);
	std::cout << getName() << " has been pardoned by Zafod Beeblebrox" << std::endl;
}

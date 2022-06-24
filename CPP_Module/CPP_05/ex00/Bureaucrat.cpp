/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:06:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/24 15:59:33 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(void) {}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name) {
	std::cout << "Bureaucrat Constructor called" << std::endl;

	if (grade >= 1 && grade <= 150)
		this->_grade = grade;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Bureaucrat Destructor called" << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src): _name(src.getName()), _grade(src.getGrade()) {}

Bureaucrat&	Bureaucrat::operator=(Bureaucrat const &src) {
	return *this;
}

std::string	Bureaucrat::getName(void) const {
	return this->_name;
}

int	Bureaucrat::getGrade(void) const {
	return this->_grade;
}

void	Bureaucrat::incre_grade(void) {
	if (this->_grade - 1 >= 1)
		this->_grade--;
}

void	Bureaucrat::decre_grade(void) {
	if (this->_grade + 1 <= 150)
		this->_grade++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:06:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/25 21:06:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include <ostream>

Bureaucrat::Bureaucrat(void) {}

const char* Bureaucrat::GradeTooHighException::what(void) const throw() {
	return "Bureaucrat Grade Too High";
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw() {
	return "Bureaucrat Grade Too Low";
}

Bureaucrat::Bureaucrat(std::string name, int grade)
	throw (GradeTooHighException, GradeTooLowException)
	: _name(name)
{
	std::cout << "Bureaucrat Constructor called" << std::endl;

	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
	this->_grade = grade;
}

Bureaucrat::~Bureaucrat(void) {
	std::cout << "Bureaucrat Destructor called" << std::endl;
}

Bureaucrat::Bureaucrat(Bureaucrat const &src)
	throw (GradeTooHighException, GradeTooLowException)
	: _name(src.getName())
{
	std::cout << "Bureaucrat Copy Constructor called" << std::endl;
	int	src_grade = src.getGrade();

	if (src_grade < 1)
		throw GradeTooHighException();
	if (src_grade > 150)
		throw GradeTooLowException();
	this->_grade = src_grade;
}

Bureaucrat&	Bureaucrat::operator=(Bureaucrat const &src) {
	if (this != &src)
		this->_grade = src._grade;
	return *this;
}

std::string	Bureaucrat::getName(void) const {
	return this->_name;
}

int	Bureaucrat::getGrade(void) const {
	return this->_grade;
}

void	Bureaucrat::incre_grade(int grade)
	throw (GradeTooHighException, GradeTooLowException)
{
	if (this->_grade - grade < 1)
		throw GradeTooHighException();
	this->_grade -= grade;

}

void	Bureaucrat::decre_grade(int grade)
	throw (GradeTooHighException, GradeTooLowException)
{
	if (this->_grade + grade > 150)
		throw GradeTooLowException();
	this->_grade += grade;
}

std::ostream&	operator<<(std::ostream& out, Bureaucrat const &bur) {
	out << bur.getName() << " bureaucrat grade "
          << bur.getGrade() << ".";
	return out;
}

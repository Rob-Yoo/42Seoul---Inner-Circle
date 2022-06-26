/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:00:33 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/26 21:00:34 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

const char* Form::GradeTooHighException::what(void) const throw() {
	return "Form Grade Too High";
}

const char* Form::GradeTooLowException::what(void) const throw() {
	return "Form Grade Too Low";
}

Form::Form(void): _sign_grade(0), _exec_grade(0) {}

Form::~Form(void) { std::cout << "Form Destructor called" << std::endl; }

Form::Form(std::string name, int sign_grade, int exec_grade)
	throw(GradeTooHighException, GradeTooLowException)
	: _name(name), _sign_grade(sign_grade), _exec_grade(exec_grade), _is_signed(false)
{
	std::cout << "Form Constructor called" << std::endl;
	if (_sign_grade < 1 || _exec_grade < 1)
		throw GradeTooHighException();
	if (_sign_grade > 150 || _exec_grade > 150)
		throw GradeTooLowException();
}


Form::Form(Form const &src)
	throw(GradeTooHighException, GradeTooLowException)
	: _name(src.getName()), _sign_grade(src.getSignGrade()), _exec_grade(src.getExecGrade()), _is_signed(src.getSigned())
{
	std::cout << "Form Copy Constructor called" << std::endl;
	if (_sign_grade < 1 || _exec_grade < 1)
		throw GradeTooHighException();
	if (_sign_grade > 150 || _exec_grade > 150)
		throw GradeTooLowException();
}

Form& Form::operator=(Form const &src) {
	if (this != &src)
		this->_is_signed = src.getSigned();
	return *this;
}

std::string Form::getName(void) const {
	return this->_name;
}

int Form::getSignGrade(void) const {
	return this->_sign_grade;
}

int Form::getExecGrade(void) const {
	return this->_exec_grade;
}

bool Form::getSigned(void) const {
	return this->_is_signed;
}

void Form::beSigned(Bureaucrat const &bur) throw(GradeTooLowException) {
	if (bur.getGrade() <= this->_sign_grade)
		this->_is_signed = true;
	else
		throw GradeTooLowException();
}

std::ostream&	operator<<(std::ostream& out, Form const &form) {
	out << "Name: " << form.getName() << std::endl
	<< "Sign grade: " << form.getSignGrade() << std::endl
	<< "Execute grade: " << form.getExecGrade() << std::endl
	<< "Is Signed: " << std::boolalpha << form.getSigned() << std::endl;
	return out;
}
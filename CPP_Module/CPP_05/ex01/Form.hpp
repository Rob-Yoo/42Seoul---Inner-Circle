/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 19:20:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 01:31:41 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include <string>
# include <exception>
# include "Bureaucrat.hpp"

class Form {
public:
	class GradeTooHighException: public std::exception {
	public:
		const char* what() const throw();
	};

	class GradeTooLowException: public std::exception {
	public:
		const char* what() const throw();
	};

	Form(std::string name, int sign_grade, int exec_grade) throw(GradeTooHighException, GradeTooLowException);
	virtual ~Form(void);
	Form(Form const &src) throw(GradeTooHighException, GradeTooLowException);

	Form& operator=(Form const &src);

	std::string getName(void) const;
	int getSignGrade(void) const;
	int getExecGrade(void) const;
	bool getSigned(void) const;

	void beSigned(Bureaucrat const &bur) throw(GradeTooLowException);
private:
	const std::string	_name;
	const int			_sign_grade;
	const int			_exec_grade;
	bool				_is_signed;
	
	Form(void);
};

std::ostream&	operator<<(std::ostream& out, Form const &form);

#endif

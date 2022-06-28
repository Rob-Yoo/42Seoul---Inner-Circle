/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:00:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 14:12:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# include "Bureaucrat.hpp"

class Form {
public:
	class GradeTooHighException: public std::exception {
	public:
		const char* what(void) const throw();
	};
	class GradeTooLowException: public std::exception {
	public:
		const char* what(void) const throw();
	};
	class DoesNotSignedException: public std::exception {
	public:
		const char* what(void) const throw();
	};
	class CanNotCreateFileException: public std::exception {
	public:
		const char* what(void) const throw();
	};

	Form(void);
	Form(std::string name, int sign_grade, int exec_grade) throw(GradeTooHighException, GradeTooLowException);
	virtual ~Form(void);
	Form(Form const &src) throw(GradeTooHighException, GradeTooLowException);

	Form& operator=(Form const &src);

	std::string	getName(void) const;
	int	getSignGrade(void) const;
	int	getExecGrade(void) const;
	bool	getSigned(void) const;

	void	beSigned(Bureaucrat const &bur) throw(GradeTooLowException);
	void	executable(const Bureaucrat& bur) const throw(DoesNotSignedException, GradeTooLowException);
	virtual void	execute(Bureaucrat const &executor) const = 0;
private:
	const std::string	_name;
	const int			_sign_grade;
	const int			_exec_grade;
	bool				_is_signed;
};

std::ostream&	operator<<(std::ostream& out, Form const &form);

#endif

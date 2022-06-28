/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:05:15 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 14:44:21 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <exception>
# include <string>

class Bureaucrat {
public:
	class GradeTooHighException: public std::exception {
	public:
		const char* what() const throw();
	};

	class GradeTooLowException: public std::exception {
	public:
		const char* what() const throw();
	};
	Bureaucrat(std::string name, int grade) throw(GradeTooHighException, GradeTooLowException);
	virtual ~Bureaucrat(void);
	Bureaucrat(Bureaucrat const &src) throw(GradeTooHighException, GradeTooLowException);

	Bureaucrat&	operator=(Bureaucrat const &src);

	std::string	getName(void) const;
	int			getGrade(void) const;
	void		incre_grade(int grade) throw(GradeTooHighException);
	void		decre_grade(int grade) throw(GradeTooLowException);
private:
	const std::string	_name;
	int					_grade;
	Bureaucrat(void);
};

std::ostream&	operator<<(std::ostream& ost, Bureaucrat const &bur);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 14:54:22 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/28 16:12:05 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"

class Intern {
public:
	class NoMatchingTypeException: public std::exception {
	public:
		const char* what(void) const throw();
	};

	Intern(void);
	virtual	~Intern(void);
	Intern&	operator=(Intern const &src);
	Intern(Intern const &src);

	Form*	makeForm(std::string const &name, std::string const &target);
};

#endif

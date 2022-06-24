/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:05:15 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/24 15:15:55 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

# include <iostream>
# include <string>

class Bureaucrat {
public:
	Bureaucrat(void);
	Bureaucrat(std::string name, int grade);
	virtual ~Bureaucrat(void);
	Bureaucrat(Bureaucrat const &src);

	Bureaucrat&	operator=(Bureaucrat const &src);

	std::string	getName(void) const;
	int			getGrade(void) const;
	void		incre_grade(void);
	void		decre_grade(void);
private:
	const std::string	_name;
	int					_grade;
};

std::ostream&	operator<<(std::ostream& ost, Bureaucrat const &bur);

#endif
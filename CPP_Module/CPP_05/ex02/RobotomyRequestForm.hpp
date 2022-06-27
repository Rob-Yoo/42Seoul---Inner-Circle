/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:48:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROBOT_MY_REQUEST_FORM_HPP
# define ROBOT_MY_REQUEST_FORM_HPP

# include "Form.hpp"
# include <cstdlib>

class RobotomyRequestForm: public Form {
public:
	RobotomyRequestForm(std::string target);
	~RobotomyRequestForm(void);
	RobotomyRequestForm(RobotomyRequestForm const &src);

	RobotomyRequestForm&	operator=(RobotomyRequestForm const &src);

	void	execute(Bureaucrat const &executor) const;
private:
	RobotomyRequestForm(void);
};

#endif

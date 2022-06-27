/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.hpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:29 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:48:22 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHRUBBERY_CREATION_FORM_HPP
# define SHRUBBERY_CREATION_FORM_HPP

# include <fstream>
# include "Form.hpp"

class ShrubberyCreationForm: public Form {
public:
	ShrubberyCreationForm(std::string target);
	~ShrubberyCreationForm(void);
	ShrubberyCreationForm(ShrubberyCreationForm const &src);

	ShrubberyCreationForm&	operator=(ShrubberyCreationForm const &src);

	void	execute(Bureaucrat const &executor) const throw(CanNotCreateFileException);
private:
	ShrubberyCreationForm(void);
};

#endif

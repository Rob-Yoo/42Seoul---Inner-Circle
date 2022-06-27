/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PresidentialPardonForm.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:15 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 15:51:01 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRESIDENTIAL_PARDON_FORM_HPP
# define PRESIDENTIAL_PARDON_FORM_HPP

# include "Form.hpp"

class PresidentialPardonForm: public Form {
public:
	PresidentialPardonForm(std::string target);
	~PresidentialPardonForm(void);
	PresidentialPardonForm(PresidentialPardonForm const &src);

	PresidentialPardonForm&	operator=(PresidentialPardonForm const &src);

	void	execute(Bureaucrat const &executor) const;
private:
	PresidentialPardonForm(void);
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 21:01:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/27 19:42:57 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(void): Form() {}

ShrubberyCreationForm::~ShrubberyCreationForm(void) { std::cout << "ShrubberyCreationForm Destructor called" << std::endl; }

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
	: Form(target, 145, 137)
{
	std::cout << "ShrubberyCreationForm Constructor called" << std::endl;
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(ShrubberyCreationForm const &src) {
	(void)src;
	return (*this);
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &src): Form(src) {
	std::cout << "ShrubberyCreationForm Copy Constructor called" << std::endl;
}

void	ShrubberyCreationForm::execute(Bureaucrat const &executor) const
	throw(CanNotCreateFileException)
{
	executable(executor);
	std::ofstream	out(getName() + "_shrubbery");
	if (!out.good())
		throw CanNotCreateFileException();
	std::string	shrubbery = "	oxoxoo    ooxoo\n"
							"  ooxoxo oo  oxoxooo\n"
							" oooo xxoxoo ooo ooox\n"
							" oxo o oxoxo  xoxxoxo\n"
							" oxo xooxoooo o ooo\n"
							"   ooo\\oo\\  /o/o\n"
							"       \\  \\/ /\n"
							"        |   /\n"
							"        |  |\n"
							"        | D|\n"
							"        |  |\n"
							"        |  |\n"
							" ______/____\\____\n";
	out << shrubbery;
	out.close();
}

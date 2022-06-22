/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:45:49 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat(void) {
	std::cout << "WrongCat Default Constructor called" << std::endl;
	this->type = "WrongCat";
}

WrongCat::~WrongCat(void) {
	std::cout << "WrongCat Destructor called" << std::endl;
}

WrongCat::WrongCat(WrongCat const &src) {
	std::cout << "WrongCat Copy Constructor called" << std::endl;
	*this = src;
}

WrongCat&	WrongCat::operator=(WrongCat const &src) {
	if (this != &src)
		this->type = src.type;
	return *this;
}

void	WrongCat::makeSound(void) const {
	std::cout << "Meow~~" << std::endl;
}

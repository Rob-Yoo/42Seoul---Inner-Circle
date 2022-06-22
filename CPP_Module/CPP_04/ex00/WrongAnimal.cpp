/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:43:26 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:44:32 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void): type("Default"){
	std::cout << "WrongAnimal Default Constructor called" << std::endl;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "WrongAnimal Destructor called" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal const &src) {
	std::cout << "WrongAnimal Copy Constructor called" << std::endl;
	*this = src;
}

WrongAnimal&	WrongAnimal::operator=(WrongAnimal const &src) {
	if (this != &src)
		this->type = src.type;
	return *this;
}

void	WrongAnimal::makeSound(void) const {
	std::cout << "I'm not decided on any type" << std::endl;
}

std::string	WrongAnimal::getType(void) const {
	return this->type;
}
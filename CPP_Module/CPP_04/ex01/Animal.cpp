/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:19 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:39:44 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal(void): type("Default"){
	std::cout << "Animal Default Constructor called" << std::endl;
}

Animal::~Animal(void) {
	std::cout << "Animal Destructor called" << std::endl;
}

Animal::Animal(Animal const &src) {
	std::cout << "Animal Copy Constructor called" << std::endl;
	*this = src;
}

Animal&	Animal::operator=(Animal const &src) {
	if (this != &src)
		this->type = src.type;
	return *this;
}

void	Animal::makeSound(void) const {
	std::cout << "I'm not decided on any type" << std::endl;
}

std::string	Animal::getType(void) const {
	return this->type;
}

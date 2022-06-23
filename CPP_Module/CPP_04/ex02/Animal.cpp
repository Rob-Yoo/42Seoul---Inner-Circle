/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:19 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/23 19:40:01 by jinyoo           ###   ########.fr       */
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

std::string	Animal::getType(void) const {
	return this->type;
}

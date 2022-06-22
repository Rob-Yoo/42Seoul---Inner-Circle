/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:40:05 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog(void) {
	std::cout << "Dog Default Constructor called" << std::endl;
	this->type = "Dog";
}

Dog::~Dog(void) {
	std::cout << "Dog Destructor called" << std::endl;
}

Dog::Dog(Dog const &src) {
	std::cout << "Dog Copy Constructor called" << std::endl;
	*this = src;
}

Dog&	Dog::operator=(Dog const &src) {
	if (this != &src)
		this->type = src.type;
	return *this;
}

void	Dog::makeSound(void) const {
	std::cout << "Bow wow!!" << std::endl;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:39:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) {
	std::cout << "Cat Default Constructor called" << std::endl;
	this->type = "Cat";
}

Cat::~Cat(void) {
	std::cout << "Cat Destructor called" << std::endl;
}

Cat::Cat(Cat const &src) {
	std::cout << "Cat Copy Constructor called" << std::endl;
	*this = src;
}

Cat&	Cat::operator=(Cat const &src) {
	if (this != &src)
		this->type = src.type;
	return *this;
}

void	Cat::makeSound(void) const {
	std::cout << "Meow~~" << std::endl;
}

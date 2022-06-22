/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:24 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 17:45:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat(void) {
	std::cout << "Cat Default Constructor called" << std::endl;
	this->type = "Cat";
	this->brain = new Brain();
	this->brain->setIdeas("Cat's Brainzzzz.....");
}

Cat::~Cat(void) {
	std::cout << "Cat Destructor called" << std::endl;
	delete this->brain;
}

Cat::Cat(Cat const &src) {
	std::cout << "Cat Copy Constructor called" << std::endl;
	*this = src;
}

Cat&	Cat::operator=(Cat const &src) {
	if (this != &src)
	{
		this->type = src.type;
		this->brain = new Brain(*(src.brain));
		// this->brain = src.brain;
	}
	return *this;
}

void	Cat::makeSound(void) const {
	std::cout << "Meow~~" << std::endl;
}

Brain*	Cat::getBrain(void) {
	return this->brain;
}

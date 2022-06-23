/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 17:49:06 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog(void) {
	std::cout << "Dog Default Constructor called" << std::endl;
	this->type = "Dog";
	this->brain = new Brain();
	this->brain->setIdeas("Dog's Brainzzzz.....");
}

Dog::~Dog(void) {
	std::cout << "Dog Destructor called" << std::endl;
	delete this->brain;
}

Dog::Dog(Dog const &src) {
	std::cout << "Dog Copy Constructor called" << std::endl;
	*this = src;
}

Dog&	Dog::operator=(Dog const &src) {
	if (this != &src)
	{
		this->type = src.type;
		this->brain = new Brain(*(src.brain));
		// this->brain = src.brain;
	}
	return *this;
}

void	Dog::makeSound(void) const {
	std::cout << "Bow wow!!" << std::endl;
}

Brain*	Dog::getBrain(void) {
	return this->brain;
}

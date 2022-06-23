/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:07:47 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 17:40:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"
#include <string>

Brain::Brain(void) {
	std::cout << "Brain Default Constructor called" << std::endl;
	for (int i = 0; i < 100; i++)
		this->ideas[i] = "Default Brainzzzz.....";
}

Brain::~Brain(void) {
	std::cout << "Brain Destructor called" << std::endl;
}

Brain::Brain(Brain const &src) {
	std::cout << "Brain Copy Constructor called" << std::endl;
	*this = src;
}

Brain&	Brain::operator=(Brain const &src) {
	if (this != &src)
	{
		for (int i = 0; i < 100; i++)
			this->ideas[i] = src.ideas[i];
	}
	return *this;
}

void	Brain::setIdeas(std::string idea) {
	for (int i = 0; i < 100; i++)
		this->ideas[i] = idea;
}

std::string*	Brain::getIdeas(void) {
	return this->ideas;
}

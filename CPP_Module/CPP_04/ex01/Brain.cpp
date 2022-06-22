/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:07:47 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 15:25:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain(void) {
	std::cout << "Brain Default Constructor called" << std::endl;
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
		
	}
}

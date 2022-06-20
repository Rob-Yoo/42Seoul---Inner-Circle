/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:51:04 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 16:59:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap(void): ClapTrap() {
	setHP(100);
	setEnergy(100);
	setDamage(30);
	std::cout << "FragTrap Default Constructor called" << std::endl;
}

FragTrap::FragTrap(std::string name): ClapTrap(name) {
	setHP(100);
	setEnergy(100);
	setDamage(30);
	std::cout << getName() << ": FragTrap Constructor called" << std::endl;
}

FragTrap::~FragTrap(void) {
	std::cout << getName() << ": FragTrap Destructor called" << std::endl;
}

FragTrap::FragTrap(FragTrap const &src) {
	*this = src;
	std::cout << "Copy Constructor called" << std::endl;
}

FragTrap&	FragTrap::operator=(FragTrap const &src) {
	if (this != &src)
		ClapTrap::operator=(src);
	return *this;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << getName() << " positive high fives request" << std::endl;
}


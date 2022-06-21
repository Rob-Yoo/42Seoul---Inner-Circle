/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 16:51:04 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/21 15:55:58 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void): ClapTrap() {
	setHP(100);
	setEnergy(50);
	setDamage(20);
	this->_guard_mode = false;
	std::cout << "ScavTrap Default Constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name): ClapTrap(name) {
	setHP(100);
	setEnergy(50);
	setDamage(20);
	this->_guard_mode = false;
	std::cout << getName() << ": ScavTrap Constructor called" << std::endl;
}

ScavTrap::~ScavTrap(void) {
	std::cout << getName() << ": ScavTrap Destructor called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap const &src) {
	*this = src;
	std::cout << "Copy Constructor called" << std::endl;
}

ScavTrap&	ScavTrap::operator=(ScavTrap const &src) {
	if (this != &src)
		ClapTrap::operator=(src);
	return *this;
}

void	ScavTrap::attack(std::string const &target) {
	if (check_dead())
		return;
	std::cout << "ScavTrap " << getName() << " attacks " << target << ", causing " << getDamage() << " points of damage!" << std::endl;
	setEnergy(getEnergy() - 1);
}

void	ScavTrap::guardGate(void) {
	this->_guard_mode = !this->_guard_mode;

	if (this->_guard_mode)
		std::cout << ClapTrap::getName() << ": Gate keeper mode is activated" << std::endl;
	else
		std::cout << ClapTrap::getName() << ": Gate keeper mode is deactivated" << std::endl;
}

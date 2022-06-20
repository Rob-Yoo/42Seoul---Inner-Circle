/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 19:34:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 22:46:43 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"
#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

DiamondTrap::DiamondTrap(void): ClapTrap(), FragTrap(), ScavTrap(), _name(ClapTrap::getName()) {
	std::cout << "DiamondTrap Default Constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name): ClapTrap(name + "_clap_name"), FragTrap(name + "_clap_name"), ScavTrap(name + "_clap_name") {
	this->_name = name;
	ClapTrap::setDamage(30);
	std::cout << this->_name << ": DiamondTrap Constructor called" << std::endl;
}

DiamondTrap::~DiamondTrap(void) {
	std::cout << this->_name << ": DiamondTrap Destructor called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap const &src) {
	std::cout << this->_name << ": DiamondTrap Copy Constructor called" << std::endl;
	*this = src;
}

DiamondTrap&	DiamondTrap::operator=(DiamondTrap const &src) {
	if (this != &src)
	{
		ClapTrap::operator=(src);
		this->_name = src._name;
	}
	return *this;
}

void	DiamondTrap::whoAmI(void) {
	std::cout << "DiamondTrap Name " << this->_name << std::endl;
	std::cout << "ClapTrap Name " << ClapTrap::getName() << std::endl;
}

void	DiamondTrap::attack(std::string const &target) {
	ScavTrap::attack(target);
}


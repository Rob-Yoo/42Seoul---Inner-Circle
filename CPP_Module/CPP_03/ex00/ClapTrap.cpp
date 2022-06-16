/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:05 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/16 22:07:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("default"), _hit(10), _energy(10), _damage(0) {
	std::cout << getName() << ": Default Constructor called" << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << getName() << ": Destructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src) {
	std::cout << getName() << ": Copy constructor called" << std::endl;
	*this = src;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hit(10), _energy(10), _damage(0) {
	std::cout << getName() << ": Constructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(ClapTrap const &src) {
	if (this != &src)
	{
		setName(src._name);
		setDamage(src._damage);
		setEnergy(src._energy);
		setHit(src._hit);
	}
	return (*this);
}

void	ClapTrap::attack(std::string const &target) {
	std::cout << "ClapTrap " << getName() << " attacks " << target << ", causing " << getDamage() << " points of damage!" << std::endl;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (amount >= getEnergy())
	{
			setEnergy(0);
			std::cout << "ClapTrap " << getName() << " died!" << std::endl;
	}
	else
	{
		setEnergy(getEnergy() - amount);
		std::cout << "ClapTrap " << getName() << "'s energy is now " << getEnergy() << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	setEnergy(getEnergy() + amount);
	std::cout << "ClapTrap " << getName() << " is repaired, energy is now " << getEnergy() << std::endl;
}

unsigned int	ClapTrap::getDamage(void) const {
	return this->_damage;
}

unsigned int	ClapTrap::getHit(void) const {
	return this->_hit;
}

unsigned int	ClapTrap::getEnergy(void) const {
	return this->_energy;
}

std::string		ClapTrap::getName(void) const {
	return this->_name;
}

void	ClapTrap::setDamage(unsigned int damage) {
	this->_damage = damage;
}

void	ClapTrap::setHit(unsigned int hit) {
	this->_hit = hit;
}

void	ClapTrap::setEnergy(unsigned int energy) {
	this->_energy = energy;
}

void	ClapTrap::setName(std::string name) {
	this->_name = name;
}

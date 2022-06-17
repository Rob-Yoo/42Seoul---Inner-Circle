/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:05 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/17 14:16:19 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("default"), _hp(10), _energy(10), _damage(0) {
	std::cout << getName() << ": Default Constructor called" << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << getName() << ": Destructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src) {
	std::cout << getName() << ": Copy constructor called" << std::endl;
	*this = src;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hp(10), _energy(10), _damage(0) {
	std::cout << getName() << ": Constructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(ClapTrap const &src) {
	if (this != &src)
	{
		setName(src.getName());
		setDamage(src.getDamage());
		setEnergy(src.getEnergy());
		setHP(src.getHP());
	}
	return *this;
}

bool	ClapTrap::check_dead(void) {
	if (getHP() == 0) {
		std::cout << "ClapTrap " << getName() << " is already dead" << std::endl;
		return true;
	}
	else if (getEnergy() == 0)
	{
		std::cout << "ClapTrap " << getName() << " has no energy" << std::endl;
		return true;
	}
	return false;
}

void	ClapTrap::attack(const std::string &target) {
	if (check_dead())
		return ;
	std::cout << "ClapTrap " << getName() << " attacks " << target << ", causing " << getDamage() << " points of damage!" << std::endl;
	setEnergy(getEnergy() - 1);
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (check_dead())
		return ;
	std::cout << "ClapTrap " << getName() << " take damages " << amount << std::endl;
	if (getHP() > amount)
		setHP(getHP() - amount);
	else 
	{
		setHP(0);
		std::cout << "ClapTrap "<< getName() << " is dead" << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (check_dead())
		return ;
	if (getHP() + amount > 10)
		setHP(10);
	else
		setHP(getHP() + amount);
	std::cout << "ClapTrap " << getName() << " has been repaired, and current HP is " << getHP() << std::endl;
	setEnergy(getEnergy() - 1);
}

unsigned int	ClapTrap::getDamage(void) const {
	return this->_damage;
}

unsigned int	ClapTrap::getHP(void) const {
	return this->_hp;
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

void	ClapTrap::setHP(unsigned int hit) {
	this->_hp = hit;
}

void	ClapTrap::setEnergy(unsigned int energy) {
	this->_energy = energy;
}

void	ClapTrap::setName(std::string name) {
	this->_name = name;
}

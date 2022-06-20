/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:05 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 22:26:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("default"), _hp(10), _energy(10), _damage(0) {
	std::cout << "ClapTrap Default Constructor called" << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << this->_name << ": ClapTrap Destructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src) {
	*this = src;
	std::cout << "ClapTrap Copy constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hp(10), _energy(10), _damage(0) {
	std::cout << this->_name << ": ClapTrap Constructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(ClapTrap const &src) {
	if (this != &src)
	{
		this->_name = src._name;
		this->_damage = src._damage;
		this->_energy = src._energy;
		this->_hp = src._energy;
	}
	return *this;
}

bool	ClapTrap::check_dead(void) {
	if (this->_hp == 0) {
		std::cout << "ClapTrap " << this->_name << " is already dead" << std::endl;
		return true;
	}
	else if (this->_energy == 0)
	{
		std::cout << "ClapTrap " << this->_name << " has no energy" << std::endl;
		return true;
	}
	return false;
}

void	ClapTrap::attack(const std::string &target) {
	if (check_dead())
		return ;
	std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_damage << " points of damage!" << std::endl;
	this->_energy--;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (check_dead())
		return ;
	std::cout << "ClapTrap " << this->_name << " take damages " << amount << std::endl;
	if (this->_hp > amount)
		this->_hp -= amount;
	else 
	{
		this->_hp = 0;
		std::cout << "ClapTrap "<< this->_name << " is dead" << std::endl;
	}
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (check_dead())
		return ;
	if (this->_hp + amount > 100)
		this->_hp = 100;
	else
		this->_hp += amount;
	std::cout << "ClapTrap " << this->_name << " has been repaired, and current HP is " << this->_hp << std::endl;
	this->_energy--;
}

std::string	ClapTrap::getName(void) const {
	return this->_name;
}

unsigned int	ClapTrap::getEnergy(void) const {
	return this->_energy;
}

unsigned int	ClapTrap::getHP(void) const {
	return this->_hp;
}

unsigned int	ClapTrap::getDamage(void) const {
	return this->_damage;
}

void	ClapTrap::setHP(unsigned int hp) {
	this->_hp = hp;
}

void	ClapTrap::setEnergy(unsigned int energy) {
	this->_energy = energy;
}

void	ClapTrap::setDamage(unsigned int damage) {
	this->_damage = damage;
}

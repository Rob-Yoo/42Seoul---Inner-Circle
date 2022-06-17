/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:05 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/17 16:39:50 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void): _name("default"), _hp(10), _energy(10), _damage(0) {
	std::cout << this->_name << ": Default Constructor called" << std::endl;
}

ClapTrap::~ClapTrap(void) {
	std::cout << this->_name << ": Destructor called" << std::endl;
}

ClapTrap::ClapTrap(ClapTrap const &src) {
	*this = src;
	std::cout << this->_name << ": Copy constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name): _name(name), _hp(10), _energy(10), _damage(0) {
	std::cout << this->_name << ": Constructor called" << std::endl;
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
	if (this->_hp + amount > 10)
		this->_hp = 10;
	else
		this->_hp += amount;
	std::cout << "ClapTrap " << this->_name << " has been repaired, and current HP is " << this->_hp << std::endl;
	this->_energy--;
}

unsigned int	ClapTrap::getDamage(void) const {
	return this->_damage;
}

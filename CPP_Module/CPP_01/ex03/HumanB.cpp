/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:51:15 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/05 20:54:06 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name) : name(name), weapon(NULL) {}

HumanB::~HumanB(void) {}

void	HumanB::setWeapon(Weapon &weapon) { this->weapon = &weapon; }

void	HumanB::attack(void)
{
	const	std::string& weapon_type = weapon->getType();

	std::cout << this->name << " attacks with their " << weapon_type << std::endl;
}

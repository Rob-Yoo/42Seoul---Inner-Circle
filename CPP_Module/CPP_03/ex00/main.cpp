/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/17 16:37:28 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	a("Warrior");
	ClapTrap	b("Wizard");
	ClapTrap	c("Archer");

	std::cout << std::endl;
	a.attack("Wizard");
	b.takeDamage(a.getDamage());
	std::cout << std::endl;
	b.attack("Warrior");
	a.takeDamage(b.getDamage());
	std::cout << std::endl;
	c.attack("Wizard");
	b.takeDamage(c.getDamage());
	std::cout << std::endl;
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.beRepaired(25);
	a.attack("Wizard");
	std::cout << std::endl;
	return (0);
}
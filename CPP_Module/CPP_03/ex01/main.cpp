/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 15:53:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int	main(void)
{
	ScavTrap	a("a");
	ScavTrap	b("b");
	ScavTrap	c(a);

	std::cout << std::endl;
	
	a.attack("b");
	b.takeDamage(a.getDamage());
	
	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());
	
	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());
	
	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());
	
	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());
	
	std::cout << std::endl;

	b.guardGate();
	b.guardGate();
	
	std::cout << std::endl;
	return (0);
}
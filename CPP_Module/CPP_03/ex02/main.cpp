/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:56:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 22:30:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int	main(void)
{
	FragTrap	a("a");
	ScavTrap	b("b");

	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());

	std::cout << std::endl;

	b.attack("a");
	a.takeDamage(b.getDamage());

	std::cout << std::endl;

	a.attack("b");
	b.takeDamage(a.getDamage());

	std::cout << std::endl;

	b.beRepaired(30);

	std::cout << std::endl;

	b.attack("a");
	a.takeDamage(b.getDamage());

	std::cout << std::endl;

	b.guardGate();

	std::cout << std::endl;

	a.highFivesGuys();

	std::cout << std::endl;
	return (0);
}
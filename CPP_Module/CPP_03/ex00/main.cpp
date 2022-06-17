/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:07:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/17 14:16:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int	main(void)
{
	ClapTrap	a("a");
	ClapTrap	b("b");
	ClapTrap	c("c");

	std::cout << std::endl;
	a.attack("b");
	b.takeDamage(a.getDamage());
	std::cout << std::endl;
	b.attack("a");
	a.takeDamage(b.getDamage());
	std::cout << std::endl;
	c.attack("b");
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
	a.attack("b");
	std::cout << std::endl;
	return (0);
}
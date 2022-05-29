/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 15:44:17 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/29 16:04:44 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie	s_zombie = Zombie("Stack");
	Zombie	*h_zombie = newZombie("Heap");

	s_zombie.announce();
	h_zombie->announce();
	randomChump("Foreign Zombie");
	delete h_zombie;
	return 0;
}

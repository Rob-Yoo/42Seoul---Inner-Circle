/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:16:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/29 22:45:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int	main(void)
{
	Zombie*	zombies = zombieHorde(10, "zombie");

	for (int i = 0; i < 10; i++)
		zombies[i].announce();
	delete[] zombies;
	return 0;
}

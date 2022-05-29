/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:45:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/29 21:19:08 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie	*zombieHorde(int N, std::string name)
{
	Zombie	*z_horde = new Zombie[N];
	std::stringstream	str;

	for (int i = 0; i < N; i++)
	{
		str << (i + 1);
		z_horde[i].set_name(name + str.str());
		str.str("");
	}
	return (z_horde);
}
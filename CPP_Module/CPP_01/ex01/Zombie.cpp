/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 20:41:38 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/29 20:59:09 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(void) {}

Zombie::~Zombie(void) {
	std::cout << m_name << ": Bye World...." << std::endl;
}

void	Zombie::set_name(std::string name) { m_name = name; }

void	Zombie::announce(void) {
	std::cout << m_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
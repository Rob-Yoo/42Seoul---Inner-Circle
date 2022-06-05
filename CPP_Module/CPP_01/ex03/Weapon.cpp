/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:50:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/05 21:29:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type) { this->type = type; }

Weapon::~Weapon(void) {}

const std::string&	Weapon::getType(void) { return type; }

void	Weapon::setType(std::string type) { this->type = type; }

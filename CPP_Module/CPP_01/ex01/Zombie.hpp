/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:10:38 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/29 20:59:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <sstream>

class Zombie {
private:
	std::string m_name;
public:
	Zombie(void);
	~Zombie(void);

	void	set_name(std::string name);
	void	announce(void);
};

Zombie	*zombieHorde(int N, std::string name);

#endif

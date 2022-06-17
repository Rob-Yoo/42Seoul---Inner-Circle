/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 18:06:31 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/17 14:00:17 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
public:
	ClapTrap(void);
	~ClapTrap(void);
	ClapTrap(ClapTrap const &src);
	ClapTrap(std::string name);

	ClapTrap&		operator=(ClapTrap const &src);
	void			attack(std::string const &target);
	void			takeDamage(unsigned int amount);
	void			beRepaired(unsigned int amount);
	bool			check_dead(void);

	unsigned int	getDamage(void) const;
	unsigned int	getHP(void) const;
	unsigned int	getEnergy(void) const;
	std::string		getName(void) const;
	void			setDamage(unsigned int damage);
	void			setHP(unsigned int hit);
	void			setEnergy(unsigned int energy);
	void			setName(std::string name);
private:
	std::string		_name;
	unsigned int	_hp;
	unsigned int	_energy;
	unsigned int	_damage;
};

#endif

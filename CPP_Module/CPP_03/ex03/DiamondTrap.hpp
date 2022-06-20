/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 17:12:55 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/20 22:00:59 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIAMOND_TRAP_HPP
# define DIAMOND_TRAP_HPP

# include "ScavTrap.hpp"
# include "FragTrap.hpp"

class DiamondTrap: public FragTrap, public ScavTrap {
public:
	DiamondTrap(void);
	DiamondTrap(std::string name);
	~DiamondTrap(void);
	DiamondTrap(DiamondTrap const &src);

	DiamondTrap&	operator=(DiamondTrap const &src);
	void			whoAmI(void);
	void			attack(std::string const &target);

	unsigned int getHP(void) const;
	unsigned int getEnergy(void) const;
	unsigned int getDamage(void) const;
private:
	std::string	_name;
};

#endif
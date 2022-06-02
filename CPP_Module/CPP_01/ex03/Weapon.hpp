/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 21:51:05 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/02 22:14:45 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include WEAPON_HPP
# define WEAPON_HPP

#include <string>

class Weapon {
private:
	std::string type;
public:
	Weapon(void);

	const std::string&	getType(void);
	void				setType(std::string type);
}
#endif

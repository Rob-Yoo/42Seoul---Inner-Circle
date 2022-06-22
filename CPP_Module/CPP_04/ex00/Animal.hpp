/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:22 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 14:39:32 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal {
public:
	Animal(void);
	virtual ~Animal(void);
	Animal(Animal const &src);

	Animal&	operator=(Animal const &src);
	virtual void	makeSound(void) const;
	std::string		getType(void) const;
protected:
	std::string	type;
};

#endif

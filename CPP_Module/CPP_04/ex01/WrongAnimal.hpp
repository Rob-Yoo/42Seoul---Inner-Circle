/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:43:22 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/23 13:58:20 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRONG_ANIMAL_HPP
# define WRONG_ANIMAL_HPP

# include <iostream>
# include <string>

class WrongAnimal {
public:
	WrongAnimal(void);
	virtual ~WrongAnimal(void);
	WrongAnimal(WrongAnimal const &src);

	WrongAnimal&	operator=(WrongAnimal const &src);
	void	makeSound(void) const;
	std::string		getType(void) const;
protected:
	std::string	type;
};

#endif

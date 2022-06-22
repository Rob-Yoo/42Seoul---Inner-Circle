/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:34 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 16:55:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOG_HPP
# define DOG_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Dog: public Animal {
public:
	Dog(void);
	~Dog(void);
	Dog(Dog const &src);

	Dog&	operator=(Dog const &src);
	void	makeSound(void) const;

	Brain*	getBrain(void);
private:
	Brain*	brain;
};

#endif

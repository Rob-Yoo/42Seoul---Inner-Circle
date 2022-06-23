/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:09:28 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 16:55:46 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAT_HPP
# define CAT_HPP

# include "Animal.hpp"
# include "Brain.hpp"

class Cat: public Animal {
public:
	Cat(void);
	~Cat(void);
	Cat(Cat const &src);

	Cat&	operator=(Cat const &src);
	void	makeSound(void) const;

	Brain*	getBrain(void);
private:
	Brain*	brain;
};

#endif

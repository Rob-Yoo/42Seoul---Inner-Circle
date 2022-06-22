/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 16:31:37 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 17:49:24 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <ostream>

int main(void)
{
	const Animal *j = new Dog();
	const Animal *i = new Cat();

	std::cout << std::endl;

	delete j;//should not create a leak
	delete i;

	std::cout << std::endl;

	Animal	*a[4];

	for(int i = 0; i < 4; i++) {
		if (i < 2) {
			a[i] = new Cat();
		}
		else {
			a[i] = new Dog();
		}
	}

	std::cout << std::endl;

	for(int i = 0; i < 4; i++) {
		a[i]->makeSound();
	}
	
	std::cout << std::endl;

	for(int i = 0; i < 4; i++) {
		delete a[i];
	}

	std::cout << std::endl;

	{
		// Cat	cat_1;
		// Cat cat_2(cat_1);
		Dog	dog_1;
		Dog dog_2(dog_1);

		std::cout << std::endl;

		// for (int i = 0; i < 100; i++)
		// 	std::cout << cat_2.getBrain()->getIdeas()[i] << std::endl;

		// std::cout << std::endl;

		// for (int i = 0; i < 100; i++)
		// 	std::cout << cat_1.getBrain()->getIdeas()[i] << std::endl;

		// std::cout << std::endl;
		for (int i = 0; i < 100; i++)
			std::cout << dog_2.getBrain()->getIdeas()[i] << std::endl;

		std::cout << std::endl;

		for (int i = 0; i < 100; i++)
			std::cout << dog_1.getBrain()->getIdeas()[i] << std::endl;

		std::cout << std::endl;
	}

	return 0;
}

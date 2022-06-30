/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:25:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/30 21:46:33 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

int main()
{
	Data *original = new Data("jinyoo", 185.1, 72.6, 25);
	std::cout << *original << std::endl;

	// Data* => uintptr_t
	uintptr_t broker = serialize(original);

	// uintptr_t => Data*
	Data *clone = deserialize(broker);
	std::cout << *clone << std::endl;
	delete original;
	return 0;
}

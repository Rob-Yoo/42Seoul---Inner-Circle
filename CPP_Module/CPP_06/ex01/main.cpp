/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:25:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 02:46:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

int main(void)
{
	Data *data = new Data("jinyoo", 185.1, 72.6, 25);
	std::cout << *data << std::endl;

	uintptr_t sr_data = serialize(data);

	Data *dsr_data = deserialize(sr_data);
	std::cout << *dsr_data << std::endl;
	delete data;
	return 0;
}

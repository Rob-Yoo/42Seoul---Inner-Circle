/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 20:25:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:44:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

int main(void)
{
	Data *boxing_data = new Data("jinyoo", 185.1, 72.6, 25);
	std::cout << *boxing_data << std::endl;

	uintptr_t data_stream = serialize(boxing_data);

	Data *unboxing_data = deserialize(data_stream);
	std::cout << *unboxing_data << std::endl;
	delete boxing_data;
	return 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:29:18 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 19:19:09 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(int argc, char *argv[])
{
	std::string	level;

	if (argc != 2)
		std::cerr << "usage : ./harlFilter {LEVEL}\n";
	else
	{
		level = argv[1];
		if (level != "DEBUG" && level != "INFO" && level != "WARNING" && level != "ERROR")
			std::cout << "[ Probably complaining about insignificant problems ]\n";
		else
		{
			Harl	harl(level);
			harl.complain();
		}
	}
	return 0;
}
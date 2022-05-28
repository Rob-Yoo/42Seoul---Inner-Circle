/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:08:02 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 17:16:00 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static void	check_validate_input(void)
{
	if (std::cin.eof() || std::cin.fail())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Invalid Input";
	}
}

int	main(void)
{
	PhoneBook	phone_book;
	std::string	command;

	std::cout << "* *************************************************** *\n";
	std::cout << "*                                                     *\n";
	std::cout << "*             jinyoo's PhoneBook Program              *\n";
	std::cout << "*                                                     *\n";
	std::cout << "* *************************************************** *\n";
	while(true)
	{
		std::cout << "I'm waiting for your command..." << std::endl;
		std::cout << "> ";
		std::getline(std::cin, command);
		check_validate_input();

		if (!command.compare("EXIT"))
			break;
		else if (!command.compare("ADD"))
			phone_book.add_new_contact();
		else if (!command.compare("SEARCH"))
			phone_book.search_saved_contacts();
		std::cout << "\n" << std::setfill('-') << std::setw(56) << "\n";
		std::cout << std::setfill(' ');
	}
	return (0);
}
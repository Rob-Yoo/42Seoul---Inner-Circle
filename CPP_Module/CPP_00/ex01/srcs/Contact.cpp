/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:14:13 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 17:37:25 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

static bool	fill_field(std::string field, std::string *info)
{

	std::cout << "| " << field;
	std::getline(std::cin, *info);
	if (std::cin.eof() || std::cin.fail())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Invalid Input";
		return false;
	}
	if ((*info).size() == 0)
	{
		std::cerr << "Cannot be empty field!";
		return false;
	}
	return true;
}

bool	Contact::make_new_contact(void)
{
	std::string fname;
	std::string lname;
	std::string nick_name;
	std::string phone_num;
	std::string d_secret;

	if (!fill_field("First Name : ", &fname) || !fill_field("Last Name : ", &lname) ||\
	!fill_field("Nickname : ", &nick_name) || !fill_field("Phone Number : ", &phone_num) || \
	!fill_field("Darkest secret : ", &d_secret))
	return false;

	setFname(fname);
	setLname(lname);
	setNickname(nick_name);
	setPnum(phone_num);
	setDsecret(d_secret);

	std::cout << "\n" << std::setfill('*') << std::setw(24) << "\n";
	std::cout << std::setfill(' ');
	std::cerr << "* Successfully Added! *" << std::endl;
	std::cout << std::setfill('*') << std::setw(24) << "\n";
	std::cout << std::setfill(' ');
	return true;
}
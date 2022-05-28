/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:07:40 by jinyoo            #+#    #+#             */
/*   Updated: 2022/05/28 17:52:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

static bool	check_validate_input(void)
{
	if (std::cin.eof() || std::cin.fail())
	{
		std::cin.clear();
		clearerr(stdin);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cerr << "Invalid Input";
		return false;
	}
	return true;
}

static std::string truncate(std::string str)
{
	if (str.length() > 9)
		return str.substr(0, 9) + ".";
	return str;
}

void	PhoneBook::add_new_contact(void)
{
	if (!m_contacts[m_contact_idx].make_new_contact())
		return ;
	m_contact_idx = (m_contact_idx + 1) % 8;
	if (m_contact_num < 8)
		m_contact_num += 1;
	if (m_is_empty)
		m_is_empty = false;
}

void	PhoneBook::show_searched_contact(int idx)
{
	std::cout << "\n| First Name : " << m_contacts[idx].getFname() << std::endl;
	std::cout << "| Last Name : " << m_contacts[idx].getLname() << std::endl;
	std::cout << "| Nickname : " << m_contacts[idx].getNickname() << std::endl;
	std::cout << "| Phone Number : " << m_contacts[idx].getPnum() << std::endl;
	std::cout << "| Darkest Secret : " << m_contacts[idx].getDsecret() << std::endl;
}

void	PhoneBook::show_search_interface(void)
{
	int	idx;

	while (true)
	{
		std::cout << "Which index number do you want to search?\n> ";
		std::cin >> idx;
		if (!check_validate_input())
			return;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (idx < 1 || idx > 8)
		{
			std::cout << "\n" << std::setfill('/') << std::setw(18) << "\n";
			std::cout << std::setfill(' ');
			std::cerr << "/ Invalid Input /" << std::endl;
			std::cout << std::setfill('/') << std::setw(18) << "\n";
			std::cout << std::setfill(' ') << "\n";
		}
		else if (idx > get_m_contact_num())
		{
			std::cout << "\n" << std::setfill('/') << std::setw(55) << "\n";
			std::cout << std::setfill(' ');
			std::cerr << "/ Could not be found. Please check the Contact List! /\n";
			std::cout << std::setfill('/') << std::setw(55) << "\n";
			std::cout << std::setfill(' ') << "\n";
		}
		else
		{
			show_searched_contact(idx - 1);
			break;
		}
	}
}

void	PhoneBook::show_saved_contact(int i, bool is_last=false)
{
	std::cout << "#" << std::setw(9) << i + 1 << "|";
	std::cout << std::setw(10) << truncate(m_contacts[i].getFname()) << "|";
	std::cout << std::setw(10) << truncate(m_contacts[i].getLname()) << "|";
	std::cout << std::setw(10) << truncate(m_contacts[i].getNickname()) << "|";
	std::cout << std::setw(4) << "#" << std::endl;
	if (is_last)
	{
		std::cout << std::setfill('#') << std::setw(49) << "\n";
		std::cout << std::setfill(' ');
	}
}

void	PhoneBook::show_contact_list(void)
{
	std::cout << std::setfill('#') << std::setw(49) << "\n";
	std::cout << std::setfill(' ');
	std::cout << "#" << std::setw(9) << "Index" << "|";
	std::cout << std::setw(10) << "First Name" << "|";
	std::cout << std::setw(10) << "Last Name" << "|";
	std::cout << std::setw(10) << "Nickname" << "|";
	std::cout << std::setw(4) << "#" << std::endl;
	std::cout << std::setfill('#') << std::setw(49) << "\n";
	std::cout << std::setfill(' ');
	for (int i = 0; i < get_m_contact_num(); i++)
	{
		if (i == get_m_contact_num() - 1)
			show_saved_contact(i, true);
		else
			show_saved_contact(i);
	}
}

void	PhoneBook::search_saved_contacts(void)
{
	if (m_is_empty)
	{
		std::cerr << "\nThere are no saved contacts in the PhoneBook...";
		return ;
	}
	show_contact_list();
	show_search_interface();
}
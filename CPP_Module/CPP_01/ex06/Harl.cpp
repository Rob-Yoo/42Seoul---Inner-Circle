/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:50:43 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 19:15:10 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(std::string level)
{
	if (level == "DEBUG")
		m_level = DEBUG;
	else if (level == "INFO")
		m_level = INFO;
	else if (level == "WARNING")
		m_level = WARNING;
	else
		m_level = ERROR;
}

Harl::~Harl(void) { }

void	Harl::debug(bool is_chain)
{
	std::cout << "[DEBUG]\n";
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!\n\n";
	if (is_chain)
	{
		this->info(false);
		this->warning(false);
		this->error();
	}
}

void	Harl::info(bool is_chain)
{
	std::cout << "[INFO]\n";
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!\n\n";
	if (is_chain)
	{
		this->warning(false);
		this->error();
	}
}

void	Harl::warning(bool is_chain)
{
	std::cout << "[WARNING]\n";
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.\n\n";
	if (is_chain)
		this->error();
}

void	Harl::error(void)
{
	std::cout << "[ERROR]\n";
	std::cout << "This is unacceptable! I want to speak to the manager now.\n\n";
}

void	Harl::complain(void)
{
	switch (m_level) {
		case DEBUG:
			this->debug(true);
			break;
		case INFO:
			this->info(true);
			break;
		case WARNING:
			this->warning(true);
			break;
		case ERROR:
			this->error();
			break;
		default:
			break;
	}
}
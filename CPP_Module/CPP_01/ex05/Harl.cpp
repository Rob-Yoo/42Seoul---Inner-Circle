/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:50:43 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 19:18:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl(void)
{
	m_comp[0].level = "DEBUG";
	m_comp[0].func_ptr = &Harl::debug;
	m_comp[1].level = "INFO";
	m_comp[1].func_ptr = &Harl::info;
	m_comp[2].level = "WARNING";
	m_comp[2].func_ptr = &Harl::warning;
	m_comp[3].level = "ERROR";
	m_comp[3].func_ptr = &Harl::error;
}

Harl::~Harl(void) { }

void	Harl::debug(void)
{
	std::cout << "[DEBUG]\n";
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!\n";
}

void	Harl::info(void)
{
	std::cout << "[INFO]\n";
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!\n";
}

void	Harl::warning(void)
{
	std::cout << "[WARNING]\n";
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month.\n";
}

void	Harl::error(void)
{
	std::cout << "[ERROR]\n";
	std::cout << "This is unacceptable! I want to speak to the manager now.\n";
}

void	Harl::complain(std::string level)
{
	for (int i(0); i < 4; i++)
	{
		if (m_comp[i].level == level)
		{
			(this->*m_comp[i].func_ptr)();
			return;
		}
	}
	std::cerr << "// Incorrect Level Argument //\n";
}
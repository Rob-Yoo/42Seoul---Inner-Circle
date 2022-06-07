/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:29:18 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 16:24:34 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int	main(void)
{
	Harl	harl = Harl();
	void	(Harl::*m_func_ptr)(std::string);

	m_func_ptr = &Harl::complain;
	harl.complain("DEBUG");
	harl.complain("debug");
	harl.complain("INFO");
	(harl.*m_func_ptr)("WARNING");
	(harl.*m_func_ptr)("ERROR");
	(harl.*m_func_ptr)("error");
	return 0;
}
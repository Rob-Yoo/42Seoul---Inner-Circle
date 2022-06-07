/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:30:01 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 16:19:14 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>

class	Harl;

struct Complain {
	std::string level;
	void	(Harl::*func_ptr)(void);
};

class Harl {
private:
	Complain	m_comp[4];
	void		debug(void);
	void		info(void);
	void		warning(void);
	void		error(void);
public:
	Harl(void);
	~Harl(void);
	void	complain(std::string level);
};

#endif

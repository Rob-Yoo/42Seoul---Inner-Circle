/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:30:01 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/07 19:14:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HARL_HPP
# define HARL_HPP

# include <iostream>
# include <string>

# define DEBUG 0
# define INFO 1
# define WARNING 2
# define ERROR 3

class Harl {
private:
	int		m_level;
	void	debug(bool is_chain);
	void	info(bool is_chain);
	void	warning(bool is_chain);
	void	error(void);
public:
	Harl(std::string level);
	~Harl(void);
	void	complain();
};

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:07:44 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/22 17:20:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string.h>

class Brain {
public:
	Brain(void);
	virtual ~Brain(void);
	Brain(Brain const &src);

	Brain&	operator=(Brain const &src);
	
	void	setIdeas(std::string idea);
	std::string*	getIdeas(void);
private:
	std::string	ideas[100];
};

#endif

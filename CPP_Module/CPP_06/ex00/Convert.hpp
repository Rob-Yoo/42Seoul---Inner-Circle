/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:08:17 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/30 02:21:06 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <string>
# include <sstream>

class Convert {
public:
	Convert(std::string input);
	~Convert(void);
	Convert(Convert const &src);

	Convert&	operator=(Convert const &src);

	char	toChar(void) const;
	int		toInt(void) const;
	float	toFloat(void) const;
	double	toDouble(void) const;
private:
	std::string _input;
	Convert(void);
};

#endif


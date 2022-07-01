/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:08:17 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:38:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

# include <iostream>
# include <string>
# include <exception>
# include <cstdlib>
# include <cmath>
# include <cctype>

class Convert {
public:

	class BadArgumentException: public std::exception {
	public:
		const char* what(void) const throw();
	};
	Convert(std::string input) throw(BadArgumentException);
	~Convert(void);
	Convert(Convert const &src);

	Convert&	operator=(Convert const &src);

	void	printConvert(void) const;

	std::string	getInput(void) const;
	double		getValue(void) const;
private:
	std::string _input;
	double		_value;
	Convert(void);

	char	toChar(void) const;
	int		toInt(void) const;
	float	toFloat(void) const;

	void	printChar(void) const;
	void	printInt(void) const;
	void	printFloat(void) const;
	void	printDouble(void) const;
};

#endif

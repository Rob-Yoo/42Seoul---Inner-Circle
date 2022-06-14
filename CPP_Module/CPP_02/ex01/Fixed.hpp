/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:54:13 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/14 22:13:49 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
public:
	Fixed(void);
	Fixed(int const value);
	Fixed(float const value);
	Fixed(const Fixed& inst);
	~Fixed(void);
	Fixed&	operator=(const Fixed& src);

	int		getRawBits(void) const;
	void	setRawBits(int const rawBits);
	float	toFloat(void) const;
	int		toInt(void) const;
private:
	const static int	_bits;
	int					_value;
};

std::ostream&	operator<<(std::ostream &s, const Fixed &fixed);

#endif

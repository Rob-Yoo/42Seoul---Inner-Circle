/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:02:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/15 16:12:35 by jinyoo           ###   ########.fr       */
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
	Fixed(Fixed const &inst);
	~Fixed(void);
	Fixed&					operator=(Fixed const &src);
	bool					operator>(Fixed const &src) const;
	bool					operator<(Fixed const &src) const;
	bool					operator>=(Fixed const &src) const;
	bool					operator<=(Fixed const &src) const;
	bool					operator==(Fixed const &src) const;
	bool					operator!=(Fixed const &src) const;
	Fixed					operator+(Fixed const &src) const;
	Fixed					operator-(Fixed const &src) const;
	Fixed					operator*(Fixed const &src) const;
	Fixed					operator/(Fixed const &src) const;
	Fixed&					operator++(void);
	Fixed					operator++(int);
	Fixed&					operator--(void);
	Fixed					operator--(int);

	int						getRawBits(void) const;
	void					setRawBits(int const rawBits);
	float					toFloat(void) const;
	int						toInt(void) const;
	static Fixed&			min(Fixed &f1, Fixed &f2);
	const static Fixed&		min(Fixed const &f1, Fixed const &f2);
	static Fixed&			max(Fixed &f1, Fixed &f2);
	const static Fixed&		max(Fixed const &f1, Fixed const &f2);
private:
	const static int	_bits;
	int					_value;
};

std::ostream&	operator<<(std::ostream &s, Fixed const &fixed);

#endif

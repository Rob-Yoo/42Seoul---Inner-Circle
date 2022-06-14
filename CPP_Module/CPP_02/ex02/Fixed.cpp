/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:02:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/14 22:48:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_bits = 8;

Fixed::Fixed(void) {
	setRawBits(0);
}

Fixed::Fixed(const int value)
{
	setRawBits(value << 8);
}

Fixed::Fixed(const float value)
{
	setRawBits(roundf(value * (1 << _bits)));
}

Fixed::Fixed(const Fixed& src) {
	*this = src;
}

Fixed::~Fixed(void) {}

Fixed&	Fixed::operator=(const Fixed& src) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &src)
		setRawBits(src._value);
	return *this;
}

int	Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return _value;
}

void	Fixed::setRawBits(int const raw) {
	_value = raw;
}

float	Fixed::toFloat(void) const {
	return (float(_value) / (1 << _bits));
}

int	Fixed::toInt(void) const {
	return _value >> _bits;
}

std::ostream&	operator<<(std::ostream &out, const Fixed &fixed)
{
	out << fixed.toFloat();
	return out;
}

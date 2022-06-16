/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:02:30 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/16 17:52:48 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

const int	Fixed::_bits = 8;

Fixed::Fixed(void) {
	setRawBits(0);
}

Fixed::Fixed(int const value)
{
	setRawBits(value << 8);
}

Fixed::Fixed(float const value)
{
	setRawBits(roundf(value * (1 << _bits)));
}

Fixed::Fixed(Fixed const &src) {
	*this = src;
}

Fixed::~Fixed(void) {}


int	Fixed::getRawBits(void) const {
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

Fixed&	Fixed::operator=(Fixed const &src) {
	if (this != &src)
		setRawBits(src._value);
	return *this;
}

std::ostream&	operator<<(std::ostream &out, Fixed const &fixed)
{
	out << fixed.toFloat();
	return out;
}

bool	Fixed::operator>(Fixed const &src) const
{
	return (this->_value > src._value);
}

bool	Fixed::operator<(Fixed const &src) const
{
	return (this->_value < src._value);
}

bool	Fixed::operator>=(Fixed const &src) const
{
	return (this->_value >= src._value);
}

bool	Fixed::operator<=(Fixed const &src) const
{
	return (this->_value <= src._value);
}

bool	Fixed::operator==(Fixed const &src) const
{
	return (this->_value == src._value);
}

bool	Fixed::operator!=(Fixed const &src) const
{
	return (this->_value != src._value);
}

Fixed	Fixed::operator+(Fixed const &src) const
{
	return (Fixed(this->toFloat() + src.toFloat()));
}

Fixed	Fixed::operator-(Fixed const &src) const
{
	return (Fixed(this->toFloat() - src.toFloat()));
}

Fixed	Fixed::operator*(Fixed const &src) const
{
	return (Fixed(this->toFloat() * src.toFloat()));
}

Fixed	Fixed::operator/(Fixed const &src) const
{
	return (Fixed(this->toFloat() / src.toFloat()));
}

Fixed&	Fixed::operator++(void)
{
	this->_value++;
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	f(*this);

	this->_value++;
	return (f);
}

Fixed&	Fixed::operator--(void)
{
	this->_value--;
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	f(*this);

	this->_value--;
	return (f);
}

Fixed&	Fixed::min(Fixed &f1, Fixed &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

const Fixed&	Fixed::min(Fixed const &f1, Fixed const &f2)
{
	if (f1 < f2)
		return (f1);
	return (f2);
}

Fixed&	Fixed::max(Fixed &f1, Fixed &f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}

const Fixed&	Fixed::max(Fixed const &f1, Fixed const &f2)
{
	if (f1 > f2)
		return (f1);
	return (f2);
}


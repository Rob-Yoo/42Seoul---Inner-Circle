/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:08:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:36:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

const char*	Convert::BadArgumentException::what(void) const throw() {
	return "Bad Argument!";
}

Convert::Convert(void): _input("") {}

Convert::~Convert(void) {}

Convert::Convert(std::string input) throw(BadArgumentException): _input(input), _value(0.0){
	char *ptr;
	this->_value = std::strtod(input.c_str(), &ptr);
	if (this->_value == 0 && (input[0] != '-' && input[0] != '+' && !std::isdigit(input[0])))
		throw (BadArgumentException());
	if (*ptr && std::strcmp(ptr, "f"))
		throw (BadArgumentException());
}

Convert::Convert(Convert const &src) {
	*this = src;
}

Convert&	Convert::operator=(Convert const &src) {
	if (this != &src)
	{
		*(const_cast<std::string*>(&_input)) = src.getInput();
		this->_value = src.getValue();
	}
	return (*this);
}

char	Convert::toChar(void) const {
	return static_cast<char>(this->_value);
}

int		Convert::toInt(void) const {
	return static_cast<int>(this->_value);
}

float	Convert::toFloat(void) const {
	return static_cast<float>(this->_value);
}

void	Convert::printChar(void) const {
	char ret = toChar();

	std::cout << "char: ";
	if (std::isnan(this->_value))
	{
		std::cout << "impossible";
		return ;
	}
	if (!std::isprint(ret))
	{
		std::cout << "Non displayable";
		return ;
	}
	std::cout << "'" << ret << "'";
}

void	Convert::printInt(void) const {
	int ret = toInt();

	std::cout << "int: ";
	if (std::isnan(this->_value))
	{
		std::cout << "impossible";
		return ;
	}
	std::cout << ret;
}

void	Convert::printFloat(void) const {
	std::cout << "float: ";
	std::cout << std::fixed;
	std::cout.precision(1);
	std::cout << toFloat() << "f";
	std::cout.unsetf(std::ios::fixed);
}

void	Convert::printDouble(void) const {
	std::cout << "double: ";
	std::cout << std::fixed;
	std::cout.precision(1);
	std::cout << getValue();
	std::cout.unsetf(std::ios::fixed);
}

void	Convert::printConvert(void) const {
	printChar();
	std::cout << std::endl;
	printInt();
	std::cout << std::endl;
	printFloat();
	std::cout << std::endl;
	printDouble();
	std::cout << std::endl;
}

std::string	Convert::getInput(void) const {
	return this->_input;
}

double	Convert::getValue(void) const {
	return this->_value;
}


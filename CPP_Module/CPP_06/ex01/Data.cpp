/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:08:47 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/30 21:53:38 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"

Data::Data(void): _name("CPP"), _height(0.0), _weight(0.0), _age(0) {}

Data::~Data(void) {}

Data::Data(std::string name, float height, float weight, int age)
	:_name(name), _height(height), _weight(weight), _age(age)
{
	
}

Data::Data(Data const &src) {
	*this = src;
}

Data&	Data::operator=(Data const &src) {
	if (this != &src)
	{
		this->_name = src.getName();
		this->_height = src.getHeight();
		this->_weight = src.getWeight();
		this->_age = src.getAge();
	}
	return (*this);
}

std::string	Data::getName(void) const {
	return this->_name;
}

float	Data::getHeight(void) const {
	return this->_height;
}

float	Data::getWeight(void) const {
	return this->_weight;
}

int	Data::getAge(void) const {
	return this->_age;
}

std::ostream&	operator<<(std::ostream& out, Data const &data) {

}

uintptr_t		serialize(Data* ptr) {

}

Data*			deserialize(uintptr_t raw) {

}

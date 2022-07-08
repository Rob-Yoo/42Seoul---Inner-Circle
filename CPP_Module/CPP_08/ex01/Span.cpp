/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:09 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/08 20:30:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

const char* Span::CannotSpanException::what(void) const throw() {
	return "Not Enough Element, so Cannot Span!!";
}

const char* Span::CannotStoreException::what(void) const throw() {
	return "Cannot Store Anymore!!";
} 

Span::Span(std::size_t N) { this->_data.reserve(N); }

Span::Span(void) {}

Span::~Span(void) {}

Span::Span(Span const &src): _data(src.getData()){}

Span&	Span::operator=(Span const &src) {
	if (this != &src)
	{
		std::vector<int>	src_cpy = src.getData();
		if (this->_data.size() > 0)
			this->_data.clear();
		if (this->_data.capacity() < src_cpy.capacity())
			this->_data.reserve(src_cpy.capacity());
		for (std::vector<int>::iterator iter = src_cpy.begin();iter != src_cpy.end();iter++)
			this->_data.push_back(*iter);
	}
	return *this;
}

void		Span::addNumber(int num) throw(CannotStoreException) {
	if (this->_data.size() == this->_data.capacity())
		throw CannotStoreException();
	this->_data.push_back(num);
}

namespace {
	int	convert_abs(int &i) {
		return std::abs(i);
	}
}

int	Span::shortestSpan(void) throw(CannotSpanException) {
	if (_data.size() < 2)
		throw CannotSpanException();
	std::vector<int>	copy_data(this->_data);
	std::sort(copy_data.begin(), copy_data.end());
	std::adjacent_difference(copy_data.begin(), copy_data.end(), copy_data.begin());
	std::transform(++copy_data.begin(), copy_data.end(), copy_data.begin(), convert_abs);
	return *std::min_element(copy_data.begin(), copy_data.end());
}

int	Span::longestSpan(void) throw(CannotSpanException) {
	if (_data.size() < 2)
		throw CannotSpanException();
	return *(std::max_element(this->_data.begin(), this->_data.end())) - *(std::min_element(this->_data.begin(), this->_data.end()));
}

std::vector<int>	Span::getData(void) const { return this->_data; }

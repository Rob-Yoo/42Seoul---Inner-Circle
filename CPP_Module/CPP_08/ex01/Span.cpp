/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:09 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/07 16:31:32 by jinyoo           ###   ########.fr       */
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
		std::vector<int>::iterator	iter;
		if (this->_data.size() != 0)
			this->_data.clear();
		if (this->_data.capacity() < src.getData().capacity())
			this->_data.reserve(src.getData().capacity());
		for (iter = src.getData().begin();iter != src.getData().end();iter++)
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
	std::sort(std::begin(copy_data), std::end(copy_data));
	std::adjacent_difference(std::begin(copy_data), std::end(copy_data), std::begin(copy_data));
	std::transform(++std::begin(copy_data), std::end(copy_data), std::begin(copy_data), convert_abs);
	return *std::min_element(std::begin(copy_data), std::end(copy_data));
}

int	Span::longestSpan(void) throw(CannotSpanException) {
	if (_data.size() < 2)
		throw CannotSpanException();
	std::pair<std::vector<int>::iterator, std::vector<int>::iterator> p = std::minmax_element(this->_data.begin(), this->_data.end());
	return *(p.second) - *(p.first);
}

std::vector<int>	Span::getData(void) const { return this->_data; }

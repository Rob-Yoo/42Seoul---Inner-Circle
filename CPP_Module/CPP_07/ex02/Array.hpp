/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:50:15 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/03 15:16:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <cstdlib>
# include <iostream>
# include <exception>

template <typename T>
class Array {
public:
	class InvalidIndexAccess: public std::exception {
		public:
			const char* what(void) const throw() {
				return "Invalid Index Access";
			}
	};

	Array(void): _size(0), _data(NULL) {}

	Array(std::size_t n): _size(n), _data(NULL) {
		if (this->_size)
			this->_data = new T[this->_size];
	}

	Array(Array const &src): _data(NULL) {
		*this = src;
	}

	~Array(void) {
		std::cout << "Array Destructor Called" << std::endl;
		if (this->_size) {
			delete[] _data;
			this->_data = NULL;
		}
	}

	Array&	operator=(Array const &src) {
		if (this != &src) {
			if (this->_size) {
				delete[] _data;
				this->_data = NULL;
			}
			this->_size = src.getSize();
			if (this->_size)
			{
				this->_data = new T[this->_size];
				for (std::size_t i = 0 ; i < this->_size ; ++i) {
						this->_data[i] = src[i];
				}
			}
		}
		return *this;
	}

	size_t	getSize(void) const {
		return this->_size;
	}

	T&	operator[](std::size_t i) {
		if (this->_size <= i)
			throw InvalidIndexAccess();
		return this->_data[i];
	}

	const T&	operator[](std::size_t i) const {
	if (i >= _size)
		throw InvalidIndexAccess();
	return _data[i];
	}
private:
	std::size_t _size;
	T* _data;
};

#endif
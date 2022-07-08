/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:45 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/08 20:27:55 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <cstddef>
# include <cstdlib>
# include <iostream>
# include <exception>
# include <algorithm>
# include <vector>
# include <numeric>
# include <utility>

class Span {
public:
	class CannotStoreException: public std::exception {
	public:
		const char* what(void) const throw();
	};

	class CannotSpanException: public std::exception {
	public:
		const char* what(void) const throw();
	};

	Span(std::size_t N);
	~Span(void);
	Span(Span const &src);

	Span&		operator=(Span const &src);

	void	addNumber(int num) throw(CannotStoreException);
	template<typename T>
	void addRange(T begin, T end) throw(CannotStoreException) {
		if (std::distance(begin, end) > static_cast<long>(_data.capacity() - _data.size()))
			throw CannotStoreException();
		while (begin != end)
			_data.push_back(*begin++);
	}
	int		shortestSpan(void) throw(CannotSpanException);
	int		longestSpan(void) throw(CannotSpanException);

	std::vector<int>	getData(void) const;
private:
	std::vector<int>	_data;
	Span(void);
};

#endif

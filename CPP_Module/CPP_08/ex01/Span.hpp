/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:04:45 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/06 22:19:29 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <cstddef>
# include <iostream>
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
	int		shortestSpan(void) throw(CannotSpanException);
	int		longestSpan(void) throw(CannotSpanException);

	std::vector<int>	getData(void) const;
private:
	std::vector<int>	_data;
	Span(void);
};

#endif

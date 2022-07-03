/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 21:10:47 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/03 14:06:50 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

# include <iostream>
# include <string>

template<typename T>
void	swap(T &x, T &y) {
	if (x == y)
		return ;
	T	tmp;
	tmp = x;
	x = y;
	y = tmp;
}

template<typename T>
T	min(const T &x, const T &y) {
	if (x <= y)
		return x;
	else
		return y;
}

template<typename T>
T	max(const T &x, const T &y) {
	if (x >= y)
		return x;
	else
		return y;
}

# endif

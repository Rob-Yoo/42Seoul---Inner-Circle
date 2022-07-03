/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 19:19:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/03 14:01:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

# include <cstddef>
# include <iostream>
# include <string>

template<typename T>
void	iter(T	*arr, std::size_t len, void(*func)(const T&)) {
	for (std::size_t i = 0; i < len; i++)
		func(arr[i]);
	std::cout << std::endl;
}

template<typename T>
void	ft_print(const T &param) {
	std::cout << param << " ";
}

#endif

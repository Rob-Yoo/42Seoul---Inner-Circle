/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 15:33:53 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/08 19:44:35 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EASY_FIND_HPP
# define EASY_FIND_HPP

# include <exception>
# include <iostream>
# include <algorithm>

template<typename T>
typename T::iterator easyfind(T& container, int data) {
	typename T::iterator	iter;
	// for (iter = container.begin();iter != container.end();iter++) {
	// 	if (*iter == data)
	// 		return iter;
	// }
	iter = std::find(container.begin(), container.end(), data);
	return iter;
}


#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 23:11:25 by jinyoo            #+#    #+#             */
/*   Updated: 2023/01/19 23:11:27 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft {

template<typename T>
struct is_integral {
	typedef T type;
	const static bool value = false;
};

template<>
struct is_integral<bool> {
	typedef bool type;
	const static bool value = true;
};
template<>
struct is_integral<char> {
	typedef char type;
	const static bool value = true;
};
template<>
struct is_integral<wchar_t> {
	typedef wchar_t type;
	const static bool value = true;
};
template<>
struct is_integral<signed char> {
	typedef signed char type;
	const static bool value = true;
};
template<>
struct is_integral<short int> {
	typedef short int type;
	const static bool value = true;
};
template<>
struct is_integral<int> {
	typedef int type;
	const static bool value = true;
};
template<>
struct is_integral<long int> {
	typedef long int type;
	const static bool value = true;
};
template<>
struct is_integral<long long int> {
	typedef long long int type;
	const static bool value = true;
};
template<>
struct is_integral<unsigned char> {
	typedef unsigned char type;
	const static bool value = true;
};
template<>
struct is_integral<unsigned short int> {
	typedef unsigned short int type;
	const static bool value = true;
};
template<>
struct is_integral<unsigned int> {
	typedef unsigned int type;
	const static bool value = true;
};
template<>
struct is_integral<unsigned long int> {
	typedef unsigned long int type;
	const static bool value = true;
};
template<>
struct is_integral<unsigned long long int> {
	typedef unsigned long long int type;
	const static bool value = true;
};

}

#endif
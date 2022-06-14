/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:00:11 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/14 12:38:19 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIXED_HPP
# define FIXED_HPP

#include <iostream>

class Fixed {
public:
	Fixed(void);
	Fixed(const Fixed& inst);
	~Fixed(void);
	Fixed&	operator=(const Fixed& src);

	int		getRawBits(void) const;
	void	setRawBits(int const rawBits);
private:
	const static int	_bits;
	int					_value;
};

#endif

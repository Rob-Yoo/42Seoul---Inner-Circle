/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:08:56 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/30 21:53:11 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_HPP
# define DATA_HPP

# include <iostream>
# include <cstdint>
# include <string>

class Data {
public:
	Data(void);
	~Data(void);
	Data(Data const &src);
	Data(std::string name, float height, float weight, int age);

	Data&	operator=(Data const &src);

	std::string	getName(void) const;
	float		getHeight(void) const;
	float		getWeight(void) const;
	int			getAge(void) const;
private:
	std::string	_name;
	float		_height;
	float		_weight;
	int			_age;
};

std::ostream&	operator<<(std::ostream& out, Data const &data);
uintptr_t		serialize(Data* ptr);
Data*			deserialize(uintptr_t raw);

#endif

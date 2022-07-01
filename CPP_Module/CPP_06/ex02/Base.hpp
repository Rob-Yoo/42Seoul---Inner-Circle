/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:10:41 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 15:15:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <exception>

class Base {
public:
	virtual ~Base(void);
};

class A: public Base {};

class B: public Base {};

class C: public Base {};

Base*	generate(void);
void	identify(Base* p);
void	identify(Base& p);

#endif

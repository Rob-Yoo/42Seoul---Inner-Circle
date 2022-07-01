/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 01:10:34 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:34:40 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base(void) {}

Base*	generate(void) {
	int c_num = std::rand() % 3;
	if (c_num == 0)
		return new A();
	else if (c_num == 1)
		return new B();
	else if (c_num == 2)
		return new C();
	return nullptr;
}

void	identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
}

namespace {
	void	try_down_cast(Base &p, std::string c_name) {
		try {
			if (c_name == "A")
				(void)dynamic_cast<A&>(p);
			else if (c_name == "B")
				(void)dynamic_cast<B&>(p);
			else if (c_name == "C")
				(void)dynamic_cast<C&>(p);
			std::cout << c_name << std::endl;
		} catch (std::exception &e) {
			return ;
		}
	}
}

void	identify(Base& p) {
	try_down_cast(p, "A");
	try_down_cast(p, "B");
	try_down_cast(p, "C");
}

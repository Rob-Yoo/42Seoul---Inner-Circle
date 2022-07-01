/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 16:00:21 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:31:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main(void)
{
	for (int i = 0 ; i < 10 ; ++i) {
		Base* base = generate();
		identify(base);
		identify(*base);
		std::cout << std::endl;
		delete base;
	}
	return 0;
}


// class Parent {
// public:
// 	virtual void print(void) { std::cout << "Parent" << std::endl; }
// };
// class Child1: public Parent {
// public:
// 	void print(void) { std::cout << "Child1" << std::endl; }
// };
// class Child2: public Parent {
// public:
// 	void print(void) { std::cout << "Child2" << std::endl; }
// };

// int main() {
// 	Child1	a;
// 	Parent	*bp = dynamic_cast<Parent*>(&a);
// 	Child1	*ap = dynamic_cast<Child1*>(bp);
// 	if (ap == nullptr)
// 		std::cout << "NULL PTR" << std::endl;
// 	else
// 	{
// 		std::cout << "NOT NULL\n";
// 		ap->print();
// 	}
// 	return (0);
// }
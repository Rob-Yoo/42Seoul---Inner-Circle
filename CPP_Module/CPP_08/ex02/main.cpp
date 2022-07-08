/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:54:00 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/08 20:45:13 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

void test_normal(void) {
	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);
	std::cout << mstack.top() << std::endl;
	mstack.pop();
	std::cout << mstack.size() << std::endl;
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
}

void test_reverse_iterator(void) {
	MutantStack<float> mstack;
	mstack.push(1.1f);
	mstack.push(2.2f);
	mstack.push(3.3f);
	mstack.push(4.4f);
	mstack.push(5.5f);
	MutantStack<float>::reverse_iterator rit = mstack.rbegin();
	MutantStack<float>::reverse_iterator rite = mstack.rend();
	++rit;
	--rit;
	while (rit != rite) {
		std::cout << *rit << std::endl;
		++rit;
	}
}

int main(void) {
	test_normal();
	std::cout << std::endl;
	test_reverse_iterator();
	std::cout << std::endl;
	return 0;
}
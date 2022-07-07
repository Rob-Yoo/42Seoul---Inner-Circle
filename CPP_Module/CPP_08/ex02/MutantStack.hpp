/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:54:48 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/07 19:37:50 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANT_STACK_HPP
# define MUTANT_STACK_HPP

# include <iostream>
# include <algorithm>
# include <stack>

template<typename T>
class MutantStack: public std::stack<T> {
public:
	MutantStack(void) {}
	~MutantStack(void) {}
	MutantStack(MutantStack const &src) { *this = src; }

	MutantStack&	operator=(MutantStack const &src) {
		if (this != &src)
			std::stack<T>::operator=(src);
		return *this;
	}

	typedef typename std::stack<T>::container_type::iterator iterator;
	typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;

	iterator begin(void) {
		return this->c.begin();
	}

	iterator end(void) {
		return this->c.end();
	}

	reverse_iterator rbegin(void) {
		return this->c.rbegin();
	}

	reverse_iterator rend(void) {
		return this->c.rend();
	}
};

#endif

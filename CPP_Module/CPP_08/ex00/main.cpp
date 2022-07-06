/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:22:55 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/06 17:02:06 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"
#include <iterator>
#include <vector>
#include <list>
#include <deque>

#define FIND_DATA 9

int main(void) {
	std::deque<int> d;
	std::list<int> l;
	std::vector<int> v;

	for (int i = 0 ; i < 10 ; i++) {
		d.push_back(i);
		l.push_back(i);
		v.push_back(i);
	}
	std::deque<int>::iterator d_iter = easyfind(d, FIND_DATA);
	if (d_iter == d.end())
		std::cerr << "Cannot find " << FIND_DATA << " in this Deque\n";
	else
		std::cout << "Find " << FIND_DATA << " in this Deque at " << std::distance(d.begin(), d_iter) << " index\n";

	std::cout << std::endl;

	std::list<int>::iterator l_iter = easyfind(l, FIND_DATA);
	if (l_iter == l.end())
		std::cerr << "Cannot find " << FIND_DATA << " in this List\n";
	else
		std::cout << "Find " << FIND_DATA << " in this List at " << std::distance(l.begin(), l_iter) << " index\n";

	std::cout << std::endl;

	std::vector<int>::iterator v_iter = easyfind(v, FIND_DATA);
	if (v_iter == v.end())
		std::cerr << "Cannot find " << FIND_DATA << " in this Vector\n";
	else
		std::cout << "Find " << FIND_DATA << " in this Vector at " << std::distance(v.begin(), v_iter) << " index\n";
	return 0;
}

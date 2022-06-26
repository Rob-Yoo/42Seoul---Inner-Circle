/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 20:50:16 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/26 20:52:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
	try
	{
		Bureaucrat A("jinyoo", 10);
		// 유효하지 않은 grade로 생성자 호출
		Bureaucrat B(A);
		Bureaucrat C("soo", 150);

		std::cout << std::endl;

		//표준출력
		std::cout << A << std::endl;
		std::cout << B << std::endl;
		std::cout << C << std::endl;
		std::cout << std::endl;

		// A.incre_grade(11);
		// A.incre_grade(10);
		// A.decre_grade(141);

		A.incre_grade(9);
		// A.decre_grade(-9);

		std::cout << std::endl;

		//표준출력
		std::cout << A << std::endl;
		std::cout << B << std::endl;
		std::cout << C << std::endl;
		std::cout << std::endl;

	}
	catch (std::exception &e)
	{
		std::cerr << "Exception : " << e.what() << std::endl;
	}
	return 0;
}
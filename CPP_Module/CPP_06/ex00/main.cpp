/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:11:17 by jinyoo            #+#    #+#             */
/*   Updated: 2022/07/01 16:36:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Convert.hpp"

int	main(int argc, char **argv)
{
	if (argc == 2) {
		try
		{
			Convert A(argv[1]);
			Convert B(A);

			A.printConvert();
		} catch (std::exception &e) {
			std::cerr << "Exception : " << e.what() << std::endl;
		}
	}
	else
		std::cerr << "./convert { Converted Input }" << std::endl;
	return 0;
}

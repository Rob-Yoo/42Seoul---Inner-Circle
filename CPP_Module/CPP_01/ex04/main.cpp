/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 21:33:33 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/06 20:22:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>

void	replace_contents(std::ifstream &input, std::ofstream &output, char *argv[])
{
	std::string::size_type	pos;
	std::string				to_find(argv[2]);
	std::string				replace(argv[3]);
	std::string				line;
	std::string				new_line;
	bool					is_first_line = true;

	while (std::getline(input, line))
	{
		pos = line.find(to_find);
		if (pos == std::string::npos)
			is_first_line ? output << line : output << std::endl << line;
		else
		{
			if (!is_first_line)
				output << std::endl;
			output << line.substr(0, pos) << replace;
			new_line = line.substr(pos + to_find.length());
			pos = new_line.find(to_find);
			while (pos != std::string::npos)
			{
				output << new_line.substr(0, pos) << replace;
				new_line = new_line.substr(pos + to_find.length());
				pos = new_line.find(to_find);
			}
			output << new_line;
		}
		if (is_first_line)
			is_first_line = false;
	}
}

int	main(int argc, char *argv[])
{

	if (argc != 4)
		std::cerr << "usage : ./replace filename s1 s2\n";
	else
	{
		std::string		file_name(argv[1]);
		std::ifstream	input_file(file_name);

		if (input_file.is_open())
		{
			std::ofstream	output_file(file_name + ".replace");
			if (output_file.is_open())
			{
				replace_contents(input_file, output_file, argv);
				output_file.close();
			}
			else
				std::cerr << "Error\n";
			input_file.close();
		}
		else
			std::cerr << "Error\n";
	}
	return 0;
}
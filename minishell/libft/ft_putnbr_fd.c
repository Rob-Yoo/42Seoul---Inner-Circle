/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:54:46 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/18 15:40:56 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	int_to_char(int num, int fd)
{
	int	fin;

	fin = num % 10;
	if (num == 0)
		return ;
	num = num / 10;
	int_to_char(num, fd);
	ft_putchar_fd(fin + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long long	num;
	long long	fin;

	if (fd < 0)
		return ;
	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	fin = num % 10;
	int_to_char(num / 10, fd);
	ft_putchar_fd(fin + '0', fd);
}

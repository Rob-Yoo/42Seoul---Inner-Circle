/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 21:09:59 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/06 15:27:22 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util.h"

static void	ft_putnbr(int n, int fd)
{
	char	num;

	if ((n / 10) == 0)
	{
		num = (n % 10) + '0';
		write(fd, &num, 1);
		return ;
	}
	ft_putnbr(n / 10, fd);
	num = (n % 10) + '0';
	write(fd, &num, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2147483648", 10);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr(-n, fd);
	}
	else
		ft_putnbr(n, fd);
}

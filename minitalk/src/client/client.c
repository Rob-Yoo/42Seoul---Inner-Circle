/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:41:49 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/07 18:54:41 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_msg(t_msg *info)
{
	int	i;
	int	bit;
	int	flag;

	i = 0;
	while (info->msg[i])
	{
		bit = 1;
		while (bit <= 8)
		{
			flag = info->msg[i] >> (8 - bit) & 1;
			if (flag == 0)
				kill(info->pid, SIGUSR1);
			else if (flag == 1)
				kill(info->pid, SIGUSR2);
			usleep(100);
			bit++;
		}
		i++;
	}
}

static char	*addNewLineChar(char *str)
{
	char	*temp;

	temp = str;
	while(*str)
		str++;
	*str = '\n';
	str++;
	*str = '\0';
	return temp;
}

int	main(int argc, char *argv[])
{
	t_msg	info;
	char	*msg;

	if (argc != 3)
	{
		ft_putstr_fd("usage => ./client pid message", 1);
		exit(1);
	}
	info.pid = ft_atoi(argv[1]);
	if (info.pid < 101 || info.pid > 99999)
	{
		ft_putstr_fd("Wrong pid Number\n", 1);
		exit(1);
	}
	msg = addNewLineChar(argv[2]);
	info.msg = msg;
	send_msg(&info);
	return (0);
}
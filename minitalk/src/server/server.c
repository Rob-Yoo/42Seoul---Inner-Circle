/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:26:25 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/09 21:37:56 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void	msg_handler(int signal)
{
	static t_text	chr;

	if (signal == SIGUSR1)
	{
		chr.character |= 0; 
		if (chr.bit < 7)
			chr.character <<= 1;
	}
	else if (signal == SIGUSR2)
	{
		chr.character |= 1;
		if (chr.bit < 7)
			chr.character <<= 1;
	}
	chr.bit++;
	if (chr.bit == 8)
	{
		write(1, &chr.character, 1);
		chr.character = 0;
		chr.bit = 0;
	}	
}

int	main(void)
{
	int	pid;

	pid = getpid();
	ft_putstr_fd("server pid: ", 1);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, msg_handler);
	signal(SIGUSR2, msg_handler);
	while (1)
		pause();
}

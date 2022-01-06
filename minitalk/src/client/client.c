/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 16:41:49 by jinyoo            #+#    #+#             */
/*   Updated: 2022/01/06 16:58:31 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int main(int argc, char *argv[])
{
	t_msg	info;

	if (argc != 3)
	{
		ft_putstr_fd("usage => ./client pid message", 1);
		exit(1);
	}
	info->pid = ft_atoi(argv[1]);
	if (info->pid < 101 || info->pid > 99999)
	{
		ft_putstr_fd("Wrong pid Number\n", 1);
		exit(1);
	}
	info.msg = argv[2];
	send_msg(&info);
	return (0);
}
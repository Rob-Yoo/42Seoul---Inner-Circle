/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 16:26:13 by minjupar          #+#    #+#             */
/*   Updated: 2021/05/11 00:12:01 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	if (fd < 0)
		return ;
	if (str)
	{
		ft_putstr_fd(str, fd);
		write(fd, "\n", 1);
	}
}

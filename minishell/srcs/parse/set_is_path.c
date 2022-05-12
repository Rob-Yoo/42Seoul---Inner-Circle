/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_is_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 03:19:21 by minjupar          #+#    #+#             */
/*   Updated: 2022/04/30 20:18:41 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_is_path(t_cmd *cmd)
{
	int		i;
	t_cmd	*cur;

	i = -1;
	cur = cmd;
	if (!cur->cmd)
		return ;
	while (cur)
	{
		if (!cur->cmd)
			return ;
		if (ft_strchr(cur->cmd, '/'))
			cur->is_path = 1;
		cur = cur->next;
	}
}

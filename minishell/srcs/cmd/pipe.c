/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 21:15:07 by jinyoo            #+#    #+#             */
/*   Updated: 2022/06/30 13:34:18 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	use_pipe(t_cmd *command, int *pipe_open)
{
	if (command->is_pipe || (command->prev && command->prev->is_pipe))
	{
		*pipe_open = TRUE;
		if (pipe(command->pipe) == ERROR)
			return (ERROR);
	}
	else
		*pipe_open = FALSE;
	return (SUCCESS);
}

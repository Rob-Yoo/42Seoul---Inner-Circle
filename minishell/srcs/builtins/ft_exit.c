/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/09 22:33:51 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	ft_exit_handler(int argv)
{
	if (argv < 0)
		exit(256 + argv);
	else
		exit(argv);
}

void	ft_exit(t_cmd *command)
{
	if (!command->is_pipe && (!command->prev || !command->prev->is_pipe))
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		if (!command->argv[1])
			exit(127);
	}
	if (!check_exit(command->argv[1]))
	{
		ft_putstr_fd("soobash: exit: ", STDERR_FILENO);
		ft_putstr_fd(command->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit(255);
	}
	else if (command->argc > 2)
	{
		ft_putendl_fd("soobash: exit: too many arguments", STDERR_FILENO);
		if (command->is_pipe || (command->prev && command->prev->is_pipe))
			exit(1);
		else
			g_state.exit_status = 1;
		return ;
	}
	else
		ft_exit_handler(ft_atoi(command->argv[1]));
}

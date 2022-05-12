/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 01:19:13 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_error_print(char *error_props)
{
	ft_putstr_fd("soobash: unset: '", STDERR_FILENO);
	ft_putstr_fd(error_props, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_state.exit_status = 1;
	return ;
}

static void	unset_env(int index)
{
	char	**temp;
	int		i;
	int		j;

	temp = (char **)malloc(sizeof(char *) * ft_twoptr_len(g_state.envp));
	if (!temp)
		return (ft_error());
	i = -1;
	j = -1;
	while (g_state.envp[++i])
	{
		if (i != index)
			temp[++j] = g_state.envp[i];
	}
	temp[j + 1] = NULL;
	free(g_state.envp[index]);
	free(g_state.envp);
	g_state.envp[index] = NULL;
	g_state.envp = temp;
}

static void	handle_unset(char *argv)
{
	int		index;

	if (!is_valid_env_key(argv))
		return (ft_unset_error_print(argv));
	index = get_env_index(argv);
	if (index >= 0)
		unset_env(index);
}

void	ft_unset(t_cmd *command)
{
	int	i;

	i = 0;
	g_state.exit_status = 0;
	while (command->argv[++i])
		handle_unset(command->argv[i]);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 01:33:20 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(char *key, char *new_value)
{
	int		index;
	char	*new_env_value;
	char	*new_temp;

	new_temp = ft_strjoin("=", new_value);
	index = get_env_index(key);
	free(g_state.envp[index]);
	g_state.envp[index] = NULL;
	if (new_temp != NULL)
		new_env_value = ft_strjoin(key, new_temp);
	else
		new_env_value = ft_strdup(key);
	g_state.envp[index] = new_env_value;
	free(new_temp);
	new_temp = NULL;
	return ;
}

void	set_new_env(char *key, char *new_value)
{
	int		i;
	int		len;
	char	**temp;
	char	*new_temp;

	new_temp = ft_strjoin("=", new_value);
	len = ft_twoptr_len(g_state.envp);
	temp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!temp)
		return (ft_error());
	i = -1;
	while (g_state.envp[++i])
		temp[i] = g_state.envp[i];
	if (new_temp != NULL)
		temp[i++] = ft_strjoin(key, new_temp);
	else
		temp[i++] = ft_strdup(key);
	temp[i] = NULL;
	free(g_state.envp);
	g_state.envp = temp;
	free(new_temp);
	new_temp = NULL;
	return ;
}

static void	print_not_valid_key(char *argv)
{
	ft_putstr_fd("soobash: export: `", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	g_state.exit_status = 1;
	return ;
}

static void	handle_export(char *argv)
{
	char	*key;
	char	*new_value;

	key = get_env_key(argv, 0);
	new_value = get_new_value(key, argv);
	if (!is_valid_env_key(key))
		return (print_not_valid_key(argv));
	if (get_env_index(key) >= 0)
		update_env(key, new_value);
	else
		set_new_env(key, new_value);
	free(key);
	key = NULL;
	free(new_value);
	new_value = NULL;
}

void	ft_export(t_cmd *command)
{
	int	i;

	g_state.exit_status = 0;
	if (command->argc == 1)
		return (print_envp());
	i = 0;
	while (command->argv[++i])
		handle_export(command->argv[i]);
}

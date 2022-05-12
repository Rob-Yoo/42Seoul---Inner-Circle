/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 04:52:40 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env(char **envp)
{
	int	i;

	i = -1;
	g_state.envp = (char **)malloc(sizeof(char *) * (ft_twoptr_len(envp) + 1));
	if (!g_state.envp)
		return (ft_error());
	while (envp[++i])
		g_state.envp[i] = ft_strdup(envp[i]);
	g_state.envp[i] = NULL;
	return ;
}

char	*get_env_key(char *command, int start)
{
	int		i;
	int		len;
	char	*key;

	len = 0;
	if (command[start] == '$')
		start++;
	i = start;
	if (command[i] == '?')
		return (ft_strdup("?"));
	while (command[i])
	{
		if (!ft_isalnum(command[i]))
			break ;
		i++;
		len++;
	}
	key = ft_substr(command, start, len);
	return (key);
}

char	*get_env(char *key)
{
	int		i;
	char	*temp;

	i = -1;
	if (ft_strlen(key) == 0)
		return (ft_strdup(""));
	if (!ft_strncmp(key, "?", ft_strlen(key)))
		return (ft_itoa(g_state.exit_status));
	temp = ft_strjoin(key, "=");
	while (g_state.envp[++i])
	{
		if (!ft_strncmp(g_state.envp[i], temp, ft_strlen(temp)))
		{
			free(temp);
			temp = NULL;
			return (ft_substr(g_state.envp[i], ft_strlen(key) + 1, \
				ft_strlen(g_state.envp[i]) - ft_strlen(key) + 1));
		}
	}
	free(temp);
	temp = NULL;
	return (ft_strdup(""));
}

void	join_env(char **temp, char *key)
{
	char	*value;
	char	*parse_temp;

	value = get_env(key);
	parse_temp = *temp;
	*temp = ft_strjoin(*temp, value);
	free(value);
	value = NULL;
	free(parse_temp);
	parse_temp = NULL;
	return ;
}

int	parse_env(char **temp, char *command, int start)
{
	char	*key;
	char	*value;
	char	*parse_temp;

	key = get_env_key(command, start);
	if (ft_strlen(key) == 0 && command[start + 1] != '"')
		value = ft_strdup("$");
	else
		value = get_env(key);
	parse_temp = *temp;
	*temp = ft_strjoin(*temp, value);
	start += ft_strlen(key);
	free(key);
	free(value);
	free(parse_temp);
	key = NULL;
	value = NULL;
	parse_temp = NULL;
	return (start);
}

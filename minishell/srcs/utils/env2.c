/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 01:50:32 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 05:23:22 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_index(char *key)
{
	int		i;
	char	**temp;

	i = -1;
	while (g_state.envp[++i])
	{
		temp = ft_split(g_state.envp[i], '=');
		if (!ft_strncmp(temp[0], key, ft_strlen(key) + 1))
		{
			ft_free_two_ptr(temp);
			return (i);
		}
		ft_free_two_ptr(temp);
	}
	return (-1);
}

int	is_valid_env_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (FALSE);
	else
		i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

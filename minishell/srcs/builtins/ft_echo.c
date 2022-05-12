/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 16:01:09 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 20:56:19 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_option(t_cmd *command, int j, char *option)
{
	int	i;

	if (command->argv[j] == NULL)
		return (0);
	if (command->argv[j][0] != '-')
		return (0);
	if (!ft_strncmp("-n", command->argv[j], 3))
	{
		*option = 'n';
		return (1);
	}
	i = 1;
	while (command->argv[j][i])
	{
		if (command->argv[j][i] != 'n')
			return (0);
		i++;
	}
	*option = command->argv[j][i - 1];
	if (*option == 'n')
		return (1);
	return (0);
}

void	ft_echo(t_cmd *command)
{
	char	option;
	int		j;
	int		is_string;

	j = 0;
	is_string = 0;
	option = 0;
	while (command->argv[++j])
	{
		while (!is_string && \
		check_n_option(command, j, &option))
			j++;
		if (command->argv[j] == NULL)
			break ;
		printf("%s", command->argv[j]);
		is_string = 1;
		if (command->argv[j + 1] != NULL)
			printf(" ");
	}
	if (option != 'n')
		printf("\n");
	g_state.exit_status = 0;
	return ;
}

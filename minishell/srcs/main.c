/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 02:13:40 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/11 15:59:30 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote(char *input)
{
	int		i;
	char	c;

	i = -1;
	c = 0;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (c == 0)
				c = input[i];
			else if (c == '\'' && input[i] == '\'')
				c = 0;
			else if (c == '"' && input[i] == '"')
				c = 0;
			else if (c == '\'' && input[i] == '"')
				continue ;
			else if (c == '"' && input[i] == '\'')
				continue ;
		}
	}
	return (c == 0);
}

int	check_input(char *input)
{
	int	i;
	int	space_cnt;

	i = -1;
	space_cnt = 0;
	if (!input)
		return (0);
	while (input[++i])
	{
		if (input[i] == ' ')
			space_cnt++;
	}
	if (ft_strlen(input) == 0)
		return (0);
	if (space_cnt == (int)ft_strlen(input))
	{
		add_history(input);
		return (0);
	}
	if (!check_quote(input))
	{
		ft_putendl_fd("Invalid quote", STDERR_FILENO);
		return (0);
	}
	return (1);
}

char	*read_input(char **input)
{
	*input = readline("soobash$ ");
	return (*input);
}

void	handle_prompt(void)
{
	int		is_error;
	char	*input;
	t_cmd	*head;

	while (read_input(&input))
	{
		if (!check_input(input))
		{
			free(input);
			input = NULL;
			continue ;
		}
		parser(&input, &head);
		is_error = error_cmds(head);
		if (is_error == FALSE)
			execute_cmds(head);
		delete_cmd_list(&head);
		add_history(input);
		free(input);
		input = NULL;
	}
	ft_free_two_ptr(g_state.envp);
}

int	main(int argc, char *argv[], char **envp)
{
	(void)argc;
	(void)argv;
	copy_env(envp);
	init_signal();
	handle_prompt();
	g_state.exit_status = 130;
	return (g_state.exit_status);
}

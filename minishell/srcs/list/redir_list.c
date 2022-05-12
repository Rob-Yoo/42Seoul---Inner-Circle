/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjupar <minjupar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:16:28 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/08 22:55:17 by minjupar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*create_redir_node(int type, char *file_name)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		ft_error();
	node->type = type;
	node->file_name = file_name;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	add_redir_node(t_redir *new_node, t_redir *head)
{
	t_redir	*cur;

	cur = head;
	while (cur->next)
		cur = cur->next;
	new_node->prev = cur;
	cur->next = new_node;
	return ;
}

void	delete_redir_list(t_redir *redir)
{
	t_redir	*temp;
	t_redir	*del_node;

	temp = redir;
	while (temp)
	{
		del_node = temp;
		temp = temp->next;
		free(del_node->file_name);
		del_node->file_name = NULL;
		free(del_node);
		del_node = NULL;
	}
	return ;
}

int	handle_redir(t_cmd *node, int type, char *file_name, int *i)
{
	if (file_name != NULL)
		(*i)++;
	if (type == REDIR_R)
	{
		if (node->output == NULL)
			node->output = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->output);
	}
	else if (type == REDIR_RR)
	{
		if (node->output == NULL)
			node->output = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->output);
	}
	else if (type == REDIR_L)
	{
		if (node->input == NULL)
			node->input = create_redir_node(type, file_name);
		else
			add_redir_node(create_redir_node(type, file_name), node->input);
	}
	return (1);
}

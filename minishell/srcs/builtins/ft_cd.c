/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 21:32:44 by minjupar          #+#    #+#             */
/*   Updated: 2022/05/10 20:50:50 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_path_error(char *path, int is_file)
{
	if (is_file)
	{
		ft_putstr_fd("soobash: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putendl_fd(": Not a directory", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("soobash: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(strerror(2), STDERR_FILENO);
	}
	g_state.exit_status = 1;
}

static void	change_directory_handler(char *old_path)
{
	char	*value;
	char	*pwd;

	pwd = getcwd(0, _PC_PATH_MAX);
	value = get_env("OLDPWD");
	if (ft_strlen(value) > 0)
		update_env("OLDPWD", old_path);
	else
		set_new_env("OLDPWD", old_path);
	update_env("PWD", pwd);
	free(value);
	value = NULL;
	free(pwd);
	pwd = NULL;
	g_state.exit_status = 0;
}

static void	change_directory(char *path, int is_file)
{
	char	*old_path;

	old_path = getcwd(0, _PC_PATH_MAX);
	if (chdir(path) == 0)
		change_directory_handler(old_path);
	else
		print_path_error(path, is_file);
	free(old_path);
	old_path = NULL;
}

void	ft_cd(t_cmd *command)
{
	char		*home;
	int			is_file;
	struct stat	buf;

	home = get_env("HOME");
	is_file = FALSE;
	if (command->argc == 1)
		change_directory(home, is_file);
	else
	{
		if (stat(command->argv[1], &buf) == 0)
			is_file = TRUE;
		change_directory(command->argv[1], is_file);
	}
	free(home);
	home = NULL;
	return ;
}

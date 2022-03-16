/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 15:47:27 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/17 02:33:39 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	is_all_map_textures(t_game *game)
{
	if (!game->map_textures.wall)
		exit(0);
	if (!game->map_textures.score)
		exit(0);
	if (!game->map_textures.player)
		exit(0);
	if (!game->map_textures.exit)
		exit(0);
}

static void	set_map_textures(t_game *game, char texture)
{
	if (texture == '1' && !game->map_textures.wall)
		game->map_textures.wall = 1;
	else if (texture == 'C' && !game->map_textures.score)
		game->map_textures.score = 1;
	else if (texture == 'P' && !game->map_textures.player)
		game->map_textures.player = 1;
	else if (texture == 'E' && !game->map_textures.exit)
		game->map_textures.exit = 1;
}

static void	check_validate_map(t_game *game, char *line, int flag)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(line);
	while (line[++i])
	{
		if (flag && line[i] != '1')
			exit(0);
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && \
		line[i] != 'C' && line[i] != 'E')
			exit(0);
		if ((i == 0 || i == len) && line[i] != '1')
			exit(0);
		if (len != game->width)
			exit(0);
		set_map_textures(game, line[i]);
	}
}

void	check_map(t_game *game, int fd)
{
	char	*line;

	game->height = 1;
	map_textures_init(game);
	while (get_next_line(fd, &line) > 0)
	{
		if (game->height == 1)
		{
			game->width = ft_strlen(line);
			check_validate_map(game, line, 1);
		}
		else
			check_validate_map(game, line, 0);
		free(line);
		game->height += 1;
	}
	check_validate_map(game, line, 1);
	free(line);
	is_all_map_textures(game);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:38:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/17 02:30:07 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	minilibx_init(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, game->width * TILE, \
	game->height * TILE, "so_long");
}

void	map_init(t_game *game, int fd)
{
	char	*line;
	int		col;
	
	col = 0;
	while (get_next_line(fd, &line) > 0)
	{
		draw_init_map(game, line, col);
		free(line);
		col++;
	}
	draw_init_map(game, line, col);
	free(line);
}

void	map_textures_init(t_game *game)
{
	game->map_textures.wall = 0;
	game->map_textures.player = 0;
	game->map_textures.exit = 0;
	game->map_textures.score = 0;
}

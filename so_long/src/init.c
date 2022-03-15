/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:38:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 22:02:53 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	position_init(t_position *position)
{
	position->x = 0;
	position->y = 0;
}

void	minilibx_init(t_game *game)
{
	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "so_long");
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

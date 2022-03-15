/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:56:23 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 22:45:47 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_texture(t_game *game, char what_texture, int x, int y)
{
	char	*xpm_file;
	int		width;
	int		height;
	
	switch (what_texture)
	{
		case 'w':
			xpm_file = "textures/wall.xpm";
		case 'p':
			xpm_file = "textures/player.xpm";
		case 's':
			xpm_file = "textures/score.xpm";
		case 'e':
			xpm_file = "textures/exit.xpm";
		default:
			xpm_file = "";
	}
	game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
	xpm_file, &width, &height);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->img.img_ptr, x, y);
}

void	draw_init_map(t_game *game, char *line, int col)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			draw_texture(game, 'w', i * 60, col * 60);
		else if (line[i] == 'P')
		{
			draw_texture(game, 'p', i * 60, col * 60);
			game->position.x = i * 60;
			game->position.y = col * 60;
		}
		else if (line[i] == 'C')
			draw_texture(game, 'c', i * 60, col * 60);
		else if (line[i] == 'E')
			draw_texture(game, 'e', i * 60, col * 60);
		i++;
	}
}

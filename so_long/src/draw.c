/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:56:23 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/17 02:49:05 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_texture(t_game *game, char texture)
{
	int	width;
	int	height;
	
	switch (texture)
	{
		case 'w':
			game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
			"textures/wall.xpm", &width, &height);
			break;
		case 'p':
			game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
			"textures/player.xpm", &width, &height);
			game->position.img_ptr = game->img.img_ptr;
			break;
		case 'c':
			game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
			"textures/collectible.xpm", &width, &height);
			break;
		case 'e':
			game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, \
			"textures/exit.xpm", &width, &height);
			break;
		default:
			return;
	}
}

void	draw_init_map(t_game *game, char *line, int col)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0')
		{
			if (line[i] == '1')
				draw_texture(game, 'w');
			else if (line[i] == 'P')
			{
				draw_texture(game, 'p');
				game->position.x = i * TILE;
				game->position.y = col * TILE;
			}
			else if (line[i] == 'C')
				draw_texture(game, 'c');
			else if (line[i] == 'E')
				draw_texture(game, 'e');
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
			game->img.img_ptr, i * TILE, col * TILE);
		}
		i++;
	}
}

void	draw_updated_player(t_game *game, int prev_x, int prev_y)
{
	t_img	img;
	int		count_h;
	int		count_w;

	img = game->img;
	img.data = (int *)mlx_get_data_addr(game->position.img_ptr, &img.bpp, \
	&img.size_line, &img.endian);
	count_h = 0;
	while (count_h < TILE)
	{
		count_w = 0;
		while (count_w < TILE)
		{
			img.data[count_h * TILE + count_w] = 0x000000;
			count_w++;
		}
		count_h++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->position.img_ptr, prev_x, prev_y);
	draw_texture(game, 'p');
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, \
	game->position.img_ptr, game->position.x, game->position.y);
}
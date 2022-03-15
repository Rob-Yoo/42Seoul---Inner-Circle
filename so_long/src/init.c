/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:38:51 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 18:01:37 by jinyoo           ###   ########.fr       */
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
	// int	width;
	// int	height;

	game->mlx_ptr = mlx_init();
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIDTH, HEIGHT, "so_long");
	// game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &width, &height);
	// mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, 0, 0);
}

// void	map_init(t_game *game)
// {
// 	int	width;
// 	int	height;


// }

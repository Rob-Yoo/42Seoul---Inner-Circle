/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 21:56:23 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 22:06:01 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_init_map(t_game *game, char *line, int col)
{
	int	width;
	int	height;
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
		{
			game->img.img_ptr = mlx_xpm_file_to_image(game->mlx_ptr, "textures/wall.xpm", &width, &height);
			mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img.img_ptr, i * 60, col * 60);
		}
		i++;
	}
}
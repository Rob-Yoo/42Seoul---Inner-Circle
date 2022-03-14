/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:39:52 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/14 22:17:54 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_pixels_of_tile(t_game *game, int row, int col)
{
	int	tile_row;
	int	tile_col;

	row *= TILES;
	col *= TILES;
	tile_row = 0;
	while (tile_row < TILES)
	{
		tile_col = 0;
		while (tile_col < TILES)
		{
			if (tile_row == TILES - 1 || tile_col == TILES - 1)
				game->img.data[(tile_row + row) * WIDTH + (tile_col + col)] = 0xFFFFFF;
			else
				game->img.data[(tile_row + row) * WIDTH + (tile_col + col)] = 0x8B4513;
			tile_col++;
		}
		tile_row++;
	}
}

void	draw_tiles(t_game *game)
{
	int	row;
	int	col;

	row = 0;
	while (row < ROW)
	{
		col = 0;
		while (col < COL)
		{
			if (game->map[row][col] == 1)
				draw_pixels_of_tile(game, row, col);
			col++;
		}
		row++;
	}
}
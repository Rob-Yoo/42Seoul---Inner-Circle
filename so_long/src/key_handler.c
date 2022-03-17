/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:48:55 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/17 16:09:23 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_player(int keycode, t_game *game)
{
	int	prev_x;
	int	prev_y;

	prev_x = game->position.x;
	prev_y = game->position.y;
	if (keycode == KEY_W)
		game->position.y -= TILE;
	else if (keycode == KEY_S)
		game->position.y += TILE;
	else if (keycode == KEY_A)
		game->position.x -= TILE;
	else if (keycode == KEY_D)
		game->position.x += TILE;
	else if (keycode == KEY_ESC)
		exit(0);
	draw_updated_player(game, prev_x, prev_y);
	return (0);
}

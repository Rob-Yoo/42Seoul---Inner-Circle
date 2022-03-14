/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:48:55 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/14 16:58:17 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, t_position *position)
{
	if (keycode == KEY_W)
		position->y++;
	else if (keycode == KEY_S)
		position->y--;
	else if (keycode == KEY_A)
		position->x--;
	else if (keycode == KEY_D)
		position->x++;
	else if (keycode == KEY_ESC)
		exit(0);
	printf("(x, y): (%d, %d)\n", position->x, position->y);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:50:46 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 22:18:04 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game		game;
	int			fd;

	if (argc != 2)
	{
		printf("[Usage] -> ./so_long {map_file_name.ber}\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	minilibx_init(&game);
	map_init(&game, fd);
	mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &game.position);
	mlx_loop(game.mlx_ptr);
	return (0);
}
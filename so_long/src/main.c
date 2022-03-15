/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:50:46 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/15 18:56:05 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game		game;
	t_position	position;
	int			fd;
	char		*line;

	if (argc != 2)
	{
		printf("[Usage] -> ./so_long {map_file_name.ber}\n");
		return (0);
	}
	(void)argv;
	fd = open(argv[1], O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	printf("%s\n", line);
	free(line);
	minilibx_init(&game);
	mlx_hook(game.win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &position);
	mlx_loop(game.mlx_ptr);
	return (0);
}
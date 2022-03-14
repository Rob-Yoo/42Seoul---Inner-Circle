/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:50:46 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/11 18:32:42 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	position_init(t_position *position)
{
	position->x = 0;
	position->y = 0;
}

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

int	main(void)
{
	t_mlx		mlx;
	t_img		image;
	int			width;
	int			height;
	t_position	position;

	mlx.mlx_ptr = mlx_init();
	position_init(&position);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "Hello, World!");
	image.img_ptr = mlx_xpm_file_to_image(mlx.mlx_ptr, "./wall_w.xpm", &width, &height);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, image.img_ptr, 0, 0);
	mlx_hook(mlx.win_ptr, X_EVENT_KEY_PRESS, 0, &key_press, &position);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

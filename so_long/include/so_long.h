/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:03:57 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/14 16:58:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <mlx.h>

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3 
# define X_EVENT_EXIT 17

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# define TILES 60
# define COL 15
# define ROW 15
# define WIDTH TILES * COL
# define HEIGHT TILES * ROW

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_img
{
	void	*img_ptr;
	int		*data;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_game
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		map[ROW][COL];
	t_img	img;
}	t_game;

void	draw_pixels_of_tile(t_game *game, int row, int col);
void	draw_tiles(t_game *game);
void	minilibx_init(t_game *game);

void	minilibx_init(t_game *game);
void	img_init(t_game *game);
void	map_init(t_game *game);
void	position_init(t_position *position);

int		key_press(int keycode, t_position *position);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinyoo <jinyoo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:03:57 by jinyoo            #+#    #+#             */
/*   Updated: 2022/03/17 02:48:12 by jinyoo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include "minilibx_opengl_20191021/mlx.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3 
# define X_EVENT_EXIT 17

# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_ESC 53

# define TILE 60

typedef struct s_position
{
	int		x;
	int		y;
	void	*img_ptr;
}	t_position;

typedef struct s_map
{
	int	wall;
	int	player;
	int	collectible;
	int	exit;
}	t_map;

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
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	t_img		img;
	t_position	position;
	t_map		map_textures;
}	t_game;

void	minilibx_init(t_game *game);
void	map_init(t_game *game, int fd);
void	map_textures_init(t_game *game);

int		move_player(int keycode, t_game *game);

void	draw_init_map(t_game *game, char *line, int col);
void	draw_texture(t_game *game, char texture);
void	draw_updated_player(t_game *game, int prev_x, int prev_y);

void	check_map(t_game *game, int fd);

void	throw_error();
#endif

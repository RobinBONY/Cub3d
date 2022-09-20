/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:34:36 by rbony             #+#    #+#             */
/*   Updated: 2022/09/20 12:56:48 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<math.h>
# include	"../mlx/mlx_mac/mlx.h"
//# include	"../mlx/mlx_linux/mlx.h"
# include	"../libft/libft.h"
# include	"errors.h"

typedef struct s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct s_vector
{
	float	dx;
	float	dy;
}				t_vector;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}				t_color;

typedef struct s_texture
{
	int					n_texture;
	int					s_texture;
	int					e_texture;
	int					w_texture;
	struct s_color		f_color;
	struct s_color		c_color;
}				t_texture;

typedef struct s_raycasting
{
	struct s_vector	dir;
	struct s_point	step;
	struct s_point	side_hit;
	struct s_vector	delta_dist;
	struct s_vector	side_dist;
	float			dist;
	float			perp_dist;
	int				map_x;
	int				map_y;
	int				side;
}					t_raycasting;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	struct s_data		img;
	int					win_width;
	int					win_height;
	struct s_texture	textures;
	int					**map;
	int					map_width;
	int					map_height;
	struct s_point		player;
	float				pa;
}				t_game;

// read_map
int				read_map(t_game *game, char *mapname);

//check_map
int				check_ext(char *str, char *ext);
int				check_closed_height(char *str);
int				check_closed_width(char *str);
int				create_int_map(t_game *game, t_list *list);
int				check_map_layout(t_list *head, t_game *game);
void			print_data(t_game *game);
void			fill_int_map(t_game *game, t_list *list);
int				check_closed_width(char *str);
int				check_closed_sides(char *str);

int				error_1(char *str);
int				error_2(char *str1, char *str2);
int				parse_textures(t_game *game, t_list **list);
int				split_size(char **split);
float			fixang(float a);
void			raycasting(t_game *game);
int				in_map(t_game *game, int x, int y);
t_raycasting	dda(t_game *game, float ra);
t_point			create_vect(t_point origin, float radian, float length);
t_vector		init_vector(t_point start, t_point dest);

#endif
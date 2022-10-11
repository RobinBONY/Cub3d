/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:34:36 by rbony             #+#    #+#             */
/*   Updated: 2022/10/11 18:56:14 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<math.h>
# include	<sys/time.h>
# include	<time.h>
# include	"../mlx/mlx_mac/mlx.h"
//# include	"../mlx/mlx_linux/mlx.h"
# include	"../libft/libft.h"
# include	"errors.h"

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

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
	struct s_point	vertical;
	struct s_point	ray;
	double			ra;
	struct s_point	o;
	struct s_point	dist;
	int				map_x;
	int				map_y;
	int				dof;
	int				vcolor;
	int				hcolor;
	double			rtan;
}					t_raycasting;

typedef struct s_player
{
	struct s_point	pos;
	struct s_point	dir;
	double			pa;
}					t_player;

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
	struct s_player		player;
	struct timeval		start;
	double				time;
	double				old_time;
	double				frametime;
	double				move_speed;
	double				rot_speed;
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
double			fixang(double a);
void			raycasting(t_game *game);
int				in_map(t_game *game, int x, int y);
void			dda(t_game *game, t_raycasting *ray);
t_point			create_vect(t_point origin, float radian, float length);
t_point			init_vector(t_point start, t_point dest, double camera);
double			get_timestamp(struct timeval start);
void			draw_map(t_game *game);
void			draw_background(t_game *game);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
void			brest(t_game *env, int sx, int sy, int ex, int ey, int color);

#endif
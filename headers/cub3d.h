/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:34:36 by rbony             #+#    #+#             */
/*   Updated: 2022/10/24 11:25:24 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include "../mlx/mlx_mac/mlx.h"
# include "../libft/libft.h"
# include "errors.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_texture
{
	void	*img;
	int		bits_per_pixel;
	int		endian;
	char	*texture_path;
	int		width;
	int		height;
	int		line_length;
	void	*text_address;
}	t_texture;

typedef struct s_map_info
{
	t_texture		n_texture;
	t_texture		s_texture;
	t_texture		e_texture;
	t_texture		w_texture;
	struct s_color	f_color;
	struct s_color	c_color;
}	t_map_info;

typedef struct s_raycasting
{
	struct s_point		vertical;
	struct s_point		ray;
	double				ra;
	struct s_point		o;
	struct s_point		dist;
	int					map_x;
	int					map_y;
	int					dof;
	int					vcolor;
	int					hcolor;
	double				rtan;
	double				tx;
	double				ty;
	double				ratio;
	struct s_texture	rtexture;
	struct s_point		col;
}	t_raycasting;

typedef struct s_player
{
	struct s_point	pos;
	struct s_point	dir;
	double			pa;
}	t_player;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	struct s_data		img;
	int					win_width;
	int					win_height;
	int					**map;
	int					map_width;
	int					map_height;
	struct s_map_info	map_info;
	struct s_player		player;
	struct timeval		start;
	double				time;
	double				old_time;
	int					frametime;
	double				move_speed;
	double				rot_speed;
	int					draw_start;
	int					draw_end;
	int					line_length;
	int					line_height;
	int					keyboard[200];
}	t_game;

// read_map
int				read_map(t_game *game, char *mapname);

// check_map
int				check_ext(char *str, char *ext);
int				check_closed_height(char *str);
int				check_closed_width(char *str);
int				create_int_map(t_game *game, t_list *list);
int				check_map_layout(t_list *head, t_game *game);
int				fill_int_map(t_game *game, t_list *list);
int				check_closed_width(char *str);
int				check_closed_sides(char *str);
int				error_1(char *str);
int				error_2(char *str1, char *str2);
int				parse_textures(t_game *game, t_list **list);
int				split_size(char **split);
double			fixang(double a);
void			raycasting(t_game *game);
int				in_map(t_game *game, int x, int y);
t_raycasting	dda(t_game *game, float ra);
t_point			create_vect(t_point origin, float radian, float length);
t_point			init_vector(t_point start, t_point dest, double camera);
double			get_timestamp(struct timeval start);
void			draw_map(t_game *game);
void			draw_background(t_game *game);
void			my_mlx_pixel_put(t_game *game, int x, int y, int color);
int				store_textures_on_image(t_game *game, t_texture *texture,
					char *texture_path);
int				get_text_pixel(t_texture *texture, int x, int y);
int				check_valid_cells(int **map, t_game *game, int i, int j);
int				ft_isspace(int c);
void			free_split(char **split);
int				split_size(char **split);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			move_left(t_game *game);
void			move_right(t_game *game);
void			rotate_right(t_game *game);
void			rotate_left(t_game *game);
void			vert_facing_left(t_game *game, t_raycasting *ray);
void			vert_facing_right(t_game *game, t_raycasting *ray);
void			vert_up_down(t_game *game, t_raycasting *ray);
void			get_disty(t_game *game, t_raycasting *ray);
void			hori_facing_up(t_game *game, t_raycasting *ray);
void			hori_facing_down(t_game *game, t_raycasting *ray);
void			vert_facing_rl(t_game *game, t_raycasting *ray);
void			print_menu(t_game *data);
int				close_window(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
int				manage_events(t_game *game);
void			clear_game(t_game *game);
void			set_default(t_game *game);
int				check_directory(char *mapname);
unsigned long	rgb_to_hexa(t_color color);
int				check_text_db(t_game *game);
void			calculate_tx(t_raycasting *ray);

#endif
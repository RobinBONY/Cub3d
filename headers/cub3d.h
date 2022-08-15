/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:34:36 by rbony             #+#    #+#             */
/*   Updated: 2022/08/15 17:56:39 by rbony            ###   ########lyon.fr   */
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

typedef struct s_raycasting
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	int		ca;
	int		lineh;
	int		lineoff;
	float	vx;
	float	vy;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	disv;
	float	dish;
}				t_raycasting;

typedef struct s_player
{
	int	px;
	int	py;
	int	pdx;
	int	pdy;
	int	pa;
}				t_player;

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
}				t_game;

// read_map
int			read_map(t_game *game, char *mapname);

//check_map
int			check_ext(char *str, char *ext);
int			check_closed_height(char *str);
int			check_closed_width(char *str);
int			create_int_map(t_game *game, t_list *list);
int			check_map_layout(t_list *head, t_game *game);
void		print_data(t_game *game);
void		fill_int_map(t_game *game, t_list *list);
int			check_closed_width(char *str);
int			check_closed_sides(char *str);

int			error_1(char *str);
int			error_2(char *str1, char *str2);
int			parse_textures(t_game *game, t_list **list);
int			split_size(char **split);
void		draw(t_game *game);
void		draw_background(t_game *game);

#endif
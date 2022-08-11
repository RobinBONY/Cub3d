/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:34:36 by rbony             #+#    #+#             */
/*   Updated: 2022/08/11 14:28:48 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include	<stdlib.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	"../mlx/mlx_mac/mlx.h"
//# include	"../mlx/mlx_linux/mlx.h"
# include	"../libft/libft.h"
# include	"errors.h"

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}				t_color;

typedef struct s_texture
{
	char				*n_texture;
	char				*s_texture;
	char				*e_texture;
	char				*w_texture;
	struct s_color		f_color;
	struct s_color		c_color;
}				t_texture;

typedef struct s_game
{
	void				*mlx;
	void				*win;
	struct s_texture	textures;
	int					**map;
}				t_game;

// read_map
int			read_map(t_game *game, char *mapname);

//check_map
int			check_ext(char *str);

#endif
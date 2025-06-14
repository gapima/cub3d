/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:25:03 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 17:42:17 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <fcntl.h>
# include "../lib/libft/libft.h"
# define WIDTH 640
# define HEIGHT 480
# define MOVE_SPEED 0.5 
# define ROT_SPEED 0.5

# define MAX_MAP_WIDTH 64
# define MAX_MAP_HEIGHT 64


typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
}	t_player;

typedef struct s_config {
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*tex_we;
	char			**map;
}	t_config;


void	init_config(t_config *cfg);
void	hook(void *param);
uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y);
void	parse_cub_file(const char *path, t_config *cfg);
extern int world_map[24][24];
void	render_frame(t_config *cfg);
void   handle_input(mlx_key_data_t keydata, void *param);

#endif

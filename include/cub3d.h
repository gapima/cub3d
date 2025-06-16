/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:25:03 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 15:51:00 by glima            ###   ########.fr       */
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
# define MOVE_SPEED 0.1 
# define ROT_SPEED 0.05

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

	char			**map;

	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;

	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_ea;
	mlx_texture_t	*tex_we;

	uint32_t		floor_color;
	uint32_t		ceiling_color;
}	t_config;

// Core
void	init_config(t_config *cfg);
void	parse_cub_file(const char *path, t_config *cfg);
void	render_frame(t_config *cfg);
void	handle_input(mlx_key_data_t keydata, void *param);
void	hook(void *param);
void	load_textures(t_config *cfg);
mlx_texture_t *get_wall_texture(t_config *cfg, int side, double rayDirX, double rayDirY);

// Validação
void	validate_closed_map(char **map, int height, int width);
// Utils
uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:30:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:30:42 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <MLX42/MLX42.h>
# include "../lib/libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
#include <math.h>

#define TILE_SIZE 32
#define WIDTH 800
#define HEIGHT 600

#define FOV (60 * (M_PI / 180)) // 60 graus em radianos
#define NUM_RAYS 800

typedef struct s_config {
	// Caminhos das texturas
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;

	// Texturas carregadas
	double	player_angle;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*we_texture;
	mlx_texture_t	*ea_texture;

	mlx_image_t *no_img;
	mlx_image_t *so_img;
	mlx_image_t *we_img;
	mlx_image_t *ea_img;

	// Cores do chão e teto
	int		floor_color;
	int		ceiling_color;

	// Mapa
	char	**map;
	int		map_height;
	int		map_width;

	// Jogador
	char	player_dir;
	int		player_x;
	int		player_y;

	// MLX
	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
}	t_config;

typedef enum e_direction {
        NORTH,
        SOUTH,
        EAST,
        WEST
}       t_direction;

typedef struct s_ray_result
{
        double          distance;
        int                     texture_x;
        mlx_texture_t *texture;
        t_direction     direction;
}       t_ray_result;



void	parse_cub_file(const char *path, t_config *cfg);
int		rgb_to_int(char *line);
void	parse_map(t_config *cfg, const char *path);
void	print_map(char **map);
void	parse_map_line(t_list **map_lines, char *line);
char	**convert_list_to_array(t_list *map_lines);
void	validate_map(t_config *cfg);
void	check_map_closed(char **map, int start_x, int start_y);
void	init_game(t_config *cfg);
void	render_frame(void *param);
int		ft_strlen_2d(char **arr);
void	handle_input(t_config *cfg);
void	draw_vertical_slice(t_config *cfg, int screen_x, t_ray_result ray, double ray_angle);
void	render_3d_frame(t_config *cfg);
t_ray_result	cast_ray(t_config *cfg, double ray_angle);

#endif


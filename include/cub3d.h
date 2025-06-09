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

#define TILE_SIZE 32
#define WIDTH 800
#define HEIGHT 600

typedef struct s_config {

	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;

	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;

	// NOVOS CAMPOS PARA O MAPA
	char	**map;
	int		map_height;
	int		map_width;

	// POSIÇÃO DO JOGADOR
	char	player_dir;
	int		player_x;
	int		player_y;

	mlx_t		*mlx;
	mlx_image_t	*img;
	int			width;
	int			height;
}	t_config;

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
#endif


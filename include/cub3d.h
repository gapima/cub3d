/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:25:03 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 01:02:43 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
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

/* ======================= STRUCTS ======================= */

typedef struct s_player {
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_config {
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	char **map;
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	mlx_texture_t *tex_no;
	mlx_texture_t *tex_so;
	mlx_texture_t *tex_ea;
	mlx_texture_t *tex_we;
	uint32_t floor_color;
	uint32_t ceiling_color;
} t_config;

typedef struct s_ray {
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;
} t_ray;

typedef struct s_dda {
	int mapX;
	int mapY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
	double sideDistY;
	int stepX;
	int stepY;
	int hit;
	int side;
} t_dda;

typedef struct s_ray_info
{
	int		x;
	int		draw_start;
	int		draw_end;
	int		line_height;
	double	ray_dir_x;
	double	ray_dir_y;
	double	perp_wall_dist;
	int		side;
}	t_ray_info;


/* ======================= CORE ======================= */

bool init_config(t_config *cfg);
bool parse_cub_file(const char *path, t_config *cfg);
bool load_textures(t_config *cfg);
void render_frame(t_config *cfg);
void handle_input(mlx_key_data_t keydata, void *param);
void hook(void *param);
void handle_close(void *param);

/* ======================= INIT ======================= */

void init_paths(t_config *cfg);
void init_textures(t_config *cfg);
void init_colors_and_map(t_config *cfg);

/* ======================= PLAYER ======================= */

void set_player_direction(t_config *cfg, char dir);
void move_forward(t_config *cfg);

/* ======================= RENDER ======================= */

void draw_ceiling_and_floor(t_config *cfg, int x, int drawStart, int drawEnd);
void draw_wall_slice(t_config *cfg, t_ray_info ray);
double compute_wall_hit_point(t_config *cfg, double perpWallDist, double rayDirX, double rayDirY, int side);
int compute_tex_x(double wallX, int tex_width, double rayDirX, double rayDirY, int side);
mlx_texture_t *get_wall_texture(t_config *cfg, int side, double rayDirX, double rayDirY);
uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y);

/* ======================= PARSE ======================= */

char **read_cub_file(const char *path, t_config *cfg, int *out_height);
bool process_line(t_config *cfg, char *line, char **map, int *y, int fd);
bool handle_map_line(char **map, char *line, int *y, int fd);
bool handle_texture_line(t_config *cfg, char *line);
bool is_map_line(char *line);
void parse_texture_or_color(t_config *cfg, char *line);
int is_valid_map_char(char c);

/* ======================= COLOR ======================= */

uint32_t parse_color(char *line);
int parse_color_component(char *str);

/* ======================= MAP ======================= */

int get_max_width(char **map, int height);
bool pad_map_lines(char **map, int height, int max_width);
void validate_closed_map(char **map, int height, int width);

/* ======================= UTILS ======================= */

void free_config(t_config *cfg);
void free_split(char **split);

#endif

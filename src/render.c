/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:34:47 by glima             #+#    #+#             */
/*   Updated: 2025/06/09 16:34:47 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// src/render.c
#include "cub3d.h"

// static void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	if (x >= 0 && y >= 0 && x < (int)img->width && y < (int)img->height)
// 		mlx_put_pixel(img, x, y, color);
// }

// static void	draw_square(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	int	i, j;

// 	for (i = 0; i < TILE_SIZE; i++)
// 	{
// 		for (j = 0; j < TILE_SIZE; j++)
// 		{
// 			put_pixel(img, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
// 		}
// 	}
// }

void render_frame(void *param)
{
	t_config *cfg = (t_config *)param;

	handle_input(cfg);

	mlx_delete_image(cfg->mlx, cfg->img);
	cfg->img = mlx_new_image(cfg->mlx, cfg->width, cfg->height);
	if (!cfg->img)
	{
		ft_putstr_fd("❌ Erro ao criar imagem na render_frame\n", 2);
		exit(EXIT_FAILURE);
	}

	// Renderiza a visão em primeira pessoa
	draw_ceiling_and_floor(cfg);
	render_3d_frame(cfg);

	// Exibe a imagem renderizada
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
}

// void	draw_vertical_slice(t_config *cfg, int screen_x, t_ray_result ray, double ray_angle)
// {
// 	int		line_height;
// 	int		start;
// 	int		end;
// 	double	corrected_dist;
// 	double	step;
// 	double	texture_pos;
// 	int		y;

// 	// Correção do efeito fish-eye (projeção correta)
// 	corrected_dist = ray.distance * cos(ray_angle - cfg->player_angle);
// 	line_height = (int)(cfg->height / corrected_dist);

// 	start = -line_height / 2 + cfg->height / 2;
// 	if (start < 0) start = 0;

// 	end = line_height / 2 + cfg->height / 2;
// 	if (end >= cfg->height) end = cfg->height - 1;

// 	step = (double)ray.texture->height / line_height;
// 	texture_pos = 0.0;

// 	y = start;
// 	while (y < end)
// 	{
// 		int tex_y = (int)texture_pos & (ray.texture->height - 1);
// 		uint8_t *pixel = ray.texture->pixels + (tex_y * ray.texture->width + ray.texture_x) * 4;
// 		uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

// 		mlx_put_pixel(cfg->img, screen_x, y, color);
// 		texture_pos += step;
// 		y++;
// 	}
// }


void draw_vertical_slice(t_config *cfg, int screen_x, t_ray_result ray, double ray_angle)
{
	int		line_height;
	int		start;
	int		end;
	double	corrected_dist;
	double	step;
	double	texture_pos;
	int		y;

	// Corrige distorção (fisheye)
	corrected_dist = ray.distance * cos(ray_angle - cfg->player_angle);
	line_height = (int)(cfg->height / corrected_dist);

	start = -line_height / 2 + cfg->height / 2;
	if (start < 0)
		start = 0;

	end = line_height / 2 + cfg->height / 2;
	if (end >= cfg->height)
		end = cfg->height - 1;

	// Desenhar teto
	for (y = 0; y < start; y++)
		mlx_put_pixel(cfg->img, screen_x, y, cfg->ceiling_color);

	// Desenhar parede com textura
	step = (double)ray.texture->height / line_height;
	texture_pos = 0.0;
	for (y = start; y < end; y++)
	{
		int tex_y = (int)texture_pos;
		uint8_t *pixel = ray.texture->pixels + (tex_y * ray.texture->width + ray.texture_x) * 4;
		uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

		mlx_put_pixel(cfg->img, screen_x, y, color);
		texture_pos += step;
	}

	// Desenhar chão
	for (y = end; y < cfg->height; y++)
		mlx_put_pixel(cfg->img, screen_x, y, cfg->floor_color);
}




void	render_3d_frame(t_config *cfg)
{
	int		screen_x;
	double	angle_step = (FOV * (M_PI / 180.0)) / cfg->width;
	double	start_angle = cfg->player_angle - (FOV * (M_PI / 180.0)) / 2;

	screen_x = 0;
	while (screen_x < cfg->width)
	{
		double ray_angle = start_angle + screen_x * angle_step;
		t_ray_result result = cast_ray(cfg, ray_angle);
		draw_vertical_slice(cfg, screen_x, result, ray_angle);
		screen_x++;
	}
}


t_ray_result cast_ray(t_config *cfg, double ray_angle)
{
	t_ray_result result;
	result.distance = MAX_DEPTH;
	result.texture = NULL;
	result.texture_x = 0;
	result.direction = ' '; // vazio por padrão

	double ray_x = cfg->player_x + 0.5;
	double ray_y = cfg->player_y + 0.5;
	double ray_dx = cos(ray_angle);
	double ray_dy = sin(ray_angle);
	double step = 0.01;
	double distance = 0.0;

	while (distance < MAX_DEPTH)
	{
		ray_x += ray_dx * step;
		ray_y += ray_dy * step;
		distance += step;

		int map_x = (int)ray_x;
		int map_y = (int)ray_y;

		if (map_x < 0 || map_y < 0 || map_y >= cfg->map_height || map_x >= (int)ft_strlen(cfg->map[map_y]))
			break;

		if (cfg->map[map_y][map_x] == '1')
		{
			result.distance = distance;

			double hit_x = ray_x - floor(ray_x);
			double hit_y = ray_y - floor(ray_y);

			if (hit_x < step && ray_dx < 0)
			{
				result.direction = 'W';
				result.texture = cfg->we_texture;
				result.texture_x = (int)(hit_y * cfg->we_texture->width);
			}
			else if (hit_x > (1.0 - step) && ray_dx > 0)
			{
				result.direction = 'E';
				result.texture = cfg->ea_texture;
				result.texture_x = (int)(hit_y * cfg->ea_texture->width);
			}
			else if (hit_y < step && ray_dy < 0)
			{
				result.direction = 'N';
				result.texture = cfg->no_texture;
				result.texture_x = (int)(hit_x * cfg->no_texture->width);
			}
			else
			{
				result.direction = 'S';
				result.texture = cfg->so_texture;
				result.texture_x = (int)(hit_x * cfg->so_texture->width);
			}
			break;
		}
	}
	return result;
}

void	draw_ceiling_and_floor(t_config *cfg)
{
	int	x, y;

	// Cor do teto
	for (y = 0; y < cfg->height / 2; y++)
	{
		for (x = 0; x < cfg->width; x++)
			mlx_put_pixel(cfg->img, x, y, cfg->ceiling_color);
	}

	// Cor do chão
	for (y = cfg->height / 2; y < cfg->height; y++)
	{
		for (x = 0; x < cfg->width; x++)
			mlx_put_pixel(cfg->img, x, y, cfg->floor_color);
	}
}

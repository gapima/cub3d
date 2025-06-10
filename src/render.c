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

	// Limpa a imagem preenchendo com preto
	for (int y = 0; y < cfg->height; y++)
	{
		for (int x = 0; x < cfg->width; x++)
		{
			mlx_put_pixel(cfg->img, x, y, 0x000000FF);
		}
	}

	// Renderiza a visão em primeira pessoa
	render_3d_frame(cfg);

	// Exibe a imagem renderizada
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
}

void	draw_vertical_slice(t_config *cfg, int screen_x, t_ray_result ray, double ray_angle)
{
	int		line_height;
	int		start;
	int		end;
	double	corrected_dist;
	double	step;
	double	texture_pos;
	int		y;

	// Correção do efeito fish-eye (projeção correta)
	corrected_dist = ray.distance * cos(ray_angle - cfg->player_angle);
	line_height = (int)(cfg->height / corrected_dist);

	start = -line_height / 2 + cfg->height / 2;
	if (start < 0) start = 0;

	end = line_height / 2 + cfg->height / 2;
	if (end >= cfg->height) end = cfg->height - 1;

	step = (double)ray.texture->height / line_height;
	texture_pos = 0.0;

	y = start;
	while (y < end)
	{
		int tex_y = (int)texture_pos & (ray.texture->height - 1);
		uint8_t *pixel = ray.texture->pixels + (tex_y * ray.texture->width + ray.texture_x) * 4;
		uint32_t color = (pixel[0] << 24) | (pixel[1] << 16) | (pixel[2] << 8) | pixel[3];

		mlx_put_pixel(cfg->img, screen_x, y, color);
		texture_pos += step;
		y++;
	}
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



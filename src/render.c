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

static void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < (int)img->width && y < (int)img->height)
		mlx_put_pixel(img, x, y, color);
}

static void	draw_square(mlx_image_t *img, int x, int y, uint32_t color)
{
	int	i, j;

	for (i = 0; i < TILE_SIZE; i++)
	{
		for (j = 0; j < TILE_SIZE; j++)
		{
			put_pixel(img, x * TILE_SIZE + j, y * TILE_SIZE + i, color);
		}
	}
}

void render_frame(void *param)
{
	t_config *cfg = (t_config *)param;
	int x, y;

	handle_input(cfg);
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);

	y = -1;
	while (cfg->map[++y])
	{
		x = -1;
		while (cfg->map[y][++x])
		{
			char tile = cfg->map[y][x];

			if (tile == '1')
			{
				// Desenha a imagem da parede norte (por enquanto)
				mlx_image_to_window(cfg->mlx, cfg->no_img, x * TILE_SIZE, y * TILE_SIZE);
			}
			else if (tile == '0')
			{
				draw_square(cfg->img, x, y, 0xAAAAAAFF); // chão
			}
			else if (tile == 'N' || tile == 'S' || tile == 'E' || tile == 'W')
			{
				draw_square(cfg->img, x, y, 0x00FF00FF); // jogador
			}
			else if (tile == ' ')
			{
				draw_square(cfg->img, x, y, 0x000000FF); // espaço vazio
			}
		}
	}
}

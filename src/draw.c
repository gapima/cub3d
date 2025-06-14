/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 17:47:18 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_frame(t_config *cfg)
{
	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = cfg->player.dir_x + cfg->player.plane_x * cameraX;
		double rayDirY = cfg->player.dir_y + cfg->player.plane_y * cameraX;

		int mapX = (int)cfg->player.pos_x;
		int mapY = (int)cfg->player.pos_y;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double sideDistX, sideDistY;

		int stepX, stepY;
		int hit = 0, side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cfg->player.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cfg->player.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cfg->player.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cfg->player.pos_y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// Validar limites antes de acessar
			if (mapY < 0 || mapX < 0 || !cfg->map[mapY] || !cfg->map[mapY][mapX])
				break;

			if (cfg->map[mapY][mapX] == '1')
				hit = 1;
		}

		double perpWallDist = (side == 0)
			? (mapX - cfg->player.pos_x + (1 - stepX) / 2) / rayDirX
			: (mapY - cfg->player.pos_y + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		uint32_t color = (side == 1) ? 0xAAAAAAFF : 0xFFFFFFFF;

		for (int y = drawStart; y < drawEnd; y++)
			mlx_put_pixel(cfg->img, x, y, color);
	}
}
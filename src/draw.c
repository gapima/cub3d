/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 18:56:06 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t *get_wall_texture(t_config *cfg, int side, double rayDirX, double rayDirY)
{
	if (side == 0)
		return (rayDirX < 0) ? cfg->tex_we : cfg->tex_ea;
	else
		return (rayDirY < 0) ? cfg->tex_no : cfg->tex_so;
}

static void draw_ceiling_and_floor(t_config *cfg, int x, int drawStart, int drawEnd)
{
	int y;
	y = 0;
	while (y < drawStart)
	{
		mlx_put_pixel(cfg->img, x, y, cfg->ceiling_color);
		y++;
	}
	y = drawEnd;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cfg->img, x, y, cfg->floor_color);
		y++;
	}
}

static void draw_wall_slice(t_config *cfg, int x, int drawStart, int drawEnd, int lineHeight, double rayDirX, double rayDirY, double perpWallDist, int side)
{
	mlx_texture_t *tex;
	int tex_width;
	int tex_height;
	double wallX;
	int tex_x;
	int y;
	int d;
	int tex_y;
	uint32_t color;

	tex = get_wall_texture(cfg, side, rayDirX, rayDirY);
	if (!tex)
		return;

	tex_width = tex->width;
	tex_height = tex->height;

	if (side == 0)
		wallX = cfg->player.pos_y + perpWallDist * rayDirY;
	else
		wallX = cfg->player.pos_x + perpWallDist * rayDirX;
	wallX -= floor(wallX);

	tex_x = (int)(wallX * tex_width);
	if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		tex_x = tex_width - tex_x - 1;
	y = drawStart;
	while (y < drawEnd)
	{
		d = y * 256 - HEIGHT * 128 + lineHeight * 128;
		tex_y = ((d * tex_height) / lineHeight) / 256;
		color = get_texture_pixel(tex, tex_x, tex_y);
		mlx_put_pixel(cfg->img, x, y, color);
		y++;
	}
}

void render_frame(t_config *cfg)
{
	int x;
	double cameraX;
	double rayDirX;
	double rayDirY;
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
	double perpWallDist;
	int lineHeight;
	int drawStart;
	int drawEnd;

	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (double)WIDTH - 1;
		rayDirX = cfg->player.dir_x + cfg->player.plane_x * cameraX;
		rayDirY = cfg->player.dir_y + cfg->player.plane_y * cameraX;
		mapX = (int)cfg->player.pos_x;
		mapY = (int)cfg->player.pos_y;
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;
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
			if (mapY < 0 || mapX < 0 || !cfg->map[mapY] || !cfg->map[mapY][mapX])
				break;
			if (cfg->map[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - cfg->player.pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cfg->player.pos_y + (1 - stepY) / 2) / rayDirY;
		lineHeight = (int)(HEIGHT / perpWallDist);
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		draw_ceiling_and_floor(cfg, x, drawStart, drawEnd);
		draw_wall_slice(cfg, x, drawStart, drawEnd, lineHeight, rayDirX, rayDirY, perpWallDist, side);
		x++;
	}
}

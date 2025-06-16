/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:07:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 19:08:32 by glima            ###   ########.fr       */
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

void draw_ceiling_and_floor(t_config *cfg, int x, int drawStart, int drawEnd)
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

double compute_wall_hit_point(t_config *cfg, double perpWallDist, double rayDirX, double rayDirY, int side)
{
	if (side == 0)
		return (cfg->player.pos_y + perpWallDist * rayDirY);
	else
		return (cfg->player.pos_x + perpWallDist * rayDirX);
}

int compute_tex_x(double wallX, int tex_width, double rayDirX, double rayDirY, int side)
{
	int tex_x;

	tex_x = (int)(wallX * tex_width);
	if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void draw_wall_slice(t_config *cfg, int x, int drawStart, int drawEnd, int lineHeight, double rayDirX, double rayDirY, double perpWallDist, int side)
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

	wallX = compute_wall_hit_point(cfg, perpWallDist, rayDirX, rayDirY, side);
	wallX -= floor(wallX);
	tex_x = compute_tex_x(wallX, tex_width, rayDirX, rayDirY, side);

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
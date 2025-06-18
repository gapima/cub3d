/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:07:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 00:44:54 by glima            ###   ########.fr       */
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

void	draw_wall_slice(t_config *cfg, t_ray_info ray)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x, tex_y, y, d;
	uint32_t		color;
	int				tex_width, tex_height;

	tex = get_wall_texture(cfg, ray.side, ray.ray_dir_x, ray.ray_dir_y);
	if (!tex)
		return;
	tex_width = tex->width;
	tex_height = tex->height;
	wall_x = compute_wall_hit_point(cfg, ray.perp_wall_dist,
			ray.ray_dir_x, ray.ray_dir_y, ray.side);
	wall_x -= floor(wall_x);
	tex_x = compute_tex_x(wall_x, tex_width, ray.ray_dir_x,
			ray.ray_dir_y, ray.side);
	y = ray.draw_start;
	while (y < ray.draw_end)
	{
		d = y * 256 - HEIGHT * 128 + ray.line_height * 128;
		tex_y = ((d * tex_height) / ray.line_height) / 256;
		color = get_texture_pixel(tex, tex_x, tex_y);
		mlx_put_pixel(cfg->img, ray.x, y, color);
		y++;
	}
}

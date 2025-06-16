/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 19:06:37 by glima            ###   ########.fr       */
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

static double compute_wall_hit_point(t_config *cfg, double perpWallDist, double rayDirX, double rayDirY, int side)
{
	if (side == 0)
		return (cfg->player.pos_y + perpWallDist * rayDirY);
	else
		return (cfg->player.pos_x + perpWallDist * rayDirX);
}

static int compute_tex_x(double wallX, int tex_width, double rayDirX, double rayDirY, int side)
{
	int tex_x;

	tex_x = (int)(wallX * tex_width);
	if ((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
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


static void	init_ray(t_config *cfg, t_ray *ray)
{
	ray->cameraX = 2 * ray->x / (double)WIDTH - 1;
	ray->rayDirX = cfg->player.dir_x + cfg->player.plane_x * ray->cameraX;
	ray->rayDirY = cfg->player.dir_y + cfg->player.plane_y * ray->cameraX;
}

static void	init_dda(t_config *cfg, t_ray *ray, t_dda *dda)
{
	dda->mapX = (int)cfg->player.pos_x;
	dda->mapY = (int)cfg->player.pos_y;
	dda->deltaDistX = fabs(1.0 / ray->rayDirX);
	dda->deltaDistY = fabs(1.0 / ray->rayDirY);

	if (ray->rayDirX < 0)
	{
		dda->stepX = -1;
		dda->sideDistX = (cfg->player.pos_x - dda->mapX) * dda->deltaDistX;
	}
	else
	{
		dda->stepX = 1;
		dda->sideDistX = (dda->mapX + 1.0 - cfg->player.pos_x) * dda->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		dda->stepY = -1;
		dda->sideDistY = (cfg->player.pos_y - dda->mapY) * dda->deltaDistY;
	}
	else
	{
		dda->stepY = 1;
		dda->sideDistY = (dda->mapY + 1.0 - cfg->player.pos_y) * dda->deltaDistY;
	}
	dda->hit = 0;
}

static void	perform_dda(t_config *cfg, t_dda *dda)
{
	while (!dda->hit)
	{
		if (dda->sideDistX < dda->sideDistY)
		{
			dda->sideDistX += dda->deltaDistX;
			dda->mapX += dda->stepX;
			dda->side = 0;
		}
		else
		{
			dda->sideDistY += dda->deltaDistY;
			dda->mapY += dda->stepY;
			dda->side = 1;
		}
		if (dda->mapX < 0 || dda->mapY < 0
			|| !cfg->map[dda->mapY] || !cfg->map[dda->mapY][dda->mapX])
			break;
		if (cfg->map[dda->mapY][dda->mapX] == '1')
			dda->hit = 1;
	}
}

static void	calc_projection(t_config *cfg, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		ray->perpWallDist = (dda->mapX - cfg->player.pos_x + (1 - dda->stepX) / 2.0) / ray->rayDirX;
	else
		ray->perpWallDist = (dda->mapY - cfg->player.pos_y + (1 - dda->stepY) / 2.0) / ray->rayDirY;

	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

void	render_frame(t_config *cfg)
{
	t_ray	ray;
	t_dda	dda;

	ray.x = 0;
	while (ray.x < WIDTH)
	{
		init_ray(cfg, &ray);
		init_dda(cfg, &ray, &dda);
		perform_dda(cfg, &dda);
		calc_projection(cfg, &ray, &dda);
		draw_ceiling_and_floor(cfg, ray.x, ray.drawStart, ray.drawEnd);
		draw_wall_slice(cfg, ray.x, ray.drawStart, ray.drawEnd,
			ray.lineHeight, ray.rayDirX, ray.rayDirY,
			ray.perpWallDist, dda.side);
		ray.x++;
	}
}

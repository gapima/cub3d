/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 19:08:16 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

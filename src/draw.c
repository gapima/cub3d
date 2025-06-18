/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 15:10:32 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_config *cfg, t_ray *ray)
{
	ray->camera_x = 2 * ray->x / (double)WIDTH - 1;
	ray->ray_dir_x = cfg->player.dir_x + cfg->player.plane_x * ray->camera_x;
	ray->ray_dir_y = cfg->player.dir_y + cfg->player.plane_y * ray->camera_x;
}

static void	init_dda(t_config *cfg, t_ray *ray, t_dda *dda)
{
	dda->map_x = (int)cfg->player.pos_x;
	dda->map_y = (int)cfg->player.pos_y;
	dda->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	dda->delta_dist_y = fabs(1.0 / ray->ray_dir_y);

	if (ray->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (cfg->player.pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - cfg->player.pos_x) * dda->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (cfg->player.pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - cfg->player.pos_y) * dda->delta_dist_y;
	}
	dda->hit = 0;
}

static void	perform_dda(t_config *cfg, t_dda *dda)
{
	while (!dda->hit)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->side = 0;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->side = 1;
		}
		if (dda->map_x < 0 || dda->map_y < 0
			|| !cfg->map[dda->map_y] || !cfg->map[dda->map_y][dda->map_x])
			break;
		if (cfg->map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
}

static void	calc_projection(t_config *cfg, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		ray->perp_wall_dist = (dda->map_x - cfg->player.pos_x + (1 - dda->step_x) / 2.0) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (dda->map_y - cfg->player.pos_y + (1 - dda->step_y) / 2.0) / ray->ray_dir_y;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	render_frame(t_config *cfg)
{
	t_ray		ray;
	t_dda		dda;
	t_ray_info	ray_info;

	ray.x = 0;
	while (ray.x < WIDTH)
	{
		init_ray(cfg, &ray);
		init_dda(cfg, &ray, &dda);
		perform_dda(cfg, &dda);
		calc_projection(cfg, &ray, &dda);
		draw_ceiling_and_floor(cfg, ray.x, ray.draw_start, ray.draw_end);
		ray_info = (t_ray_info){
			.x = ray.x,
			.draw_start = ray.draw_start,
			.draw_end = ray.draw_end,
			.line_height = ray.line_height,
			.ray_dir_x = ray.ray_dir_x,
			.ray_dir_y = ray.ray_dir_y,
			.perp_wall_dist = ray.perp_wall_dist,
			.side = dda.side
		};
		draw_wall_slice(cfg, ray_info);
		ray.x++;
	}
}

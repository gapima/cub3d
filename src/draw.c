/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:37:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 18:14:05 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_ray(t_config *cfg, t_ray *ray)
{
	ray->camera_x = 2 * ray->x / (double)WIDTH - 1;
	ray->ray_dir_x = cfg->player.dir_x + cfg->player.plane_x * ray->camera_x;
	ray->ray_dir_y = cfg->player.dir_y + cfg->player.plane_y * ray->camera_x;
}

static void	init_dda_x(t_config *cfg, t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (
				(cfg->player.pos_x - dda->map_x) * dda->delta_dist_x);
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (
				(dda->map_x + 1.0 - cfg->player.pos_x) * dda->delta_dist_x);
	}
}

static void	init_dda_y(t_config *cfg, t_ray *ray, t_dda *dda)
{
	if (ray->ray_dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (
				(cfg->player.pos_y - dda->map_y) * dda->delta_dist_y);
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (
				(dda->map_y + 1.0 - cfg->player.pos_y) * dda->delta_dist_y);
	}
}

static void	init_dda(t_config *cfg, t_ray *ray, t_dda *dda)
{
	dda->map_x = (int)cfg->player.pos_x;
	dda->map_y = (int)cfg->player.pos_y;
	dda->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	dda->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	init_dda_x(cfg, ray, dda);
	init_dda_y(cfg, ray, dda);
	dda->hit = 0;
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

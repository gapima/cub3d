/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:35:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 18:14:51 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_max_width(char **map, int height)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool	validate_and_prepare_map(char **map, int height, t_config *cfg)
{
	int				max_width;
	int				player_x;
	int				player_y;
	t_map_check_ctx	mctx;

	max_width = get_max_width(map, height);
	if (!pad_map_lines(map, height, max_width))
		return (false);
	mctx.map = map;
	mctx.height = height;
	mctx.px = &player_x;
	mctx.py = &player_y;
	if (!validate_player_and_chars(cfg, &mctx))
		return (false);
	validate_closed_map(map, height, max_width);
	cfg->player.pos_x = player_x + 0.5;
	cfg->player.pos_y = player_y + 0.5;
	map[player_y][player_x] = '0';
	cfg->map = map;
	return (true);
}

void	calc_projection(t_config *cfg, t_ray *ray, t_dda *dda)
{
	if (dda->side == 0)
		ray->perp_wall_dist = (
				dda->map_x - cfg->player.pos_x + (1 - dda->step_x) / 2.0
				) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (
				dda->map_y - cfg->player.pos_y + (1 - dda->step_y) / 2.0
				) / ray->ray_dir_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	perform_dda(t_config *cfg, t_dda *dda)
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
			break ;
		if (cfg->map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
	}
}

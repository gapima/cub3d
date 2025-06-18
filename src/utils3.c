/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:07:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 17:46:38 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*get_wall_texture(t_config *cfg, int side,
	double ray_dir_x, double ray_dir_y)
{
	if (side == 0)
	{
		if (ray_dir_x < 0)
			return (cfg->tex_we);
		else
			return (cfg->tex_ea);
	}
	else
	{
		if (ray_dir_y < 0)
			return (cfg->tex_no);
		else
			return (cfg->tex_so);
	}
}

void	draw_ceiling_and_floor(t_config *cfg, int x,
	int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		mlx_put_pixel(cfg->img, x, y, cfg->ceiling_color);
		y++;
	}
	y = draw_end;
	while (y < HEIGHT)
	{
		mlx_put_pixel(cfg->img, x, y, cfg->floor_color);
		y++;
	}
}

double	compute_wall_hit_point(t_config *cfg, t_ray_info *ray)
{
	if (ray->side == 0)
		return (cfg->player.pos_y + ray->perp_wall_dist * ray->ray_dir_y);
	else
		return (cfg->player.pos_x + ray->perp_wall_dist * ray->ray_dir_x);
}

int	compute_tex_x(double wallX, int tex_width, t_ray_info *ray)
{
	int	tex_x;

	tex_x = (int)(wallX * tex_width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_wall_slice(t_config *cfg, t_ray_info ray)
{
	t_draw_vars	v;

	v.tex = get_wall_texture(cfg, ray.side, ray.ray_dir_x, ray.ray_dir_y);
	if (!v.tex)
		return ;
	v.tex_width = v.tex->width;
	v.tex_height = v.tex->height;
	v.wall_x = compute_wall_hit_point(cfg, &ray);
	v.wall_x -= floor(v.wall_x);
	v.tex_x = compute_tex_x(v.wall_x, v.tex_width, &ray);
	v.y = ray.draw_start;
	while (v.y < ray.draw_end)
	{
		v.d = v.y * 256 - HEIGHT * 128 + ray.line_height * 128;
		v.tex_y = ((v.d * v.tex_height) / ray.line_height) / 256;
		v.color = get_texture_pixel(v.tex, v.tex_x, v.tex_y);
		mlx_put_pixel(cfg->img, ray.x, v.y, v.color);
		v.y++;
	}
}

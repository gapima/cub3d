/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:07:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 17:13:32 by glima            ###   ########.fr       */
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

double	compute_wall_hit_point(t_config *cfg, double perp_wall_dist,
	double ray_dir_x, double ray_dir_y, int side)
{
	if (side == 0)
		return (cfg->player.pos_y + perp_wall_dist * ray_dir_y);
	else
		return (cfg->player.pos_x + perp_wall_dist * ray_dir_x);
}

int	compute_tex_x(double wallX, int tex_width, double ray_dir_x,
	double ray_dir_y, int side)
{
	int	tex_x;

	tex_x = (int)(wallX * tex_width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

void	draw_wall_slice(t_config *cfg, t_ray_info ray)
{
	mlx_texture_t	*tex;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	int				y;
	int				d;
	uint32_t		color;
	int				tex_width;
	int				tex_height;

	tex = get_wall_texture(cfg, ray.side, ray.ray_dir_x, ray.ray_dir_y);
	if (!tex)
		return ;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:15:41 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 16:43:05 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	int index = (y * tex->width + x) * 4;
	uint8_t r = tex->pixels[index + 0];
	uint8_t g = tex->pixels[index + 1];
	uint8_t b = tex->pixels[index + 2];
	uint8_t a = tex->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

void	free_config(t_config *cfg)
{
	int i;

	if (cfg->map)
	{
		i = 0;
		while (cfg->map[i])
			free(cfg->map[i++]);
		free(cfg->map);
	}
	free(cfg->no_path);
	free(cfg->so_path);
	free(cfg->we_path);
	free(cfg->ea_path);

	if (cfg->tex_no)
		mlx_delete_texture(cfg->tex_no);
	if (cfg->tex_so)
		mlx_delete_texture(cfg->tex_so);
	if (cfg->tex_we)
		mlx_delete_texture(cfg->tex_we);
	if (cfg->tex_ea)
		mlx_delete_texture(cfg->tex_ea);

	if (cfg->img)
		mlx_delete_image(cfg->mlx, cfg->img);
}

void set_player_direction(t_config *cfg, char dir)
{
	cfg->player.dir_x = 0;
	cfg->player.dir_y = 0;
	cfg->player.plane_x = 0;
	cfg->player.plane_y = 0;

	if (dir == 'N')
	{
		cfg->player.dir_y = -1;
		cfg->player.plane_x = 0.66;
	}
	else if (dir == 'S')
	{
		cfg->player.dir_y = 1;
		cfg->player.plane_x = -0.66;
	}
	else if (dir == 'E')
	{
		cfg->player.dir_x = 1;
		cfg->player.plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		cfg->player.dir_x = -1;
		cfg->player.plane_y = -0.66;
	}
}
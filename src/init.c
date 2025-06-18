/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:26:33 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 15:13:06 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	load_textures(t_config *cfg)
{
	cfg->tex_no = mlx_load_png(cfg->no_path);
	cfg->tex_so = mlx_load_png(cfg->so_path);
	cfg->tex_we = mlx_load_png(cfg->we_path);
	cfg->tex_ea = mlx_load_png(cfg->ea_path);
	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we || !cfg->tex_ea)
		return (false);
	return (true);
}



bool	init_config(t_config *cfg)
{
	cfg->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cfg->mlx)
		return (false);
	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	if (!cfg->img)
		return (false);
	init_paths(cfg);
	init_textures(cfg);
	init_colors_and_map(cfg);
	return (true);
}

void	hook(void *param)
{
	t_config *cfg = (t_config *)param;

	mlx_delete_image(cfg->mlx, cfg->img);
	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
	render_frame(cfg);
}

void	handle_close(void *param)
{
	t_config *cfg = (t_config *)param;
	free_config(cfg);
	mlx_terminate(cfg->mlx);
	exit(EXIT_SUCCESS);
}
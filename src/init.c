/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:26:33 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 19:19:17 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_texture_error(char *label, char *path)
{
	ft_putstr_fd(label, 2);
	ft_putstr_fd(path, 2);
	ft_putchar_fd('\n', 2);
}

static void	print_all_texture_errors(t_config *cfg)
{
	ft_putstr_fd("❌ Erro ao carregar texturas:\n", 2);
	if (!cfg->tex_no)
		print_texture_error("- Norte (NO): ", cfg->no_path);
	if (!cfg->tex_so)
		print_texture_error("- Sul   (SO): ", cfg->so_path);
	if (!cfg->tex_we)
		print_texture_error("- Oeste (WE): ", cfg->we_path);
	if (!cfg->tex_ea)
		print_texture_error("- Leste (EA): ", cfg->ea_path);
}

static void	cleanup_failed_textures(t_config *cfg)
{
	if (cfg->tex_no)
		mlx_delete_texture(cfg->tex_no);
	if (cfg->tex_so)
		mlx_delete_texture(cfg->tex_so);
	if (cfg->tex_we)
		mlx_delete_texture(cfg->tex_we);
	if (cfg->tex_ea)
		mlx_delete_texture(cfg->tex_ea);
}

bool	load_textures(t_config *cfg)
{
	cfg->tex_no = mlx_load_png(cfg->no_path);
	cfg->tex_so = mlx_load_png(cfg->so_path);
	cfg->tex_we = mlx_load_png(cfg->we_path);
	cfg->tex_ea = mlx_load_png(cfg->ea_path);
	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we || !cfg->tex_ea)
	{
		print_all_texture_errors(cfg);
		cleanup_failed_textures(cfg);
		return (false);
	}
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


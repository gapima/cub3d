/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:26:33 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 16:40:49 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *cfg)
{
	cfg->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cfg->mlx)
	{
		fprintf(stderr, "Erro ao iniciar MLX\n");
		exit(EXIT_FAILURE);
	}

	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	if (!cfg->img)
	{
		fprintf(stderr, "Erro ao criar imagem\n");
		exit(EXIT_FAILURE);
	}

	cfg->map = NULL;

	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;

	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;

	cfg->floor_color = 0x000000FF;   // preto
	cfg->ceiling_color = 0xAAAAAAFF; // cinza claro
}

bool	load_textures(t_config *cfg)
{
	cfg->tex_no = mlx_load_png(cfg->no_path);
	cfg->tex_so = mlx_load_png(cfg->so_path);
	cfg->tex_we = mlx_load_png(cfg->we_path);
	cfg->tex_ea = mlx_load_png(cfg->ea_path);

	if (!cfg->tex_no || !cfg->tex_so || !cfg->tex_we || !cfg->tex_ea)
	{
		fprintf(stderr, "❌ Erro ao carregar texturas:\n");
		if (!cfg->tex_no)
			fprintf(stderr, "- Norte (NO): %s\n", cfg->no_path);
		if (!cfg->tex_so)
			fprintf(stderr, "- Sul   (SO): %s\n", cfg->so_path);
		if (!cfg->tex_we)
			fprintf(stderr, "- Oeste (WE): %s\n", cfg->we_path);
		if (!cfg->tex_ea)
			fprintf(stderr, "- Leste (EA): %s\n", cfg->ea_path);
		return false;
	}
	return true;
}

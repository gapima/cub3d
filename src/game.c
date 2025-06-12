/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:34:01 by glima             #+#    #+#             */
/*   Updated: 2025/06/09 16:34:01 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_config *cfg)
{
	if (!cfg->map || !cfg->map[0])
	{
		ft_putstr_fd("❌ Erro: mapa não carregado corretamente\n", 2);
		exit(EXIT_FAILURE);
	}

	cfg->width = TILE_SIZE * ft_strlen(cfg->map[0]);
	cfg->height = TILE_SIZE * ft_strlen_2d(cfg->map);

	cfg->mlx = mlx_init(cfg->width, cfg->height, "cub3D", false);
	if (!cfg->mlx)
	{
		ft_putstr_fd("❌ Erro ao iniciar o MLX\n", 2);
		exit(EXIT_FAILURE);
	}

	cfg->img = mlx_new_image(cfg->mlx, cfg->width, cfg->height);
	if (!cfg->img)
	{
		ft_putstr_fd("❌ Erro ao criar a imagem\n", 2);
		exit(EXIT_FAILURE);
	}

	// 🔧 Trime espaços e quebras de linha dos caminhos (se ainda não tiver feito no parser)
	cfg->no_path = ft_strtrim(cfg->no_path, " \n");
	cfg->so_path = ft_strtrim(cfg->so_path, " \n");
	cfg->we_path = ft_strtrim(cfg->we_path, " \n");
	cfg->ea_path = ft_strtrim(cfg->ea_path, " \n");

	// ✅ Carregar texturas PNG
	cfg->no_texture = mlx_load_png(cfg->no_path);
	cfg->so_texture = mlx_load_png(cfg->so_path);
	cfg->we_texture = mlx_load_png(cfg->we_path);
	cfg->ea_texture = mlx_load_png(cfg->ea_path);

	if (!cfg->no_texture || !cfg->so_texture || !cfg->we_texture || !cfg->ea_texture)
	{
		ft_putstr_fd("❌ Erro ao carregar as texturas PNG\n", 2);
		if (!cfg->no_texture) ft_putstr_fd("⛔ NO falhou\n", 2);
		if (!cfg->so_texture) ft_putstr_fd("⛔ SO falhou\n", 2);
		if (!cfg->we_texture) ft_putstr_fd("⛔ WE falhou\n", 2);
		if (!cfg->ea_texture) ft_putstr_fd("⛔ EA falhou\n", 2);
		exit(EXIT_FAILURE);
	}

	// ✅ Converter para imagens MLX
	cfg->no_img = mlx_texture_to_image(cfg->mlx, cfg->no_texture);
	cfg->so_img = mlx_texture_to_image(cfg->mlx, cfg->so_texture);
	cfg->we_img = mlx_texture_to_image(cfg->mlx, cfg->we_texture);
	cfg->ea_img = mlx_texture_to_image(cfg->mlx, cfg->ea_texture);

	if (!cfg->no_img || !cfg->so_img || !cfg->we_img || !cfg->ea_img)
	{
		ft_putstr_fd("❌ Erro ao criar as imagens das texturas\n", 2);
		exit(EXIT_FAILURE);
	}

	// ✅ Liberar texturas após conversão
	mlx_delete_texture(cfg->no_texture);
	mlx_delete_texture(cfg->so_texture);
	mlx_delete_texture(cfg->we_texture);
	mlx_delete_texture(cfg->ea_texture);

	// (Opcional) Debug
	printf("✅ Texturas carregadas com sucesso\n");
}





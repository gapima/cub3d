/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:26:33 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 13:07:18 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_config(t_config *cfg)
{
	cfg->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!cfg->mlx)
	{
		puts("Erro ao inicializar janela");
		exit(EXIT_FAILURE);
	}

	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	if (!cfg->img)
	{
		puts("Erro ao criar imagem");
		mlx_terminate(cfg->mlx);
		exit(EXIT_FAILURE);
	}

	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);

	// Posição e direção inicial do player
	cfg->player.pos_x = 22.0;
	cfg->player.pos_y = 12.0;
	cfg->player.dir_x = -1.0;
	cfg->player.dir_y = 0.0;
	cfg->player.plane_x = 0.0;
	cfg->player.plane_y = 0.66;
}

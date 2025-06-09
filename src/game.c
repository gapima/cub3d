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

	cfg->width = TILE_SIZE * ft_strlen(cfg->map[0]); // largura da primeira linha
	cfg->height = TILE_SIZE * ft_strlen_2d(cfg->map); // número de linhas
    
    if (!cfg->map || !cfg->map[0])
    {
        ft_putstr_fd("❌ Erro: mapa não carregado corretamente\n", 2);
        exit(EXIT_FAILURE);
    }
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
}


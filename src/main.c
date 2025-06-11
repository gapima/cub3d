/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:21:14 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:21:14 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
	{
		ft_putstr_fd("Uso: ./cub3D <arquivo.cub>\n", 2);
		return (1);
	}
	ft_memset(&cfg, 0, sizeof(t_config));
	parse_cub_file(argv[1], &cfg);
	validate_map(&cfg);
	check_single_player(&cfg);
	init_game(&cfg); // cria cfg->mlx, mas não cfg->img

	if (cfg.mlx)
	{
		mlx_loop_hook(cfg.mlx, render_frame, &cfg); // correto agora
		mlx_loop(cfg.mlx);
		mlx_terminate(cfg.mlx);
	}
	return (0);
}

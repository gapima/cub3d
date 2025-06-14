/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 00:27:03 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 19:19:23 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	hook(void *param)
{
	t_config *cfg = (t_config *)param;

	mlx_delete_image(cfg->mlx, cfg->img);
	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);

	render_frame(cfg);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
	{
		puts("Uso: ./cub3D <mapa.cub>");
		return (EXIT_FAILURE);
	}
	init_config(&cfg);
	parse_cub_file(argv[1], &cfg);
	load_textures(&cfg); // ⬅️ ADICIONE AQUI

	mlx_loop_hook(cfg.mlx, &hook, &cfg);
	mlx_key_hook(cfg.mlx, &handle_input, &cfg);
	mlx_loop(cfg.mlx);
	mlx_terminate(cfg.mlx);
	return (EXIT_SUCCESS);
}


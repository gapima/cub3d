/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:15:40 by glima             #+#    #+#             */
/*   Updated: 2025/06/21 20:10:29 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	show_usage(void)
{
	ft_putstr_fd("Uso: ./cub3D <mapa.cub>\n", 2);
	exit(EXIT_FAILURE);
}

static void	cleanup_and_exit(t_config *cfg, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	free_config(cfg);
	mlx_terminate(cfg->mlx);
	exit(EXIT_FAILURE);
}

static void	start_loop(t_config *cfg)
{
	if (!cfg->mlx)
		return ;
	mlx_loop_hook(cfg->mlx, &hook, cfg);
	mlx_key_hook(cfg->mlx, &handle_input, cfg);
	mlx_close_hook(cfg->mlx, &handle_close, cfg);
	mlx_loop(cfg->mlx);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
		show_usage();
	if (!init_config(&cfg))
		cleanup_and_exit(&cfg, "Error: failed to initialize configuration.\n");
	if (!parse_cub_file(argv[1], &cfg))
		cleanup_and_exit(&cfg, "");
	if (!load_textures(&cfg))
		cleanup_and_exit(&cfg, "Error: failed to load textures\n");
	start_loop(&cfg);
	free_config(&cfg);
	mlx_terminate(cfg.mlx);
	return (EXIT_SUCCESS);
}

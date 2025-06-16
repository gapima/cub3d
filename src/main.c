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
	exit(EXIT_FAILURE);
}

static void	start_loop(t_config *cfg)
{
	mlx_loop_hook(cfg->mlx, &hook, cfg);
	mlx_key_hook(cfg->mlx, &handle_input, cfg);
	mlx_loop(cfg->mlx);
	mlx_terminate(cfg->mlx);
}

void	hook(void *param)
{
	t_config *cfg;

	cfg = (t_config *)param;
	mlx_delete_image(cfg->mlx, cfg->img);
	cfg->img = mlx_new_image(cfg->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(cfg->mlx, cfg->img, 0, 0);
	render_frame(cfg);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
		show_usage();
	if (!init_config(&cfg))
	{
		fprintf(stderr, "Erro ao inicializar a configuração.\n");
		return (EXIT_FAILURE);
	}
	if (!parse_cub_file(argv[1], &cfg))
		cleanup_and_exit(&cfg, "Erro ao analisar o arquivo .cub\n");
	if (!load_textures(&cfg))
		cleanup_and_exit(&cfg, "Erro ao carregar texturas\n");
	start_loop(&cfg);
	free_config(&cfg);
	return (EXIT_SUCCESS);
}

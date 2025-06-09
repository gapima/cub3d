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

// #include "cub3d.h"

// #define WIDTH 800
// #define HEIGHT 600

// void	hook(void *param)
// {
// 	mlx_t	*mlx = param;

// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// }

// int	main(void)
// {
// 	mlx_t		*mlx;
// 	mlx_image_t	*img;

//     t_config	cfg;

//     ft_memset(&cfg, 0, sizeof(cfg));
//     parse_cub_file("maps/test.cub", &cfg);
//     printf("Cor do chão: 0x%X\n", cfg.floor_color);
//     printf("NO: %s\n", cfg.no_path);


// 	// Inicializa a janela
// 	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
// 	if (!mlx)
// 		return (EXIT_FAILURE);

// 	// Cria uma imagem para desenhar
// 	img = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	if (!img)
// 	{
// 		mlx_terminate(mlx);
// 		return (EXIT_FAILURE);
// 	}

// 	// Céu (parte superior)
// 	for (int y = 0; y < HEIGHT / 2; y++)
// 		for (int x = 0; x < WIDTH; x++)
// 			mlx_put_pixel(img, x, y, 0xFF87CEFA); // Azul claro (LightSkyBlue)

// 	// Chão (parte inferior)
// 	for (int y = HEIGHT / 2; y < HEIGHT; y++)
// 		for (int x = 0; x < WIDTH; x++)
// 			mlx_put_pixel(img, x, y, 0xFF8B4513); // Marrom (SaddleBrown)

// 	// Adiciona imagem na janela
// 	mlx_image_to_window(mlx, img, 0, 0);

// 	// Adiciona hook para ESC
// 	mlx_loop_hook(mlx, hook, mlx);

// 	// Loop principal
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

#include <stdio.h>
#include "cub3d.h"

#define WIDTH 800
#define HEIGHT 600

void	hook(void *param)
{
	mlx_t	*mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (argc != 2)
	{
		printf("Uso: %s <arquivo .cub>\n", argv[0]);
		return (1);
	}

	ft_memset(&cfg, 0, sizeof(t_config));
	parse_cub_file(argv[1], &cfg);   // Texturas e cores
	parse_map(&cfg, argv[1]);        // Mapa
	print_map(cfg.map);              // Função pra ver o resultado (posso mandar)


	return (0);
}


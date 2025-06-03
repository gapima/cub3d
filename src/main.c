/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:08:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/03 17:08:30 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_config(const t_config *c)
{
	printf("NO: %s\n", c->no_tex);
	printf("SO: %s\n", c->so_tex);
	printf("WE: %s\n", c->we_tex);
	printf("EA: %s\n", c->ea_tex);
}

int	main(int argc, char **argv)
{
	t_config config;

	memset(&config, 0, sizeof(t_config)); // ← isso tem que estar aqui DENTRO do main

	if (argc != 2)
	{
		write(2, "Error\nUsage: ./cub3D map.cub\n", 29);
		return (1);
	}
	if (parse_cub_file(argv[1], &config) != 0)
	{
		write(2, "Error\nFailed to parse map\n", 27);
		return (1);
	}
	print_config(&config);
	free_config(&config); // ainda vamos implementar isso
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:55:19 by glima             #+#    #+#             */
/*   Updated: 2025/06/09 14:55:19 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	validate_map(t_config *cfg)
{
	int	x, y;
	int	start_count = 0;

	y = -1;
	while (cfg->map[++y])
	{
		x = -1;
		while (cfg->map[y][++x])
		{
			char c = cfg->map[y][x];
			if (!is_valid_char(c))
			{
				printf("Caractere inválido detectado: '%c' (ASCII: %d) na linha %d, coluna %d\n", c, c, y, x);
				ft_putstr_fd("❌ Erro: Caractere inválido no mapa.\n", 2);
				exit(EXIT_FAILURE);
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				cfg->player_x = x;
				cfg->player_y = y;
				cfg->player_dir = c;
				start_count++;
			}
		}
	}
	if (start_count != 1)
	{
		ft_putstr_fd("❌ Erro: O mapa deve ter exatamente 1 player.\n", 2);
		exit(EXIT_FAILURE);
	}

	// Aqui sim, corretamente:
	check_map_closed(cfg->map, cfg->player_x, cfg->player_y);
}


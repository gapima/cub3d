/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:14:56 by glima             #+#    #+#             */
/*   Updated: 2025/06/09 16:14:56 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(char **map, int x, int y)
{
	if (y < 0 || x < 0 || !map[y] || x >= (int)ft_strlen(map[y]))
	{
		ft_putstr_fd("❌ Erro: Mapa possui buracos nas bordas.\n", 2);
		exit(EXIT_FAILURE);
	}
	if (map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == ' ')
	{
		ft_putstr_fd("❌ Erro: Mapa possui espaços inválidos próximos ao jogador.\n", 2);
		exit(EXIT_FAILURE);
	}

	map[y][x] = 'F'; // F de "Filled"
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static char	**dup_map(char **src)
{
	int		i;
	char	**copy;

	i = 0;
	while (src[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = ft_strdup(src[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	free_map_copy(char **map)
{
	int	i = 0;

	while (map[i])
		free(map[i++]);
	free(map);
}

void	check_map_closed(char **map, int start_x, int start_y)
{
	char	**map_copy;

	map_copy = dup_map(map);
	if (!map_copy)
	{
		ft_putstr_fd("Erro: falha ao duplicar mapa para validação.\n", 2);
		exit(EXIT_FAILURE);
	}
	flood_fill(map_copy, start_x, start_y);
	free_map_copy(map_copy);
}

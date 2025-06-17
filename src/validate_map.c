/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:46:50 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 23:19:59 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool check_diagonals(char **map, int x, int y, int height, int width)
{
	if (y > 0 && x > 0 && (map[y - 1][x - 1] == ' ' || map[y - 1][x - 1] == 2))
		return false;
	if (y + 1 < height && x > 0 && (map[y + 1][x - 1] == ' ' || map[y + 1][x - 1] == 2))
		return false;
	if (y > 0 && x + 1 < width && (map[y - 1][x + 1] == ' ' || map[y - 1][x + 1] == 2))
		return false;
	if (y + 1 < height && x + 1 < width && (map[y + 1][x + 1] == ' ' || map[y + 1][x + 1] == 2))
		return false;
	return true;
}

static bool check_sides(char **map, int x, int y, int height, int width)
{
	if (y <= 0 || y >= height || x <= 0 || x >= width)
		return false;
	if (y > 0 && (map[y - 1][x] == ' ' || map[y - 1][x] == 2))
		return false;
	if (y + 1 < height && (map[y + 1][x] == ' ' || map[y + 1][x] == 2))
		return false;
	if (x > 0 && (map[y][x - 1] == ' ' || map[y][x - 1] == 2))
		return false;
	if (x + 1 < width && (map[y][x + 1] == ' ' || map[y][x + 1] == 2))
		return false;
	return true;
}

void validate_closed_map(char **map, int height, int width)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			char c = map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!check_sides(map, x, y, height, width) || !check_diagonals(map, x, y, height, width))
				{
					fprintf(stderr, "❌ Erro: Mapa não está completamente fechado nas coordenadas (%d, %d)\n", x, y);
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}

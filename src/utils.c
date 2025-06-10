/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:46:41 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:46:41 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

t_ray_result	cast_ray(t_config *cfg, double ray_angle)
{
	t_ray_result	result;
	double			ray_x = cfg->player_x + 0.5;
	double			ray_y = cfg->player_y + 0.5;
	double			delta = 0.01;

	while (1)
	{
		int map_x = (int)ray_x;
		int map_y = (int)ray_y;

		if (cfg->map[map_y][map_x] == '1')
		{
			result.distance = sqrt(pow(ray_x - (cfg->player_x + 0.5), 2)
								+ pow(ray_y - (cfg->player_y + 0.5), 2));

			// Escolher textura com base na direção (simplificado)
			if (fabs(cos(ray_angle)) > fabs(sin(ray_angle)))
				result.texture = (cos(ray_angle) > 0) ? cfg->we_texture : cfg->ea_texture;
			else
				result.texture = (sin(ray_angle) > 0) ? cfg->no_texture : cfg->so_texture;

			result.texture_x = ((int)(ray_x * TILE_SIZE)) % TILE_SIZE; // Ponto x da textura
			break;
		}

		ray_x += cos(ray_angle) * delta;
		ray_y += sin(ray_angle) * delta;
	}
	return (result);
}


int	rgb_to_int(char *line)
{
	int	r, g, b;
	char **parts = ft_split(line, ',');

	if (!parts || !parts[0] || !parts[1] || !parts[2])
		return (-1); // erro

	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);

	// libera memória do split
	for (int i = 0; parts[i]; i++)
		free(parts[i]);
	free(parts);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

void	print_map(char **map)
{
	int i = 0;
	printf("\nMAPA:\n");
	while (map[i])
	{
		printf("%s", map[i]);
		i++;
	}
}

char	**convert_list_to_array(t_list *map_lines)
{
	int		count = ft_lstsize(map_lines);
	char	**map = malloc(sizeof(char *) * (count + 1));
	t_list	*tmp = map_lines;
	int		i = 0;

	if (!map)
		return (NULL);
	while (tmp)
	{
		map[i++] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
	}
	map[i] = NULL;
	return (map);
}

int	ft_strlen_2d(char **arr)
{
	int	i = 0;

	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

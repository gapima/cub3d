/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:47:12 by glima             #+#    #+#             */
/*   Updated: 2025/06/16 18:48:29 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int parse_color_component(char *str)
{
	int value;

	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("\u274c Erro: Componente de cor fora do intervalo (0-255): ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	return (value);
}

char **read_cub_file(const char *path, t_config *cfg, int *out_height)
{
	int		fd;
	char	*line;
	char	**map;
        *out_height = 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Erro ao abrir o arquivo .cub\n", 2);
		return (NULL);
	}
	map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));
	if (!map)
		return (close(fd), NULL);
	line = get_next_line(fd);
	while (line && *out_height < MAX_MAP_HEIGHT)
	{
                if (!process_line(cfg, line, map, out_height, fd))
                {
                        free_map(map, *out_height);
                        close(fd);
                        return (NULL);
                }
		line = get_next_line(fd);
	}
	map[*out_height] = NULL;
	close(fd);
	return (map);
}


int get_max_width(char **map, int height)
{
	int i;
	int len;
	int max;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool pad_map_lines(char **map, int height, int max_width)
{
	int i;
	int len;
	int j;
	char *padded;

	i = 0;
	while (i < height)
	{
		padded = ft_calloc(max_width + 1, sizeof(char));
		if (!padded)
			return (false);
		len = ft_strlen(map[i]);
		ft_memcpy(padded, map[i], len);
		j = len;
		while (j < max_width)
			padded[j++] = ' ';
		free(map[i]);
		map[i] = padded;
		i++;
	}
	return (true);
}
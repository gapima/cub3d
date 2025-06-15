/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:31:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/15 17:40:03 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N');
}

static int parse_color_component(char *str)
{
	int value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		fprintf(stderr, "❌ Erro: Componente de cor fora do intervalo (0-255): %s\n", str);
		exit(EXIT_FAILURE);
	}
	return value;
}

static void free_split(char **split)
{
	int i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static uint32_t parse_color(char *line)
{
	char **components = ft_split(line, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		fprintf(stderr, "❌ Erro: Formato de cor inválido: %s\n", line);
		exit(EXIT_FAILURE);
	}
	int r = parse_color_component(components[0]);
	int g = parse_color_component(components[1]);
	int b = parse_color_component(components[2]);
	free_split(components);
	return (r << 24 | g << 16 | b << 8 | 0xFF);
}



static void parse_texture_or_color(t_config *cfg, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		cfg->no_path = ft_strtrim(line + 3, " \n\r");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cfg->so_path = ft_strtrim(line + 3, " \n\r");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cfg->we_path = ft_strtrim(line + 3, " \n\r");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cfg->ea_path = ft_strtrim(line + 3, " \n\r");
	else if (ft_strncmp(line, "F ", 2) == 0)
		cfg->floor_color = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		cfg->ceiling_color = parse_color(line + 2);
	else
	{
		fprintf(stderr, "❌ Erro: Linha inválida: %s\n", line);
		exit(EXIT_FAILURE);
	}
}

void parse_cub_file(const char *path, t_config *cfg)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo .cub");
		exit(EXIT_FAILURE);
	}

	char *line;
	int y = 0;
	int player_found = 0;
	int map_started = 0;
	char **map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));

	while ((line = get_next_line(fd)) && y < MAX_MAP_HEIGHT)
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (!map_started && (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0))
		{
			parse_texture_or_color(cfg, line);
			free(line);
			continue;
		}
		map_started = 1;
		map[y] = ft_strtrim(line, "\n");
		free(line);
		for (int x = 0; map[y][x]; x++)
		{
			char c = map[y][x];
			if (!is_valid_map_char(c))
			{
				fprintf(stderr, "❌ Erro: Caractere inválido no mapa: '%c'\n", c);
				exit(EXIT_FAILURE);
			}
			if (c == 'N')
			{
				if (player_found)
				{
					fprintf(stderr, "❌ Erro: Mais de uma posição inicial encontrada.\n");
					exit(EXIT_FAILURE);
				}
				cfg->player.pos_x = x + 0.5;
				cfg->player.pos_y = y + 0.5;
				cfg->player.dir_x = 0;
				cfg->player.dir_y = -1;
				cfg->player.plane_x = 0.66;
				cfg->player.plane_y = 0;
				map[y][x] = '0';
				player_found = 1;
			}
		}
		y++;
	}
	map[y] = NULL;
	close(fd);

	if (!player_found)
	{
		fprintf(stderr, "❌ Erro: Nenhuma posição inicial do jogador encontrada.\n");
		exit(EXIT_FAILURE);
	}

	cfg->map = map;
}
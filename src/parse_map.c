/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:31:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/15 18:07:49 by glima            ###   ########.fr       */
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

static void flood_fill(char **map, int x, int y, int max_x, int max_y)
{
	if (x < 0 || y < 0 || y >= max_y || x >= (int)ft_strlen(map[y]) || map[y][x] == '1' || map[y][x] == 'F')
		return;
	if (x == 0 || y == 0 || x == max_x - 1 || y == max_y - 1)
	{
		fprintf(stderr, "❌ Erro: Flood fill chegou na borda — mapa não fechado.\n");
		exit(EXIT_FAILURE);
	}
	if (map[y][x] == ' ' || map[y][x] == '\0')
	{
		fprintf(stderr, "❌ Erro: Mapa não está fechado corretamente.\n");
		exit(EXIT_FAILURE);
	}
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, max_x, max_y);
	flood_fill(map, x - 1, y, max_x, max_y);
	flood_fill(map, x, y + 1, max_x, max_y);
	flood_fill(map, x, y - 1, max_x, max_y);
}

static void validate_closed_map(char **map, int x, int y, int map_height, int map_width)
{
	char **map_copy = ft_calloc(map_height + 1, sizeof(char *));
	for (int i = 0; i < map_height; i++)
		map_copy[i] = ft_strdup(map[i]);
	flood_fill(map_copy, x, y, map_width, map_height);
	free_split(map_copy);
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
	int player_x = -1, player_y = -1;
	char **map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));

	while ((line = get_next_line(fd)) && y < MAX_MAP_HEIGHT)
	{
		if (line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		{
			parse_texture_or_color(cfg, line);
			free(line);
			continue;
		}
		map[y++] = ft_strtrim(line, " \n\r");
		free(line);
	}
	map[y] = NULL;
	close(fd);

	int max_width = 0;
	for (int i = 0; i < y; i++)
		if ((int)ft_strlen(map[i]) > max_width)
			max_width = ft_strlen(map[i]);

	for (int i = 0; i < y; i++) {
		char *padded = ft_calloc(max_width + 1, sizeof(char));
		int len = ft_strlen(map[i]);
		ft_memcpy(padded, map[i], len);
		for (int j = len; j < max_width; j++)
			padded[j] = ' ';
		free(map[i]);
		map[i] = padded;
	}

	for (int i = 0; i < y; i++) {
		for (int x = 0; map[i][x]; x++) {
			if (map[i][x] == 'N') {
				if (player_found) {
					fprintf(stderr, "❌ Erro: Mais de uma posição inicial encontrada.\n");
					exit(EXIT_FAILURE);
				}
				player_found = 1;
				player_x = x;
				player_y = i;
			}
			if (!is_valid_map_char(map[i][x]) && map[i][x] != ' ') {
				fprintf(stderr, "❌ Erro: Caractere inválido no mapa: '%c'\n", map[i][x]);
				exit(EXIT_FAILURE);
			}
		}
	}

	if (!player_found) {
		fprintf(stderr, "❌ Erro: Nenhuma posição inicial do jogador encontrada.\n");
		exit(EXIT_FAILURE);
	}

	validate_closed_map(map, player_x, player_y, y, max_width);

	cfg->player.pos_x = player_x + 0.5;
	cfg->player.pos_y = player_y + 0.5;
	cfg->player.dir_x = 0;
	cfg->player.dir_y = -1;
	cfg->player.plane_x = 0.66;
	cfg->player.plane_y = 0;
	map[player_y][player_x] = '0';

	cfg->map = map;
}

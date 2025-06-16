/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:31:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/16                                    */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int parse_color_component(char *str)
{
	int value;

	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("❌ Erro: Componente de cor fora do intervalo (0-255): ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	return (value);
}

static void free_split(char **split)
{
	int i;
	i = 0;
	while (split && split[i])
		free(split[i++]);
	free(split);
}

static uint32_t parse_color(char *line)
{
	char **components;
	int r;
	int g;
	int b;

	components = ft_split(line, ',');
	if (!components || !components[0] || !components[1] || !components[2])
	{
		ft_putstr_fd("❌ Erro: Formato de cor inválido: ", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	r = parse_color_component(components[0]);
	g = parse_color_component(components[1]);
	b = parse_color_component(components[2]);
	free_split(components);
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
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
		ft_putstr_fd("❌ Erro: Linha inválida: ", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
}

bool parse_cub_file(const char *path, t_config *cfg)
{
	int fd;
	char *line;
	char **map;
	int y;
	int player_found;
	int player_x;
	int player_y;
	int max_width;
	int i;
	int j;
	int len;
	char *newline;
	char *padded;

	fd = open(path, O_RDONLY);
	line = NULL;
	map = NULL;
	y = 0;
	player_found = 0;
	player_x = -1;
	player_y = -1;
	max_width = 0;

	if (fd < 0)
	{
		ft_putstr_fd("Erro ao abrir o arquivo .cub\n", 2);
		return (false);
	}
	map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));
	if (!map)
		return (close(fd), false);
	while ((line = get_next_line(fd)) && y < MAX_MAP_HEIGHT)
	{
		if (line[0] == '\n' || line[0] == '\0')
			free(line);
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
				ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
				ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		{
			parse_texture_or_color(cfg, line);
			free(line);
		}
		else
		{
			newline = ft_strchr(line, '\n');
			if (newline)
				*newline = '\0';
			map[y] = ft_strdup(line);
			if (!map[y])
				return (close(fd), false);
			y++;
			free(line);
		}
	}
	map[y] = NULL;
	close(fd);
	i = 0;
	while (i < y)
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	i = 0;
	while (i < y)
	{
		padded = ft_calloc(max_width + 1, sizeof(char));
		if (!padded)
			return (false);
		len = ft_strlen(map[i]);
		ft_memcpy(padded, map[i], len);
		j = len;
		while (j < max_width)
		{
			padded[j] = ' ';
			j++;
		}
		free(map[i]);
		map[i] = padded;
		i++;
	}
	i = 0;
	while (i < y)
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (player_found)
				{
					ft_putstr_fd("❌ Erro: Mais de uma posição inicial.\n", 2);
					return (false);
				}
				player_found = 1;
				player_x = j;
				player_y = i;
				set_player_direction(cfg, map[i][j]);
			}
			if (!is_valid_map_char(map[i][j]) && map[i][j] != ' ')
			{
				ft_putstr_fd("❌ Caractere inválido: ", 2);
				ft_putchar_fd(map[i][j], 2);
				ft_putchar_fd('\n', 2);
				return (false);
			}
			j++;
		}
		i++;
	}
	if (!player_found)
	{
		ft_putstr_fd("❌ Erro: Nenhuma posição inicial do jogador.\n", 2);
		return (false);
	}
	validate_closed_map(map, y, max_width);
	cfg->player.pos_x = player_x + 0.5;
	cfg->player.pos_y = player_y + 0.5;
	map[player_y][player_x] = '0';
	cfg->map = map;
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:42:43 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:42:43 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_texture(t_config *cfg, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		cfg->no_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		cfg->so_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		cfg->we_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		cfg->ea_path = ft_strdup(line + 3);
}

static void	parse_color(t_config *cfg, char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		cfg->floor_color = rgb_to_int(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		cfg->ceiling_color = rgb_to_int(line + 2);
}

void	parse_cub_file(const char *path, t_config *cfg)
{
	int		fd;
	char	*line;
	t_list	*map_lines = NULL;
	bool	map_started = false;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo .cub");
		exit(EXIT_FAILURE);
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue;
		}

		if (!map_started && (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0))
			parse_texture(cfg, line);
		else if (!map_started && (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0))
			parse_color(cfg, line);
		else
		{
			map_started = true;
			parse_map_line(&map_lines, line);
		}
		free(line);
	}
	close(fd);

	cfg->map = convert_list_to_array(map_lines);
	ft_lstclear(&map_lines, free);
}


void	parse_map(t_config *cfg, const char *path)
{
	int		fd;
	char	*line;
	int		i = 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao reabrir .cub para ler o mapa");
		exit(EXIT_FAILURE);
	}

	// Pular cabeçalhos (NO, SO, etc.)
	while ((line = get_next_line(fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0' ||
			ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		{
			free(line);
			continue;
		}
		break;
	}

	// Começa a armazenar o mapa
	cfg->map = malloc(sizeof(char *) * 1024); // tamanho arbitrário por agora
	if (!cfg->map)
		return ;

	while (line)
	{
		cfg->map[i++] = line;
		line = get_next_line(fd);
	}
	cfg->map[i] = NULL;
	cfg->map_height = i;
	close(fd);
}

void	parse_map_line(t_list **map_lines, char *line)
{
	char *trimmed;

	trimmed = ft_strtrim(line, "\n"); // ou outro trim se preferir
	if (!trimmed)
	{
		ft_lstclear(map_lines, free);
		exit(EXIT_FAILURE);
	}
	ft_lstadd_back(map_lines, ft_lstnew(trimmed));
}


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

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo .cub");
		exit(EXIT_FAILURE);
	}

	printf("CHECKPOINT A %d\n", fd);

	while ((line = get_next_line(fd)) != NULL)
	{

		if (line[0] == '\n' || line[0] == '\0')
		{
			free(line);
			continue;
		}
		if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			parse_texture(cfg, line);
		else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			parse_color(cfg, line);
		// depois tratamos o mapa
		free(line);
	}
	close(fd);
}

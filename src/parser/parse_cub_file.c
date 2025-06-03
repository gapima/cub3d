/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:16:18 by glima             #+#    #+#             */
/*   Updated: 2025/06/03 17:16:18 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int	is_texture_line(const char *line)
// {
// 	return (strncmp(line, "NO ", 3) == 0
// 		|| strncmp(line, "SO ", 3) == 0
// 		|| strncmp(line, "WE ", 3) == 0
// 		|| strncmp(line, "EA ", 3) == 0);
// }

// static int	is_color_line(const char *line)
// {
// 	return (line[0] == 'F' || line[0] == 'C');
// }

// static int	is_map_line(const char *line)
// {
// 	while (*line)
// 	{
// 		if (*line != ' ' && *line != '0' && *line != '1'
// 			&& *line != 'N' && *line != 'S' && *line != 'E' && *line != 'W')
// 			return (0);
// 		line++;
// 	}
// 	return (1);
// }

static char	**read_file_lines(char *path)
{
	int		fd;
	char	*line = NULL;
	char	**lines = NULL;
	int		count = 0;
	char	buf[1024];
	int		ret;
	int		i = 0;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);

	// 1. Conta quantas linhas tem
	while ((ret = read(fd, buf, 1024)) > 0)
		for (int j = 0; j < ret; j++)
			if (buf[j] == '\n')
				count++;
	close(fd);

	lines = malloc(sizeof(char *) * (count + 2));
	if (!lines)
		return (NULL);

	fd = open(path, O_RDONLY);
	while ((ret = read(fd, buf, 1)) > 0)
	{
		if (!line) line = strdup("");
		if (buf[0] != '\n')
			line = realloc(line, strlen(line) + 2);
		strncat(line, buf, 1);
		if (buf[0] == '\n')
		{
			lines[i++] = line;
			line = NULL;
		}
	}
	if (line)
		lines[i++] = line;
	lines[i] = NULL;
	close(fd);
	return (lines);
}

int	parse_cub_file(char *path, t_config *config)
{
	char	**lines = read_file_lines(path);
	int		i = 0;

	if (!lines)
		return (1);

	while (lines[i])
	{
		if (strncmp(lines[i], "NO ", 3) == 0)
			config->no_tex = strdup(lines[i] + 3);
		else if (strncmp(lines[i], "SO ", 3) == 0)
			config->so_tex = strdup(lines[i] + 3);
		else if (strncmp(lines[i], "WE ", 3) == 0)
			config->we_tex = strdup(lines[i] + 3);
		else if (strncmp(lines[i], "EA ", 3) == 0)
			config->ea_tex = strdup(lines[i] + 3);
		// Ainda vamos lidar com F, C e mapa depois
		i++;
	}
	return (0);
}


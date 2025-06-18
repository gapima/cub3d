/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:47:12 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 17:35:21 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**free_parse_error(char **map, int *out_height, int fd, char *line)
{
	int	i;

	i = 0;
	while (i < *out_height)
		free(map[i++]);
	free(map);
	close(fd);
	free(line);
	return (NULL);
}

static char	**parse_map_lines(t_parse_ctx *ctx, char *line)
{
	while (line && *(ctx->y) < MAX_MAP_HEIGHT)
	{
		if (!process_line(ctx, line))
			return (free_parse_error(ctx->map, ctx->y, ctx->fd, line));
		line = get_next_line(ctx->fd);
	}
	if (line)
		free(line);
	ctx->map[*(ctx->y)] = NULL;
	return (ctx->map);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	parse_color_component(char *str)
{
	int	value;

	value = ft_atoi(str);
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("❌ Error: Color component out of range (0-255): ", 2);
		ft_putstr_fd(str, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
	return (value);
}

char	**read_cub_file(const char *path, t_config *cfg, int *out_height)
{
	int			fd;
	char		*line;
	char		**map;
	t_parse_ctx	ctx;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_putstr_fd("Error opening .cub file\n", 2), NULL);
	map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));
	if (!map)
		return (close(fd), NULL);
	ctx = (t_parse_ctx){cfg, map, out_height, fd};
	*out_height = 0;
	line = get_next_line(fd);
	map = parse_map_lines(&ctx, line);
	close(fd);
	return (map);
}

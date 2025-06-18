/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:44:32 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 17:22:50 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_texture_or_color(t_config *cfg, char *line)
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
		ft_putstr_fd("❌ Error: Invalid line: ", 2);
		ft_putstr_fd(line, 2);
		ft_putchar_fd('\n', 2);
		exit(EXIT_FAILURE);
	}
}

bool	is_map_line(char *line)
{
	return (!(
			ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0
			|| ft_strncmp(line, "EA ", 3) == 0
			|| ft_strncmp(line, "F ", 2) == 0
			|| ft_strncmp(line, "C ", 2) == 0
		));
}

bool	handle_texture_line(t_config *cfg, char *line)
{
	if (!line)
		return (false);
	parse_texture_or_color(cfg, line);
	free(line);
	return (true);
}

bool	handle_map_line(char **map, char *line, int *y, int fd)
{
	char	*newline;

	newline = ft_strchr(line, '\n');
	if (newline)
		*newline = '\0';
	map[*y] = ft_strdup(line);
	if (!map[*y])
	{
		close(fd);
		return (false);
	}
	(*y)++;
	free(line);
	return (true);
}

bool	process_line(t_parse_ctx *ctx, char *line)
{
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		return (true);
	}
	if (!is_map_line(line))
		return (handle_texture_line(ctx->cfg, line));
	return (handle_map_line(ctx->map, line, ctx->y, ctx->fd));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:30:32 by glima             #+#    #+#             */
/*   Updated: 2025/06/21 20:09:13 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_or_report_error(char c)
{
	if (!is_valid_map_char(c) && c != ' ')
	{
		ft_putstr_fd("Error: Invalid character: ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	return (true);
}

static bool	check_and_set_player(char c, int x, int y, t_player_ctx *ctx)
{
	if (ft_strchr("NSEW", c))
	{
		if (*(ctx->found))
		{
			ft_putstr_fd("Error: More than one starting position found.\n", 2);
			return (false);
		}
		*(ctx->found) = 1;
		*(ctx->px) = x;
		*(ctx->py) = y;
		set_player_direction(ctx->cfg, c);
	}
	return (true);
}

static bool	scan_map_for_player(char **map, int height, t_player_ctx *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_and_set_player(map[i][j], j, i, ctx))
				return (false);
			if (!is_valid_or_report_error(map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_player_and_chars(t_config *cfg, t_map_check_ctx *mctx)
{
	int				found;
	t_player_ctx	ctx;

	found = 0;
	ctx.cfg = cfg;
	ctx.found = &found;
	ctx.px = mctx->px;
	ctx.py = mctx->py;
	if (!scan_map_for_player(mctx->map, mctx->height, &ctx))
		return (false);
	if (!found)
	{
		ft_putstr_fd("Error: No player starting position found.\n", 2);
		return (false);
	}
	return (true);
}

bool	parse_cub_file(const char *path, t_config *cfg)
{
	char	**map;
	int		height;

	map = read_cub_file(path, cfg, &height);
	if (!map)
		return (false);
	if (!validate_and_prepare_map(map, height, cfg))
		return (false);
	return (true);
}

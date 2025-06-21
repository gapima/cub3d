/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 15:28:27 by glima             #+#    #+#             */
/*   Updated: 2025/06/21 15:28:28 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_diagonals(int x, int y, t_map_check *ctx)
{
	if (y > 0 && x > 0 && (ctx->map[y - 1][x - 1] == ' '
		|| ctx->map[y - 1][x - 1] == 2))
		return (false);
	if (y + 1 < ctx->height && x > 0 && (ctx->map[y + 1][x - 1] == ' '
		|| ctx->map[y + 1][x - 1] == 2))
		return (false);
	if (y > 0 && x + 1 < ctx->width && (ctx->map[y - 1][x + 1] == ' '
		|| ctx->map[y - 1][x + 1] == 2))
		return (false);
	if (y + 1 < ctx->height && x + 1 < ctx->width
		&& (ctx->map[y + 1][x + 1] == ' ' || ctx->map[y + 1][x + 1] == 2))
		return (false);
	return (true);
}

static bool	check_sides(int x, int y, t_map_check *ctx)
{
	if (y <= 0 || y >= ctx->height - 1 || x <= 0 || x >= ctx->width - 1)
		return (false);
	if (x >= (int)ft_strlen(ctx->map[y - 1])
		|| x >= (int)ft_strlen(ctx->map[y + 1]))
		return (false);
	if (ctx->map[y - 1][x] == ' ' || ctx->map[y - 1][x] == 2)
		return (false);
	if (ctx->map[y + 1][x] == ' ' || ctx->map[y + 1][x] == 2)
		return (false);
	if (ctx->map[y][x - 1] == ' ' || ctx->map[y][x - 1] == 2)
		return (false);
	if (ctx->map[y][x + 1] == ' ' || ctx->map[y][x + 1] == 2)
		return (false);
	return (true);
}

static void	put_coord_error(int x, int y)
{
	ft_putstr_fd("Error: Map is not completely enclosed at coordinates (", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd(", ", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd(")\n", 2);
}

static void	check_cell(int x, int y, t_map_check *ctx)
{
	char	c;

	if (x >= (int)ft_strlen(ctx->map[y]))
		return ;
	c = ctx->map[y][x];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (!check_sides(x, y, ctx) || !check_diagonals(x, y, ctx))
		{
			put_coord_error(x, y);
			exit(EXIT_FAILURE);
		}
	}
}

void	validate_closed_map(char **map, int height, int width)
{
	t_map_check	ctx;
	int			y;
	int			x;

	ctx.map = map;
	ctx.height = height;
	ctx.width = width;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
			check_cell(x++, y, &ctx);
		y++;
	}
}

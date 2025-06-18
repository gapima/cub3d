/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:35:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 18:06:25 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_max_width(char **map, int height)
{
	int	i;
	int	len;
	int	max;

	i = 0;
	max = 0;
	while (i < height)
	{
		len = ft_strlen(map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

bool	validate_and_prepare_map(char **map, int height, t_config *cfg)
{
	int				max_width;
	int				player_x;
	int				player_y;
	t_map_check_ctx	mctx;

	max_width = get_max_width(map, height);
	if (!pad_map_lines(map, height, max_width))
		return (false);
	mctx.map = map;
	mctx.height = height;
	mctx.px = &player_x;
	mctx.py = &player_y;
	if (!validate_player_and_chars(cfg, &mctx))
		return (false);
	validate_closed_map(map, height, max_width);
	cfg->player.pos_x = player_x + 0.5;
	cfg->player.pos_y = player_y + 0.5;
	map[player_y][player_x] = '0';
	cfg->map = map;
	return (true);
}

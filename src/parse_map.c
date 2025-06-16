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

static bool check_and_set_player(char c, int x, int y, int *found, t_config *cfg, int *px, int *py)
{
	if (ft_strchr("NSEW", c))
	{
		if (*found)
		{
			ft_putstr_fd("❌ Erro: Mais de uma posição inicial.\n", 2);
			return (false);
		}
		*found = 1;
		*px = x;
		*py = y;
		set_player_direction(cfg, c);
	}
	return (true);
}


static bool is_valid_or_report_error(char c)
{
	if (!is_valid_map_char(c) && c != ' ')
	{
		ft_putstr_fd("❌ Caractere inválido: ", 2);
		ft_putchar_fd(c, 2);
		ft_putchar_fd('\n', 2);
		return (false);
	}
	return (true);
}

static bool validate_player_and_chars(char **map, int height, t_config *cfg, int *px, int *py)
{
	int i;
	int j;
	int found;

	i = 0;
	found = 0;
	while (i < height)
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_and_set_player(map[i][j], j, i, &found, cfg, px, py))
				return (false);
			if (!is_valid_or_report_error(map[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	if (!found)
	{
		ft_putstr_fd("❌ Erro: Nenhuma posição inicial do jogador.\n", 2);
		return (false);
	}
	return (true);
}


static bool validate_and_prepare_map(char **map, int height, t_config *cfg)
{
	int max_width;
	int player_x;
	int player_y;

	max_width = get_max_width(map, height);
	if (!pad_map_lines(map, height, max_width))
		return (false);
	if (!validate_player_and_chars(map, height, cfg, &player_x, &player_y))
		return (false);
	validate_closed_map(map, height, max_width);
	cfg->player.pos_x = player_x + 0.5;
	cfg->player.pos_y = player_y + 0.5;
	map[player_y][player_x] = '0';
	cfg->map = map;
	return (true);
}



bool parse_cub_file(const char *path, t_config *cfg)
{
	char **map;
	int height;

    map = read_cub_file(path, cfg, &height);
    if (!map)
    {
            free_map(map, height);
            return (false);
    }
    if (!validate_and_prepare_map(map, height, cfg))
    {
            free_map(map, height);
            return (false);
    }
    return (true);
}

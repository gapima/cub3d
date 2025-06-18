/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:18:52 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 18:44:37 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_paths(t_config *cfg)
{
	cfg->no_path = NULL;
	cfg->so_path = NULL;
	cfg->we_path = NULL;
	cfg->ea_path = NULL;
}

void	init_textures(t_config *cfg)
{
	cfg->tex_no = NULL;
	cfg->tex_so = NULL;
	cfg->tex_we = NULL;
	cfg->tex_ea = NULL;
}

void	init_colors_and_map(t_config *cfg)
{
	cfg->floor_color = 0x000000FF;
	cfg->ceiling_color = 0xAAAAAAFF;
	cfg->map = NULL;
}

void	move_forward(t_config *cfg)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &cfg->player;
	new_x = p->pos_x + p->dir_x * MOVE_SPEED;
	new_y = p->pos_y + p->dir_y * MOVE_SPEED;
	if (cfg->map[(int)new_y][(int)new_x] == '0')
	{
		p->pos_x = new_x;
		p->pos_y = new_y;
	}
}

bool	pad_map_lines(char **map, int height, int max_width)
{
	int		i;
	int		len;
	int		j;
	char	*padded;

	i = 0;
	while (i < height)
	{
		padded = ft_calloc(max_width + 1, sizeof(char));
		if (!padded)
			return (false);
		len = ft_strlen(map[i]);
		ft_memcpy(padded, map[i], len);
		j = len;
		while (j < max_width)
			padded[j++] = ' ';
		free(map[i]);
		map[i] = padded;
		i++;
	}
	return (true);
}

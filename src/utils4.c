/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:18:52 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 17:15:33 by glima            ###   ########.fr       */
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
	if (cfg->map[(int)new_y][(int)p->pos_x] == '0')
		p->pos_y = new_y;
	if (cfg->map[(int)p->pos_y][(int)new_x] == '0')
		p->pos_x = new_x;
}

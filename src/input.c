/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:40:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 18:06:46 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void handle_input(mlx_key_data_t keydata, void *param)
{
	t_config *cfg = (t_config *)param;
	t_player *p = &cfg->player;
	double new_x, new_y;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(cfg->mlx);

	if (keydata.key == MLX_KEY_W)
	{
		new_x = p->pos_x + p->dir_x * MOVE_SPEED;
		new_y = p->pos_y + p->dir_y * MOVE_SPEED;
		if (cfg->map[(int)new_y][(int)p->pos_x] == '0')
			p->pos_y = new_y;
		if (cfg->map[(int)p->pos_y][(int)new_x] == '0')
			p->pos_x = new_x;
	}
	if (keydata.key == MLX_KEY_S)
	{
		new_x = p->pos_x - p->dir_x * MOVE_SPEED;
		new_y = p->pos_y - p->dir_y * MOVE_SPEED;
		if (cfg->map[(int)new_y][(int)p->pos_x] == '0')
			p->pos_y = new_y;
		if (cfg->map[(int)p->pos_y][(int)new_x] == '0')
			p->pos_x = new_x;
	}
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_A))
	{
		new_x = p->pos_x - p->plane_x * MOVE_SPEED;
		new_y = p->pos_y - p->plane_y * MOVE_SPEED;
		if (cfg->map[(int)new_y][(int)p->pos_x] == '0')
			p->pos_y = new_y;
		if (cfg->map[(int)p->pos_y][(int)new_x] == '0')
			p->pos_x = new_x;
	}
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_D))
	{
		new_x = p->pos_x + p->plane_x * MOVE_SPEED;
		new_y = p->pos_y + p->plane_y * MOVE_SPEED;
		if (cfg->map[(int)new_y][(int)p->pos_x] == '0')
			p->pos_y = new_y;
		if (cfg->map[(int)p->pos_y][(int)new_x] == '0')
			p->pos_x = new_x;
	}
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_LEFT))
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(-ROT_SPEED) - p->dir_y * sin(-ROT_SPEED);
		p->dir_y = old_dir_x * sin(-ROT_SPEED) + p->dir_y * cos(-ROT_SPEED);

		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(-ROT_SPEED) - p->plane_y * sin(-ROT_SPEED);
		p->plane_y = old_plane_x * sin(-ROT_SPEED) + p->plane_y * cos(-ROT_SPEED);
	}
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_RIGHT))
	{
		double old_dir_x = p->dir_x;
		p->dir_x = p->dir_x * cos(ROT_SPEED) - p->dir_y * sin(ROT_SPEED);
		p->dir_y = old_dir_x * sin(ROT_SPEED) + p->dir_y * cos(ROT_SPEED);

		double old_plane_x = p->plane_x;
		p->plane_x = p->plane_x * cos(ROT_SPEED) - p->plane_y * sin(ROT_SPEED);
		p->plane_y = old_plane_x * sin(ROT_SPEED) + p->plane_y * cos(ROT_SPEED);
	}
}

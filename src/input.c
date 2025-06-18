/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:40:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/18 18:45:43 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_backward(t_config *cfg)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &cfg->player;
	new_x = p->pos_x - p->dir_x * MOVE_SPEED;
	new_y = p->pos_y - p->dir_y * MOVE_SPEED;

	if (cfg->map[(int)new_y][(int)new_x] == '0')
	{
		p->pos_x = new_x;
		p->pos_y = new_y;
	}
}

static void	strafe_left(t_config *cfg)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &cfg->player;
	new_x = p->pos_x - p->plane_x * MOVE_SPEED;
	new_y = p->pos_y - p->plane_y * MOVE_SPEED;

	if (cfg->map[(int)new_y][(int)new_x] == '0')
	{
		p->pos_x = new_x;
		p->pos_y = new_y;
	}
}

static void	strafe_right(t_config *cfg)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = &cfg->player;
	new_x = p->pos_x + p->plane_x * MOVE_SPEED;
	new_y = p->pos_y + p->plane_y * MOVE_SPEED;

	if (cfg->map[(int)new_y][(int)new_x] == '0')
	{
		p->pos_x = new_x;
		p->pos_y = new_y;
	}
}

static void	rotate_view(t_config *cfg, double angle)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &cfg->player;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	t_config	*cfg;

	cfg = (t_config *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_close_window(cfg->mlx);
		return ;
	}

	if (mlx_is_key_down(cfg->mlx, MLX_KEY_W))
		move_forward(cfg);
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_S))
		move_backward(cfg);
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_A))
		strafe_left(cfg);
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_D))
		strafe_right(cfg);
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_LEFT))
		rotate_view(cfg, -ROT_SPEED);
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_RIGHT))
		rotate_view(cfg, ROT_SPEED);
}

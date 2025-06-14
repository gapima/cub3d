/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:40:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 13:57:43 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void   handle_input(mlx_key_data_t keydata, void *param)
{
    t_config    *cfg = (t_config *)param;
    t_player    *p = &cfg->player;

    if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
        return;

    if (keydata.key == MLX_KEY_ESCAPE)
        mlx_close_window(cfg->mlx);
    
    if (keydata.key == MLX_KEY_W)
    {
        p->pos_x += p->dir_x * MOVE_SPEED;
        p->pos_y += p->dir_y * MOVE_SPEED;
    }
    if (keydata.key == MLX_KEY_S)
    {
        p->pos_x -= p->dir_x * MOVE_SPEED;
        p->pos_y -= p->dir_y * MOVE_SPEED;
    }
    if (keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_D)
    {
        double old_dir_x = p->dir_x;
		double old_plane_x = p->plane_x;
		double rot = (keydata.key == MLX_KEY_D) ? -ROT_SPEED : ROT_SPEED;

		p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
		p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);

		p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
		p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
    }
}
    
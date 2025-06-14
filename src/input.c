/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:40:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 14:09:36 by glima            ###   ########.fr       */
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
    if (mlx_is_key_down(cfg->mlx, MLX_KEY_A))
    {
        cfg->player.pos_x -= cfg->player.plane_x * MOVE_SPEED;
        cfg->player.pos_y -= cfg->player.plane_y * MOVE_SPEED;
    }
    if (mlx_is_key_down(cfg->mlx, MLX_KEY_D))
    {
        cfg->player.pos_x += cfg->player.plane_x * MOVE_SPEED;
        cfg->player.pos_y += cfg->player.plane_y * MOVE_SPEED;
    }
    if (mlx_is_key_down(cfg->mlx, MLX_KEY_LEFT))
    {
        double old_dir_x = cfg->player.dir_x;
        cfg->player.dir_x = cfg->player.dir_x * cos(-ROT_SPEED) - cfg->player.dir_y * sin(-ROT_SPEED);
        cfg->player.dir_y = old_dir_x * sin(-ROT_SPEED) + cfg->player.dir_y * cos(-ROT_SPEED);
    
        double old_plane_x = cfg->player.plane_x;
        cfg->player.plane_x = cfg->player.plane_x * cos(-ROT_SPEED) - cfg->player.plane_y * sin(-ROT_SPEED);
        cfg->player.plane_y = old_plane_x * sin(-ROT_SPEED) + cfg->player.plane_y * cos(-ROT_SPEED);
    }
    if (mlx_is_key_down(cfg->mlx, MLX_KEY_RIGHT))
    {
        double old_dir_x = cfg->player.dir_x;
        cfg->player.dir_x = cfg->player.dir_x * cos(ROT_SPEED) - cfg->player.dir_y * sin(ROT_SPEED);
        cfg->player.dir_y = old_dir_x * sin(ROT_SPEED) + cfg->player.dir_y * cos(ROT_SPEED);

        double old_plane_x = cfg->player.plane_x;
        cfg->player.plane_x = cfg->player.plane_x * cos(ROT_SPEED) - cfg->player.plane_y * sin(ROT_SPEED);
        cfg->player.plane_y = old_plane_x * sin(ROT_SPEED) + cfg->player.plane_y * cos(ROT_SPEED);
    }
}
    
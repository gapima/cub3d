/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 10:32:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/10 10:32:42 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	handle_input(t_config *cfg)
{
	static double	last_move_time = 0;
	double			current_time;

	current_time = mlx_get_time(); // segundos

	if (current_time - last_move_time < 0.2)
		return;

	int	x = cfg->player_x;
	int	y = cfg->player_y;

	if (mlx_is_key_down(cfg->mlx, MLX_KEY_W) && cfg->map[y - 1][x] == '0')
		y--;
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_S) && cfg->map[y + 1][x] == '0')
		y++;
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_A) && cfg->map[y][x - 1] == '0')
		x--;
	if (mlx_is_key_down(cfg->mlx, MLX_KEY_D) && cfg->map[y][x + 1] == '0')
		x++;

	// se não mudou de posição, não faz nada
	if (x == cfg->player_x && y == cfg->player_y)
		return;

	cfg->map[cfg->player_y][cfg->player_x] = '0';
	cfg->map[y][x] = cfg->player_dir;
	cfg->player_x = x;
	cfg->player_y = y;

	last_move_time = current_time;
}

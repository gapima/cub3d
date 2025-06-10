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
	int	new_x = cfg->player_x;
	int	new_y = cfg->player_y;

	if (mlx_is_key_down(cfg->mlx, MLX_KEY_W))
		new_y--;
	else if (mlx_is_key_down(cfg->mlx, MLX_KEY_S))
		new_y++;
	else if (mlx_is_key_down(cfg->mlx, MLX_KEY_A))
		new_x--;
	else if (mlx_is_key_down(cfg->mlx, MLX_KEY_D))
		new_x++;

	// Verifica se o novo local é válido
	if (cfg->map[new_y][new_x] == '0')
	{
		cfg->map[cfg->player_y][cfg->player_x] = '0';
		cfg->player_x = new_x;
		cfg->player_y = new_y;
		cfg->map[new_y][new_x] = 'N'; // ou a direção real
	}
}

void	handle_key_event(mlx_key_data_t keydata, void *param)
{
	t_config *cfg = (t_config *)param;
	int new_x = cfg->player_x;
	int new_y = cfg->player_y;

	if (keydata.action != MLX_PRESS)
		return;

	if (keydata.key == MLX_KEY_W)
		new_y--;
	else if (keydata.key == MLX_KEY_S)
		new_y++;
	else if (keydata.key == MLX_KEY_A)
		new_x--;
	else if (keydata.key == MLX_KEY_D)
		new_x++;

	if (cfg->map[new_y][new_x] == '0')
	{
		cfg->map[cfg->player_y][cfg->player_x] = '0';
		cfg->player_x = new_x;
		cfg->player_y = new_y;
		cfg->map[new_y][new_x] = 'N'; // ou direção real
	}
}

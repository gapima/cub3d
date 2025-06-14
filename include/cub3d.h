/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:30:42 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:30:42 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "MLX42/MLX42.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 640
#define HEIGHT 480

typedef struct s_player {
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
} t_player;

void	hook(void* param);
extern int worldMap[24][24];
extern t_player player;
void	handle_input(mlx_key_data_t keydata, void *param);



#endif


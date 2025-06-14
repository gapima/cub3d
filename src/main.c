/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:21:14 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:21:14 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_t		*mlx;
mlx_image_t	*img;

int worldMap[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

t_player player = {
	.posX = 22.0,
	.posY = 12.0,
	.dirX = -1.0,
	.dirY = 0.0,
	.planeX = 0.0,
	.planeY = 0.66
};

void	hook(void *param)
{
	(void)param;

	for (int x = 0; x < WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = player.dirX + player.planeX * cameraX;
		double rayDirY = player.dirY + player.planeY * cameraX;

		int mapX = (int)player.posX;
		int mapY = (int)player.posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;
		int hit = 0; 
		int side;  

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapY][mapX] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;

		uint32_t color = (side == 1) ? 0xFFAAAAAA : 0xFFFFFFFF;

		for (int y = drawStart; y < drawEnd; y++)
			mlx_put_pixel(img, x, y, color);
	}
}

void	handle_input(mlx_key_data_t keydata, void *param)
{
	(void)param;

	double moveSpeed = 0.1;
	double rotSpeed = 0.05;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W)
		{
			if (worldMap[(int)(player.posY)][(int)(player.posX + player.dirX * moveSpeed)] == 0)
				player.posX += player.dirX * moveSpeed;
			if (worldMap[(int)(player.posY + player.dirY * moveSpeed)][(int)(player.posX)] == 0)
				player.posY += player.dirY * moveSpeed;
		}
		else if (keydata.key == MLX_KEY_S)
		{
			if (worldMap[(int)(player.posY)][(int)(player.posX - player.dirX * moveSpeed)] == 0)
				player.posX -= player.dirX * moveSpeed;
			if (worldMap[(int)(player.posY - player.dirY * moveSpeed)][(int)(player.posX)] == 0)
				player.posY -= player.dirY * moveSpeed;
		}
		else if (keydata.key == MLX_KEY_A)
		{
			if (worldMap[(int)(player.posY)][(int)(player.posX - player.planeX * moveSpeed)] == 0)
				player.posX -= player.planeX * moveSpeed;
			if (worldMap[(int)(player.posY - player.planeY * moveSpeed)][(int)(player.posX)] == 0)
				player.posY -= player.planeY * moveSpeed;
		}
		else if (keydata.key == MLX_KEY_D)
		{
			if (worldMap[(int)(player.posY)][(int)(player.posX + player.planeX * moveSpeed)] == 0)
				player.posX += player.planeX * moveSpeed;
			if (worldMap[(int)(player.posY + player.planeY * moveSpeed)][(int)(player.posX)] == 0)
				player.posY += player.planeY * moveSpeed;
		}
		else if (keydata.key == MLX_KEY_LEFT)
		{
			double oldDirX = player.dirX;
			player.dirX = player.dirX * cos(rotSpeed) - player.dirY * sin(rotSpeed);
			player.dirY = oldDirX * sin(rotSpeed) + player.dirY * cos(rotSpeed);

			double oldPlaneX = player.planeX;
			player.planeX = player.planeX * cos(rotSpeed) - player.planeY * sin(rotSpeed);
			player.planeY = oldPlaneX * sin(rotSpeed) + player.planeY * cos(rotSpeed);
		}
		else if (keydata.key == MLX_KEY_RIGHT)
		{
			double oldDirX = player.dirX;
			player.dirX = player.dirX * cos(-rotSpeed) - player.dirY * sin(-rotSpeed);
			player.dirY = oldDirX * sin(-rotSpeed) + player.dirY * cos(-rotSpeed);

			double oldPlaneX = player.planeX;
			player.planeX = player.planeX * cos(-rotSpeed) - player.planeY * sin(-rotSpeed);
			player.planeY = oldPlaneX * sin(-rotSpeed) + player.planeY * cos(-rotSpeed);
		}
	}
}



int	main(void)
{
	mlx = mlx_init(WIDTH, HEIGHT, "cub3D - Lodev", true);
	if (!mlx)
		return (EXIT_FAILURE);

	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (EXIT_FAILURE);

	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
	{
		mlx_close_window(mlx);
		return (EXIT_FAILURE);
	}

	mlx_loop_hook(mlx, &hook, NULL);

	mlx_key_hook(mlx, &handle_input, NULL);

	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}


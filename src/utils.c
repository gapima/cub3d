/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 19:15:41 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 19:15:53 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	int index = (y * tex->width + x) * 4;
	uint8_t r = tex->pixels[index + 0];
	uint8_t g = tex->pixels[index + 1];
	uint8_t b = tex->pixels[index + 2];
	uint8_t a = tex->pixels[index + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

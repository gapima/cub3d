/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:46:41 by glima             #+#    #+#             */
/*   Updated: 2025/06/05 19:46:41 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	rgb_to_int(char *line)
{
	int	r, g, b;
	char **parts = ft_split(line, ',');

	if (!parts || !parts[0] || !parts[1] || !parts[2])
		return (-1); // erro

	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);

	// libera memória do split
	for (int i = 0; parts[i]; i++)
		free(parts[i]);
	free(parts);

	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

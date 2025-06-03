/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:27:05 by glima             #+#    #+#             */
/*   Updated: 2025/06/03 17:27:05 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_config(t_config *config)
{
	if (config->no_tex)
		free(config->no_tex);
	if (config->so_tex)
		free(config->so_tex);
	if (config->we_tex)
		free(config->we_tex);
	if (config->ea_tex)
		free(config->ea_tex);

	// Libera mapa se tiver sido carregado
	if (config->map)
	{
		int i = 0;
		while (config->map[i])
			free(config->map[i++]);
		free(config->map);
	}
}

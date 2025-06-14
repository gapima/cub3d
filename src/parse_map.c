/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:31:04 by glima             #+#    #+#             */
/*   Updated: 2025/06/14 17:54:48 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N');
}

void parse_cub_file(const char *path, t_config *cfg)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo .cub");
		exit(EXIT_FAILURE);
	}

	char *line;
	int y = 0;
	int player_found = 0;
	int has_started = 0;
	int has_ended = 0;
	char **map = malloc(sizeof(char *) * (MAX_MAP_HEIGHT + 1));

	while ((line = get_next_line(fd)) && y < MAX_MAP_HEIGHT)
	{
		if (line[0] == '\n')
		{
			free(line);
			if (has_started)
				has_ended = 1;
			continue;
		}

		if (has_ended)
		{
			fprintf(stderr, "❌ Erro: Linha encontrada após fim do mapa.\n");
			exit(EXIT_FAILURE);
		}

		map[y] = ft_strtrim(line, "\n");
		free(line);

		for (int x = 0; map[y][x]; x++)
		{
			char c = map[y][x];
			if (!is_valid_map_char(c))
			{
				fprintf(stderr, "❌ Erro: Caractere inválido no mapa: '%c'\n", c);
				exit(EXIT_FAILURE);
			}
			if (c == 'N')
			{
				if (player_found)
				{
					fprintf(stderr, "❌ Erro: Mais de uma posição inicial encontrada.\n");
					exit(EXIT_FAILURE);
				}
				cfg->player.pos_x = x + 0.5;
				cfg->player.pos_y = y + 0.5;
				cfg->player.dir_x = 0;
				cfg->player.dir_y = -1;
				cfg->player.plane_x = 0.66;
				cfg->player.plane_y = 0;
				map[y][x] = '0';
				player_found = 1;
			}
		}
		has_started = 1;
		y++;
	}
	map[y] = NULL;
	close(fd);

	if (!player_found)
	{
		fprintf(stderr, "❌ Erro: Nenhuma posição inicial do jogador encontrada.\n");
		exit(EXIT_FAILURE);
	}

	cfg->map = map;
}

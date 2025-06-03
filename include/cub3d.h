/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 16:59:05 by glima             #+#    #+#             */
/*   Updated: 2025/06/03 16:59:05 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

typedef struct s_color {
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_config {
	char	*no_tex;
	char	*so_tex;
	char	*we_tex;
	char	*ea_tex;
	t_color	floor;
	t_color	ceiling;
	char	**map;
	int		map_height;
}	t_config;


//funcoes para do parsing
int		parse_cub_file(char *path, t_config *config);
void	free_config(t_config *config);
void	print_config(const t_config *config);


#endif
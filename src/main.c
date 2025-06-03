/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:08:30 by glima             #+#    #+#             */
/*   Updated: 2025/06/03 17:08:30 by glima            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int argc, char **argv)
{
    t_config config;

    if (argc != 2)
    {
        write(2, "Error\nUsage: ./cub3D map.cub\n", 29);
        return (1);
    }
    if (parse_cub_file(argv[1], &config) != 0)
    {
        write(2, "Error\nFailed to parse map\n", 27);
        return (1);
    }
    print_config(&config);
    free_config(&config);
    return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 12:25:15 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:13:41 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Charge un fichier .xpm en image MLX et recupere l'adresse des pixels */
static int	load_one_texture(t_game *game, char *path, int i)
{
	if (!path)
		return (-1);
	game->textures[i].image_ptr = mlx_xpm_file_to_image(game->mlx_connexion,
			path, &game->textures[i].width, &game->textures[i].height);
	if (!game->textures[i].image_ptr)
		return (-1);
	game->textures[i].pixels_addr = mlx_get_data_addr(
			game->textures[i].image_ptr,
			&game->textures[i].bits_per_pixel, &game->textures[i].line_length,
			&game->textures[i].endian);
	return (0);
}

/* Charge les 4 textures des murs (NO, SO, WE, EA) */
int	load_textures(t_game *game)
{
	if (load_one_texture(game, game->config.path_north, 0) == -1)
		return (-1);
	if (load_one_texture(game, game->config.path_south, 1) == -1)
		return (-1);
	if (load_one_texture(game, game->config.path_west, 2) == -1)
		return (-1);
	if (load_one_texture(game, game->config.path_east, 3) == -1)
		return (-1);
	return (0);
}

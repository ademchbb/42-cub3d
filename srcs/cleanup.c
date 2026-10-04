/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:30:16 by ragolden          #+#    #+#             */
/*   Updated: 2026/09/29 12:28:09 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Libere toute la memoire puis quitte le programme avec status */
void	clean_exit(t_game *game, int status)
{
	free_all(game);
	exit(status);
}

/* Hook de la croix rouge : quitte proprement le programme */
int	close_window(t_game *game)
{
	clean_exit(game, EXIT_SUCCESS);
	return (0);
}

/* Detruit les textures, l'image, la fenetre et la connexion MLX */
static void	free_mlx(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (game->textures[i].image_ptr)
			mlx_destroy_image(game->mlx_connexion, game->textures[i].image_ptr);
		i++;
	}
	if (game->frame.image_ptr)
		mlx_destroy_image(game->mlx_connexion, game->frame.image_ptr);
	if (game->mlx_window)
		mlx_destroy_window(game->mlx_connexion, game->mlx_window);
	if (game->mlx_connexion)
	{
		mlx_destroy_display(game->mlx_connexion);
		free(game->mlx_connexion);
	}
}

/* Libere les chemins, la map puis toutes les ressources MLX */
void	free_all(t_game *game)
{
	int	i;

	free(game->config.path_east);
	free(game->config.path_north);
	free(game->config.path_south);
	free(game->config.path_west);
	i = 0;
	while (game->map.map && game->map.map[i])
	{
		free(game->map.map[i]);
		i++;
	}
	free(game->map.map);
	free_mlx(game);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:13:47 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:22:04 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx_co(t_game *game)
{
	game->mlx_connexion = mlx_init();
	if (!game->mlx_connexion)
	{
		print_error("mlx_init failed");
		clean_exit(game, EXIT_FAILURE);
	}
	game->mlx_window = mlx_new_window(game->mlx_connexion, WIN_WIDTH,
			WIN_HEIGHT, WIN_TITLE);
	if (!game->mlx_window)
	{
		print_error("Cannot create the window");
		clean_exit(game, EXIT_FAILURE);
	}
}

void	init_img(t_game *game)
{
	game->frame.image_ptr = mlx_new_image(game->mlx_connexion, WIN_WIDTH,
			WIN_HEIGHT);
	if (!game->frame.image_ptr)
	{
		print_error("Cannot create the image");
		clean_exit(game, EXIT_FAILURE);
	}
	game->frame.pixels_addr = mlx_get_data_addr(game->frame.image_ptr,
			&game->frame.bits_per_pixel, &game->frame.line_length,
			&game->frame.endian);
}

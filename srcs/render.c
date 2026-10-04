/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 17:25:58 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:12:03 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Ecrit un pixel de couleur dans l'image (ignore s'il sort de l'ecran) */
void	put_px(t_game *game, int pos_x, int pos_y, int color)
{
	int	offset;

	if (pos_x < 0 || pos_x >= WIN_WIDTH || pos_y < 0 || pos_y >= WIN_HEIGHT)
		return ;
	offset = (pos_y * game->frame.line_length) + (pos_x
			* (game->frame.bits_per_pixel / 8));
	*(unsigned int *)(game->frame.pixels_addr + offset) = color;
}

/* Appelee a chaque frame : deplace le joueur puis dessine la scene */
int	render_frames(t_game *game)
{
	if (game->key_w)
		move_forward(&game->player, &game->map);
	if (game->key_s)
		move_backward(&game->player, &game->map);
	if (game->key_a)
		move_left(&game->player, &game->map);
	if (game->key_d)
		move_right(&game->player, &game->map);
	if (game->key_left)
		rotate_left(&game->player);
	if (game->key_right)
		rotate_right(&game->player);
	render_floor_ceiling(game);
	render_wall_col(game, &game->map, &game->player, &game->ray);
	mlx_put_image_to_window(game->mlx_connexion, game->mlx_window,
		game->frame.image_ptr, 0, 0);
	return (0);
}

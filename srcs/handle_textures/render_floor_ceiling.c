/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:48:50 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:54:00 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Peint la moitie haute avec la couleur C et la moitie basse avec F */
void	render_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < WIN_HEIGHT / 2)
			color = game->config.ceiling_color;
		else
			color = game->config.floor_color;
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_px(game, x, y, color);
			x++;
		}
		y++;
	}
}

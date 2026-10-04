/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:55:06 by adchebbi          #+#    #+#             */
/*   Updated: 2026/10/03 14:16:35 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Dessine un carre plein de cote size a la position pos */
static void	draw_square(t_game *game, t_point pos, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (pos.x + i >= 0 && pos.x + i < WIN_WIDTH && pos.y + j >= 0
				&& pos.y + j < WIN_HEIGHT)
				put_px(game, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

/* Dessine une case de la minimap (mur ou sol) autour du joueur */
static void	draw_minimap_tile(t_game *game, t_point offset)
{
	t_point	screen_pos;
	char	c;

	screen_pos.x = MINIMAP_OFFSET_X + ((offset.x + MINIMAP_RADIUS)
			* MINIMAP_TILE_SIZE);
	screen_pos.y = MINIMAP_OFFSET_Y + ((offset.y + MINIMAP_RADIUS)
			* MINIMAP_TILE_SIZE);
	c = get_safe_char(&game->map, (int)game->player.pos_y + offset.y,
			(int)game->player.pos_x + offset.x);
	if (c == '1')
		draw_square(game, screen_pos, MINIMAP_TILE_SIZE, MINIMAP_COLOR_WALL);
	else if (c == '0' || is_spawn_char(c))
		draw_square(game, screen_pos, MINIMAP_TILE_SIZE, MINIMAP_COLOR_FLOOR);
}

/* Dessine toutes les cases dans un rayon de 10 autour du joueur */
static void	draw_minimap_tiles(t_game *game)
{
	t_point	offset;

	offset.y = -MINIMAP_RADIUS;
	while (offset.y <= MINIMAP_RADIUS)
	{
		offset.x = -MINIMAP_RADIUS;
		while (offset.x <= MINIMAP_RADIUS)
		{
			draw_minimap_tile(game, offset);
			offset.x++;
		}
		offset.y++;
	}
}

/* Dessine la minimap puis le point du joueur */
void	draw_minimap(t_game *game)
{
	t_point	player_draw_p;

	draw_minimap_tiles(game);
	player_draw_p.x = MINIMAP_OFFSET_X + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE)
		+ (int)((game->player.pos_x - (int)game->player.pos_x)
			* MINIMAP_TILE_SIZE) - 2;
	player_draw_p.y = MINIMAP_OFFSET_Y + (MINIMAP_RADIUS * MINIMAP_TILE_SIZE)
		+ (int)((game->player.pos_y - (int)game->player.pos_y)
			* MINIMAP_TILE_SIZE) - 2;
	draw_square(game, player_draw_p, 4, MINIMAP_COLOR_PLAYER);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floor_ceiling_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/17 12:48:50 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:54:30 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

/* Prepare une ligne de sol : distance et position du premier pixel */
void	init_floor_dim(t_game *game, t_tex_floor *floor, int y)
{
	int	p;

	p = y - (WIN_HEIGHT / 2);
	if (p == 0)
		p = 1;
	floor->row_dist = (0.5 * WIN_HEIGHT) / p;
	floor->ray_dir_x0 = game->player.dir_x - game->player.plane_x;
	floor->ray_dir_y0 = game->player.dir_y - game->player.plane_y;
	floor->ray_dir_x1 = game->player.dir_x + game->player.plane_x;
	floor->ray_dir_y1 = game->player.dir_y + game->player.plane_y;
	floor->floor_step_x = floor->row_dist * (floor->ray_dir_x1
			- floor->ray_dir_x0) / WIN_WIDTH;
	floor->floor_step_y = floor->row_dist * (floor->ray_dir_y1
			- floor->ray_dir_y0) / WIN_WIDTH;
	floor->floor_x = game->player.pos_x + floor->row_dist * floor->ray_dir_x0;
	floor->floor_y = game->player.pos_y + floor->row_dist * floor->ray_dir_y0;
}

/* Dessine une ligne de sol texturee et la ligne de plafond symetrique */
void	draw_floor_line(t_game *game, t_tex_floor *f, int y)
{
	int	x;
	int	tex_x;
	int	tex_y;
	int	ceil_y;

	x = 0;
	ceil_y = WIN_HEIGHT - y - 1;
	while (x < WIN_WIDTH)
	{
		tex_x = (int)(game->textures[4].width * (f->floor_x
					- floor(f->floor_x))) % game->textures[4].width;
		tex_y = (int)(game->textures[4].height * (f->floor_y
					- floor(f->floor_y))) % game->textures[4].height;
		put_px(game, x, y, get_tex_color(&game->textures[4], tex_x, tex_y));
		put_px(game, x, ceil_y, get_tex_color(&game->textures[5], tex_x,
				tex_y));
		f->floor_x += f->floor_step_x;
		f->floor_y += f->floor_step_y;
		x++;
	}
}

void	render_floor_ceiling(t_game *game)
{
	t_tex_floor	floor;
	int			y;

	y = WIN_HEIGHT / 2;
	while (y < WIN_HEIGHT)
	{
		init_floor_dim(game, &floor, y);
		draw_floor_line(game, &floor, y);
		y++;
	}
}

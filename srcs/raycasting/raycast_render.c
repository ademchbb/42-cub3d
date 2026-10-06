/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 13:42:03 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 19:11:10 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Hauteur du mur a l'ecran et lignes de debut et de fin de la colonne*/
static void	help_to_calc(t_ray *ray)
{
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

/* Desine la colonne de mur pixel par pixel avec la texture*/
static void	draw_textured_col(t_game *game, t_ray *ray, int x, int draw_start)
{
	t_texture	*texture;
	double		step;
	double		tex_pos;
	int			y;
	int			tex_y;

	texture = &game->textures[ray->tex_index];
	step = (double)texture->height / ray->line_height;
	tex_pos = (draw_start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos % texture->height;
		tex_pos += step;
		put_px(game, x, y, get_tex_color(texture, ray->tex_x, tex_y));
		y++;
	}
}

/* Calcule puis dessine la colonne de mur x*/
static void	draw_wall_col(t_game *game, t_ray *ray, int x)
{
	help_to_calc(ray);
	draw_textured_col(game, ray, x, ray->draw_start);
}

/* Lance un rayon par colonne de l'ecran et dessine les murs*/
void	render_wall_col(t_game *game, t_map *map, t_player *player, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray_dir(player, ray, x);
		init_ray_dda(player, ray);
		init_ray_step(player, ray);
		exec_dda(map, ray);
		get_wall_dist(ray);
		ray->tex_index = get_tex_index(ray);
		ray->wall_x = get_wallx(player, ray);
		ray->tex_x = get_tex_x(ray, ray->wall_x,
				game->textures[ray->tex_index].width);
		draw_wall_col(game, ray, x);
		x++;
	}
}

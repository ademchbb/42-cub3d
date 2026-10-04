/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 15:27:10 by ragolden          #+#    #+#             */
/*   Updated: 2026/09/11 16:06:45 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Regle la direction et le plan camera pour un depart vers l'ouest */
void	west_dir(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -0.66;
}

/* Distance perpendiculaire au mur touche (evite l'effet fish-eye) */
void	get_wall_dist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
}

/* Place le joueur au centre de sa case de depart */
void	init_player_pos(t_player *player)
{
	player->pos_x = player->start_x + 0.5;
	player->pos_y = player->start_y + 0.5;
}

/* Avance le rayon d'une case en x ou en y (vers le bord le plus proche) */
void	step_ray_help(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

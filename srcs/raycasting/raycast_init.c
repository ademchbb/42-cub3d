/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 11:38:36 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:36:17 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_dir(t_player *player)
{
	if (player->orientation == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->orientation == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->orientation == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->orientation == 'W')
		west_dir(player);
}

/* Calcule la direction du rayon pour la colonne x de l'ecran*/
void	init_ray_dir(t_player *player, t_ray *ray, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
}

/* Cade de depart du rayon et distance pour traverser une case en x/y*/
void	init_ray_dda(t_player *player, t_ray *ray)
{
	ray->map_x = player->pos_x;
	ray->map_y = player->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

/* Sens du pas en x et y et distance jusqu'au premier bord de case*/
void	init_ray_step(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}

/* Avance le rayon case par case jusqu'a toucher un mur*/
void	exec_dda(t_map *map, t_ray *ray)
{
	int	steps;

	steps = 0;
	ray->hit = 0;
	while (ray->hit == 0 && steps < 2000)
	{
		step_ray_help(ray);
		if (ray->map_y < 0 || ray->map_y >= map->height || ray->map_x < 0
			|| ray->map_x >= (int)ft_strlen(map->map[ray->map_y])
			|| map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
		steps++;
	}
	if (steps >= 2000)
		ray->hit = 1;
}

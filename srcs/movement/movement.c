/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ragolden <ragolden@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 11:08:54 by ragolden          #+#    #+#             */
/*   Updated: 2026/09/11 16:54:50 by ragolden         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_x * MOVE_SPEED;
	new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	if (move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_backward(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_x * MOVE_SPEED;
	new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	if (move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_left(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x + player->dir_y * MOVE_SPEED;
	new_y = player->pos_y - player->dir_x * MOVE_SPEED;
	if (move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

void	move_right(t_player *player, t_map *map)
{
	double	new_x;
	double	new_y;

	new_x = player->pos_x - player->dir_y * MOVE_SPEED;
	new_y = player->pos_y + player->dir_x * MOVE_SPEED;
	if (move_to(map, new_x, player->pos_y))
		player->pos_x = new_x;
	if (move_to(map, player->pos_x, new_y))
		player->pos_y = new_y;
}

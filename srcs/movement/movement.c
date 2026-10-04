/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 11:08:54 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:13:32 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Avance dans la direction du regard (x et y testes separement) */
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

/* Recule a l'oppose du regard (x et y testes separement) */
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

/* Pas de cote vers la gauche (perpendiculaire au regard) */
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

/* Pas de cote vers la droite (perpendiculaire au regard) */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 15:59:40 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:52:05 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Vrai si le point (x, y) est dans une case qui n'est ni mur ni vide */
int	is_walkable_cell(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)x;
	map_y = (int)y;
	if (map_y < 0 || map_y >= map->height || map_x < 0)
		return (0);
	if (map_x >= (int)ft_strlen(map->map[map_y]))
		return (0);
	cell = get_safe_char(map, map_y, map_x);
	return (cell != '1' && cell != ' ');
}

/* Vrai si les 4 coins du joueur (marge 0.15) sont sur des cases libres */
int	move_to(t_map *map, double x, double y)
{
	double	margin;

	margin = 0.15;
	if (!is_walkable_cell(map, x - margin, y - margin))
		return (0);
	if (!is_walkable_cell(map, x + margin, y - margin))
		return (0);
	if (!is_walkable_cell(map, x - margin, y + margin))
		return (0);
	if (!is_walkable_cell(map, x + margin, y + margin))
		return (0);
	return (1);
}

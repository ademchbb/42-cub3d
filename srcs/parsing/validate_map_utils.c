/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 10:28:34 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:13:19 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Vrai si c est autorise dans la map (0, 1, N, S, E, W ou espace) */
int	is_valid_map_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ')
		return (1);
	return (0);
}

/* Vrai si c est une position de depart (N, S, E ou W) */
int	is_spawn_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

/* Renvoie la case (y, x), ou un espace si elle est hors de la map */
char	get_safe_char(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->height)
		return (' ');
	else if (x < 0 || x >= (int)ft_strlen(map->map[y]))
		return (' ');
	return (map->map[y][x]);
}

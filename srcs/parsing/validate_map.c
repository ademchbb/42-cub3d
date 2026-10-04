/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 14:02:54 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:13:22 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Verifie que la map n'a que des caracteres autorises et un seul joueur */
int	valid_map_chars(t_map *map)
{
	int	spawn_count;
	int	x;
	int	y;

	spawn_count = 0;
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (!is_valid_map_char(map->map[y][x]))
				return (print_error("Invalid character in the map"));
			else if (is_spawn_char(map->map[y][x]))
				spawn_count++;
			x++;
		}
		y++;
	}
	if (spawn_count == 0)
		return (print_error("No player start position (N, S, E or W)"));
	if (spawn_count > 1)
		return (print_error("Several player start positions in the map"));
	return (0);
}

/* Retient la case de depart du joueur et son orientation */
int	extract_player(t_map *map, t_player *player)
{
	int	x;
	int	y;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (is_spawn_char(map->map[y][x]))
			{
				player->start_x = x;
				player->start_y = y;
				player->orientation = map->map[y][x];
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}

/* Renvoie -1 si une des 4 cases voisines est un espace ou hors map */
static int	check_spaces(t_map *map, int y, int x)
{
	if (get_safe_char(map, y - 1, x) == ' ' || get_safe_char(map, y + 1,
			x) == ' ' || get_safe_char(map, y, x - 1) == ' '
		|| get_safe_char(map, y, x + 1) == ' ')
		return (-1);
	return (0);
}

/* Verifie que la map est fermee : aucun 0 ni joueur ne touche le vide */
int	check_map_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == ' ')
				;
			else if (map->map[y][x] == '0' || is_spawn_char(map->map[y][x]))
			{
				if (check_spaces(map, y, x) == -1)
					return (print_error("The map is not closed by walls"));
			}
			x++;
		}
		y++;
	}
	return (0);
}

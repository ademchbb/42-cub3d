/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 13:41:51 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:48:31 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_map_lines(char **lines, int map_start)
{
	int	i;
	int	last;

	i = map_start;
	last = map_start;
	while (lines[i])
	{
		if (!empty_line(lines[i]))
			last = i;
		i++;
	}
	return (last - map_start + 1);
}

static int	has_empty_line(char **lines, int map_start, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		if (empty_line(lines[map_start + i]))
			return (1);
		i++;
	}
	return (0);
}

char	*copy_map_line(char *line)
{
	int		i;
	char	*copy;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	copy = ft_substr(line, 0, i);
	return (copy);
}

int	get_map_width(char **map)
{
	int	i;
	int	len;
	int	max_width;

	i = 0;
	len = 0;
	max_width = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (len > max_width)
			max_width = len;
		i++;
	}
	return (max_width);
}

/* Copie les lignes de la map dans map->map (tableau termine par NULL) */
int	extract_map(char **lines, int map_start, t_map *map)
{
	int	height;
	int	i;

	height = count_map_lines(lines, map_start);
	if (has_empty_line(lines, map_start, height))
		return (print_error("Empty line inside the map"));
	map->height = height;
	map->map = malloc(sizeof(char *) * (height + 1));
	if (!map->map)
		return (print_error("Memory allocation failed"));
	i = 0;
	while (i < height)
	{
		map->map[i] = copy_map_line(lines[map_start + i]);
		if (!map->map[i])
			return (print_error("Memory allocation failed"));
		i++;
	}
	map->map[height] = NULL;
	map->width = get_map_width(map->map);
	return (0);
}

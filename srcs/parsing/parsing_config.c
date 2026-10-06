/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/01 14:01:57 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 18:49:30 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_config(t_config *config)
{
	config->path_north = NULL;
	config->path_south = NULL;
	config->path_west = NULL;
	config->path_east = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
}

static int	is_id(char *line, char *id)
{
	int	len;

	len = ft_strlen(id);
	return (ft_strncmp(line, id, len) == 0 && line[len] == ' ');
}

static int	assign_config_line(t_config *config, char *line)
{
	while (*line == ' ')
		line++;
	if (is_id(line, "NO"))
		return (assign_path(&config->path_north, line + 2));
	else if (is_id(line, "SO"))
		return (assign_path(&config->path_south, line + 2));
	else if (is_id(line, "WE"))
		return (assign_path(&config->path_west, line + 2));
	else if (is_id(line, "EA"))
		return (assign_path(&config->path_east, line + 2));
	else if (is_id(line, "F"))
		return (assign_color(&config->floor_color, line + 1));
	else if (is_id(line, "C"))
		return (assign_color(&config->ceiling_color, line + 1));
	return (print_error("Unknown identifier (use NO, SO, WE, EA, F, C)"));
}

static int	complete_config(t_config *config)
{
	if (!config->path_north || !config->path_south || !config->path_west
		|| !config->path_east || config->floor_color == -1
		|| config->ceiling_color == -1)
		return (0);
	return (1);
}

int	parse_config(char **lines, int map_start, t_config *config)
{
	int	i;

	init_config(config);
	if (map_start == -1)
		return (print_error("No map found in the .cub file"));
	i = 0;
	while (i < map_start)
	{
		if (!empty_line(lines[i]) && assign_config_line(config, lines[i]) == -1)
			return (-1);
		i++;
	}
	if (!complete_config(config))
		return (print_error("Missing element (NO, SO, WE, EA, F or C)"));
	return (0);
}

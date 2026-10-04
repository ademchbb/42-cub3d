/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 13:30:53 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 10:13:06 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Convertit un morceau de couleur en nombre de 0 a 255 (-1 si invalide) */
static int	parse_component(char *str)
{
	char	*nb;
	int		value;
	int		i;

	nb = ft_strtrim(str, " \n");
	if (!nb)
		return (-1);
	value = 0;
	i = 0;
	while (i < 3 && ft_isdigit(nb[i]))
	{
		value = value * 10 + (nb[i] - '0');
		i++;
	}
	if (i == 0 || nb[i] != '\0' || value > 255)
		value = -1;
	free(nb);
	return (value);
}

/* Convertit une couleur R,G,B en entier 0xRRGGBB (-1 si invalide) */
int	parse_color(char *line)
{
	char	**parts;
	int		rgb[3];
	int		i;

	if (count_char(line, ',') != 2)
		return (-1);
	parts = ft_split(line, ',');
	if (!parts)
		return (-1);
	i = 0;
	while (i < 3 && parts[i])
	{
		rgb[i] = parse_component(parts[i]);
		if (rgb[i] == -1)
			return (free_split(parts), -1);
		i++;
	}
	free_split(parts);
	if (i != 3)
		return (-1);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

/* Enregistre un chemin de texture apres l'avoir verifie (.xpm, ouvrable) */
int	assign_path(char **field, char *line)
{
	int	fd;

	if (*field)
		return (print_error("Duplicate texture identifier"));
	*field = ft_strtrim(line, " \n");
	if (!*field)
		return (print_error("Memory allocation failed"));
	if ((*field)[0] == '\0')
		return (print_error("Missing texture path"));
	if (!has_extension(*field, ".xpm"))
		return (print_error("Texture file must have a .xpm extension"));
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open a texture file"));
	close(fd);
	return (0);
}

/* Enregistre une couleur (F ou C) apres l'avoir verifiee */
int	assign_color(int *field, char *line)
{
	if (*field != -1)
		return (print_error("Duplicate color identifier"));
	*field = parse_color(line);
	if (*field == -1)
		return (print_error("Invalid color: expected R,G,B in [0,255]"));
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 15:58:59 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/04 09:54:42 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Agrandit le tableau de lignes d'une case et y ajoute line */
char	**add_line_to_array(char **lines, char *line, int count)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (count + 2));
	if (!tab)
		return (free(line), free_split(lines), NULL);
	i = 0;
	while (i < count)
	{
		tab[i] = lines[i];
		i++;
	}
	tab[count] = line;
	tab[count + 1] = NULL;
	free(lines);
	return (tab);
}

/* Lit la fin du fichier pour que get_next_line libere sa reserve */
static void	drain_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

/* Lit tout le fichier .cub ligne par ligne dans un tableau */
char	**read_file_lines(char *filepath)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (print_error("Cannot open the .cub file"), NULL);
	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = add_line_to_array(lines, line, count);
		if (!lines)
			return (close(fd), print_error("Memory allocation failed"), NULL);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	if (!lines)
		return (drain_gnl(fd), close(fd),
			print_error("Memory allocation failed"), NULL);
	return (lines);
}

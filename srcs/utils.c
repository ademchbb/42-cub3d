/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:55:06 by adchebbi          #+#    #+#             */
/*   Updated: 2026/10/04 10:12:07 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Affiche Error puis le message sur la sortie d'erreur, renvoie -1 */
int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putendl_fd(msg, 2);
	return (-1);
}

/* Vrai si le nom du fichier se termine par l'extension ext */
int	has_extension(char *path, char *ext)
{
	int	len;
	int	ext_len;

	len = ft_strlen(path);
	ext_len = ft_strlen(ext);
	if (len <= ext_len || path[len - ext_len - 1] == '/')
		return (0);
	return (ft_strncmp(path + len - ext_len, ext, ext_len + 1) == 0);
}

/* Compte le nombre de fois ou le caractere c apparait dans str */
int	count_char(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

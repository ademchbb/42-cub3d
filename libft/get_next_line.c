/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 08:26:46 by adchebbi          #+#    #+#             */
/*   Updated: 2026/10/04 09:52:47 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Ajoute le buffer lu au texte deja accumule, libere l'ancien texte et buff */
char	*ft_verify(char *tmp, char *buff)
{
	char	*joined;

	if (!tmp)
		joined = ft_strdup(buff);
	else
		joined = ft_strjoin(tmp, buff);
	free(tmp);
	free(buff);
	return (joined);
}

/* Garde ce qui reste apres le \n pour le prochain appel (0 si malloc echoue) */
int	ft_extract(char **ptr)
{
	char	*keep_tmp;
	char	*newline_pos;

	keep_tmp = NULL;
	newline_pos = ft_strchr(*ptr, '\n');
	if (newline_pos && *(newline_pos + 1))
	{
		keep_tmp = ft_strdup(newline_pos + 1);
		if (!keep_tmp)
			return (0);
	}
	free(*ptr);
	*ptr = keep_tmp;
	return (1);
}

/* Extrait la ligne a renvoyer et nettoie la memoire */
char	*ft_free(char **ptr_tmp, char **ptr_buff, ssize_t rb)
{
	char	*line;

	line = NULL;
	if (*ptr_tmp && ft_strchr(*ptr_tmp, '\n') != NULL)
	{
		line = ft_substr(*ptr_tmp, 0, (ft_strlen(*ptr_tmp)
					- ft_strlen(ft_strchr(*ptr_tmp, '\n'))) + 1);
		if (line && ft_extract(ptr_tmp))
			return (line);
		free(line);
		line = NULL;
	}
	else if (*ptr_tmp && **ptr_tmp && rb == 0)
		line = ft_strdup(*ptr_tmp);
	free(*ptr_tmp);
	*ptr_tmp = NULL;
	free(*ptr_buff);
	*ptr_buff = NULL;
	return (line);
}

/* Lit et renvoie une ligne (jusqu'au \n) depuis un fd */
char	*get_next_line(int fd)
{
	static char	*tmp;
	char		*buff;
	ssize_t		read_bytes;

	buff = NULL;
	read_bytes = 1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (read_bytes != 0)
	{
		if (tmp && (ft_strchr(tmp, '\n') != NULL))
			return (ft_free(&tmp, &buff, read_bytes));
		buff = (char *)malloc(BUFFER_SIZE + 1);
		if (buff == NULL)
			return (ft_free(&tmp, &buff, -1));
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes <= 0)
			break ;
		buff[read_bytes] = '\0';
		tmp = ft_verify(tmp, buff);
		buff = NULL;
		if (!tmp)
			return (NULL);
	}
	return (ft_free(&tmp, &buff, read_bytes));
}

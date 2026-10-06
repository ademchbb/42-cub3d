/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/15 12:22:54 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 19:21:23 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (3);
		return (2);
	}
	if (ray->ray_dir_y > 0)
		return (1);
	return (0);
}

/* Position exacte de l'impact sur le mur, entre 0 et 1 */
double	get_wallx(t_player *player, t_ray *ray)
{
	double	wallx;

	if (ray->side == 0)
		wallx = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wallx = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wallx -= floor(wallx);
	return (wallx);
}

/* Colonne de texture a utiliser (inversee pour eviter l'effet miroir) */
int	get_tex_x(t_ray *ray, double wallx, int tex_width)
{
	int	tex_x;

	tex_x = (int)(wallx * (double)tex_width);
	if (ray->side == 0 && ray->ray_dir_x <= 0)
		tex_x = tex_width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

/* Lit la couleur du pixel (tex_x, tex_y) dans la texture */
int	get_tex_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*px;

	px = texture->pixels_addr + (tex_y * texture->line_length + tex_x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)px);
}

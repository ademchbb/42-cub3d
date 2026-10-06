/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:55:06 by adchebbi          #+#    #+#             */
/*   Updated: 2026/10/06 19:00:01 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "cub3d.h"

# define MINIMAP_TILE_SIZE 8
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10
# define MINIMAP_RADIUS 10
# define MINIMAP_COLOR_WALL 0x00546C8F
# define MINIMAP_COLOR_FLOOR 0x002F3E47
# define MINIMAP_COLOR_PLAYER 0x00FF8C1A

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_tex_floor
{
	double		ray_dir_x0;
	double		ray_dir_y0;
	double		ray_dir_x1;
	double		ray_dir_y1;
	double		row_dist;
	double		floor_step_x;
	double		floor_step_y;
	double		floor_x;
	double		floor_y;
}				t_tex_floor;

void			init_floor_dim(t_game *game, t_tex_floor *floor, int y);
void			draw_floor_line(t_game *game, t_tex_floor *floor, int y);
void			draw_minimap(t_game *game);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 15:32:10 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/06 19:15:34 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MOVE_SPEED 0.01
# define ROTATION_SPEED 0.03
# define WIN_TITLE "cub3D"

typedef struct s_image
{
	void		*image_ptr;
	char		*pixels_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_image;

typedef struct s_config
{
	char		*path_north;
	char		*path_south;
	char		*path_west;
	char		*path_east;
	int			floor_color;
	int			ceiling_color;
}				t_config;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
}				t_map;

typedef struct s_player
{
	int			start_x;
	int			start_y;
	char		orientation;
	double		dir_x;
	double		dir_y;
	double		pos_x;
	double		pos_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			tex_index;
	double		wall_x;
	int			tex_x;
	int			draw_start;
	int			draw_end;
	int			line_height;
	double		perp_wall_dist;
}				t_ray;

typedef struct s_texture
{
	void		*image_ptr;
	char		*pixels_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_texture;

typedef struct s_game
{
	void		*mlx_connexion;
	void		*mlx_window;
	bool		key_w;
	bool		key_a;
	bool		key_s;
	bool		key_d;
	bool		key_left;
	bool		key_right;
	t_image		frame;
	t_config	config;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_texture	textures[6];
}				t_game;

/* ==== INIT ==== */
void			init_mlx_co(t_game *game);
void			init_img(t_game *game);
void			put_px(t_game *game, int pos_x, int pos_y, int color);
int				close_window(t_game *game);
int				render_frames(t_game *game);
void			clean_exit(t_game *game, int status);
void			free_all(t_game *game);
int				print_error(char *msg);
int				has_extension(char *path, char *ext);
int				count_char(char *str, char c);

/* ==== PARSING ==== */
char			**read_file_lines(char *filepath);
char			**add_line_to_array(char **lines, char *line, int count);
int				empty_line(char *line);
int				find_map_start(char **lines);
int				parse_config(char **lines, int map_start, t_config *config);
int				parse_color(char *line);
int				assign_path(char **field, char *line);
int				assign_color(int *field, char *line);

int				count_map_lines(char **lines, int map_start);
char			*copy_map_line(char *line);
int				get_map_width(char **map);
int				extract_map(char **lines, int map_start, t_map *map);

int				is_valid_map_char(char c);
int				is_spawn_char(char c);
int				valid_map_chars(t_map *map);
int				extract_player(t_map *map, t_player *player);
char			get_safe_char(t_map *map, int y, int x);
int				check_map_walls(t_map *map);

/* ==== RAYCASTING ==== */
void			west_dir(t_player *player);
void			init_player_pos(t_player *player);
void			init_player_dir(t_player *player);
void			init_ray_step(t_player *player, t_ray *ray);
void			init_ray_dda(t_player *player, t_ray *ray);
void			init_ray_dir(t_player *player, t_ray *ray, int x);
void			step_ray_help(t_ray *ray);
void			exec_dda(t_map *map, t_ray *ray);
void			get_wall_dist(t_ray *ray);
void			render_wall_col(t_game *game, t_map *map, t_player *player,
					t_ray *ray);

/* ==== MOVEMENT ==== */
int				handle_keypress(int keycode, t_game *game);
int				handle_keyrelease(int keycode, t_game *game);
int				handle_focus_out(t_game *game);
int				is_walkable_cell(t_map *map, double x, double y);
int				move_to(t_map *map, double x, double y);
void			move_forward(t_player *player, t_map *map);
void			move_backward(t_player *player, t_map *map);
void			move_left(t_player *player, t_map *map);
void			move_right(t_player *player, t_map *map);
void			rotate_left(t_player *player);
void			rotate_right(t_player *player);

/* ==== TEXTURES ==== */
int				load_textures(t_game *game);
int				get_tex_index(t_ray *ray);
double			get_wallx(t_player *player, t_ray *ray);
int				get_tex_x(t_ray *ray, double wallx, int tex_width);
int				get_tex_color(t_texture *texture, int tex_x, int tex_y);
void			render_floor_ceiling(t_game *game);

#endif

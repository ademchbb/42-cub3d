/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 16:22:24 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/03 15:19:25 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Lit le .cub puis remplit la config et la map (libere tout si erreur) */
static int	parse_map(t_game *game, char *file)
{
	char	**lines;
	int		start;

	lines = read_file_lines(file);
	if (!lines)
		return (-1);
	start = find_map_start(lines);
	if (parse_config(lines, start, &game->config) == -1)
		return (free_split(lines), free_all(game), -1);
	if (extract_map(lines, start, &game->map) == -1)
		return (free_split(lines), free_all(game), -1);
	free_split(lines);
	return (0);
}

/* Verifie la map : caracteres, joueur unique, murs fermes */
static int	check_map(t_game *game)
{
	if (valid_map_chars(&game->map) == -1)
		return (-1);
	if (extract_player(&game->map, &game->player) == -1)
		return (print_error("No player start position"));
	if (check_map_walls(&game->map) == -1)
		return (-1);
	return (0);
}

/* Valide la map puis place le joueur et regle son orientation */
static int	init_game(t_game *game)
{
	if (check_map(game) == -1)
		return (free_all(game), -1);
	init_player_pos(&game->player);
	init_player_dir(&game->player);
	return (0);
}

/* Ouvre la fenetre, charge les textures et branche les hooks MLX */
static int	init_mlx_hooks(t_game *game)
{
	init_mlx_co(game);
	init_img(game);
	if (load_textures(game) == -1)
		return (free_all(game), print_error("Cannot load a texture"));
	mlx_hook(game->mlx_window, 17, 0, (int (*)())close_window, game);
	mlx_hook(game->mlx_window, 2, (1L << 0) | (1L << 1),
		(int (*)())handle_keypress, game);
	mlx_hook(game->mlx_window, 3, (1L << 0) | (1L << 1),
		(int (*)())handle_keyrelease, game);
	/// TODO enlever si pas utilise mlx_hook(game->mlx_window, 10, 1L << 21, (int (*)())handle_focus_out, game);
	mlx_loop_hook(game->mlx_connexion, (int (*)())render_frames, game);
	return (0);
}

/* Verifie les arguments, parse le .cub puis lance la boucle du jeu */
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("Usage: ./cub3D <map.cub>"), 1);
	if (!has_extension(av[1], ".cub"))
		return (print_error("The map file must have a .cub extension"), 1);
	ft_bzero(&game, sizeof(t_game));
	if (parse_map(&game, av[1]) == -1)
		return (1);
	if (init_game(&game) == -1)
		return (1);
	if (init_mlx_hooks(&game) == -1)
		return (1);
	mlx_loop(game.mlx_connexion);
	return (0);
}

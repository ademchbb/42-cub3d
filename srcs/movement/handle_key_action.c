/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:56:43 by ragolden          #+#    #+#             */
/*   Updated: 2026/10/03 15:19:33 by adchebbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Touche enfoncee : ESC quitte, sinon active le booleen de la touche */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		clean_exit(game, EXIT_SUCCESS);
	else if (keycode == KEY_W)
		game->key_w = true;
	else if (keycode == KEY_A)
		game->key_a = true;
	else if (keycode == KEY_S)
		game->key_s = true;
	else if (keycode == KEY_D)
		game->key_d = true;
	else if (keycode == KEY_LEFT)
		game->key_left = true;
	else if (keycode == KEY_RIGHT)
		game->key_right = true;
	return (0);
}

/* Touche relachee : desactive le booleen de la touche */
int	handle_keyrelease(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->key_w = false;
	else if (keycode == KEY_A)
		game->key_a = false;
	else if (keycode == KEY_S)
		game->key_s = false;
	else if (keycode == KEY_D)
		game->key_d = false;
	else if (keycode == KEY_LEFT)
		game->key_left = false;
	else if (keycode == KEY_RIGHT)
		game->key_right = false;
	return (0);
}
/*TODO verifier si on garde (empecher le maintien de touche en cas de changement de page)
int	handle_focus_out(t_game *game)
{
	game->key_w = false;
	game->key_a = false;
	game->key_s = false;
	game->key_d = false;
	game->key_left = false;
	game->key_right = false;
	return (0);
}*/

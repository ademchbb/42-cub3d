# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adchebbi <adchebbi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/11 17:31:40 by ragolden          #+#    #+#              #
#    Updated: 2026/10/06 18:56:04 by adchebbi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ==== CONFIG ====
NAME		= cub3D
NAME_BONUS	= cub3D_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Wno-cast-function-type -g3

# ==== DIRS ====
SRCS_DIR	= srcs
INCS_DIR	= includes
LIBFT_DIR	= libft
MLX_DIR		= mlx
OBJS_DIR	= objs

# ==== FILES ====
SRCS_COMMON	= main.c \
			  init_mlx.c \
			  cleanup.c \
			  utils.c \
			  parsing/parsing.c \
			  parsing/parsing_utils.c \
			  parsing/parsing_config.c \
			  parsing/parsing_config_utils.c \
			  parsing/parsing_map.c \
			  parsing/validate_map.c \
			  parsing/validate_map_utils.c \
			  raycasting/raycast_init.c \
			  raycasting/raycast_init_utils.c \
			  raycasting/raycast_render.c \
			  movement/handle_key_action.c \
			  movement/movement.c \
			  movement/movement_utils.c \
			  movement/rotation.c \
			  handle_textures/render_textures_utils.c

SRCS		= $(SRCS_COMMON) \
			  render.c \
			  handle_textures/load_textures.c \
			  handle_textures/render_floor_ceiling.c

SRCS_BONUS	= $(SRCS_COMMON) \
			  render_bonus.c \
			  handle_textures/load_textures_bonus.c \
			  handle_textures/render_floor_ceiling_bonus.c \
			  handle_textures/minimap_bonus.c

OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))
OBJS_BONUS	= $(addprefix $(OBJS_DIR)/, $(SRCS_BONUS:.c=.o))

HEADERS		= $(INCS_DIR)/cub3d.h $(INCS_DIR)/cub3d_bonus.h

# ==== LIBS ====
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_LIB		= $(MLX_DIR)/libmlx.a

INCLUDES	= -I $(INCS_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR)

LIBS		= -L $(LIBFT_DIR) -lft \
			  -L $(MLX_DIR) -lmlx \
			  -lXext -lX11 -lm

# ==== RULES ====
all: $(NAME)

bonus: $(NAME_BONUS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	chmod +x $(MLX_DIR)/configure
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBS) -o $(NAME_BONUS)

clean:
	rm -rf $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all bonus clean fclean re

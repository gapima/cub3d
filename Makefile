# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glima <glima@student.42sp.org.br>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16                                  #+#    #+#              #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -Ilib/MLX42/include

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include
LIBFT_DIR = lib/libft
MLX_DIR = lib/MLX42
BUILD_DIR = $(MLX_DIR)/build

# Bibliotecas
MLX_LIB = $(BUILD_DIR)/libmlx42.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_FLAGS = -I$(MLX_DIR)/include -L$(BUILD_DIR) -lmlx42 -ldl -lm -lglfw -pthread

# Arquivos fonte
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

# Compilação dos objetos (forçando dependência da MLX antes)
%.o: %.c $(MLX_LIB)
	$(CC) $(CFLAGS) -c $< -o $@

# Regras principais
all: $(NAME)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR)/.git ]; then \
		rm -rf $(MLX_DIR); \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR); \
	fi
	cd $(MLX_DIR) && cmake -B build && cmake --build build

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -iquote $(INCLUDE_DIR) -I$(LIBFT_DIR) \
		-I$(MLX_DIR)/include $(OBJ) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)

# Limpeza
clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
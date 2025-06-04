NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -I./lib/MLX42/include

# Fontes do projeto
SRC = src/main.c \
      src/parser/parse_cub_file.c \
      src/parser/free_config.c

OBJ = $(SRC:.c=.o)

# Libft
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# MLX42
MLX_DIR = ./lib/MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX = $(MLX_BUILD)/libmlx42.a
MLX_FLAGS = -L$(MLX_BUILD) -lmlx42 -ldl -lglfw -pthread -lm

# Compilar tudo
all: $(NAME)

# Compilar libft
$(LIBFT):
	@echo "🔧 Compilando libft..."
	@make -C $(LIBFT_DIR) > /dev/null

# Compilar MLX42 de forma silenciosa
$(MLX):
	@echo "🔧 Compilando MLX42 (silencioso)..."
	@cmake -S $(MLX_DIR) -B $(MLX_BUILD) > /dev/null 2>&1
	@cmake --build $(MLX_BUILD) > /dev/null 2>&1

# ASCII animation
ascii:
	@clear
	@echo "      ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀🧠"
	@echo "     ⠀⠀⠀⠀⠀⠀⠀⠀🧱 Iniciando cub3D... ⌂⠀⠀"
	@i=0; while [ $$i -le 20 ]; do \
		printf "\r🛰️  Raycasting mapa [%-20s] %d%%" $$(printf '#%.0s' $$(seq 1 $$i)) $$(( $$i * 5 )); \
		sleep 0.05; \
		i=`expr $$i + 1`; \
	done; \
	echo "\n🚀 cub3D carregado!"

# Compilar binário com loading animado
$(NAME): ascii $(OBJ) $(LIBFT) $(MLX)
	@echo "🚀 Linkando $(NAME)..."
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(MLX_FLAGS)

# Compilar arquivos .c → .o com log amigável
%.o: %.c
	@echo "🛠️  Compilando $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Limpar objetos
clean:
	@echo "🧹 Limpando objetos..."
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@rm -rf $(MLX_BUILD)

# Limpar tudo
fclean: clean
	@echo "🧨 Limpando binário..."
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null

# Recompilar tudo
re: fclean all

.PHONY: all clean fclean re ascii

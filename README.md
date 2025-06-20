# Cub3D - Documentação para Avaliação 42

## ✨ Visão Geral

O projeto **cub3D** é uma recriação em 3D estilo Wolfenstein 3D utilizando a biblioteca **MLX42**. O objetivo é renderizar um mapa 2D em perspectiva 3D usando **raycasting**, permitindo que o jogador se mova por um labirinto com paredes texturizadas.

## 🌐 Estrutura do Projeto

```
cub3d/
├── include/         # Headers (cub3d.h)
├── lib/             # Libft + MLX42
├── maps/            # Mapas .cub
├── src/             # Código-fonte principal
├── textures/        # Texturas PNG
├── Makefile         # Compila o projeto
├── mlx_sup          # Arquivo Valgrind
```

## ⚖️ Compilando e Executando

```bash
make
./cub3D maps/test.cub
```

## ⚡ Fluxo Principal

1. **main()** chama `init_config()`
2. `parse_cub_file()` carrega o mapa, texturas e cores
3. `mlx_loop_hook()` chama `render_frame()` a cada frame
4. `render_frame()` faz raycasting linha a linha
5. `mlx_key_hook()` chama `handle_input()` para movimentação

## 🪨 Structs Importantes

### `t_config`

Armazena o estado global do jogo:

* Ponteiros MLX
* Texturas e caminhos
* Mapa 2D
* Cores do chão/teto
* Struct `t_player`

### `t_player`

* `pos_x`, `pos_y`: posição atual
* `dir_x`, `dir_y`: direção
* `plane_x`, `plane_y`: plano da câmera para FOV

### `t_ray`, `t_dda` e `t_slice_data`

* `t_ray` e `t_dda`: usados no algoritmo de raycasting para cálculos de colisão com paredes
* `t_slice_data`: novo struct usado para agrupar dados da parede na função `draw_wall_slice()`

```c
// exemplo da struct
typedef struct s_slice_data {
	int x;
	int draw_start;
	int draw_end;
	int line_height;
	double ray_dir_x;
	double ray_dir_y;
	double perp_wall_dist;
	int side;
} t_slice_data;
```

## 🔹 Módulos e Funções

### Parse

#### `parse_cub_file()`

Lê e interpreta o arquivo `.cub`. Carrega as texturas, cores e constrói o mapa. Valida a existência de uma posição inicial e que o mapa está fechado.

#### `parse_texture_or_color()`

Recebe uma linha e identifica se ela contém o caminho de uma textura ou valores RGB. Chama `parse_color()` quando necessário.

#### `validate_closed_map()`

Verifica se todos os espaços acessíveis estão cercados por paredes ou delimitadores válidos. Garante que não há "buracos" nas bordas.

#### `parse_color()`

Divide uma string do tipo "220,100,0" em componentes RGB inteiros. Valida o intervalo (0 a 255).

### Renderização

#### `render_frame()`

Função chamada a cada frame. Itera sobre cada coluna da tela e dispara um raio (raycast) para determinar qual parede está visível.

#### `draw_wall_slice()` + `draw_wall_line()`

Para seguir a norma de 25 linhas e máximo 4 parâmetros, a função foi dividida:

* `draw_wall_slice(cfg, slice)` calcula textura e posição base
* `draw_wall_line(cfg, tex, slice, tex_x)` faz o loop vertical da parede

```c
void draw_wall_slice(t_config *cfg, t_slice_data slice);
void draw_wall_line(t_config *cfg, mlx_texture_t *tex, t_slice_data slice, int tex_x);
```

#### `draw_ceiling_and_floor()`

Preenche a parte superior da tela com a cor do teto e a inferior com a cor do chão.

### Movimento

#### `handle_input()`

Processa as teclas pressionadas (W, A, S, D, ESC). Atualiza a posição do jogador ou fecha o jogo.

#### `move_forward()`

Movimenta o jogador para frente, com colisão simples (não atravessa paredes).

### Utilitárias

#### `get_texture_pixel()`

Recebe uma textura e coordenadas (x, y), retorna o pixel correspondente.

#### `free_config()`

Libera todos os ponteiros e memória alocada dinamicamente ao final do programa.

#### `free_split()`

Libera um array de strings (usado após `ft_split`).

## 🚬 Perguntas Frequentes da Banca

* **Como o raycasting funciona?**

  * É traçada uma "linha" (raio) para cada coluna da tela. O ponto de interseção com a parede define o que desenhar.

* **Como você garante que o mapa é fechado?**

  * Usamos `validate_closed_map()` que verifica se ao redor de cada espaço jogável não há vazamentos (espaço em branco ou fora dos limites).

* **Como é calculada a altura da parede?**

  * Com `perpWallDist` (distância perpendicular) e a altura da tela.

* **Por que a MLX42 imprime erro de PNG?**

  * A `mlx_load_png()` usa LodePNG que printa no `stderr` ao falhar. Isso é esperado e explicado no README.

* **Qual a diferença entre `dir` e `plane` no player?**

  * `dir` define a direção da visão. `plane` define o campo de visão lateral, perpendicular à direção.

## 📅 Regras da 42 Seguidas
* Sem `for`, apenas `while`
* Funções com até 25 linhas
* Uso de `libft` e `MLX42`

---

# Variables
SRCS        =   mandatory/utils/utils_print.c  \
				mandatory/utils/utils_array.c \
				mandatory/utils/utils_atod.c \
				mandatory/utils/utils_close.c  \
				mandatory/utils/utils_color.c \
				mandatory/utils/utils_double.c \
				mandatory/utils/utils_int.c \
				mandatory/utils/utils_free.c \
				mandatory/parsing/parsing_.c \
				mandatory/parsing/parsing_utils1.c \
				mandatory/parsing/parsing_utils2.c \
				mandatory/parsing/store_.c \
				mandatory/parsing/store_cylinder.c \
				mandatory/parsing/store_plane.c \
				mandatory/parsing/store_sphere.c \
				mandatory/parsing/store_scene.c \
				mandatory/parsing/store_utils1.c \
				mandatory/parsing/store_utils2.c \
				mandatory/vector/utils_vector.c \
				mandatory/vector/utils_vector2.c \
				mandatory/vector/utils_vector3.c \
				mandatory/intersection/intersect_.c \
				mandatory/intersection/intersect_cylinder.c \
				mandatory/intersection/intersect_plan.c \
				mandatory/intersection/intersect_sphere.c \
				mandatory/render/color.c \
				mandatory/render/phong.c \
				mandatory/render/rays.c \
				mandatory/render/render.c \
				mandatory/render/viewport.c \
				dclst/dclst1.c \
				dclst/dclst2.c \
				dclst/dclst3.c \
				test/print_parsing.c \
				mandatory/main.c 
				
OBJ_DIR     =   obj
OBJS        =   $(SRCS:mandatory/%.c=$(OBJ_DIR)/%.o)

HEADERS     =   includes/miniRT.h     

NAME        =   miniRT
NAME_BONUS  =   miniRT_bonus

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -I./libft/srcs -Iincludes
# FLAGS       =   -lm -L./minilibx-linux -lmlx -L./libft -lft -lXext -lX11
# flags for linux:
# FLAGS		=	-L./minilibx-linux -L/opt/X11/lib -lmlx -lXext -lX11 -lm
# flags for macos:
FLAGS		=	-L./minilibx-linux -lmlx -L/opt/X11/lib -lXext -lX11 -lm -L./libft -lft

# Commandes colorées et décoratives
GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY      =   👍
SMILEY2	    =   😎

# Règle pour générer chaque fichier .o dans obj/
$(OBJ_DIR)/%.o: mandatory/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Cible principale
all: libft mlx $(NAME)

$(NAME): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) $(FLAGS)
	@echo "$(GREEN)Executable $(NAME) created! $(SMILEY2)$(RESET)"
	@echo "$(GREEN)Usage: ./miniRT [scenes.rt]$(RESET)"

# Cible bonus
bonus: libft mlx $(NAME_BONUS)

$(NAME_BONUS): $(OBJS) $(HEADERS)
	@echo "$(CYAN)Linking bonus...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME_BONUS) $(FLAGS)
	@echo "$(GREEN)Executable $(NAME_BONUS) created! $(SMILEY2)$(RESET)"
	@echo "$(GREEN)Usage: ./miniRT_bonus [scene.rt]$(RESET)"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)
	@make -s clean -C libft
	@make -s clean -C minilibx-linux >/dev/null 2>&1
	@echo "$(CYAN)Object files cleaned!$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -s fclean -C libft
	@echo "$(CYAN)Executable $(NAME) or $(NAME_BONUS) removed!$(RESET)"

# Recompiler à partir de zéro
re: fclean all

# Génération de la bibliothèque libft avec sortie masquée
libft:
	@make -s -C libft

# Génération de la bibliothèque minilibx avec sortie masquée
mlx:
	@make -s -C minilibx-linux all >/dev/null 2>&1

# Éviter les conflits avec des fichiers portant les noms des cibles
.PHONY: all clean fclean re libft mlx bonus

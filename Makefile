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
				mandatory/test/print_parsing.c \
				mandatory/main.c

SRCS_BONUS  =   bonus/utils/utils_print.c  \
				bonus/utils/utils_array.c \
				bonus/utils/utils_atod.c \
				bonus/utils/utils_close.c  \
				bonus/utils/utils_color.c \
				bonus/utils/utils_double.c \
				bonus/utils/utils_int.c \
				bonus/utils/utils_free.c \
				bonus/parsing/parsing_.c \
				bonus/parsing/parsing_utils1.c \
				bonus/parsing/parsing_utils2.c \
				bonus/parsing/store_.c \
				bonus/parsing/store_cylinder.c \
				bonus/parsing/store_plane.c \
				bonus/parsing/store_sphere.c \
				bonus/parsing/store_triangle.c \
				bonus/parsing/store_scene.c \
				bonus/parsing/store_utils1.c \
				bonus/parsing/store_utils2.c \
				bonus/vector/utils_vector.c \
				bonus/vector/utils_vector2.c \
				bonus/vector/utils_vector3.c \
				bonus/vector/utils_vector4.c \
				bonus/intersection/intersect_.c \
				bonus/intersection/intersect_cone.c \
				bonus/intersection/intersect_cylinder.c \
				bonus/intersection/intersect_plan.c \
				bonus/intersection/intersect_sphere.c \
				bonus/intersection/intersect_triangle.c \
				bonus/render/color.c \
				bonus/render/phong.c \
				bonus/render/rays.c \
				bonus/render/render.c \
				bonus/render/viewport.c \
				dclst/dclst1.c \
				dclst/dclst2.c \
				dclst/dclst3.c \
				bonus/test/print_parsing.c \
				bonus/main.c 

OBJ_DIR      =   obj
OBJ_BONUS_DIR = obj_bonus

OBJS        =   $(SRCS:mandatory/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS  =   $(SRCS_BONUS:bonus/%.c=$(OBJ_BONUS_DIR)/%.o)

HEADERS     =   includes/miniRT.h     

NAME        =   miniRT
NAME_BONUS  =   miniRT_bonus

CC          =   cc
CFLAGS      =   -Wall -Wextra -Werror -g -I./libft/srcs -Iincludes

FLAGS		=	-L./minilibx-linux -lmlx -L/opt/X11/lib -lXext -lX11 -lm -L./libft -lft

# Commandes colorées et décoratives
GREEN       =   \033[1;35m
CYAN        =   \033[1;34m
RESET       =   \033[0m
SMILEY2	    =   😎

# Règle pour générer chaque fichier .o dans obj/
$(OBJ_DIR)/%.o: mandatory/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: bonus/%.c $(HEADERS)
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

$(NAME_BONUS): $(OBJS_BONUS) $(HEADERS)
	@echo "$(CYAN)Linking bonus...$(RESET)"
	@$(CC) $(OBJS_BONUS) -o $(NAME_BONUS) $(FLAGS)
	@echo "$(GREEN)Executable $(NAME_BONUS) created! $(SMILEY2)$(RESET)"
	@echo "$(GREEN)Usage: ./miniRT_bonus [scene.rt]$(RESET)"

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@make -s clean -C libft
	@make -s clean -C minilibx-linux >/dev/null 2>&1
	@echo "$(CYAN)Object files cleaned!$(RESET)"

# Nettoyage complet
fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)
	@make -s fclean -C libft
	@echo "$(CYAN)Executables removed!$(RESET)"

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

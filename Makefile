# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/17 01:23:03 by imurugar          #+#    #+#              #
#    Updated: 2023/08/19 22:14:59 by imurugar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~~ FOLDERS DIR ~~~~~~~ */
SRCS_DIR	= ./src/
OBJ_DIR		= ./obj/
INC_DIR		= ./inc/
BONUS_DIR	= bonus/

# /* ~~~~~~~ MAIN DIRS ~~~~~~~ */
DRAW_SRC	= draw/
IMGAGES_SRC	= img/
ERROR_SRC	= error/
PARSER_SRC	= parser/
MENU_SRC	= menu/
MINIMAP_SRC	= minimap/

# /* ~~~~~~~ HEADER FILES ~~~~~~~ */
INC 			=   cub3d.h

# /* ~~~~~~~ SOURCE FILES ~~~~~~~ */
SRCS		=	main.c \
				input.c \
				utils.c \
				${DRAW_SRC}draw_floor_celi.c \
				${DRAW_SRC}draw_wall.c \
				${DRAW_SRC}draw_minimap.c \
				${IMGAGES_SRC}init_images.c \
				${ERROR_SRC}error.c \
				${PARSER_SRC}parse_map.c \
				${PARSER_SRC}color_validating.c \
				${PARSER_SRC}input_check.c \
				${PARSER_SRC}map_validating.c \
				${PARSER_SRC}map_validating_helper.c \
				${PARSER_SRC}object_validating.c \
				${PARSER_SRC}save_data.c \
				${PARSER_SRC}validating_utils.c \
				${PARSER_SRC}check_closed_map.c \

# /* ~~~~~~~ INCLUDE CONFIG ~~~~~~~ */
OBJ_FILES   = $(SRCS:.c=.o)
SRC			= $(addprefix $(SRCS_DIR), $(SRCS))
OBJS		= $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INCLUDES	= $(addprefix $(INC_DIR), $(INC))
OBJ_DIRS	:= $(sort $(dir $(OBJS)))

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = libft
LIBFT_MAKE = Makefile
LIBFT_PATH = ${LIBFT_DIR}/libft.a

# /* ~~~~~~~ INCLUDING MINILIBX ~~~~~~~ */
MLX_DIR = ./minilibx
MLX_MAKE = Makefile
MLX_PATH = ${MLX_DIR}/libmlx.a

# /* ~~~~~~~ TESTING FLAGS ~~~~~~~ */
SANITIZE =
#SANITIZE = -fsanitize=address

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
GCC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 $(SANITIZE)
MFLAGS = -L ${MLX_DIR} -lmlx -lXext -lX11 -lm -lbsd
#MFLAGS = -ldl -lmlx -L${MLX_DIR} -framework OpenGL -framework AppKit -lz
LFLAGS:= -L $(LIBFT_DIR) -lft

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = cub3D
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"

# /* ~~~~~~~ GENERATE DIRS ~~~~~~~ */
$(OBJ_DIR)%.o: $(SRCS_DIR)%.c $(INCLUDES)
	@mkdir -p $(@D)
	$(GCC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -c $< -o $@
	
all:	${NAME}

obj:
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	@echo $(CYAN) " - Compiling minilibx" $(RED)
	@make -C ${MLX_DIR}
	@echo $(CYAN) " - Compiling libft" $(RED)
	@cd $(LIBFT_DIR) && $(MAKE)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(GCC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) $(MFLAGS) 
	@echo $(GREEN) "[FINISHED OK]" $(EOC)
	
clean:
	@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
	@${RM} ${OBJS}
	@${RM} -r ${OBJ_DIR}
	@make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} fclean
	@make -C ${MLX_DIR} -f ${MLX_MAKE} clean

fclean: clean
	@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
	@${RM} ${OBJS} ${NAME}

re: 	fclean all

.PHONY: all clean fclean re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/05 17:40:51 by mfinette          #+#    #+#              #
#    Updated: 2022/12/13 20:53:35 by mfinette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
SRC =	main.c				\
		pixel_parsing.c		\
		check_parameters.c 	\
		iterations.c		\
		hook_actions.c

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -O3
LINKS = -framework OpenGL -framework AppKit

NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'

all: $(NAME)

$(NAME): $(OBJ) ./mlx
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@make -C ./mlx
	@cc $(FLAGS) $(OBJ) $(LINKS) mlx/libmlx.a -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)
	@echo $(CURSIVE)$(GRAY) "     Deleted object files" $(NONE)

$(OBJ): $(SRC)
	@echo $(CURSIVE)$(GRAY) "     - Making object files..." $(NONE)
	@cc $(FLAGS) -c $(SRC) -Imlx

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@rm -rf $(OBJ)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

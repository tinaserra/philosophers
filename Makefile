# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tinaserra <tinaserra@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 12:04:40 by vserra            #+#    #+#              #
#    Updated: 2021/12/16 23:20:22 by tinaserra        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
		init_struct.c \
		init_utils.c \
		do_it.c \
		print.c \
		threads.c \
		utils.c

NAME = philo

# override -> permet de reecrire la suite de la variable
override CFLAGS += -Wall -Wextra -Werror -MMD -O3 -fsanitize=address
LPTHREAD = -lpthread

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
DPD = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.d))

# -j = jobs : multithreader / separe les taches de compliation
opti:
	@make -j all

all:
	@$(MAKE) $(NAME)

# permet de pouvoir comparer la derniere modification de la dependance 
# par rapport a la regle
$(NAME): $(OBJ)
		@cc $(CFLAGS) -o $(NAME) $(OBJ) $(LPTHREAD)
		@echo $(NAME) : Created !

# si le .c est plus recent que le .o on rentre dans la regle
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | .gitignore
		@mkdir -p $(OBJ_DIR)
		@cc $(CFLAGS) -I $(INC_DIR) -c $< -o $@

.gitignore:
		@echo $(NAME) > .gitignore

debug : fclean
	make all CFLAGS:="-DDEBUG -g"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "obj deleted"

fclean:	clean
	@rm -rf $(NAME)
	@echo "[$(NAME)]: deleted"

re: fclean all

.PHONY: all, clean, fclean, re

# utilise les .d (et ignore s'ils n'existe pas)
-include $(DPD)

# le secret c'est de commenter son Makefile <3
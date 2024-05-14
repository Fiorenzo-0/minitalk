# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbruschi <lbruschi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 18:29:05 by lbruschi          #+#    #+#              #
#    Updated: 2024/05/14 15:35:21 by lbruschi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

NAME_SERVER_BONUS = server_bonus
NAME_CLIENT_BONUS = client_bonus

SRC_SERVER = server.c
SRC_CLIENT = client.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

SRC_SERVER_BONUS = server_bonus.c
SRC_CLIENT_BONUS = client_bonus.c
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

LIBFT_DIR = ./git_libft
LIBFT = $(LIBFT_DIR)/libft.a
CC = cc -Wextra -Werror -Werror -g

all: $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
		@make all -C $(LIBFT_DIR)
		@$(CC) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)
		@echo "\nServer compiled {d'altronde}\n"

$(NAME_CLIENT): $(OBJ_CLIENT)
		@make all -C $(LIBFT_DIR)
		@$(CC) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
		@echo "\nClient compiled {d'altronde}\n"

bonus: $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)

$(NAME_SERVER_BONUS): $(OBJ_SERVER_BONUS)
		@make all -C $(LIBFT_DIR)
		@$(CC) $(OBJ_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER_BONUS)
		@echo "\nServer bonus compiled {pefforza}\n"

$(NAME_CLIENT_BONUS): $(OBJ_CLIENT_BONUS)
		@make all -C $(LIBFT_DIR)
		@$(CC) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT_BONUS)
		@echo "\nClient bonus compiled {pefforza}\n"


%.o: %.c
		$(CC) -c $< -o $@

clean:
		make clean -C $(LIBFT_DIR)
		rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)
		@echo "\nwe are frogs\n"

fclean: clean
		make fclean -C $(LIBFT_DIR)
		rm -f $(NAME_SERVER) $(NAME_CLIENT) $(NAME_SERVER_BONUS) $(NAME_CLIENT_BONUS)
		@echo "\neh ma lo fanno\n"

re: fclean all

.PHONY: all bonus clean fclean re
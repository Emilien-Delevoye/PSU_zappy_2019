##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME_SERVER	=	zappy_server

SRC_SERVER	=	src/main.c	\
			src/utils/parameters/get_parameters.c	\
			src/utils/parameters/c_flag.c	\
			src/utils/parameters/f_flag.c	\
			src/utils/parameters/n_flag.c	\
			src/utils/parameters/p_flag.c	\
			src/utils/parameters/x_flag.c	\
			src/utils/parameters/y_flag.c	\
			src/setup_map/setup_map.c	\
			src/sockets/setup_socket.c	\
			src/utils/server/close_server.c	\
			src/sockets/run_server.c	\
			src/sockets/select/select.c	\
			src/sockets/accept_connections.c	\
			src/sockets/read_socket.c	\
			src/sockets/close_clients/utils_close_client.c	\
			src/sockets/close_clients/close_client.c	\
			src/setup_map/create_map.c	\
			src/sockets/gnl.c	\
			src/utils/time/time.c	\
			src/utils/write_list/write_list.c	\
			src/sockets/write_socket.c	\
			src/setup_map/free_map.c	\
			src/commands/every_commands.c	\
			src/commands/msz_command.c

OBJ_SERVER	=	$(SRC_SERVER:.c=.o)

CFLAGS = -W -Wall -Wextra -pedantic -ansi -std=gnu11 -I include

all:	$(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER)
	gcc -o $(NAME_SERVER) $(OBJ_SERVER)

debug:	CFLAGS += -g
debug:	all

debugre:	CFLAGS += -g
debugre:	re

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY	=	all $(NAME_SERVER) debug debugre clean fclean re

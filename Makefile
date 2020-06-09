##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME_SERVER	=	zappy_server

SRC_MAIN_SERVER	=	server/src/main.c

SRC_SERVER	=	server/src/utils/parameters/get_parameters.c	\
			server/src/utils/parameters/c_flag.c	\
			server/src/utils/parameters/f_flag.c	\
			server/src/utils/parameters/n_flag.c	\
			server/src/utils/parameters/p_flag.c	\
			server/src/utils/parameters/x_flag.c	\
			server/src/utils/parameters/y_flag.c	\
			server/src/setup_map/setup_map.c	\
			server/src/sockets/setup_socket.c	\
			server/src/utils/server/close_server.c	\
			server/src/sockets/run_server.c	\
			server/src/sockets/select/select.c	\
			server/src/sockets/accept_connections.c	\
			server/src/sockets/read_socket.c	\
			server/src/sockets/close_clients/utils_close_client.c	\
			server/src/sockets/close_clients/utils_close_cli_co.c	\
			server/src/sockets/close_clients/close_client.c	\
			server/src/setup_map/create_map.c	\
			server/src/utils/time/time.c	\
			server/src/utils/write_list/write_list.c	\
			server/src/sockets/write_socket.c	\
			server/src/setup_map/free_map.c	\
			server/src/commands/every_commands.c	\
			server/src/commands/msz_command.c	\
			server/src/utils/extract_command.c	\
			server/src/sockets/valid_client.c	\
			server/src/commands/remove_first_cmd_queue.c

SRC_TEST	=	tests/src/main.cpp	\
			tests/src/get_parameters.cpp	\
			tests/src/setup_map.cpp

OBJ	=	$(SRC_SERVER:.c=.o)

OBJ_SRC_MAIN	=	$(SRC_MAIN_SERVER:.c=.o)

OBJ_SRC_TEST	=	$(SRC_TEST:.cpp=.o)

CFLAGS	=	-W -Wall -Wextra -I server/include
CPPFLAGS	=	-W -Wall -Wextra -I server/include -I tests/include

all:	$(NAME_SERVER)

debug:	CFLAGS += -g
debug:	all

debugre:	CFLAGS += -g
debugre:	re

$(NAME_SERVER):	$(OBJ) $(OBJ_SRC_MAIN)
	gcc -o $(NAME_SERVER) $(OBJ) $(OBJ_SRC_MAIN) -I server/include

clean:
	rm -f $(OBJ_SRC_TEST) $(OBJ_SRC_MAIN) $(OBJ)
	find . -name "*.gcda" -exec /bin/rm '{}' \;
	find . -name "*.gcno" -exec /bin/rm '{}' \;

fclean:	clean
	rm -f $(NAME_SERVER)

tests_run: CFLAGS += --coverage
tests_run: clean $(OBJ) $(OBJ_SRC_TEST)
	g++ $(OBJ) $(OBJ_SRC_TEST) -o tests_run -lgtest -lgtest_main -lpthread --coverage -I tests/include -I server/include
	./tests_run
	rm tests_run

re:	fclean all

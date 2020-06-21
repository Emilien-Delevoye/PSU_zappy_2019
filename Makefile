##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME_SERVER	=	zappy_server

NAME_AI		=	zappy_ai

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
			server/src/utils/write_list/write_list.c	\
			server/src/sockets/write_socket.c	\
			server/src/setup_map/free_map.c	\
			server/src/commands/every_commands.c	\
			server/src/commands/msz_command.c	\
			server/src/utils/extract_command.c	\
			server/src/sockets/valid_client.c	\
			server/src/commands/remove_first_cmd_queue.c	\
			server/src/setup_map/generate_map.c	\
			server/src/utils/my_str_to_word_array.c	\
			server/src/commands/bct_command.c	\
			server/src/utils/list_actions/new_client_to_wait_list.c	\
			server/src/ai_interaction/ai_interaction_main.c	\
			server/src/ai_interaction/ai_commands_main.c	\
			server/src/utils/list_actions/move_waiting_to_working_list.c	\
			server/src/commands/pnw_command.c	\
			server/src/commands/ppo_command.c	\
			server/src/commands/tna_command.c	\
			server/src/sockets/generate_new_drone.c	\
			server/src/sockets/close_clients/close_in_cli_ww_list.c	\
			server/src/ai_interaction/work_actions.c	\
			server/src/ai_interaction/movement.c	\
			server/src/setup_map/spawn_player.c	\
			server/src/ai_interaction/forward.c	\
			server/src/ai_interaction/broadcast.c	\
			server/src/ai_interaction/search_left_broadcast.c	\
			server/src/ai_interaction/search_right_broadcast.c	\
			server/src/ai_interaction/look.c	\
			server/src/ai_interaction/inventory.c	\
			server/src/ai_interaction/connect_nbr.c	\
			server/src/ai_interaction/eject.c	\
			server/src/ai_interaction/fork.c	\
			server/src/ai_interaction/take.c	\
			server/src/ai_interaction/set.c		\
			server/src/ai_interaction/incantation.c	\
			server/src/commands/seg_command.c	\
			server/src/commands/pic_command.c	\
			server/src/commands/pie_command.c	\
			server/src/commands/pdi_command.c	\
			server/src/commands/pbc_command.c	\
			server/src/commands/sgt_command.c	\
			server/src/commands/plv_command.c	\
			server/src/commands/pin_command.c	\
			server/src/sockets/end_valid_client.c	\
			server/src/utils/egg/create_egg.c

SRC_TEST	=	tests/src/bct_command.cpp	\
                        tests/src/close_server.cpp	\
                        tests/src/get_parameters.cpp	\
                        tests/src/main.cpp	\
                        tests/src/msz_command.cpp	\
                        tests/src/read_socket.cpp	\
                        tests/src/setup_map.cpp	\
                        tests/src/setup_socket.cpp	\
                        tests/src/str_to_word_array.cpp	\
                        tests/src/valid_client.cpp	\
                        tests/src/write_list.cpp	\
                        tests/src/write_socket.cpp	\
			tests/src/close_clients.cpp	\
			tests/src/new_client_to_ww_list.cpp

OBJ	=	$(SRC_SERVER:.c=.o)

OBJ_SRC_MAIN	=	$(SRC_MAIN_SERVER:.c=.o)

OBJ_SRC_TEST	=	$(SRC_TEST:.cpp=.o)

CFLAGS	=	-W -Wall -Wextra -I server/include -O3 -std=gnu11
CPPFLAGS	=	-W -Wall -Wextra -I server/include -I tests/include

all:	$(NAME_SERVER) $(NAME_AI)

debug:	CFLAGS += -g
debug:	all

debugre:	CFLAGS += -g
debugre:	re

$(NAME_AI):
	cp ai/main.py $(NAME_AI)

$(NAME_SERVER):	$(OBJ) $(OBJ_SRC_MAIN)
	gcc -o $(NAME_SERVER) $(OBJ) $(OBJ_SRC_MAIN) -I server/include -O3

clean:
	rm -f $(OBJ_SRC_TEST) $(OBJ_SRC_MAIN) $(OBJ)
	find . -name "*.gcda" -exec /bin/rm '{}' \;
	find . -name "*.gcno" -exec /bin/rm '{}' \;

fclean:	clean
	rm -f $(NAME_SERVER) $(NAME_AI)

tests_run: CFLAGS += --coverage
tests_run: clean $(OBJ) $(OBJ_SRC_TEST)
	g++ $(OBJ) $(OBJ_SRC_TEST) -o tests_run -lgtest -lgtest_main -lpthread --coverage -I tests/include -I server/include
	./tests_run
	rm tests_run

tests_build: CFLAGS += --coverage
tests_build: clean $(OBJ) $(OBJ_SRC_TEST)
	g++ $(OBJ) $(OBJ_SRC_TEST) -o tests_run -lgtest -lgtest_main -lpthread --coverage -I tests/include -I server/include

re:	fclean all

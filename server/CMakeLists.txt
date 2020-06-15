cmake_minimum_required(VERSION 3.15)

project(zappy_server)

include_directories(include/)

add_executable(zappy_server
        src/main.c
        src/utils/parameters/get_parameters.c
        src/utils/parameters/c_flag.c
        src/utils/parameters/f_flag.c
        src/utils/parameters/n_flag.c
        src/utils/parameters/p_flag.c
        src/utils/parameters/x_flag.c
        src/utils/parameters/y_flag.c
        src/setup_map/setup_map.c
        src/sockets/setup_socket.c
        src/utils/server/close_server.c
        include/server.h
        include/utils/parameters.h
        include/map/setup_map.h
        include/sockets/control_socket.h
        include/utils/close_server.h
        src/sockets/run_server.c
        include/sockets/run_server.h
        src/sockets/select/select.c
        src/sockets/accept_connections.c
        include/sockets/accept_connections.h
        src/sockets/read_socket.c
        src/sockets/close_clients/close_client.c
        src/sockets/close_clients/utils_close_client.c
        src/setup_map/create_map.c
        include/utils/write_list.h
        src/utils/write_list/write_list.c
        src/sockets/write_socket.c
        src/setup_map/free_map.c
        src/commands/every_commands.c
        src/commands/msz_command.c
        include/commands/commands.h
        src/utils/extract_command.c
        src/sockets/valid_client.c
        src/sockets/close_clients/utils_close_cli_co.c
        src/commands/remove_first_cmd_queue.c
        src/utils/my_str_to_word_array.c
        src/commands/bct_command.c
        src/setup_map/generate_map.c
        src/utils/list_actions/new_client_to_wait_list.c
        src/ai_interaction/ai_interaction_main.c
        src/ai_interaction/ai_commands_main.c
        src/utils/list_actions/move_waiting_to_working_list.c
        src/commands/pnw_command.c src/sockets/generate_new_drone.c
        src/sockets/close_clients/close_in_cli_ww_list.c src/ai_interaction/work_actions.c src/ai_interaction/movement.c src/commands/ppo_command.c src/commands/tna_command.c)

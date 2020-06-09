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
        src/utils/time/time.c
        src/sockets/run_server.c
        include/sockets/run_server.h
        src/sockets/select/select.c
        include/sockets/select.h
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
        src/utils/extract_command.c src/sockets/valid_client.c src/sockets/close_clients/utils_close_cli_co.c)

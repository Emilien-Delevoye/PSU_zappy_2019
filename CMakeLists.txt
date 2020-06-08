cmake_minimum_required(VERSION 3.16)
project(PSU_zappy_2019)

set(CMAKE_CXX_STANDARD 14)

include_directories(server/include)
include_directories(server/include/commands)
include_directories(server/include/map)
include_directories(server/include/sockets)
include_directories(server/include/utils)
include_directories(tests/include)

add_executable(PSU_zappy_2019
        server/include/commands/commands.h
        server/include/map/setup_map.h
        server/include/sockets/accept_connections.h
        server/include/sockets/control_socket.h
        server/include/sockets/run_server.h
        server/include/sockets/select.h
        server/include/utils/close_server.h
        server/include/utils/parameters.h
        server/include/utils/timer.h
        server/include/utils/write_list.h
        server/include/server.h
        server/src/commands/every_commands.c
        server/src/commands/msz_command.c
        server/src/setup_map/create_map.c
        server/src/setup_map/free_map.c
        server/src/setup_map/setup_map.c
        server/src/sockets/close_clients/close_client.c
        server/src/sockets/close_clients/utils_close_client.c
        server/src/sockets/select/select.c
        server/src/sockets/accept_connections.c
        server/src/sockets/read_socket.c
        server/src/sockets/run_server.c
        server/src/sockets/setup_socket.c
        server/src/sockets/write_socket.c
        server/src/utils/parameters/c_flag.c
        server/src/utils/parameters/f_flag.c
        server/src/utils/parameters/get_parameters.c
        server/src/utils/parameters/n_flag.c
        server/src/utils/parameters/p_flag.c
        server/src/utils/parameters/x_flag.c
        server/src/utils/parameters/y_flag.c
        server/src/utils/server/close_server.c
        server/src/utils/time/time.c
        server/src/utils/write_list/write_list.c
        server/src/utils/extract_command.c
        server/src/main.c
        tests/include/tests.h
        tests/src/get_parameters.cpp
        tests/src/main.cpp
        tests/src/setup_map.cpp server/src/setup_map/generate_map.c)

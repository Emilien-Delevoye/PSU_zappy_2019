cmake_minimum_required(VERSION 3.15)

project(server_tests)

include_directories(include/)
include_directories(../server/include)

SET(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unused --coverage")

add_executable(server_tests
        ../server/src/utils/parameters/get_parameters.c
        ../server/src/utils/parameters/c_flag.c
        ../server/src/utils/parameters/f_flag.c
        ../server/src/utils/parameters/n_flag.c
        ../server/src/utils/parameters/p_flag.c
        ../server/src/utils/parameters/x_flag.c
        ../server/src/utils/parameters/y_flag.c
        ../server/src/setup_map/setup_map.c
        ../server/src/sockets/setup_socket.c
        ../server/src/utils/server/close_server.c
        ../server/include/server.h
        ../server/include/utils/parameters.h
        ../server/include/map/setup_map.h
        ../server/include/sockets/control_socket.h
        ../server/include/utils/close_server.h
        ../server/src/utils/time/time.c
        ../server/src/sockets/run_server.c
        ../server/include/sockets/run_server.h
        ../server/src/sockets/select/select.c
        ../server/include/sockets/select.h
        ../server/src/sockets/accept_connections.c
        ../server/include/sockets/accept_connections.h
        ../server/src/sockets/read_socket.c
        ../server/src/sockets/close_clients/close_client.c
        ../server/src/sockets/close_clients/utils_close_client.c
        ../server/src/setup_map/create_map.c
        ../server/include/utils/write_list.h
        ../server/src/utils/write_list/write_list.c
        ../server/src/sockets/write_socket.c
        ../server/src/setup_map/free_map.c
        ../server/src/utils/extract_command.c
        ../server/src/utils/my_str_to_word_array.c
        ../server/src/setup_map/generate_map.c
        ../server/src/commands/bct_command.c
        ../server/src/setup_map/generate_map.c
        ../server/src/commands/every_commands.c
        ../server/src/commands/msz_command.c
        ../server/include/commands/commands.h
        ../server/src/sockets/valid_client.c
        ../server/src/sockets/close_clients/utils_close_cli_co.c
        ../server/src/utils/list_actions/new_client_to_wait_list.c
        src/main.cpp src/get_parameters.cpp include/tests.h
        src/setup_map.cpp
        src/bct_command.cpp src/msz_command.cpp src/str_to_word_array.cpp
        ../server/src/commands/remove_first_cmd_queue.c
        src/valid_client.cpp
        src/write_list.cpp
        src/write_socket.cpp
        src/setup_socket.cpp
        src/read_socket.cpp
        src/time.cpp
        src/close_server.cpp
        src/close_clients.cpp src/new_client_to_ww_list.cpp)

target_link_libraries(server_tests gtest gtest_main pthread gcov)

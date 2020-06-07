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
        src/main.cpp src/get_parameters.cpp include/tests.h src/setup_map.cpp)

target_link_libraries(server_tests gtest gtest_main pthread gcov)

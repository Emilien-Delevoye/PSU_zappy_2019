/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#ifndef ZAPPY_TESTS_H
#define ZAPPY_TESTS_H

extern "C" {
    #include "server.h"
    #include "utils/write_list.h"

    data_server_t get_parameters(int ac, char **av);
    int setup_map(data_server_t *data);
    void free_map(data_server_t data);
    void add_client_to_list(data_server_t *data, int new_fd);
    void valid_client(data_server_t *data, client_t *cli);
}

#endif //ZAPPY_TESTS_H

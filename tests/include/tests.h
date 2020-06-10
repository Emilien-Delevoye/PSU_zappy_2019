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
    void bct_command(client_t *cli, data_server_t *data, char **arg);
    void msz_command(client_t *cli, data_server_t *data, char **arg);
    char **my_str_to_word_array(char *str);
    void write_socket(data_server_t *data);
    void client_validation(data_server_t *data, client_t *cli, int team_id);
    void setup_fdset(data_server_t *data);
    bool select_fd(data_server_t *data);
    int setup_socket(data_server_t *data);
    void read_socket(data_server_t *data);
    void timer(data_server_t *data);
    void setup_timer(data_server_t *data);
    void close_server(data_server_t data);
}

#endif //ZAPPY_TESTS_H

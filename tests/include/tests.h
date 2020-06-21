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
    #include "commands/commands.h"

    data_server_t get_parameters(int ac, char **av);
    int setup_map(data_server_t *data);
    void free_map(data_server_t data);
    void add_client_to_list(data_server_t *data, int new_fd);
    void bct_command(client_t *cli, data_server_t *data, char **arg);
    void msz_command(client_t *cli, data_server_t *data, char **arg);
    char **my_str_to_word_array(char *str);
    void client_validation(data_server_t *data, client_t *cli, int team_id);
    int setup_socket(data_server_t *data);
    void close_server(data_server_t data);
    void graphical_validation(data_server_t *data, client_t *cli);
    data_server_t *create_data_server();
}

#endif //ZAPPY_TESTS_H

/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** header for each command's function
*/

#ifndef PSU_ZAPPY_2019_COMMANDS_H
#define PSU_ZAPPY_2019_COMMANDS_H

#include "server.h"

void msz_command(client_t *cli, data_server_t *data, __attribute__((unused))char **arg);
void bct_command(client_t *client, data_server_t *data, char **arg);
void loop_tmp_check_every_buffer(data_server_t *data);

#endif //PSU_ZAPPY_2019_COMMANDS_H

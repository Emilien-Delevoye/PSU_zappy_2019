/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** header for each command's function
*/

#ifndef PSU_ZAPPY_2019_COMMANDS_H
#define PSU_ZAPPY_2019_COMMANDS_H

#include "server.h"

void msz_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg);
void bct_command(client_t *cli, data_server_t *data, char **arg);
void tna_command(client_t *cli, data_server_t *data, char **arg);
void ppo_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg);
void pnw_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg);
void pic_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg);
void seg_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg);

#endif //PSU_ZAPPY_2019_COMMANDS_H

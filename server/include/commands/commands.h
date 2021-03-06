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
void sgt_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg);
void ppo_command(client_t *cli, data_server_t *data);
void pnw_command(client_t *cli, data_server_t *data);
void pic_command(client_t *cli, data_server_t *data);
void seg_command(data_server_t *data, char *team_name);
void pie_command(client_t *cli, data_server_t *data, char result);
void pdi_command(client_t *cli, data_server_t *data);
void pbc_command(client_t *cli, data_server_t *data);
void plv_command(client_t *cli, data_server_t *data);
void pin_command(client_t *cli, data_server_t *data);
void enw_command(client_t *cli, data_server_t *data, const int param[2]);
void eht_command(int egg_id, data_server_t *data);

#endif //PSU_ZAPPY_2019_COMMANDS_H

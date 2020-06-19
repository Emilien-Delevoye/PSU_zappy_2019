/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void connect_nbr(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;
    char buffer[50] = {0};

    sprintf(buffer, "%d\n", data->params.r_cli[cli->team_id]);
    add_to_write_list(cli, buffer);
}
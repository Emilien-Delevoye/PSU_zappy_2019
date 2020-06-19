/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void fork_cmd(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;

    ++data->params.r_cli[cli->team_id];
    add_to_write_list(cli, "ok\n");
}
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

    create_egg(data, cli);
    add_to_write_list(cli, "ok\n");
}
/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void right(data_server_t *data)
{
    ++data->cli_work->cli->drone.orientation;
    if (data->cli_work->cli->drone.orientation > 5)
        data->cli_work->cli->drone.orientation = 1;
    add_to_write_list(data->cli_work->cli, "ok\n");
}

void left(data_server_t *data)
{
    --data->cli_work->cli->drone.orientation;
    if (data->cli_work->cli->drone.orientation < 5)
        data->cli_work->cli->drone.orientation = 1;
    add_to_write_list(data->cli_work->cli, "ok\n");
}
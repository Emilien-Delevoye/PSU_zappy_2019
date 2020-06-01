/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/select.h"

void close_clients(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next) {
        if (cli->to_close == false)
            continue;
        remove_a_client(data, cli);
        close_clients(data);
        return;
    }
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/select.h"
#include <unistd.h>

void read_buffer(data_server_t *data, client_t *cli)
{
    char buffer[129] = {0};

    if (!read(cli->fd, buffer, 128))
        close_client(data, cli);
}

void read_socket(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next)
        if (FD_ISSET(cli->fd, &data->fdset_read))
            read_buffer(data, cli);
}
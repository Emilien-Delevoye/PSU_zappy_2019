/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/select.h"
#include <unistd.h>
#include <stdio.h>

void read_buffer(client_t *cli)
{
    char buffer[129] = {0};

    if (!read(cli->fd, buffer, 128)) {
        cli->to_close = true;
        return;
    }
    printf("Buffer read : %s\n", buffer);
}

void read_socket(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next)
        if (FD_ISSET(cli->fd, &data->fdset_read))
            read_buffer(cli);
}
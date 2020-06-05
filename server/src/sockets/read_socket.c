/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/select.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/write_list.h"

void read_buffer(client_t *cli)
{
    char *buffer = gnl(cli->fd, true);

    if (!buffer) {
        cli->to_close = true;
        return;
    }
    printf("Buffer read : %s\n", buffer);
    if (strcmp(buffer, "ping") == 0)
        add_to_write_list(cli, "pong\n");
    free(buffer);
}

void read_socket(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next)
        if (FD_ISSET(cli->fd, &data->fdset_read))
            read_buffer(cli);
}
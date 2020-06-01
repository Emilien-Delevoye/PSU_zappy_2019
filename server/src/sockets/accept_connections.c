/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

void accept_connections(data_server_t *data)
{
    client_t *new;
    struct sockaddr_in addr_in = {0};
    int len = sizeof(addr_in);

    if (!FD_ISSET(data->fd, &data->fdset_read))
        return;
    new = malloc(sizeof(client_t));
    if (!new)
        return;
    new->fd = accept(data->fd, (struct sockaddr *)&addr_in, (socklen_t *)&len);
    new->next = NULL;
    new->prev = NULL;
    if (!data->l_cli.first) {
        data->l_cli.first = new;
        data->l_cli.last = new;
    } else {
        data->l_cli.last->next = new;
        data->l_cli.last = new;
    }
}
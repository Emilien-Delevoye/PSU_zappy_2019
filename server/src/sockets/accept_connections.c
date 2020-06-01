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
#include <unistd.h>
#include <stdio.h>

void add_client_to_list(data_server_t *data, int new_fd)
{
    client_t *new;

    new = malloc(sizeof(client_t));
    if (!new) {
        close(new_fd);
        return;
    }
    new->fd = new_fd;
    new->next = NULL;
    new->prev = NULL;
    new->to_close = false;
    if (!data->l_cli.first) {
        data->l_cli.first = new;
        data->l_cli.last = new;
    } else {
        data->l_cli.last->next = new;
        new->prev = data->l_cli.last;
        data->l_cli.last = new;
    }
    printf("New connection (client %d)\n", new_fd);
}

void accept_connections(data_server_t *data)
{
    int new_fd;
    struct sockaddr_in addr_in = {0};
    int len = sizeof(addr_in);

    if (!FD_ISSET(data->fd, &data->fdset_read))
        return;
    new_fd = accept(data->fd, (struct sockaddr *)&addr_in, (socklen_t *)&len);
    if (new_fd < 0)
        return;
    add_client_to_list(data, new_fd);
}
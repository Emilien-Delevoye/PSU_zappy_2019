/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/accept_connections.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

static bool add_drone(client_t *new)
{
    static int id_cli = -1;

    new->drone = initialise_new_drone(id_cli++);
    if (!new->drone) {
        free(new);
        close(new->fd);
        return (false);
    }
    return (true);
}

void setup_cli_in_list(data_server_t *data, client_t *new)
{
    if (!data->l_waiting.first) {
        data->l_waiting.first = new;
        data->l_waiting.last = new;
    } else {
        data->l_waiting.last->next = new;
        new->prev = data->l_waiting.last;
        data->l_waiting.last = new;
    }
}

void add_client_to_list(data_server_t *data, int new_fd)
{
    client_t *new;

    new = malloc(sizeof(client_t));
    if (!new) {
        close(new_fd);
        return;
    }
    memset(new, 0, sizeof(client_t));
    new->fd = new_fd;
    if (add_drone(new) == false)
        return;
    new->to_close = false;
    setup_cli_in_list(data, new);
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
    write(new_fd, "WELCOME\n", 8);
    add_client_to_list(data, new_fd);
}
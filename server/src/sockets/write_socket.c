/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static void write_to_client(client_t *c)
{
    write_cli_t *save;

    if (!c->list_msg)
        return;
    save = c->list_msg;
    if (!c->list_msg->to_write) {
        c->list_msg = c->list_msg->next;
        free(save);
    } else {
        write(c->fd, c->list_msg->to_write, strlen(c->list_msg->to_write));
        free(c->list_msg->to_write);
        c->list_msg = c->list_msg->next;
        free(save);
    }
}

void write_socket(data_server_t *data)
{
    for (client_t *c = data->l_waiting.first; c; c = c->next)
        if (c->list_msg && FD_ISSET(c->fd, &data->fdset_write))
            write_to_client(c);
}
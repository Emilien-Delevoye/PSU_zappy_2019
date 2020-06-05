/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "utils/write_list.h"
#include "server.h"
#include "sockets/select.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_to_end_list(char *buffer, command_queue_t *new, command_queue_t *cur,
    short counter)
{
    while (cur->next) {
        cur = cur->next;
        ++counter;
    }
    if (counter > 10) {
        free(new);
        free(buffer);
        return;
    }
    cur->next = new;
}

static void add_to_client(client_t *cli, char *buffer)
{
    command_queue_t *new = malloc(sizeof(command_queue_t));
    command_queue_t *cur = cli->cmd_queue;
    short counter = 0;

    if (!new)
        return;
    new->next = NULL;
    new->command = buffer;
    if (!cli->cmd_queue)
        cli->cmd_queue = new;
    else
        add_to_end_list(buffer, new, cur, counter);
}

void read_buffer(client_t *cli)
{
    char *buffer = gnl(cli->fd, true, &cli->to_close);

    while (buffer) {
        add_to_client(cli, buffer);
        printf("Buffer read : %s\n", buffer);
        if (strcmp(buffer, "ping") == 0)
            add_to_write_list(cli, "pong\n");
        free(buffer);
        buffer = gnl(cli->fd, true, &cli->to_close);
    }
}

void read_socket(data_server_t *data)
{
    for (client_t *cli = data->l_cli.first; cli; cli = cli->next)
        if (FD_ISSET(cli->fd, &data->fdset_read))
            read_buffer(cli);
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <unistd.h>

static void free_command_queue(client_t *cli)
{
    command_queue_t *save = NULL;

    if (cli->buffer)
        free(cli->buffer);
    for (command_queue_t *c = cli->cmd_queue; c; c = c->next) {
        if (!save)
            continue;
        if (save->command)
            free(save->command);
        free(save);
        save = c;
    }
}

static void close_graphical(data_server_t *data, client_t *first)
{
    if (!first || first->to_close == false)
        return;
    free_command_queue(first);
    close(first->fd);
    free(first);
    data->l_graphical.first = NULL;
    data->l_graphical.last = NULL;
}

void close_clients(data_server_t *data)
{
    for (client_t *cli = data->l_waiting.first; cli; cli = cli->next) {
        if (cli->to_close == false)
            continue;
        free_command_queue(cli);
        remove_a_client(data, cli);
        close_clients(data);
        return;
    }
    for (client_t *cli = data->l_connected.first; cli; cli = cli->next) {
        if (cli->to_close == false)
            continue;
        free_command_queue(cli);
        remove_a_client_connected(data, cli);
        close_in_cli_ww_list(data, cli);
        close_clients(data);
        return;
    }
    close_graphical(data, data->l_graphical.first);
}
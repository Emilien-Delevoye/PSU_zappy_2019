/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "sockets/select.h"
#include <stdlib.h>

void close_clients(data_server_t *data)
{
    command_queue_t *save = NULL;

    for (client_t *cli = data->l_cli.first; cli; cli = cli->next) {
        if (cli->to_close == false)
            continue;
        for (command_queue_t *c = cli->cmd_queue; c; c = c->next) {
            if (save) {
                if (save->command)
                    free(save->command);
                free(save);
            }
            save = c;
        }
        remove_a_client(data, cli);
        close_clients(data);
        return;
    }
}
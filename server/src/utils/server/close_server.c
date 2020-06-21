/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "map/setup_map.h"
#include <unistd.h>
#include <stdlib.h>

void free_client(data_server_t data)
{
    client_t *prev = NULL;
    list_actions_t *prev1 = NULL;

    for (client_t *cli = data.l_connected.first; cli; cli = cli->next) {
        if (prev)
            free(prev);
        prev = cli;
    }
    if (prev)
        free(prev);
    for (list_actions_t *cur = data.cli_work; cur; cur = cur->next) {
        if (prev1)
            free(prev1);
        prev1 = cur;
    }
    if (prev1)
        free(prev1);
}

void close_server(data_server_t data)
{
    free_team_names(data);
    free_map(data);
    free_eggs(data);
    free_client(data);
    close(data.fd);
}
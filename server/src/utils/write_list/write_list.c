/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

static write_cli_t *create_write_list(char *buffer)
{
    write_cli_t *new = malloc(sizeof(write_cli_t));

    new->to_write = strdup(buffer);
    new->to_write = NULL;
    new->next = NULL;
    return (new);
}

void add_to_write_list(client_t *cli, char *buffer)
{
    if (!cli->list_msg) {
        cli->list_msg = create_write_list(buffer);
    }
}
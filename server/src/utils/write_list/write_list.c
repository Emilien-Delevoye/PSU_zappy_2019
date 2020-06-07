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

    if (!new)
        return (NULL);
    new->to_write = strdup(buffer);
    if (!new->to_write)
        return (NULL);
    new->next = NULL;
    return (new);
}

static void add_to_list(client_t *cli, char *buffer)
{
    write_cli_t *new = create_write_list(buffer);
    write_cli_t *cur = cli->list_msg;

    while (cur->next)
        cur = cur->next;
    cur->next = new;
}

void add_to_write_list(client_t *cli, char *buffer)
{
    if (!cli->list_msg)
        cli->list_msg = create_write_list(buffer);
    else
        add_to_list(cli, buffer);
}
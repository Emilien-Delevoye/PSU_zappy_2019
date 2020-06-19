/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

static list_actions_t *new_node(client_t *cli)
{
    list_actions_t *new = malloc(sizeof(list_actions_t));

    if (!new)
        return (NULL);
    memset(new, 0, sizeof(list_actions_t));
    new->next = NULL;
    new->cli = cli;
    return (new);
}

static void not_empty_list(list_actions_t **cli_work, client_t *cli)
{
    list_actions_t *new = new_node(cli);
    list_actions_t *cur = (*cli_work);

    while (cur->next)
        cur = cur->next;
    cur->next = new;
}

static void empty_list(list_actions_t **cli_work, client_t *cli)
{
    (*cli_work) = new_node(cli);
}

void new_client_to_ww_list(client_t *cli, list_actions_t **cli_work)
{
    if (!cli || !cli_work)
        return;
    if (!(*cli_work))
        empty_list(cli_work, cli);
    else
        not_empty_list(cli_work, cli);
}
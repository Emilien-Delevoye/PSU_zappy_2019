/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

static void remove_node(list_actions_t **list, list_actions_t *prev,
    list_actions_t *cur)
{
    if (cur == *list || !prev) {
        (*list) = cur->next;
        return;
    }
    prev->next = cur->next;
}

void read_list(list_actions_t **list, client_t *cli)
{
    list_actions_t *first = (*list);
    list_actions_t *prev = NULL;

    if (!first)
        return;
    for (list_actions_t *cur = first; cur; cur = cur->next) {
        if (cur->cli == cli) {
            remove_node(list, prev, cur);
            return;
        }
        prev = cur;
    }
}

void close_in_cli_ww_list(data_server_t *data, client_t *cli)
{
    read_list(&data->cli_wait, cli);
    read_list(&data->cli_work, cli);
}
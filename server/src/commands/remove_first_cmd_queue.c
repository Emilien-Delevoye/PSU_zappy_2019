/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

void remove_first_cmd_queue(client_t *current)
{
    command_queue_t *first = current->cmd_queue;

    if (!first)
        return;
    current->cmd_queue = current->cmd_queue->next;
    free(first->command);
    free(first);
}
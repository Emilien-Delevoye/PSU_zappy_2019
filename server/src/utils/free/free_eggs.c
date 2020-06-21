/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

void free_eggs(data_server_t data)
{
    list_egg_t *to_free = NULL;

    for (list_egg_t *cur = data.egg_waiting; cur; cur = cur->next) {
        if (to_free)
            free(to_free);
        to_free = cur;
    }
    if (to_free)
        free(to_free);
    to_free = NULL;
    for (list_egg_t *cur = data.hatch_eggs; cur; cur = cur->next) {
        if (to_free)
            free(to_free);
        to_free = cur;
    }
    if (to_free)
        free(to_free);
    to_free = NULL;
}
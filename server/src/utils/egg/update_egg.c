/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void update_egg(data_server_t *data)
{
    list_egg_t *cur = data->egg_waiting;

    if (!cur)
        return;
    if (!((data->tv.tv_sec == cur->tv.tv_sec &&
        data->tv.tv_usec > cur->tv.tv_sec) ||
        data->tv.tv_sec > cur->tv.tv_sec))
        return;
    data->egg_waiting = cur->next;
    cur->next = NULL;
    for (list_egg_t *tmp = data->hatch_eggs; tmp; tmp = tmp->next) {
        if (!tmp->next) {
            tmp->next = cur;
            return;
        }
    }
}
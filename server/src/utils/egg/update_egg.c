/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void update_egg(data_server_t *d)
{
    list_egg_t *c = d->egg_waiting;

    if (!c)
        return;
    if (!((d->tv.tv_sec == c->tv.tv_sec && d->tv.tv_usec > c->tv.tv_sec) ||
        d->tv.tv_sec > c->tv.tv_sec))
        return;
    d->egg_waiting = c->next;
    c->next = NULL;
    ++d->params.egg_r_c[c->team_id];
    if (!d->hatch_eggs) {
        d->hatch_eggs = c;
        return;
    }
    for (list_egg_t *tmp = d->hatch_eggs; tmp; tmp = tmp->next) {
        if (!tmp->next) {
            tmp->next = c;
            return;
        }
    }
}
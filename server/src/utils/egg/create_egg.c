/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

static void calc_egg_time(data_server_t *d, struct timeval tv,
    struct timeval *tv_out)
{
    double time = (double)600 / d->params.freq;
    int seconds = (int)time;
    double microseconds = ((time - (int)time) * 1000000);

    tv_out->tv_sec = tv.tv_sec;
    tv_out->tv_usec = tv.tv_usec;
    tv_out->tv_usec += microseconds;
    if (tv_out->tv_usec > 1000000)
        seconds += (int)(microseconds / 1000000);
    tv_out->tv_sec += seconds;
}

void add_to_end_egg_list(data_server_t *data, list_egg_t *new)
{
    if (!data->egg_waiting) {
        data->egg_waiting = new;
        return;
    }
    for (list_egg_t *cur = data->egg_waiting; cur; cur = cur->next) {
        if (!cur->next) {
            cur->next = new;
            return;
        }
    }
}

void create_egg(data_server_t *data, client_t *cli)
{
    list_egg_t *new = malloc(sizeof(list_egg_t));

    if (!new)
        return;
    new->next = NULL;
    new->team_id = cli->team_id;
    new->egg_id = init_id();
    new->coord[0] = (int)cli->drone.tile->coord[0];
    new->coord[1] = (int)cli->drone.tile->coord[1];
    calc_egg_time(data, data->tv, &new->tv);
    add_to_end_egg_list(data, new);
}
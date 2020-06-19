/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <sys/time.h>
#include <stdlib.h>

static void (*fct[])(data_server_t *) =
{
    forward, right, left, look, inventory, broadcast, connect_nbr, fork_cmd,
    eject, take, set, incantation_after, NULL
};

static void update_work_cli(data_server_t *d)
{
    while (d->cli_work) {
        if (d->cli_work->tv.tv_sec > d->tv.tv_sec ||
            (d->cli_work->tv.tv_sec == d->tv.tv_sec &&
            d->cli_work->tv.tv_usec > d->tv.tv_usec))
            return;
        if (d->cli_work->cmd_nb < 12)
            fct[d->cli_work->cmd_nb](d);
        if (d->cli_work->cmd_str)
            free(d->cli_work->cmd_str);
        d->cli_work->cmd_str = NULL;
        move_to_wait_list(d);
    }
}

static void update_waiting_cli(data_server_t *data, struct timeval cur_time,
    list_actions_t *first)
{
    list_actions_t *prev = NULL;

    for (list_actions_t *cur = first; cur; cur = cur->next) {
        if (!cur->cli->cmd_queue) {
            prev = cur;
            continue;
        }
        read_new_cmd(data, cur->cli, cur_time);
        if (prev)
            update_waiting_cli(data, cur_time, prev);
        else
            update_waiting_cli(data, cur_time, data->cli_wait);
    }
}

static void update_time(struct timeval tv[2], unsigned int freq)
{
    static int performance = 0;
    double loop_du;
    double min_du;

    tv[0].tv_sec = tv[1].tv_sec;
    tv[0].tv_usec = tv[1].tv_usec;
    gettimeofday(&tv[1], NULL);
    performance++;
    if (tv[0].tv_sec != tv[1].tv_sec) {
        loop_du = ((1.0 / performance) * 1000000);
        min_du = (1.0 / freq) * 1000000;
        printf("Perf : %d tps || %lf loop duration (µs) ||"
            " %lf min duration (µs)\n", performance, loop_du, min_du);
        if (loop_du > min_du)
            printf("WARNING: Server is slow !\n");
        performance = 0;
    }
}

void ai_interaction(data_server_t *data)
{
    static struct timeval tv[2];

    update_time(tv, data->params.freq);
    data->tv = tv[1];
    update_work_cli(data);
    update_waiting_cli(data, tv[0], data->cli_wait);
}
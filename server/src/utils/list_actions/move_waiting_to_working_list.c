/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

static void do_move_node(data_server_t *data, list_actions_t *prev,
    list_actions_t *tmp)
{
    if (prev) {
        tmp->next = prev->next;
        prev->next = tmp;
    } else {
        data->cli_work = tmp;
        tmp->next = NULL;
    }
}

static void move_to_work_list(list_actions_t *cur, data_server_t *data,
    struct timeval cu_time)
{
    list_actions_t *prev = NULL;

    cur->next = NULL;
    if (!data->cli_work) {
        data->cli_work = cur;
        return;
    }
    for (list_actions_t *tmp = data->cli_work; tmp; tmp = tmp->next) {
        if ((tmp->tv.tv_sec == cu_time.tv_sec &&
            tmp->tv.tv_usec < cu_time.tv_usec) ||
            (tmp->tv.tv_sec > cu_time.tv_sec))
            do_move_node(data, prev, tmp);
        prev = tmp;
    }
}

static void calc_cu_time(data_server_t *data, struct timeval *tv, int duration)
{
    double time = (double)duration / data->params.freq;
    int seconds = (int)time;
    double microseconds = ((time - (int)time) * 1000000);

    tv->tv_usec += microseconds;
    if (tv->tv_usec > 1000000)
        seconds += (int)(microseconds / 1000000);
    tv->tv_sec += seconds;
}

void move_wait_to_work_list(data_server_t *data, client_t *cli,
    struct timeval cu_time, short cmd_nb)
{
    list_actions_t *prev = NULL;
    list_actions_t *next;

    for (list_actions_t *cur = data->cli_wait; cur; cur = cur->next) {
        next = cur->next;
        if (cur->cli == cli) {
            calc_cu_time(data, &cu_time, cmd_nb);
            move_to_work_list(cur, data, cu_time);
            if (!prev)
                data->cli_wait = next;
            else
                prev->next = next;
        }
        prev = cur;
    }
}
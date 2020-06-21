/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

extern const struct cmd_ai_s cmd[];

static void do_move_node(data_server_t *data, list_actions_t *prev,
    list_actions_t *new_elem)
{
    if (prev) {
        new_elem->next = prev->next;
        prev->next = new_elem;
    } else {
        new_elem->next = data->cli_work;
        data->cli_work = new_elem;
    }
}

static void add_to_end_work_list(data_server_t *data, list_actions_t *cur)
{
    list_actions_t *first = data->cli_work;

    if (!first) {
        data->cli_work = cur;
    } else {
        while (first->next)
            first = first->next;
        first->next = cur;
    }
}

static void move_to_work_list(list_actions_t *cur, data_server_t *d,
    struct timeval ti)
{
    list_actions_t *prev = NULL;

    cur->next = NULL;
    if (!d->cli_work) {
        d->cli_work = cur;
        return;
    }
    if (cur->cmd_nb == 11) {
        add_to_end_work_list(d, cur);
        return;
    }
    for (list_actions_t *t = d->cli_work; t; t = t->next) {
        if ((t->tv.tv_sec == ti.tv_sec && t->tv.tv_usec > ti.tv_usec) ||
            (t->tv.tv_sec > ti.tv_sec)) {
            do_move_node(d, prev, cur);
            return;
        }
        prev = t;
    }
    add_to_end_work_list(d, cur);
}

static void calc_cu_time(data_server_t *data, struct timeval *tv, int cmd_nb,
    list_actions_t *cur)
{
    double time = (double)cmd[cmd_nb].duration / data->params.freq;
    int seconds = (int)time;
    double microseconds = ((time - (int)time) * 1000000);

    cur->tv.tv_sec = tv->tv_sec;
    cur->tv.tv_usec = tv->tv_usec;
    cur->tv.tv_usec += microseconds;
    if (cur->tv.tv_usec > 1000000)
        seconds += (int)(microseconds / 1000000);
    cur->tv.tv_sec += seconds;
    cur->cmd_nb = (short)cmd_nb;
}

void move_wait_to_work_list(data_server_t *data, client_t *cli,
    struct timeval cu_time, short cmd_nb)
{
    list_actions_t *prev = NULL;
    list_actions_t *next;

    for (list_actions_t *cur = data->cli_wait; cur; cur = cur->next) {
        next = cur->next;
        if (cur->cli == cli) {
            calc_cu_time(data, &cu_time, cmd_nb, cur);
            move_to_work_list(cur, data, cu_time);
            if (!prev)
                data->cli_wait = next;
            else
                prev->next = next;
            cur->cmd_str = cli->cmd_queue->command;
            return;
        }
        prev = cur;
    }
}
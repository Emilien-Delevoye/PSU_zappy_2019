/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <sys/time.h>

static void update_work_cli(data_server_t *data)
{
    /*TODO: Parcourir en fonction du temps et exécuter les commandes qui ont
        besoin de l'être*/
    (void)data;
}

static void update_waiting_cli(data_server_t *data, struct timeval cur_time)
{
    for (list_actions_t *cur = data->cli_wait; cur; cur = cur->next) {
        if (!cur->cli->cmd_queue)
            continue;
        read_new_cmd(data, cur->cli, cur_time);
    }
}

static void update_time(struct timeval tv[2])
{
    tv[0].tv_sec = tv[1].tv_sec;
    tv[0].tv_usec = tv[1].tv_usec;
    gettimeofday(&tv[1], NULL);
}

void ai_interaction(data_server_t *data)
{
    static struct timeval tv[2];

    update_time(tv);
    update_work_cli(data);
    update_waiting_cli(data, tv[0]);
}
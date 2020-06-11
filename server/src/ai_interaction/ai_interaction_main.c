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

}

static void update_waiting_cli(data_server_t *data)
{

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
    update_waiting_cli(data);
}
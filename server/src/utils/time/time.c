/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Every function for timer
*/

#include "utils/timer.h"
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void setup_timer(data_server_t *data)
{
    gettimeofday(&data->tv, NULL);
    data->tm = localtime(&data->tv.tv_sec);
    data->timer = data->tv.tv_usec;
    data->sec = data->tm->tm_sec;
}

void timer(data_server_t *data)
{
    long int timer;
    int sec;

    gettimeofday(&data->tv, NULL);
    data->tm = localtime(&data->tv.tv_sec);
    timer = data->tv.tv_usec;
    sec = data->tm->tm_sec;
    if ((sec - data->sec) * 1000000 + timer - data->timer > 1 /
        (double)data->freq * 1000000) {
        data->timer = data->tv.tv_usec;
        data->sec = data->tm->tm_sec;
    }
    if (sec == 0 && data->sec != 0 && data->sec != -1)
        data->sec = -1;
}
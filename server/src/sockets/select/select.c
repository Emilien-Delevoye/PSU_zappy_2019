/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "sockets/select.h"
#include <stdlib.h>

void setup_fdset(data_server_t *data)
{
    FD_ZERO(&data->fdset_read);
    FD_ZERO(&data->fdset_write);
    FD_SET(data->fd, &data->fdset_read);
}

static int get_max_fd(data_server_t *data)
{
    int max_fd = data->fd;

    return (max_fd + 1);
}

bool select_fd(data_server_t *data)
{
    if (select(get_max_fd(data), &data->fdset_read,
        &data->fdset_write, NULL, NULL) < 0) {
        return (false);
    }
    return (true);
}
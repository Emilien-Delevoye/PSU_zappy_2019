/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"

static void list_fd_set(data_server_t *data, client_t *first)
{
    while (first) {
        FD_SET(first->fd, &data->fdset_read);
        if (first->list_msg)
            FD_SET(first->fd, &data->fdset_write);
        first = first->next;
    }
}

void setup_fdset(data_server_t *data)
{
    FD_ZERO(&data->fdset_read);
    FD_ZERO(&data->fdset_write);
    FD_SET(data->fd, &data->fdset_read);
    list_fd_set(data, data->l_waiting.first);
    list_fd_set(data, data->l_connected.first);
    list_fd_set(data, data->l_graphical.first);
}

static int get_max_fd(data_server_t *data)
{
    int max_fd = data->fd;

    for (client_t *cur = data->l_waiting.first; cur; cur = cur->next)
        if (cur->fd > max_fd)
            max_fd = cur->fd;
    for (client_t *cur = data->l_connected.first; cur; cur = cur->next)
        if (cur->fd > max_fd)
            max_fd = cur->fd;
    return (max_fd + 1);
}

bool select_fd(data_server_t *data)
{
    struct timeval tv;

    tv.tv_usec = 0;
    tv.tv_sec = 0;
    if (select(get_max_fd(data), &data->fdset_read,
        &data->fdset_write, NULL, &tv) < 0) {
        return (false);
    }
    return (true);
}
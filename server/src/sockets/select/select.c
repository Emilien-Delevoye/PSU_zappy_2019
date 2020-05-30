/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "sockets/select.h"

void setup_fdset(data_server_t *data)
{
    FD_ZERO(&data->fdset_read);
    FD_ZERO(&data->fdset_write);
    FD_SET(data->fd, &data->fdset_read);
}
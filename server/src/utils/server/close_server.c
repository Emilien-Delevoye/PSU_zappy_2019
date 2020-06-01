/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <unistd.h>

void close_server(data_server_t data)
{
    close(data.fd);
}
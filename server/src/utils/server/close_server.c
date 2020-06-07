/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "map/setup_map.h"
#include <unistd.h>

void close_server(data_server_t data)
{
    free_team_names(data);
    free_map(data);
    close(data.fd);
}
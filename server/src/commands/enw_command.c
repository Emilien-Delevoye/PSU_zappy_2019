/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the enw command
*/

#include "server.h"
#include <string.h>

void enw_command(client_t *cli, data_server_t *data)
{
    char str[50];
    int e = 0;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];

    memset(str, 0, sizeof(str));
    sprintf(str, "enw %d %d %d\n", e, y, x);
    add_to_write_list(data->l_graphical.first, str);
}
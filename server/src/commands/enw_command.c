/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the enw command
*/

#include "server.h"
#include <string.h>

void enw_command(client_t *cli, data_server_t *data, const int param[2])
{
    char str[50];
    int n = param[0];
    int e = param[1];
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];

    memset(str, 0, sizeof(str));
    sprintf(str, "enw %d %d %d %d\n", n, e, x, y);
    add_to_write_list(data->l_graphical.first, str);
}
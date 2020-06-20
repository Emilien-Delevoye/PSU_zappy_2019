/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pie command
*/

#include "server.h"
#include <string.h>

void pie_command(client_t *cli, data_server_t *data, char result)
{
    char str[35];
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];

    memset(str, 0, sizeof(str));
    sprintf(str, "pie %d %d %c\n", x, y, result);
    add_to_write_list(data->l_graphical.first, str);
}
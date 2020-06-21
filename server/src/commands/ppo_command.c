/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the ppo command
*/

#include "server.h"

void ppo_command(client_t *cli, data_server_t *data)
{
    int ori[4] = {4, 3, 2, 1};
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int o = ori[cli->drone.orientation - 1];
    char str[53] = {0};

    if (o > 4)
        o -= 4;
    sprintf(str, "ppo %d %d %d %d\n", n, x, y, o);
    add_to_write_list(data->l_graphical.first, str);
}
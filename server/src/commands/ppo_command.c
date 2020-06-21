/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the ppo command
*/

#include "server.h"

void ppo_command(client_t *cli, data_server_t *data)
{
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int o = cli->drone.orientation;
    char str[53] = {0};

    sprintf(str, "ppo %d %d %d %d\n", n, x, y, o);
    add_to_write_list(data->l_graphical.first, str);
}
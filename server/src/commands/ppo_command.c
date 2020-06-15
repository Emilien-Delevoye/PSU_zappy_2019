/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the ppo command
*/

#include "server.h"
#include <string.h>

void ppo_command(data_server_t *data, client_t *cli,
    __attribute__((unused))char **arg)
{
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int o = cli->drone.orientation;
    char str[53];

    memset(str, 0, 53);
    sprintf(str, "ppo %d %d %d %d\n", n, x, y, o);
    add_to_write_list(cli, str);
}
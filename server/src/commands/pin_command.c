/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pin command
*/

#include "server.h"
#include <string.h>

void pin_command(client_t *cli, data_server_t *data)
{
    char str[300];
    int n = cli->drone.id;

    memset(str, 0, sizeof(str));
    sprintf(str, "pin %d %d %d %d %d %d %d %d\n", n,
        cli->drone.inventory[0], cli->drone.inventory[1],
        cli->drone.inventory[2], cli->drone.inventory[3],
        cli->drone.inventory[4], cli->drone.inventory[5],
        cli->drone.inventory[6]);
    add_to_write_list(data->l_graphical.first, str);
}
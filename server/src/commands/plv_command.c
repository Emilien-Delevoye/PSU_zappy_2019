/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the plv command
*/

#include "server.h"
#include <string.h>

void plv_command(client_t *cli, data_server_t *data)
{
    char str[35];
    int n = cli->drone.id;
    int l = cli->drone.lvl;

    memset(str, 0, sizeof(str));
    sprintf(str, "plv %d %d\n", n, l);
    add_to_write_list(data->l_graphical.first, str);
}
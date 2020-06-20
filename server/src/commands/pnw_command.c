/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pnw command
*/

#include "server.h"
#include <string.h>

void pnw_command(client_t *cli, data_server_t *data)
{
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int o = cli->drone.orientation;
    unsigned int l = cli->drone.lvl;
    char *name = data->params.team_names[cli->team_id];
    char str[66 + strlen(name)];

    memset(str, 0, 66 + strlen(name));
    sprintf(str, "pnw %d %d %d %d %d %s\n", n, y, x, o, l, name);
    add_to_write_list(data->l_graphical.first, str);
}
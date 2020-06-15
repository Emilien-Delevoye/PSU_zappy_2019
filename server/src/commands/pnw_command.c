/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pnw command
*/

#include "server.h"
#include <string.h>

void pnw_command(data_server_t *data, client_t *cli,
    __attribute__((unused))char **arg)
{
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int o = cli->drone.orientation;
    unsigned int l = cli->drone.lvl = 0;
    char *name = data->params.team_names[cli->team_id];
    char str[66 + strlen(name)];

    memset(str, 0, 66 + strlen(name));
    sprintf(str, "pnw %d %d %d %d %d %s\n", n, x, y, o, l, name);
    add_to_write_list(cli, str);
}
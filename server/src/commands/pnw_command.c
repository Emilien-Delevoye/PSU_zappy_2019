/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pnw command
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

void pnw_command(data_server_t *data, client_t *cli,
    __attribute__((unused))char **arg)
{
    int n = cli->drone.id;
    unsigned int x = cli->map->coord[0];
    unsigned int y = cli->map->coord[1];
    unsigned int o = cli->drone.orientation;
    unsigned int l = cli->drone.lvl = 0;
    char *name = data->params.team_names[cli->team_id];
    char *str = malloc(sizeof(char) * 66 + strlen(name));

    if (str == NULL) {
        remove_a_client(data, cli);
        return;
    }
    memset(str, 0, 66 + strlen(name));
    sprintf(str, "pnw %d %d %d %d %d %s\n", n, x, y, o, l, name);
    add_to_write_list(cli, str);
}
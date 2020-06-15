/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pnw command
*/

#include "server.h"

void pnw_command(data_server_t *data, client_t *cli,
    __attribute__((unused))char **arg)
{
    int n = cli->drone.id;
//    int x = 0;
//    int y = 0;
    int O = cli->drone.orientation;
    int L = cli->drone.lvl = 0;
    char *N = data->params.team_names[cli->team_id];
}
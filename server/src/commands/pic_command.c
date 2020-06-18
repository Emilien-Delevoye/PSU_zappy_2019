/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pic command
*/

#include "server.h"
#include <string.h>

void pic_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg)
{
    char str[120];
    char id[11];
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int l = cli->drone.lvl;

    memset(str, 0, sizeof(str));
    sprintf(str, "pic %d %d %d %d", x, y, l, n);
    for (client_t *tmp = cli; tmp != NULL; tmp = tmp->next) {
        strcat(str, " ");
        sprintf(id, "%d", tmp->drone.id);
        strcat(str, id);
    }
    strcat(str, "\n");
    add_to_write_list(cli, str);
}
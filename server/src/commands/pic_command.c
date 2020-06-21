/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pic command
*/

#include "server.h"
#include <string.h>

void pic_command(client_t *cli, data_server_t *data)
{
    char str[120];
    char id[11];
    int n = cli->drone.id;
    unsigned int x = cli->drone.tile->coord[0];
    unsigned int y = cli->drone.tile->coord[1];
    unsigned int l = cli->drone.lvl;

    memset(str, 0, sizeof(str));
    sprintf(str, "pic %d %d %d %d", y, x, l, n);
    for (client_t *tmp = cli; tmp; tmp = tmp->next) {
        strcat(str, " ");
        sprintf(id, "%d", tmp->drone.id);
        strcat(str, id);
    }
    strcat(str, "\n");
    add_to_write_list(data->l_graphical.first, str);
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the seg command
*/

#include "server.h"
#include <string.h>

void seg_command(data_server_t *data, char *team_name)
{
    char str[7 + strlen(team_name)];

    memset(str, 0, sizeof(str));
    sprintf(str, "seg %s\n", team_name);
    add_to_write_list(data->l_graphical.first, str);
}
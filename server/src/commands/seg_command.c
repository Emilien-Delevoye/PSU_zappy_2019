/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the seg command
*/

#include "server.h"
#include <string.h>

void seg_command(client_t *cli, data_server_t *data)
{
    (void)cli;
    char str[6 + strlen("test")];

    memset(str, 0, sizeof(str));
    sprintf(str, "seg %s\n", "test");
    add_to_write_list(data->l_graphical.first, str);
}
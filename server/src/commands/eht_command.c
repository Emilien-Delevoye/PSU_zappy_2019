/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the eht command
*/

#include "server.h"
#include <string.h>

void eht_command(client_t *cli, data_server_t *data)
{
    char str[20];
    int e = 0;

    memset(str, 0, sizeof(str));
    sprintf(str, "eht %d\n", e);
    add_to_write_list(data->l_graphical.first, str);
}
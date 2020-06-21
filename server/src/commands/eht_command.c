/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the eht command
*/

#include "server.h"
#include <string.h>

void eht_command(int egg_id, data_server_t *data)
{
    char str[20];

    memset(str, 0, sizeof(str));
    sprintf(str, "eht %d\n", egg_id);
    add_to_write_list(data->l_graphical.first, str);
}
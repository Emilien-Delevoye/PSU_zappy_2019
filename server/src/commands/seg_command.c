/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the seg command
*/

#include "server.h"
#include <string.h>

void seg_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg)
{
    char str[strlen("test")];

    memset(str, 0, sizeof(str));
    sprintf(str, "seg %s\n", str);
    add_to_write_list(cli, str);
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the command msz
*/

#include "utils/write_list.h"
#include <stdio.h>
#include <string.h>

void msz_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg)
{
    char str[29];

    memset(str, 0, 29);
    sprintf(str, "msz %d %d\n", data->params.width, data->params.height);
    add_to_write_list(cli, str);
}
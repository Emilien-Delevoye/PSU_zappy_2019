/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the command sgt
*/

#include "utils/write_list.h"
#include <stdio.h>

void sgt_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg)
{
    char str[18] = {0};

    sprintf(str, "sgt %d\n", data->params.freq);
    add_to_write_list(cli, str);
}
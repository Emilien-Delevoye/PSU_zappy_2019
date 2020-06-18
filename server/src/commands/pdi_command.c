/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pdi command
*/

#include "server.h"
#include <string.h>

void pdi_command(client_t *cli, __attribute__((unused))data_server_t *data,
    __attribute__((unused))char **arg)
{
    char str[18];
    unsigned int n = cli->drone.id;

    memset(str, 0, sizeof(str));
    sprintf(str, "pdi %d\n", n);
    add_to_write_list(cli, str);
}
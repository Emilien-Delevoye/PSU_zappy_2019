/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the pbc command
*/

#include "server.h"
#include <string.h>

void pbc_command(client_t *cli, data_server_t *data)
{
    char str[18];
    unsigned int n = cli->drone.id;

    memset(str, 0, sizeof(str));
    sprintf(str, "pbc %d\n", n);
    add_to_write_list(data->l_graphical.first, str);
}
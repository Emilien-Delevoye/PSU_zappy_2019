/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the bct command
*/

#include "sockets/select.h"
#include "utils/write_list.h"
#include "server.h"
#include <stdlib.h>
#include <string.h>

void send_bct_info(data_server_t *data, client_t *cli, char **arg, map_t *map)
{
    char *str = malloc(sizeof(char) * 113);

    if (str == NULL) {
        remove_a_client(data, cli);
        return;
    }
    memset(str, 0, 113);
    sprintf(str, "bct %s %s %d %d %d %d %d %d %d\n", arg[1], arg[2], map->items[0], map->items[1], map->items[2], map->items[3], map->items[4], map->items[5], map->items[6]);
    add_to_write_list(cli, str);
}

void bct_command(client_t *cli, data_server_t *data, char **arg)
{
    map_t *cur = data->bottom_left;

    if (!arg[1] || !arg[2])
        return;
    for (int i = 0; i < atoi(arg[1]); ++i)
        cur = cur->right;
    for (int j = 0; j < atoi(arg[2]); ++j)
        cur = cur->top;
    send_bct_info(data, cli, arg, cur);
}
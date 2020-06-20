/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the bct command
*/

#include "utils/write_list.h"
#include "server.h"
#include <stdlib.h>
#include <string.h>

void send_bct_info(data_server_t *data, char **arg, map_t *map)
{
    char str[113] = {0};

    sprintf(str, "bct %s %s %d %d %d %d %d %d %d\n", arg[2], arg[1],
        map->items[0], map->items[1], map->items[2], map->items[3],
        map->items[4], map->items[5], map->items[6]);
    add_to_write_list(data->l_graphical.first, str);
}

void bct_command(__attribute__((unused))client_t *cli,
    data_server_t *data, char **arg)
{
    map_t *cur = data->bottom_left;

    if (!arg[1] || !arg[2])
        return;
    for (int i = 0; i < atoi(arg[2]); ++i)
        cur = cur->right;
    for (int j = 0; j < atoi(arg[1]); ++j)
        cur = cur->top;
    send_bct_info(data, arg, cur);
}
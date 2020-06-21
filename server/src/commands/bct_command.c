/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the bct command
*/

#include "utils/write_list.h"
#include "server.h"
#include <stdlib.h>

void send_bct_info(data_server_t *data, char **arg, map_t *map, client_t *cli)
{
    char str[200] = {0};

    if (cli != data->l_graphical.first) {
        sprintf(str, "bct %d %s %s %d %d %d %d %d %d %d\n", cli->drone.id,
            arg[1], arg[2], map->items[0], map->items[1], map->items[2],
            map->items[3], map->items[4], map->items[5], map->items[6]);
    } else {
        sprintf(str, "bct %d %s %s %d %d %d %d %d %d %d\n", -1,
            arg[1], arg[2], map->items[0], map->items[1], map->items[2],
            map->items[3], map->items[4], map->items[5], map->items[6]);
    }
    add_to_write_list(data->l_graphical.first, str);
}

void bct_command(__attribute__((unused))client_t *cli,
    data_server_t *data, char **arg)
{
    map_t *cur = data->bottom_left;

    if (!arg || !arg[1] || !arg[2])
        return;
    for (int i = 0; i < atoi(arg[2]); ++i)
        cur = cur->right;
    for (int i = 0; i < atoi(arg[1]); ++i)
        cur = cur->top;
    send_bct_info(data, arg, cur, cli);
    for (int a = 0; arg[a]; ++a)
        free(arg[a]);
    free(arg);
}
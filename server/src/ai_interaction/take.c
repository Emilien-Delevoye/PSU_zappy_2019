/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

char *get_take_arg(char *str)
{
    char *tmp = malloc(sizeof(char) * strlen(str) - 4);

    memset(tmp, 0, sizeof(char) * strlen(str) - 4);
    for (int i = 4; str[i]; ++i) {
        if (i != 4)
            tmp[i - 5] = str[i];
    }
    return tmp;
}

void spawn_random_food(data_server_t *data, int value)
{
    int x = rand() % data->params.width;
    int y = rand() % data->params.height;
    map_t *start = data->bottom_left;

    if (value == FOOD) {
        for (int i = 0; i < x; ++i, start = start->right);
        for (int i = 0; i < y; ++i, start = start->top);
        start->items[FOOD] += 1;
    }
}

void take(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;
    char *str = get_take_arg(data->cli_work->cmd_str);
    map_t *cur = cli->drone.tile;
    char *equi[7] = {"food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame"};

    for (int i = 0; i < 7; ++i) {
        if (strcmp(equi[i], str) == 0 && cur->items[i] > 0) {
            spawn_random_food(data, i);
            cur->items[i] -= 1;
            cli->drone.inventory[i] += 1;
            add_to_write_list(cli, "ok\n");
            return;
        }
    }
    add_to_write_list(cli, "ko\n");
}
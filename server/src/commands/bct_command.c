/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the bct command
*/

#include <stdlib.h>
#include "server.h"

void bct_command(client_t *client, data_server_t *data, char **arg)
{
    map_t *cur = data->bottom_left;

    for (int i = 0; i < atoi(arg[1]); ++i) {
        for (int j = 0; j < atoi(arg[2]); ++j) {
            for (int h = 0; h < 7; ++h) {
                printf("%d - %d = cur->items[%d] : %d\n", i, j, h, cur->items[h]);
            }
            printf("----------------------\n");
            cur = cur->top;
        }
        cur = cur->right;
    }
}
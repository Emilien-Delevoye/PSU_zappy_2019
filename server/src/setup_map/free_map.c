/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

void free_team_names(data_server_t data)
{
    if (!data.team_names)
        return;
    for (int a = 0; data.team_names[a]; ++a) {
        printf("%s\n", data.team_names[a]);
        free(data.team_names[a]);
    }
    free(data.team_names);
}

void free_map(data_server_t data)
{
    map_t *left = data.bottom_left;
    map_t *cur;
    map_t *to_free;

    for (int a = 0; a < data.height; ++a) {
        if (data.width > 1)
            cur = left->right;
        for (int b = 1; b < data.width; ++b) {
            to_free = cur;
            cur = cur->right;
            free(to_free);
        }
        to_free = left;
        left = left->top;
        free(to_free);
    }
}
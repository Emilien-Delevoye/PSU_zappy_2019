/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "map/setup_map.h"
#include <stdlib.h>

map_t *create_node(void)
{
    map_t *new = malloc(sizeof(map_t));

    if (!new)
        return (NULL);
    new->right = NULL;
    new->left = NULL;
    new->bottom = NULL;
    new->top = NULL;
    return (new);
}

int setup_map(data_server_t *data)
{
    map_t *first = create_node();
    map_t *cur_start = first;
    map_t *cur;

    if (!first)
        return (84);
    data->top_left = first;
    for (int a = 1; a < data->height; ++a) {
        cur = cur_start;
        for (int b = 1; b < data->width; ++b) {
            cur->right = create_node();
            cur->right->left = cur;
            cur = cur->right;
        }
        cur_start->bottom = create_node();
        cur_start->bottom->top = cur_start;
        cur_start = cur_start->bottom;
    }
    return (0);
}
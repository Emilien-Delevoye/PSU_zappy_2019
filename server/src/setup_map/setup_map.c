/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "map/setup_map.h"
#include <stdlib.h>

static map_t *create_node(void)
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

static void read_to_create_links(data_server_t *data, map_t *first)
{
    if (data->width < 2)
        return;
    for (map_t *cur_1 = first->top; cur_1; cur_1 = cur_1->top) {
        (void)(NULL);
        first = first->top;
    }
}

int setup_map(data_server_t *data)
{
    map_t *cur = create_node();

    for (int a = 0; a < data->height; ++a) {
        if (a != 0) {
            cur->bottom = create_node();
            cur->bottom->top = cur;
            cur = cur->bottom;
        }
        for (int b = 1; b < data->width; ++b) {
            cur->right = create_node();
            cur->right->left = cur;
            cur = cur->right;
        }
        for (cur; cur->left; cur = cur->left);
    }
    read_to_create_links(data, cur);
    return (0);
}
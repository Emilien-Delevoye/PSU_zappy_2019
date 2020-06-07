/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "map/setup_map.h"
#include <stdio.h>

map_t *create_first_elem(map_t *cur, unsigned int a)
{
    cur->bottom = create_node(a, 0);
    if (!cur->bottom) {
        fputs("Not enough memory to create the map\n", stderr);
        return (NULL);
    }
    cur->bottom->top = cur;
    cur = cur->bottom;
    return (cur);
}

map_t *create_cur_elem(map_t *cur, unsigned int a, unsigned int b)
{
    cur->right = create_node(a, b);
    if (!cur->right) {
        fputs("Not enough memory to create the map\n", stderr);
        return (NULL);
    }
    cur->right->left = cur;
    cur = cur->right;
    return (cur);
}

int setup_map(data_server_t *data)
{
    map_t *cur = create_node(data->height - 1, 0);

    if (data->height <= 0 || data->width <= 0)
        return (84);
    for (int a = data->height - 1; a >= 0; --a) {
        if (a != data->height - 1) {
            cur = create_first_elem(cur, a);
            if (!cur)
                return (84);
        }
        for (int b = 1; b < data->width; ++b) {
            cur = create_cur_elem(cur, a, b);
            if (!cur)
                return (84);
        }
        for (; cur->left; cur = cur->left);
    }
    read_to_create_links(data, cur);
    return (0);
}
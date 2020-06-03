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

int setup_map(data_server_t *data __attribute__((unused)))
{
    return (0);
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

map_t *create_node(unsigned int x, unsigned int y)
{
    map_t *new = malloc(sizeof(map_t));

    if (!new)
        return (NULL);
    new->coord[0] = x;
    new->coord[1] = y;
    new->right = NULL;
    new->left = NULL;
    new->bottom = NULL;
    new->top = NULL;
    return (new);
}

static void create_links(map_t *top, map_t *bottom)
{
    while (top) {
        top->bottom = bottom;
        bottom->top = top;
        bottom = bottom->right;
        top = top->right;
    }
}

static void create_boarders(map_t *first)
{
    map_t *top_l = first;
    map_t *top_r;

    for (top_r = first; top_r->right; top_r = top_r->right);
    while (top_r) {
        top_r->right = top_l;
        top_l->left = top_r;
        top_r = top_r->bottom;
        top_l = top_l->bottom;
    }
    top_l = first;
    for (top_r = first; top_r->bottom; top_r = top_r->bottom);
    while (!top_l->top) {
        top_l->top = top_r;
        top_r->bottom = top_l;
        top_r = top_r->right;
        top_l = top_l->right;
    }
}

void read_to_create_links(data_server_t *data, map_t *first)
{
    if (data->width < 2)
        return;
    for (map_t *cur_1 = first->top; cur_1; cur_1 = cur_1->top) {
        create_links(cur_1, first);
        first = first->top;
    }
    create_boarders(first);
    for (; first->coord[0] != 0; first = first->top);
    for (; first->coord[1] != 0; first = first->left);
    data->top_left = first;
}
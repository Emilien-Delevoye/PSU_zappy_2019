/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#include "server.h"
#include "map/setup_map.h"
#include <stdlib.h>
#include <string.h>

map_t *create_node(unsigned int x, unsigned int y)
{
    map_t *new = malloc(sizeof(map_t));

    if (!new)
        return (NULL);
    memset(new, 0, sizeof(map_t));
    new->coord[0] = x;
    new->coord[1] = y;
    return (new);
}

static void create_links(map_t *top, map_t *bottom)
{
    while (top) {
        generate_stone_on_one_case(top);
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
        generate_stone_on_one_case(top_r);
        top_l->top = top_r;
        top_r->bottom = top_l;
        top_r = top_r->right;
        top_l = top_l->right;
    }
}

static void setup_link_1_width(map_t *cur)
{
    map_t *save_first = cur;
    map_t *save_second = cur;

    while (cur) {
        generate_stone_on_one_case(cur);
        save_second = cur;
        cur->right = cur;
        cur->left = cur;
        cur = cur->top;
    }
    save_second->top = save_first;
    save_first->bottom = save_second;
}

void read_to_create_links(data_server_t *data, map_t *first)
{
    if (data->params.width < 2) {
        setup_link_1_width(first);
    } else {
        for (map_t *cur_1 = first->top; cur_1; cur_1 = cur_1->top) {
            generate_stone_on_one_case(cur_1);
            create_links(cur_1, first);
            first = first->top;
        }
        create_boarders(first);
    }
    for (; first->coord[0] != 0; first = first->top);
    for (; first->coord[1] != 0; first = first->left);
    data->bottom_left = first;
}
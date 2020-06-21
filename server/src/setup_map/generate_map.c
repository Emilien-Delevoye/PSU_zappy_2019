/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** file that will contain function for generating everything on map
*/

#include <server.h>
#include <stdlib.h>

void generate_stone_on_one_case(map_t *map)
{
    for (int i = 0; i < rand() % 12 + 8; ++i)
        map->items[i] = rand() % 2;
}
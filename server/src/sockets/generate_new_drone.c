/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the generation of a new drone
*/

#include "server.h"
#include <stdlib.h>

drone_t initialise_new_drone(int previous_id)
{
    drone_t new = {0};

    new.lvl = 0;
    new.orientation = (rand() % 4 + 1);
    for (int i = 0; i < 7; ++i)
        new.inventory[i] = 0;
    new.id = previous_id + 1;
    return new;
}
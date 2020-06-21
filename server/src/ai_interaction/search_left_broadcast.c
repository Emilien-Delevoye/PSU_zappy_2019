/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** file for the broadcast command
*/

#include "server.h"
#include "commands/broadcast.h"
#include <math.h>

void search_vertical(client_t *client, char *str, int y)
{
    if (y == 0) {
        write_for_broadcast(client, str, 0);
    } else if (y > 0) {
        write_for_broadcast(client, str, 1);
    } else {
        write_for_broadcast(client, str, 5);
    }
}

void search_left_up(client_t *client, char *str, int x, int y)
{
    if (fabsf((float)y / (float)x) >= 0.33) {
        if (fabsf((float)y / (float)x) > 1 &&
        fabsf((float)x / (float)y) < 0.33)
            write_for_broadcast(client, str, 1);
        else
            write_for_broadcast(client, str, 2);
    } else {
        write_for_broadcast(client, str, 3);
    }
}

void search_left_down(client_t *client, char *str, int x, int y)
{
    if (fabsf((float)y / (float)x) >= 0.33) {
        if (fabsf((float)y / (float)x) > 1 &&
        fabsf((float)x / (float)y) < 0.33)
            write_for_broadcast(client, str, 5);
        else
            write_for_broadcast(client, str, 4);
    } else {
        write_for_broadcast(client, str, 3);
    }
}

void search_left(client_t *client, char *str, int x, int y)
{
    if (y > 0) {
        search_left_up(client, str, x, y);
    } else if (y == 0) {
        search_vertical(client, str, x);
    } else {
        search_left_down(client, str, x, y);
    }
}
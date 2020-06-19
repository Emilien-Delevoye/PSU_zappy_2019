/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** file for the broadcast command
*/

#ifndef ZAPPY_BROADCAST_H
#define ZAPPY_BROADCAST_H

#include "server.h"

void write_for_broadcast(client_t *client, char *text, int tile);
void search_right(client_t *client, char *str, int x, int y);
void search_left(client_t *client, char *str, int x, int y);
void search_vertical(client_t *client, char *str, int y);
void search_horizontal(client_t *client, char *str, int x);

#endif //ZAPPY_BROADCAST_H

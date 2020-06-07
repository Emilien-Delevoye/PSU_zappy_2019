/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#ifndef ZAPPY_SERVER_SETUP_MAP_H
#define ZAPPY_SERVER_SETUP_MAP_H

#include "server.h"

int setup_map(data_server_t *);
map_t *create_node(unsigned int, unsigned int);
void read_to_create_links(data_server_t *, map_t *);
void free_map(data_server_t);
void free_team_names(data_server_t);

#endif //ZAPPY_SERVER_SETUP_MAP_H

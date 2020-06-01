/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#ifndef ZAPPY_SERVER_SELECT_H
#define ZAPPY_SERVER_SELECT_H

#include "server.h"
#include <sys/select.h>

void setup_fdset(data_server_t *);
bool select_fd(data_server_t *);
void read_socket(data_server_t *);
void close_client(data_server_t *, client_t *);

#endif //ZAPPY_SERVER_SELECT_H

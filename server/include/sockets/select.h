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

#define READ_SIZE 2048

void setup_fdset(data_server_t *);
bool select_fd(data_server_t *);
void read_socket(data_server_t *);
void write_socket(data_server_t *);
void close_clients(data_server_t *);
void remove_a_client(data_server_t *, client_t *);
void extract_command(client_t *);
bool add_to_client(client_t *, char *);
void valid_client(data_server_t *, client_t *);

#endif //ZAPPY_SERVER_SELECT_H

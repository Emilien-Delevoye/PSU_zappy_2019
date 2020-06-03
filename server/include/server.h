/*
** EPITECH PROJECT, 2020
** server
** File description:
** Created by emilien
*/

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

#include <stdbool.h>
#include <sys/select.h>

typedef struct map_s {
    struct map_s *right;
    struct map_s *left;
    struct map_s *top;
    struct map_s *bottom;
} map_t;

typedef struct client_s {
    int fd;
    bool to_close;
    struct client_s *prev;
    struct client_s *next;
} client_t;

struct list_client_s {
    client_t *first;
    client_t *last;
};

typedef struct data_server_s {
    //Server settings
    int port;
    unsigned int width;
    unsigned int height;
    char **team_names;
    unsigned int team_nb;
    unsigned short client_nb;
    unsigned int freq;
    bool valid_params;
    //Server socket
    int fd;
    fd_set fdset_read;
    fd_set fdset_write;
    //Clients structures
    struct list_client_s l_cli;
    map_t *top_left;
} data_server_t;

#endif //SERVER_SERVER_H

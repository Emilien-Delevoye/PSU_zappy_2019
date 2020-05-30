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
} data_server_t;

#endif //SERVER_SERVER_H

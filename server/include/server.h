/*
** EPITECH PROJECT, 2020
** server
** File description:
** Created by emilien
*/

#ifndef SERVER_SERVER_H
#define SERVER_SERVER_H

typedef struct data_server_s {
    //Server settings
    int port;
    unsigned int width;
    unsigned int height;
    char **team_names;
    unsigned short client_nb;
    unsigned int freq;
    //Server socket
    int fd;
} data_server_t;

#endif //SERVER_SERVER_H

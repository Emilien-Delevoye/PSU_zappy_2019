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
#include <stdio.h>

typedef struct map_s {
    unsigned int coord[2];
    struct map_s *right;
    struct map_s *left;
    struct map_s *top;
    struct map_s *bottom;
} map_t;

typedef struct write_cli_s {
    char *to_write;
    struct write_cli_s *next;
} write_cli_t;

typedef struct command_queue_s {
    char *command;
    struct command_queue_s *next;
} command_queue_t;

typedef struct client_s {
    int fd;
    bool to_close;
    char *buffer;
    command_queue_t *cmd_queue;
    write_cli_t *list_msg;
    struct client_s *prev;
    struct client_s *next;
} client_t;

struct list_client_s {
    client_t *first;
    client_t *last;
};

typedef struct param_s {
    int port;
    int width;
    int height;
    char **team_names;
    unsigned int team_nb;
    unsigned short client_nb;
    unsigned int freq;
    bool valid_params;
} param_t;

typedef struct data_server_s {
    //Server settings
    param_t params;
    //Server socket
    int fd;
    fd_set fdset_read;
    fd_set fdset_write;
    //Clients structures
    struct list_client_s l_cli;
    map_t *bottom_left;
    //Timer structures
    struct timeval tv;
    struct tm *tm;
    long int timer;
    int sec;
} data_server_t;

#endif //SERVER_SERVER_H

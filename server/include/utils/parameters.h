/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** Created by emilien
*/

#ifndef ZAPPY_SERVER_PARAMETERS_H
#define ZAPPY_SERVER_PARAMETERS_H

#include <stdbool.h>

typedef struct data_server_s data_server_t;

data_server_t get_parameters(int, char **);

bool p_flag(char **, data_server_t *);
bool x_flag(char **, data_server_t *);
bool y_flag(char **, data_server_t *);
bool n_flag(char **, data_server_t *);
bool c_flag(char **, data_server_t *);
bool f_flag(char **, data_server_t *);

#endif //ZAPPY_SERVER_PARAMETERS_H

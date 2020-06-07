/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the command msz
*/

#include "utils/write_list.h"
#include "sockets/select.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void msz_command(client_t *cli, data_server_t *data)
{
    char x[11];
    char y[11];
    char *str;

    memset(x, 0, sizeof(x));
    memset(y, 0, sizeof(y));
    sprintf(x, "%d", data->height);
    sprintf(y, "%d", data->width);
    str = malloc(sizeof(char) * 7 + strlen(x) + strlen(y));
    if (str == NULL)
        remove_a_client(data, cli);
    memset(str, 0, sizeof(char) * 7 + strlen(x) + strlen(y));
    strcat(str, "msz ");
    strcat(str, x);
    strcat(str, " ");
    strcat(str, y);
    strcat(str, "\n");
    add_to_write_list(cli, str);
}
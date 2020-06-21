/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the ppo command
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

void tna_command(client_t *cli, data_server_t *data,
    __attribute__((unused))char **arg)
{
    char *str;
    size_t size = 5;
    int i = 0;

    for (; data->params.team_names[i]; ++i)
        size += strlen(data->params.team_names[i]);
    str = malloc(sizeof(char) * size + i);
    if (str == NULL) {
        remove_a_client(data, cli);
        return;
    }
    memset(str, 0, size + i);
    strcpy(str, "tna");
    for (i = 0; data->params.team_names[i]; ++i) {
        strcat(str, " ");
        strcat(str, data->params.team_names[i]);
    }
    strcat(str, "\n");
    add_to_write_list(cli, str);
    free(str);
}
/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** file for the broadcast command
*/

#include "server.h"
#include <string.h>

void write_for_broadcast(client_t *client, char *text, int tile)
{
    char str[13 + strlen(text)];

    (void)client;
    memset(str, 0, sizeof(str));
    sprintf(str, "message %d, %s\n", tile, text);
}

void exception_handlings(data_server_t *data, client_t *client,
    unsigned int x, unsigned int y)
{
    (void)data;
    (void)client;
    if (x == 0) {
        if (y == 0) {

        }
    }
}

unsigned int get_fastest_way(data_server_t *data, client_t *tmp, int value)
{
    unsigned int x = data->cli_work->cli->drone.tile->coord[value] -
        tmp->drone.tile->coord[value];

    if (x > (unsigned)data->params.width / 2) {
        if (data->cli_work->cli->drone.tile->coord[value] <
            (unsigned)(data->params.width / 2))
            x = data->cli_work->cli->drone.tile->coord[value] +
                data->params.width - tmp->drone.tile->coord[value] - 1;
        else
            x = tmp->drone.tile->coord[value] + data->params.width -
                data->cli_work->cli->drone.tile->coord[value] - 1;
    }
    return x;
}

void broadcast(data_server_t *data)
{
    unsigned int x;
    unsigned int y;

    printf("dans broadcast\n");
    for (client_t *tmp = data->l_connected.first; tmp->next; tmp = tmp->next) {
        x = get_fastest_way(data, tmp, 0);
        y = get_fastest_way(data, tmp, 1);
        printf("%d", x);
        printf("%d", y);
//        exception_handlings(data, tmp, x, y);
    }
}
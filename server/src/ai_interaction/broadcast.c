/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** file for the broadcast command
*/

#include "server.h"
#include "commands/broadcast.h"
#include "commands/commands.h"
#include <string.h>
#include <stdlib.h>

void write_for_broadcast(client_t *client, char *text, int tile)
{
    char str[13 + strlen(text)];
    int tile_tmp;

    if (tile != 0)
        tile_tmp = tile + (client->drone.orientation - 1) * 2;
    else
        tile_tmp = tile;
    if (tile_tmp > 8)
        tile_tmp -= 8;
    memset(str, 0, sizeof(str));
    sprintf(str, "message %d, %s\n", tile_tmp, text);
    add_to_write_list(client, str);
}

char *get_broadcast_arg(char *str)
{
    char *tmp = malloc(sizeof(char) * strlen(str) - 9);

    memset(tmp, 0, sizeof(char) * strlen(str) - 9);
    for (int i = 9; str[i]; ++i) {
        if (i != 9)
            tmp[i - 10] = str[i];
    }
    return tmp;
}

void search_tile(data_server_t *data, client_t *client, int x, int y)
{
    char *str = get_broadcast_arg(data->cli_work->cmd_str);

    if (x > 0) {
        search_right(client, str, x, y);
    } else if (x == 0) {
        search_horizontal(client, str, y);
    } else {
        search_left(client, str, x, y);
    }
    free(str);
}

int get_fastest_way(data_server_t *data, client_t *tmp, int i)
{
    int x = (int)(data->cli_work->cli->drone.tile->coord[i] -
        tmp->drone.tile->coord[i]);

    if (abs(x) > data->params.width / 2) {
        if (data->cli_work->cli->drone.tile->coord[i] <
        (unsigned)data->params.width / 2)
            x = (int)(data->cli_work->cli->drone.tile->coord[i] +
                data->params.width - tmp->drone.tile->coord[i]) * -1;
        else
            x = (int)(tmp->drone.tile->coord[i] + data->params.width -
                data->cli_work->cli->drone.tile->coord[i]) * -1;
    }
    return x;
}

void broadcast(data_server_t *data)
{
    int x;
    int y;

    pbc_command(data->l_connected.first, data);
    for (client_t *tmp = data->l_connected.first; tmp; tmp = tmp->next) {
        if (tmp != data->cli_work->cli) {
            x = get_fastest_way(data, tmp, 0);
            y = get_fastest_way(data, tmp, 1);
            search_tile(data, tmp, x, y);
        }
    }
    add_to_write_list(data->cli_work->cli, "ok\n");
}
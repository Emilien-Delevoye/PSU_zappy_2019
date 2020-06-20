/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include "commands/commands.h"
#include <stdlib.h>

static tile_players_t *get_new_tile(client_t *cli)
{
    tile_players_t *new = malloc(sizeof(tile_players_t));

    if (!new)
        return (NULL);
    new->next = NULL;
    new->cli = cli;
    return (new);
}

static void add_to_tile(map_t *tile, client_t *cli)
{
    tile_players_t *new = get_new_tile(cli);
    tile_players_t *cur = tile->list_players;

    if (tile->list_players == NULL) {
        tile->list_players = new;
    } else {
        while (cur->next)
            cur = cur->next;
        cur->next = new;
    }
    cli->drone.tile = tile;
    cli->drone.orientation = (rand() % 4) + 1;
}

void spawn_player(data_server_t *data, client_t *cli)
{
    unsigned int coord[2];
    map_t *obj_tile = data->bottom_left;

    if (!obj_tile)
        return;
    if (!data->params.width || !data->params.height) {
        coord[WIDTH] = 0;
        coord[HEIGHT] = 0;
    } else {
        coord[WIDTH] = rand() % data->params.width;
        coord[HEIGHT] = rand() % data->params.height;
    }
    while (obj_tile->coord[WIDTH] != coord[WIDTH])
        obj_tile = obj_tile->right;
    while (obj_tile->coord[HEIGHT] != coord[HEIGHT])
        obj_tile = obj_tile->top;
    add_to_tile(obj_tile, cli);
    pnw_command(cli, data);
}
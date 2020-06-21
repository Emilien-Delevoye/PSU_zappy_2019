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

void spawn_player_end(data_server_t *data, client_t *cli, map_t *obj_tile,
    const unsigned int *coord)
{
    cli->drone.inventory[FOOD] = 9;
    while (obj_tile->coord[WIDTH] != coord[WIDTH])
        obj_tile = obj_tile->right;
    while (obj_tile->coord[HEIGHT] != coord[HEIGHT])
        obj_tile = obj_tile->top;
    add_to_tile(obj_tile, cli);
    pnw_command(cli, data);
    pin_command(cli, data);
}

void spawn_player(data_server_t *data, client_t *cli, const int c[2])
{
    map_t *obj_tile = data->bottom_left;
    unsigned int coord[2];

    if (!obj_tile)
        return;
    if (c[0] != -1 && c[1] != -1) {
        coord[HEIGHT] = (c[0] < 0) ? 0 : c[0];
        coord[WIDTH] = (c[1] < 0) ? 0 : c[1];
    } else {
        coord[WIDTH] = rand() % data->params.width;
        coord[HEIGHT] = rand() % data->params.height;
    }
    spawn_player_end(data, cli, obj_tile, coord);
}
/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "commands/commands.h"
#include "server.h"

map_t *get_dest_tile(drone_t drone)
{
    switch (drone.orientation) {
        case NORTH:
            return (drone.tile->top);
        case EAST:
            return (drone.tile->right);
        case SOUTH:
            return (drone.tile->bottom);
        case WEST:
            return (drone.tile->left);
        default:
            return (NULL);
    }
}

void move_to_other_tile(map_t *dest, tile_players_t *cu_l)
{
    cu_l->next = NULL;
    if (!dest->list_players) {
        dest->list_players = cu_l;
        return;
    }
    for (tile_players_t *n = dest->list_players; n; n = n->next) {
        if (!n->next) {
            n->next = cu_l;
            return;
        }
    }
}

void forward(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;
    map_t *cur = data->cli_work->cli->drone.tile;
    map_t *dest = get_dest_tile(data->cli_work->cli->drone);
    tile_players_t *prev = NULL;
    if (!dest)
        return;
    for (tile_players_t *cu_l = cur->list_players; cu_l; cu_l = cu_l->next) {
        if (cu_l->cli != cli) {
            prev = cu_l;
            continue;
        }
        if (!prev)
            cur->list_players = cu_l->next;
        else
            prev->next = cu_l->next;
        move_to_other_tile(dest, cu_l);
        cli->drone.tile = dest;
    }
    add_to_write_list(cli, "ok\n");
    ppo_command(cli, data);
}

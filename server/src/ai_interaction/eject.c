/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "commands/commands.h"
#include "server.h"

void change_tile_eject(map_t *cur, client_t *cli, map_t *dest)
{
    tile_players_t *prev = NULL;

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
}

void move_for_eject(client_t *cli, int orientation)
{
    char str[20] = {0};
    int ref[4] = {3, 4, 1, 2};
    int tile;

    if (orientation == 1 || orientation == 3)
        tile = 1 + (ref[cli->drone.orientation - 1] - 1) * 2 +
            (orientation - 1) * 2;
    else
        tile = 1 + (cli->drone.orientation - 1) * 2 + (orientation - 1) * 2;
    if (tile > 8)
        tile -= 8;
    sprintf(str, "eject %d\n", tile);
    change_tile_eject(cli->drone.tile, cli,
        get_direction1(cli->drone.tile, orientation));
    add_to_write_list(cli, str);
}

void eject(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;
    int counter = 0;

    for (tile_players_t *tmp =
        cli->drone.tile->list_players; tmp; tmp = tmp->next) {
        if (tmp->cli != cli) {
            move_for_eject(tmp->cli, cli->drone.orientation);
            ppo_command(tmp->cli, data);
            ++counter;
        }
    }
    if (counter == 0)
        add_to_write_list(cli, "ko\n");
}
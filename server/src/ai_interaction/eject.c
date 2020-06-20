/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void move_for_eject(client_t *cli, int orientation)
{
    char str[20] = {0};


}

void eject(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;

    for (tile_players_t *tmp =
        cli->drone.tile->list_players; tmp; tmp = tmp->next) {
        if (tmp->cli != cli) {
            move_for_eject(tmp->cli, cli->drone.orientation);
        }
    }
    (void)cli;
}
/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

const unsigned int condi[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4 ,1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

void incantation_ok(client_t *cli, int choice)
{
    char str[50] = {0};

    if (choice == 0) {
        for (tile_players_t *tmp =
            cli->drone.tile->list_players; tmp; tmp = tmp->next) {
            tmp->cli->drone.lvl += 1;
            sprintf(str, "Current level: %d\n", tmp->cli->drone.lvl);
            add_to_write_list(tmp->cli, str);
        }
    } else {
        for (tile_players_t *tmp =
            cli->drone.tile->list_players; tmp; tmp = tmp->next)
            add_to_write_list(tmp->cli, "Elevation underway\n");
    }
}

void incantation_after(data_server_t *data)
{
    unsigned int nb_player = 0;
    client_t *cli = data->cli_work->cli;

    for (tile_players_t *tmp =
        cli->drone.tile->list_players; tmp; tmp = tmp->next) {
        if (cli->drone.lvl == tmp->cli->drone.lvl)
            ++nb_player;
    }
    if (condi[cli->drone.lvl - 1][0] == nb_player &&
    condi[cli->drone.lvl - 1][1] == cli->drone.tile->items[LINEMATE] &&
    condi[cli->drone.lvl - 1][2] == cli->drone.tile->items[DERAUMERE] &&
    condi[cli->drone.lvl - 1][3] == cli->drone.tile->items[SIBUR] &&
    condi[cli->drone.lvl - 1][4] == cli->drone.tile->items[MENDIANE] &&
    condi[cli->drone.lvl - 1][5] == cli->drone.tile->items[PHIRAS] &&
    condi[cli->drone.lvl - 1][6] == cli->drone.tile->items[THYSTAME]) {
        incantation_ok(cli, 0);
    } else
        add_to_write_list(cli, "ko\n");
}

void incantation_before(client_t *cli)
{
    unsigned int nb_player = 0;

    for (tile_players_t *tmp =
        cli->drone.tile->list_players; tmp; tmp = tmp->next) {
        if (cli->drone.lvl == tmp->cli->drone.lvl)
            ++nb_player;
    }
    if (condi[cli->drone.lvl - 1][0] == nb_player &&
    condi[cli->drone.lvl - 1][1] == cli->drone.tile->items[LINEMATE] &&
    condi[cli->drone.lvl - 1][2] == cli->drone.tile->items[DERAUMERE] &&
    condi[cli->drone.lvl - 1][3] == cli->drone.tile->items[SIBUR] &&
    condi[cli->drone.lvl - 1][4] == cli->drone.tile->items[MENDIANE] &&
    condi[cli->drone.lvl - 1][5] == cli->drone.tile->items[PHIRAS] &&
    condi[cli->drone.lvl - 1][6] == cli->drone.tile->items[THYSTAME]) {
        incantation_ok(cli, 1);
    } else
        add_to_write_list(cli, "ko\n");
}
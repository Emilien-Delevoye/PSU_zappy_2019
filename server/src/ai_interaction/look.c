/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

const int len_str = 8192;

const char tab_inventory[7][10] = {"food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame"};

static void read_tile(char str[len_str], map_t *tile)
{
    char tmp[15];

    for (tile_players_t *cur = tile->list_players; cur; cur = cur->next)
        strcat(str, (str[1] ? " player" : "player"));
    for (int a = 0; a < 7; ++a) {
        for (unsigned int b = 0; b < tile->items[a]; ++b) {
            sprintf(tmp, (str[1] ? " %s" : "%s"), tab_inventory[a]);
            strcat(str, tmp);
        }
    }
}

static void str_to_list_write(char str[len_str], client_t *cli)
{
    strcat(str, "]\n");
    add_to_write_list(cli, str);
}

static void map_move(map_t *start, char *str, int a, int orientation)
{
    map_t *current = start;

    for (int b = 0; b < a; ++b)
        current = get_direction1(current, orientation);
    for (int b = a; b > 0; --b)
        current = get_direction2(current, orientation);
    for (int b = (a * 2 + 1); b > 0; --b) {
        if (a != 0)
            strcat(str, ",");
        read_tile(str, current);
        current = get_direction3(current, orientation);
    }
}

void look(data_server_t *data)
{
    client_t *cli = data->cli_work->cli;
    map_t *start = cli->drone.tile;
    char str[len_str];

    memset(str, 0, len_str);
    str[0] = '[';
    for (int a = 0; a <= cli->drone.lvl; ++a) {
        if (strlen(str) > (len_str - 96))
            break;
        map_move(start, str, a, cli->drone.orientation);
    }
    str_to_list_write(str, cli);
}
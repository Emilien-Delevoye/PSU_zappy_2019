/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void inventory(data_server_t *data)
{
    char str[500] = {0};
    drone_t cur = data->cli_work->cli->drone;

    sprintf(str, "[linemate %d, sibur %d, deraumere %d, mendiane %d,"
        "phiras %d, thystame %d, food %d\n", cur.inventory[LINEMATE],
        cur.inventory[SIBUR], cur.inventory[DERAUMERE],
        cur.inventory[MENDIANE], cur.inventory[PHIRAS],
        cur.inventory[THYSTAME], cur.inventory[FOOD]);
    add_to_write_list(data->cli_work->cli, str);
}
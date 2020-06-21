/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include "lib.h"
#include "commands/commands.h"
#include <stdlib.h>
#include <string.h>

char *get_set_arg(char *str)
{
    char *tmp = malloc(sizeof(char) * strlen(str) - 3);

    memset(tmp, 0, sizeof(char) * strlen(str) - 3);
    for (int i = 3; str[i]; ++i) {
        if (i != 3)
            tmp[i - 4] = str[i];
    }
    return tmp;
}

void set(data_server_t *data)
{
    char arg[30] = {0};
    client_t *cli = data->cli_work->cli;
    char *str = get_set_arg(data->cli_work->cmd_str);
    map_t *cur = get_good_tile(cli->drone.tile, data);
    char *equi[7] = {"food", "linemate", "deraumere", "sibur", "mendiane",
        "phiras", "thystame"};

    for (int i = 0; i < 7; ++i) {
        if (strcmp(equi[i], str) == 0 && cli->drone.inventory[i] > 0) {
            cur->items[i] += 1;
            cli->drone.inventory[i] -= 1;
            add_to_write_list(cli, "ok\n");
            sprintf(arg, "bct %d %d", cur->coord[0], cur->coord[1]);
            bct_command(cli, data, my_str_to_word_array(arg));
            pin_command(cli, data);
            return;
        }
    }
    add_to_write_list(cli, "ko\n");
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the ppo command
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

void ppo_command(data_server_t *data, client_t *cli,
    __attribute__((unused))char **arg)
{
    int n = cli->drone->id;
    unsigned int x = cli->map->coord[0];
    unsigned int y = cli->map->coord[1];
    unsigned int o = cli->drone->orientation;
    char *str = malloc(sizeof(char) * 53);

    if (str == NULL) {
        remove_a_client(data, cli);
        return;
    }
    memset(str, 0, 53);
    sprintf(str, "ppo %d %d %d %d\n", n, x, y, o);
    add_to_write_list(cli, str);
}
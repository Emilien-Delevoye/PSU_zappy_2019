/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>

void add_client_from_egg(data_server_t *data, client_t *cli, list_egg_t *hatch,
    list_egg_t *prev)
{
    char str[66] = {0};
    int c[2] = {0, 0};

    cli->drone.id = hatch->egg_id;
    if (!prev)
        data->hatch_eggs = hatch->next;
    else
        prev->next = hatch->next;
    c[0] = hatch->coord[0];
    c[1] = hatch->coord[1];
    free(hatch);
    sprintf(str, "%d\n%d %d\n", (data->params.r_cli[cli->team_id] +
        data->params.egg_r_c[cli->team_id]),
        data->params.width, data->params.height);
    add_to_write_list(cli, str);
    new_client_to_ww_list(cli, &data->cli_wait);
    spawn_player(data, cli, c);
    calc_food_time(data, data->tv, cli);
}

void egg_to_player(data_server_t *data, client_t *cli)
{
    list_egg_t *prev = NULL;

    if (!data->params.egg_r_c[cli->team_id]) {
        add_to_write_list(cli, "ko\n");
        cli->to_close = true;
        return;
    }
    --data->params.egg_r_c[cli->team_id];
    for (list_egg_t *hatch = data->hatch_eggs; hatch; hatch = hatch->next) {
        if (hatch->team_id == cli->team_id)
            add_client_from_egg(data, cli, hatch, prev);
        prev = hatch;
    }
}
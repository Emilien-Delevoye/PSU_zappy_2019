/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <stdlib.h>
#include <string.h>

static void add_to_valid_list(data_server_t *data, client_t *cli)
{
    if (data->l_connected.first == NULL && data->l_connected.last == NULL) {
        data->l_connected.first = cli;
        data->l_connected.last = cli;
        cli->next = NULL;
        cli->prev = NULL;
    } else if (data->l_connected.first && data->l_connected.last) {
        data->l_connected.last->next = cli;
        cli->prev = data->l_connected.last;
        cli->next = NULL;
        data->l_connected.last = cli;
    }
}

static void remove_from_first_list(data_server_t *data, client_t *cli)
{
    if (cli->next == NULL && cli->prev == NULL) {
        data->l_waiting.first = NULL;
        data->l_waiting.last = NULL;
        return;
    } else if (cli->prev) {
        cli->prev->next = cli->next;
        data->l_waiting.last = cli->prev;
        cli->prev = NULL;
        cli->next = NULL;
    } else {
        cli->next->prev = cli->prev;
        data->l_waiting.first = cli->next;
        cli->prev = NULL;
        cli->next = NULL;
    }
}

void client_validation(data_server_t *data, client_t *cli, int team_id)
{
    char team_nb[20] = {0};

    if (cli->next != NULL && cli->prev != NULL) {
        cli->next->prev = cli->prev;
        cli->prev->next = cli->next;
    } else {
        remove_from_first_list(data, cli);
    }
    cli->team_id = (unsigned short)team_id;
    add_to_valid_list(data, cli);
    if (!data->params.r_cli)
        sprintf(team_nb, "0\n");
    else
        sprintf(team_nb, "%d\n", --data->params.r_cli[cli->team_id]);
    add_to_write_list(cli, team_nb);
    new_client_to_ww_list(cli, &data->cli_wait);
}

static void graphical_validation(data_server_t *data, client_t *cli)
{
    if (cli->next && cli->prev) {
        cli->next->prev = cli->prev;
        cli->prev->next = cli->next;
    } else {
        remove_from_first_list(data, cli);
    }
    data->l_graphical.first = cli;
    data->l_graphical.last = cli;
    cli->next = NULL;
    cli->prev = NULL;
}

void valid_client(data_server_t *d, client_t *cli)
{
    char *cmd;
    command_queue_t *to_delete;

    if (!cli->cmd_queue)
        return;
    cmd = cli->cmd_queue->command;
    to_delete = cli->cmd_queue;
    if (!cmd) {
        cli->cmd_queue = cli->cmd_queue->next;
        free(to_delete);
    }
    for (int a = 0; d->params.team_names && d->params.team_names[a]; ++a) {
        if (strcmp(d->params.team_names[a], cli->cmd_queue->command) == 0)
            client_validation(d, cli, a);
        if (strcmp(cli->cmd_queue->command, "GRAPHICAL42") == 0) {
            graphical_validation(d, cli);
            break;
        }
    }
    remove_first_cmd_queue(cli);
}

/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the command array
*/

#include "utils/write_list.h"
#include "commands/commands.h"
#include <string.h>
#include <stdio.h>

static void (*array[1])(client_t *, data_server_t *) = {msz_command};

void call_command_function(data_server_t *data, client_t *cli)
{
    const char *corresponding[1] = {"msz"};

    for (int i = 0; i < 1; ++i) {
        if (strcmp(cli->cmd_queue->command, corresponding[i]) == 0) {
            array[i](cli, data);
            return;
        }
    }
}

void loop_tmp_check_every_buffer(data_server_t *data)
{
    client_t *current = data->l_connected.first;

    while (current) {
        if (current->cmd_queue && current->cmd_queue->command) {
            printf("--%s--\n", current->cmd_queue->command);
            call_command_function(data, current);
        }
        current = current->next;
    }
}
/*
** EPITECH PROJECT, 2020
** zappy_server
** File description:
** File for the command array
*/

#include "utils/write_list.h"
#include "commands/commands.h"
#include "lib.h"
#include <string.h>
#include <stdio.h>

static void (*array[2])(client_t *, data_server_t *, char **) = {msz_command, bct_command};

void call_command_function(data_server_t *data, client_t *cli, char **arg)
{
    const char *corresponding[2] = {"msz", "bct"};

    for (int i = 0; i < 2; ++i) {
        if (strcmp(arg[0], corresponding[i]) == 0) {
            array[i](cli, data, arg);
            return;
        }
    }
}

void loop_tmp_check_every_buffer(data_server_t *data)
{
    client_t *current = data->l_connected.first;
    /*    map_t *cur = data->bottom_left;

        for (int i = 0; i < data->params.width; ++i) {
            for (int j = 0; j < data->params.height; ++j) {
                for (int h = 0; h < 7; ++h) {
                    printf("%d - %d = cur->items[%d] : %d\n", i, j, h, cur->items[h]);
                }
                printf("----------------------\n");
                cur = cur->top;
            }
            cur = cur->right;
        }*/
    while (current) {
        if (current->cmd_queue && current->cmd_queue->command) {
            printf("--%s--\n", current->cmd_queue->command);
            call_command_function(data, current, my_str_to_word_array(current->cmd_queue->command));
        }
        current = current->next;
    }
}
/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"
#include <string.h>

const struct cmd_ai_s cmd[] = {
    {"Forward", 7},
    {"Right", 7},
    {"Left", 7},
    {"Look", 7},
    {"Inventory", 1},
    {"Broadcast", 7},
    {"Connect_nbr", 0},
    {"Fork", 42},
    {"Eject", 7},
    {"Take", 7},
    {"Set", 7},
    {"Incantation", 300},
    {NULL, -1}
};

void read_new_cmd(data_server_t *data, client_t *cl, struct timeval cu_time)
{
    bool valid_cmd = false;
    short cmd_nb;

    for (short a = 0; cmd[a].c; ++a) {
        if (strncmp(cmd[a].c, cl->cmd_queue->command, strlen(cmd[a].c)) == 0) {
            valid_cmd = true;
            cmd_nb = a;
            if (cmd_nb == 11)
                incantation_before(data, cl);
            break;
        }
    }
    if (!valid_cmd)
        add_to_write_list(cl, "ko\n");
    else
        move_wait_to_work_list(data, cl, cu_time, cmd_nb);
    remove_first_cmd_queue(cl);
}
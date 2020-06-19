/*
** EPITECH PROJECT, 2020
** zappy
** File description:
** Created by emilien
*/

#include "server.h"

void do_action(data_server_t *data __attribute__((unused)))
{

}

void move_to_wait_list(data_server_t *data)
{
    list_actions_t *save = data->cli_work;

    data->cli_work = data->cli_work->next;
    save->next = data->cli_wait;
    data->cli_wait = save;
}